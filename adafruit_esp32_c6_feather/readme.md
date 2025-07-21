## Adafruit Feather ESP32-C6


![Adafruit Feather ESP32-C6](https://cdn-learn.adafruit.com/assets/assets/000/131/997/original/adafruit_products_Artboard_1-100.jpg?1724360908)
The Adafruit Feather ESP32-C6 is a compact and versatile development board featuring the ESP32-C6 chip, which includes Wi-Fi and Bluetooth capabilities. This board is designed for IoT applications, making it easy to connect to the internet and communicate with other devices wirelessly.

### Features
- **ESP32-C6 Chip**: Dual-core processor with Wi-Fi and Bluetooth support.
- **Compact Design**: Small form factor suitable for portable projects.
- **Feather-Compatible**: Fits into the Feather ecosystem, allowing for easy expansion with FeatherWings and accessories.
- **USB-C Connector**: For power and data transfer.
- **Battery Charging**: Built-in battery management for LiPo batteries.

### WLAN
```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "***";
const char* password = "***";

WebServer server(80); // HTTP-Port 80

void handleRoot() {
  server.send(200, "text/html", "<h1>Hallo vom ESP32-C6!</h1>");
}

void setup() {
  Serial.begin(115200);
  Serial.print("Verbinde mit WLAN");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  pinMode(sensorPin, INPUT);

  Serial.println("\nWLAN verbunden!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // Route definieren
  server.begin();
  Serial.println("Webserver gestartet");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Neuer Client");
    while (client.connected()) {
      if (client.available()) {
        client.read(); // HTTP-Zeile verwerfen

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<h1>ESP32 läuft!</h1>");
        break;
      }
    }
    client.stop();
    Serial.println("Client getrennt");
  }
}
```

Wi-Fi Manager über Access Point
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

WebServer server(80);
Preferences preferences;

String ssid, password;

void handleRoot() {
  String page = "<h1>WiFi Konfiguration</h1>"
                "<form action='/save'>"
                "SSID: <input name='ssid'><br>"
                "Passwort: <input name='pass'><br><br>"
                "<input type='submit' value='Speichern'>"
                "</form>";
  server.send(200, "text/html", page);
}

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
  WiFi.softAP("ESP32_Config", "12345678");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP-Adresse: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.begin();
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
      Serial.print("IP: ");
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
  if (!connectToWiFi()) {
    Serial.println("🛜 Starte Access Point zur Konfiguration...");
    startAPMode();
  }
}

void loop() {
  server.handleClient();
}
```

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

WebServer server(80);
Preferences preferences;

String ssid, password;

// HTML-Seite mit IP-Anzeige
String getDashboardPage() {
  IPAddress ip = WiFi.localIP();
  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>"
                "<title>ESP32-C6 Dashboard</title></head><body>"
                "<h1>🌐 ESP32-C6 Dashboard</h1>"
                "<p><strong>IP-Adresse:</strong> " + ip.toString() + "</p>"
                "</body></html>";
  return html;
}

// WiFi-Konfigurationsseite (nur wenn keine Daten vorhanden)
void handleRoot() {
  String page = "<h1>WiFi Konfiguration</h1>"
                "<form action='/save'>"
                "SSID: <input name='ssid'><br>"
                "Passwort: <input name='pass'><br><br>"
                "<input type='submit' value='Speichern'>"
                "</form>";
  server.send(200, "text/html", page);
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
  WiFi.softAP("ESP32_Config", "12345678");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP-Adresse: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.begin();
  Serial.println("🛜 Access Point läuft");
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

  // clear wifi
  preferences.begin("wifi", false);
  preferences.clear();  // alles unter "wifi" löschen
  preferences.end();
  Serial.println("✅ WLAN-Daten geloescht");

  // set AP
  if (!connectToWiFi()) {
    Serial.println("⚙️ Starte Konfigurationsmodus...");
    startAPMode();
  } else {
    server.on("/", []() {
      server.send(200, "text/html", getDashboardPage());
    });
    server.begin();
    Serial.println("🚀 Webserver läuft");
  }

  server.on("/reset", []() {
    preferences.begin("wifi", false);
    preferences.clear();   // alle Werte löschen
    preferences.end();
    server.send(200, "text/html", "<h1>WiFi-Daten gelöscht. Neustart...</h1>");
    delay(2000);
    ESP.restart();
  });
}

void loop() {
  server.handleClient();
}
```