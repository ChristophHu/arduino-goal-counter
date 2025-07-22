#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

WebServer server(80);
Preferences preferences;

//const char* ssid = "nxt";
//const char* password = "06215256444917228020";

String ssid, password;

#define TOR_SENSOR_PIN_A 5  // erster Sensor
#define TOR_SENSOR_PIN_B 6  // zweiter Sensor

int toreA = 0;
int toreB = 0;
bool stateA = false;
bool stateB = false;

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

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Torzähler</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 50px; }
    #counter { font-size: 48px; color: darkgreen; }
  </style>
</head>
<body>
  <h1>Torzähler</h1>
  <div>Aktuelle Tore:</div>
  <div id="counter">0</div>
  
  <button onclick="resetScore()">Zurücksetzen</button>
  <script>
    async function updateScore() {
      const res = await fetch("/status");
      const data = await res.json();
      document.getElementById("counter").textContent = data.scoreA + ":" + data.scoreB;
    }
    async function resetScore() {
      await fetch("/goalreset");
      updateScore();
    }
    setInterval(updateScore, 5000);
    updateScore();
  </script>
</body>
</html>
)rawliteral";

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

  // Sensor vorbereiten
  //pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(TOR_SENSOR_PIN_A, INPUT);
  pinMode(TOR_SENSOR_PIN_B, INPUT);

  // Webseite ausliefern
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  // Zähler-API
  server.on("/status", []() {
    String json = "{\"scoreA\":" + String(toreA) + ", \"scoreB\":" + String(toreB) + "}";
    server.send(200, "application/json", json);
  });

  // goalreset
  server.on("/goalreset", []() {
    toreA = 0;
    toreB = 0;
    server.send(200, "application/json", "{\"goalreset\":true}");
  });

  // wifireset
  server.on("/reset", []() {
    preferences.begin("wifi", false);
    preferences.clear();   // alle Werte löschen
    preferences.end();
    server.send(200, "text/html", "<h1>WiFi-Daten gelöscht. Neustart...</h1>");
    delay(2000);
    ESP.restart();
  });

  //server.begin();
}

void loop() {
  server.handleClient(); // wichtig für WebServer

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
