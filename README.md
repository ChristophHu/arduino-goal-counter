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
