#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <DNSServer.h>
#include <time.h>

#include "ap_html.h"
#include "dashboard_html.h"

const byte DNS_PORT = 53;
DNSServer dnsServer;

WebServer server(80);
Preferences preferences;

String ssid, password;

// pins
#define TOR_SENSOR_PIN_A 5  // erster Sensor
#define TOR_SENSOR_PIN_B 6  // zweiter Sensor

// counter
int toreA = 0;
int toreB = 0;
bool stateA = false;
bool stateB = false;

// playtime
unsigned long starttimeMillis = 0;
#define MY_TZ "CET-1CEST,M3.5.0,M10.5.0/3"

// WiFi-Konfigurationsseite (nur wenn keine Daten vorhanden)
void handleRoot() {
  preferences.begin("wifi", true);
  String savedSSID = preferences.getString("ssid", "");
  preferences.end();

  IPAddress IP = WiFi.softAPIP();
  String ip = IP.toString();
  String mac = WiFi.softAPmacAddress();

  String ap_html;
  ap_html += AP_HTML_HEAD;
  ap_html += savedSSID;
  ap_html += AP_HTML_SCRIPT;
  
  ap_html.replace("{{IP}}", ip);  // falls du ein Platzhalter-Template nutzt
  ap_html.replace("{{MAC}}", mac);  // falls du ein Platzhalter-Template nutzt

  server.send(200, "text/html", ap_html);
}

// Speichert SSID/PW und startet ESP neu
void handleSave() {
  ssid = server.arg("ssid");
  password = server.arg("pass");

  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("pass", password);
  preferences.end();

  String page = "<h1>Gespeichert. Neustart...</h1>";
  server.send(200, "text/html", page);
  delay(2000);
  ESP.restart();
}

void startAPMode() {
  // ip-configuration
  IPAddress localIP(192, 168, 4, 1);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(localIP, gateway, subnet);
  String mac = WiFi.macAddress();
  
  // DNS-Server
  dnsServer.start(DNS_PORT, "*", localIP);  // <- DNS fängt alle Domains ab
  
  // ap-mode
  Serial.println("🌐 Starte Access Point...");
  WiFi.softAP("ESP32_Config", "12345678");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP-Adresse: ");
  Serial.println(IP);

  // handle routes
  server.on("/", handleRoot);
  
  server.begin();
  Serial.println("🛜 Access Point läuft");

  server.on("/save", handleSave);
  server.on("/generate_204", []() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });
  server.on("/hotspot-detect.html", []() {
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  });
  server.onNotFound([]() {
    server.send(404, "text/html", "<h1>Seite konnte nicht gefunden werden...</h1>");
  });
}

bool connectToWiFi() {
  preferences.begin("wifi", true);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("pass", "");
  preferences.end();

  if (ssid == "" || password == "") return false;

  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Verbinde mit WLAN");

  for (int i = 0; i < 20; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n✅ Verbunden!");
      Serial.print("🌐 IP: ");
      Serial.println(WiFi.localIP());
      return true;
    }
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n❌ Verbindung fehlgeschlagen");
  return false;
}

void setup() {
  Serial.begin(115200);
  starttimeMillis = millis();

  if (!connectToWiFi()) {
    Serial.println("⚙️ Starte Konfigurationsmodus...");
    startAPMode();
  } else {
    // get time
    setupTime();
    //server.on("/", []() {
    //  server.send(200, "text/html", getDashboardPage());
    //});
    server.on("/", []() {
      String dashboard_html = DASHBOARD_HTML;
      server.send(200, "text/html", dashboard_html);
    });
    server.begin();
    Serial.println("🚀 Webserver läuft");
  }

  // Zähler-API
  server.on("/status", []() {
    String json = "{\"scoreA\":" + String(toreA) + 
                  ", \"scoreB\":" + String(toreB) + "}";
    server.send(200, "application/json", json);
  });
  server.on("/starttime", []() {
    String datetime = getDateTime();
    String json = "{\"starttime\":" + String(datetime) + "}";
    server.send(200, "application/json", json);
  });
  server.on("/unixtime", []() {
    time_t now;
    time(&now);
    server.send(200, "text/plain", String(now));
  });

  // goalreset
  server.on("/goalreset", []() {
    toreA = 0;
    toreB = 0;
    starttimeMillis = millis();
    server.send(200, "application/json", "{\"goalreset\":true}");
  });
  
  server.on("/reset", []() {
    preferences.begin("wifi", false);
    preferences.clear();   // alle Werte löschen
    preferences.end();
    server.send(200, "text/html", "<h1>WiFi-Daten gelöscht. Neustart...</h1>");
    delay(2000);
    ESP.restart();
  });

  server.on("/wifis", []() {
    int n = WiFi.scanNetworks();
    String json = "[";
    for (int i = 0; i < n; ++i) {
      if (i > 0) json += ",";
      json += "\"" + WiFi.SSID(i) + "\"";
    }
    json += "]";
    server.send(200, "application/json", json);
  });
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  bool erkanntA = digitalRead(TOR_SENSOR_PIN_A) == LOW;
  bool erkanntB = digitalRead(TOR_SENSOR_PIN_B) == LOW;

  if (erkanntA && !stateA) {
    toreA++;
    Serial.print("Tor erkannt! Tore: ");
    Serial.println(toreA);
    delay(2000);  // Entprellung
  }
   if (erkanntB && !stateB) {
    toreB++;
    Serial.print("Gegentor erkannt! Tore: ");
    Serial.println(toreB);
    delay(2000);  // Entprellung
  }

  stateA = erkanntA;
  stateB = erkanntB;
}

void setupTime() {
  configTzTime(MY_TZ, "pool.ntp.org", "time.nist.gov");
}

String getDateTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "NTP-Fehler";

  char buffer[32];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
  return String(buffer);
}