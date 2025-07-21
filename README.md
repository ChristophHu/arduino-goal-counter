# arduino-goal-counter

## Komponenten

- Adafruit ESP32-C6: Mikrocontroller mit Wi-Fi, BLE, Zigbee/Thread (sehr vielseitig!)
- Lichtschranke (z. B. Reflexions- oder Gabellichtschranke): Zur Erkennung, wenn ein Ball durch das Tor geht.
- Waveshare E-Ink Display (z. B. 2.9" oder 4.2" SPI): Für die Anzeige des Spielstands.
- Stromversorgung (Powerbank, Netzteil oder Akku)
- Optional: Taster zum Zurücksetzen des Spielstands

## Funktionsweise/Ablauf

### Torerkennung mit Lichtschranke
Die Lichtschranke erkennt, wenn ein Ball durch das Tor rollt (Strahl unterbrochen).
ESP32 erkennt die Unterbrechung über einen digitalen Eingang.
Softwareseitig wird ein Zähler erhöht (ggf. mit Entprellung und Verzögerung gegen Mehrfachzählung).

### Spielstand verwalten
Zähler für Team A und B (z. B. bei zwei Lichtschranken – für jedes Tor eine).

### Anzeige auf E-Ink Display
Der ESP32 sendet den aktuellen Spielstand über SPI an das Waveshare E-Ink Display.
Aktualisierung z. B. alle paar Sekunden oder direkt nach einem Tor.

## Elektronik-Verkabelung (schematisch)

| Komponente | ESP32-C6 Pin | Hinweis |
|---|---|---|
| Lichtschranke A |	GPIO (z. B. D2)	| Pulldown/Interrupt-fähig |
| Lichtschranke B	| GPIO (z. B. D3)	| bei 2 Toren |
| E-Ink (SPI-Modul)	| MOSI, CLK, CS, DC, RST, BUSY | Pinout abhängig vom Displaymodell |
| Reset-Taster | GPIO (z. B. D4) | Spielstand zurücksetzen |

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
