# arduino-goal-counter

## Idee
Die Idee hinter dem Arduino Goal Counter ist es, ein einfaches und effektives System zur Zählung von Toren an einem Tischkicker zu entwickeln. Durch den Einsatz von Lichtschranken und einem Mikrocontroller (ESP32-C6) soll das System in der Lage sein, Tore automatisch zu erkennen und den Spielstand anzuzeigen.

## Anforderungen
- Es sollten Tore automatisch bei der Heim- und der Gast-Manschaft erkannt werden.
- Der aktuelle Spielstand soll im Browser angezeigt werden.
- Es soll möglich sein, den Spielstand zurückzusetzen.

## Benötigte Hardware
- **Microcontroller - Adafruit ESP32-C6**: Ein Mikrocontroller mit Wi-Fi, BLE und Zigbee/Thread, der vielseitig einsetzbar ist.
- **Lichtschranke - TCRM5000**: Zum Beispiel zwei Reflexions- oder Gabellichtschranken.
- **E-Ink Display - Waveshare 1.54"**: Ein E-Ink Display zur Anzeige des Spielstands.
- **Taster**: (optional) Zum Zurücksetzen des Spielstands.
- **Stromversorgung**: USB oder Batterie (z. B. 18650 Li-Ion Akku).
- **Kabel und Steckbrett**: Für die Verkabelung der Komponenten.
- **Widerstände**: Falls nötig, z. B. für Pull-Up/Pull-Down bei den Lichtschranken.
- **Optional**: Gehäuse für die Elektronik.

## Software
- **Arduino IDE**: Zur Programmierung des ESP32-C6.
- **Bibliotheken**: Für E-Ink Displays (z. B. GxEPD2) und Lichtschranken.
- **Webserver**: Um den Spielstand im Browser anzuzeigen (z. B. mit ESPAsyncWebServer).

## Funktionsweise/Ablauf

### Torerkennung mit Lichtschranke
Die Lichtschranke erkennt, wenn ein Ball durch das Tor rollt (Strahl unterbrochen).
ESP32 erkennt die Unterbrechung über einen digitalen Eingang.
Softwareseitig wird ein Zähler erhöht (ggf. mit Entprellung und Verzögerung gegen Mehrfachzählung).

### Spielstand verwalten
Zähler für Team A und B (z. B. bei zwei Lichtschranken – für jedes Tor eine).

## Elektronik-Verkabelung (schematisch)

| Komponente | ESP32-C6 Pin | Hinweis |
|---|---|---|
| Lichtschranke A |	GPIO (z. B. D2)	| Pulldown/Interrupt-fähig |
| Lichtschranke B	| GPIO (z. B. D3)	| bei 2 Toren |

## Software (Arduino)

Mit der Arduino IDE oder PlatformIO kannst du das ESP32-C6 programmieren. Es gibt Bibliotheken für:
- E-Ink Displays von Waveshare: z. B. GxEPD, Waveshare_EPD, GxEPD2
- Interrupts oder polling für Lichtschranken
- Displaygrafik & Fonts

## Mögliche Herausforderungen
| Herausforderung	| Lösung |
|---|---|
| Geisterzählungen | Entprellung + kleine Pause nach jeder Zählung |
| E-Ink langsam	| Nur bei Toren aktualisieren, nicht permanent |
| Display flackert | Teil-Updates nutzen (bei unterstützten Displays) |
| Stromverbrauch (Akku)	| ESP32 in den Deep Sleep schicken zwischendurch |

## Erweiterungen (optional)
- Wi-Fi-Anbindung (Spielstand online übertragen)
- OLED statt E-Ink (wenn’s schneller sein soll)
- Soundeffekte oder LED bei Tor
- Webinterface für Reset

