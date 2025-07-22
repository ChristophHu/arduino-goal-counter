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

### WLAN Konfiguration mit Webserver
This example demonstrates how to set up a web server on the ESP32-C6 to allow users to configure Wi-Fi settings through a web interface. The ESP32-C6 will create an access point if no Wi-Fi credentials are saved, allowing users to enter their SSID and password.

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

To reset the Wi-Fi configuration, you can access the following URL in your web browser:
```text
http://<IP_des_ESP32>/reset
```

### Features

#### IP-Adresse des AP vorgeben
Vor dem Start des Access Points kann die IP-Adresse des ESP32-C6 festgelegt werden. Dies ist nützlich, um eine konsistente IP-Adresse für den Konfigurationszugriff zu haben.
```cpp
void startAPMode() {
  IPAddress localIP(192, 168, 1, 1);        // Wunsch-IP des AP
  IPAddress gateway(192, 168, 1, 1);        // gleich wie localIP
  IPAddress subnet(255, 255, 255, 0);       // Standard-Subnetz

  WiFi.softAPConfig(localIP, gateway, subnet);  // IP konfigurieren

  WiFi.softAP("ESP32_Config", "12345678");
  ...
}
```

#### DNS zur Weiterleitung auf Webserver
Um sicherzustellen, dass alle DNS-Anfragen an den Webserver des ESP32-C6 weitergeleitet werden, kann der DNS-Server des Access Points so konfiguriert werden, dass er alle Anfragen an die IP-Adresse des ESP32-C6 umleitet. Dies ermöglicht es, dass Benutzer einfach die IP-Adresse des Access Points in ihrem Browser eingeben können, ohne eine spezifische URL angeben zu müssen.

```cpp
#include <DNSServer.h>

const byte DNS_PORT = 53;
DNSServer dnsServer;

void startAPMode() {
  IPAddress localIP(192, 168, 1, 1);        // Wunsch-IP des AP
  IPAddress gateway(192, 168, 1, 1);        // gleich wie localIP
  IPAddress subnet(255, 255, 255, 0);       // Standard-Subnetz

  WiFi.softAPConfig(localIP, gateway, subnet);  // IP konfigurieren

  // DNS-Server
  dnsServer.start(DNS_PORT, "*", localIP);  // <- DNS fängt alle Domains ab

  WiFi.softAP("ESP32_Config", "12345678");
  ...
}

void loop() {
  dnsServer.processNextRequest();  // <- DNS Anfragen beantworten
  server.handleClient();           // Webserver bedienen
}
```

#### Captive Portale
Ein Captive Portal ist eine Webanwendung, die automatisch geöffnet wird, wenn ein Benutzer eine Verbindung zu einem Wi-Fi-Netzwerk herstellt. Es ermöglicht die einfache Konfiguration von Netzwerkeinstellungen und bietet eine benutzerfreundliche Oberfläche für die Eingabe von SSID und Passwort.

```cpp
server.on("/generate_204", []() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
});

server.on("/hotspot-detect.html", []() {
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
});

server.onNotFound([]() {
  server.send(200, "text/html", getRootPage());
});
```

#### SSID speichern und verfügbare WLANs anzeigen
Um die SSID des Netzwerks zu speichern und verfügbare WLANs anzuzeigen, können Sie die `WiFi.scanNetworks()`-Funktion verwenden, um eine Liste der verfügbaren Netzwerke zu erhalten. Diese Liste kann dann in der Weboberfläche angezeigt werden, sodass Benutzer ein Netzwerk auswählen und die SSID speichern können.

```cpp
void handleRoot() {
  // Vorhandene gespeicherte SSID laden
  preferences.begin("wifi", true);
  String savedSSID = preferences.getString("ssid", "");
  preferences.end();

  // WLAN-Netzwerke scannen
  int n = WiFi.scanNetworks();

  // Beginne HTML-Seite
  String page = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="UTF-8">
    <title>ESP32 WLAN Konfiguration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: Arial, sans-serif;
        background: #f2f2f2;
        color: #333;
        padding: 0;
        margin: 0;
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100vh;
      }
      .card {
        background: #fff;
        padding: 2rem;
        border-radius: 1rem;
        box-shadow: 0 4px 12px rgba(0,0,0,0.1);
        max-width: 400px;
        width: 90%;
      }
      h1 {
        font-size: 1.5rem;
        margin-bottom: 1rem;
        text-align: center;
        color: #222;
      }
      label {
        display: block;
        margin-top: 1rem;
        font-weight: bold;
      }
      select, input {
        width: 100%;
        padding: 0.5rem;
        margin-top: 0.25rem;
        border: 1px solid #ccc;
        border-radius: 0.5rem;
        font-size: 1rem;
      }
      button {
        width: 100%;
        padding: 0.75rem;
        margin-top: 1.5rem;
        background: #007bff;
        color: white;
        border: none;
        border-radius: 0.5rem;
        font-size: 1rem;
        cursor: pointer;
        transition: background 0.3s;
      }
      button:hover {
        background: #0056b3;
      }
    </style>
  </head>
  <body>
    <div class="card">
      <h1>WLAN konfigurieren</h1>
      <form action="/save" method="get">
        <label for="ssid">SSID</label>
        <select name="ssid" id="ssid" required>
  )rawliteral";

  // WLAN-Netzwerke hinzufügen
  for (int i = 0; i < n; ++i) {
    String ssid = WiFi.SSID(i);
    bool selected = (ssid == savedSSID);
    page += "<option value='" + ssid + "'";
    if (selected) page += " selected";
    page += ">" + ssid + "</option>";
  }

  // Eingabe für Passwort und Submit-Button
  page += R"rawliteral(
        </select>

        <label for="pass">Passwort</label>
        <input type="password" id="pass" name="pass" required>

        <button type="submit">Speichern &amp; Verbinden</button>
      </form>
    </div>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", page);
}
```