## Ein Sensor
Anschluß der beiden TCRT5000 an den Adafruit Feather m0 Bluefruit
```cpp
#define TOR_SENSOR_PIN 5  // oder 6 für zweiten Sensor

int tore = 0;
bool vorherigerStatus = false;

void setup() {
  Serial.begin(115200);
  pinMode(TOR_SENSOR_PIN, INPUT);
}

void loop() {
  bool ballErkannt = digitalRead(TOR_SENSOR_PIN) == LOW;

  if (ballErkannt && !vorherigerStatus) {
    tore++;
    Serial.print("Tor erkannt! Tore: ");
    Serial.println(tore);
    delay(300);  // Entprellung
  }

  vorherigerStatus = ballErkannt;
}
```

| Modul	| TCRT5000 #1	| TCRT5000 #2 |
|---|---|---|
| VCC	| 3.3 V oder 5 V | 3.3 V oder 5 V |
| GND	| GND	| GND |
| DO | D5 (Pin 5) | D6 (Pin 6) |

Spannungsteiler	ja (falls 5 V-Modul)	ja (falls 5 V-Modul)

## Zwei Sensoren
```cpp
#define TOR_SENSOR_A_PIN 5  // erster Sensor
#define TOR_SENSOR_B_PIN 6  // zweiter Sensor

int toreA = 0;
int toreB = 0;
bool statusA = false;
bool statusB = false;

void setup() {
  Serial.begin(115200);
  pinMode(TOR_SENSOR_A_PIN, INPUT);
  pinMode(TOR_SENSOR_B_PIN, INPUT);
}

void loop() {
  bool erkanntA = digitalRead(TOR_SENSOR_A_PIN) == LOW;
  bool erkanntB = digitalRead(TOR_SENSOR_B_PIN) == LOW;

  if (erkanntA && !statusA) {
    toreA++;
    Serial.print("Tor erkannt! Tore: ");
    Serial.println(toreA);
    delay(300);  // Entprellung
  }
   if (erkanntB && !statusB) {
    toreB++;
    Serial.print("Gegentor erkannt! Tore: ");
    Serial.println(toreB);
    delay(300);  // Entprellung
  }

  statusA = erkanntA;
  statusB = erkanntB;
}
```

## Mit Waveshare 1.54" ePaper

| Display-Pin | Feather M0 Bluefruit | Beschreibung |
|---|---|---|
| VCC | 3V | 3.3 V Versorgung |
| GND | GND | Masse |
| DIN | MOSI (Pin 23 / D11) | SPI-Datenleitung |
| CLK | SCK (Pin 24 / D13) | SPI-Takt |
| CS | D10 | Chip Select |
| DC | D9 | Data/Command Control |
| RST | D12 | Reset |
| BUSY | D13 | Busy-Status (High = beschäftigt) |


```cpp
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// Definition für dein 1.54" Display (200x200)
#define EPD_CS     10
#define EPD_DC     9
#define EPD_RST    12
#define EPD_BUSY   13

GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

#define TOR_SENSOR_A_PIN 5  // erster Sensor
#define TOR_SENSOR_B_PIN 6  // zweiter Sensor

int toreA = 0;
int toreB = 0;
bool statusA = false;
bool statusB = false;

void setup() {
  Serial.begin(115200);

  display.init();
  display.setRotation(1);
  display.setTextColor(GxEPD_BLACK);
  updateDisplay();
  
  pinMode(TOR_SENSOR_A_PIN, INPUT);
  pinMode(TOR_SENSOR_B_PIN, INPUT);
}

void loop() {
  bool erkanntA = digitalRead(TOR_SENSOR_A_PIN) == LOW;
  bool erkanntB = digitalRead(TOR_SENSOR_B_PIN) == LOW;

  if (erkanntA && !statusA) {
    toreA++;
    Serial.print("Tor erkannt! Tore: ");
    Serial.println(toreA);
    delay(300);  // Entprellung
  }
   if (erkanntB && !statusB) {
    toreB++;
    Serial.print("Gegentor erkannt! Tore: ");
    Serial.println(toreB);
    delay(300);  // Entprellung
  }

  statusA = erkanntA;
  statusB = erkanntB;

  delay(10000);
  updateDisplay();
}

void updateDisplay() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(0, 70);
    display.print("A: ");
    display.print(toreA);
    display.setCursor(0, 150);
    display.print("B: ");
    display.print(toreB);
  } while (display.nextPage());
}
```