#### Implementierung des WLAN Scan per AJAX
Um die WLAN-Netzwerke asynchron zu laden, können Sie AJAX verwenden. Dies ermöglicht es, die Netzwerkliste zu aktualisieren, ohne die gesamte Seite neu zu laden.

```cpp
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
```

```cpp
void handleRoot() {
  preferences.begin("wifi", true);
  String savedSSID = preferences.getString("ssid", "");
  preferences.end();

  String page = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="UTF-8">
    <title>ESP32 WLAN Konfiguration</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: Arial, sans-serif;
        background: #f2f2f2;
        color: #333;
        margin: 0;
        padding: 0;
        display: flex;
        justify-content: center;
        align-items: center;
        height: 100vh;
      }
      .card {
        background: #fff;
        padding: 2rem;
        border-radius: 1rem;
        box-shadow: 0 4px 12px rgba(0,0,0,0.1);
        max-width: 400px;
        width: 90%;
      }
      h1 {
        font-size: 1.5rem;
        text-align: center;
        color: #222;
        margin-bottom: 1rem;
      }
      label {
        display: block;
        margin-top: 1rem;
        font-weight: bold;
      }
      select, input {
        width: 100%;
        padding: 0.5rem;
        margin-top: 0.25rem;
        border: 1px solid #ccc;
        border-radius: 0.5rem;
        font-size: 1rem;
      }
      button {
        width: 100%;
        padding: 0.75rem;
        margin-top: 1.5rem;
        background: #007bff;
        color: white;
        border: none;
        border-radius: 0.5rem;
        font-size: 1rem;
        cursor: pointer;
        transition: background 0.3s;
      }
      button:hover {
        background: #0056b3;
      }
      .loading {
        font-style: italic;
        color: #888;
        margin-top: 0.5rem;
      }
    </style>
  </head>
  <body>
    <div class="card">
      <h1>WLAN konfigurieren</h1>
      <form action="/save" method="get">
        <label for="ssid">SSID</label>
        <select id="ssid" name="ssid" required>
          <option disabled selected>Netzwerke werden geladen...</option>
        </select>
        <div class="loading" id="status"></div>

        <label for="pass">Passwort</label>
        <input type="password" id="pass" name="pass" required>

        <button type="submit">Speichern &amp; Verbinden</button>
      </form>
    </div>

    <script>
      const savedSSID = ")rawliteral";

  page += savedSSID;  // gespeicherte SSID einfügen

  page += R"rawliteral(";

      fetch("/wifis")
        .then(response => response.json())
        .then(data => {
          const ssidSelect = document.getElementById("ssid");
          ssidSelect.innerHTML = "";
          data.forEach(ssid => {
            const option = document.createElement("option");
            option.value = ssid;
            option.textContent = ssid;
            if (ssid === savedSSID) {
              option.selected = true;
            }
            ssidSelect.appendChild(option);
          });
          document.getElementById("status").textContent = "✅ Netzwerke geladen";
        })
        .catch(() => {
          document.getElementById("status").textContent = "⚠️ Fehler beim Laden der Netzwerke";
        });
    </script>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", page);
}
```

#### Webseiten extrahieren
##### SPIFFS
Um die HTML-Seite in eine separate Datei auszulagern, können Sie die `ESPAsyncWebServer`-Bibliothek verwenden, die es ermöglicht, HTML-Dateien aus dem Dateisystem (SPIFFS oder LittleFS) zu laden. Hier ist ein Beispiel, wie Sie eine HTML-Datei namens `index.html` laden können:

https://github.com/me-no-dev/arduino-esp32fs-plugin?tab=readme-ov-file

Nach dem Neustart von Arduino kann unter `Sketch > Sketch Ordner anzeigen` ein Ordner `data` erstellt werden. In diesem Ordner kann die Datei `index.html` abgelegt werden.

##### LittleFS

https://github.com/lorol/arduino-esp32littlefs-plugin?tab=readme-ov-file

```cpp
#include <LittleFS.h>
...
server.on("/testFS", []() {
  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "Fehler: /index.html nicht gefunden");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
});

void setup() {
  if (!LittleFS.begin(true)) {
    Serial.println("❌ Fehler beim Mounten von LittleFS");
    return;
  }
  Serial.println("📂 LittleFS bereit");
}
```