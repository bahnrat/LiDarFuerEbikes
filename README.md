# 🚲 Anti-Collision Lidar Warning System (ESP32-S2)

Ein intelligentes Abstands-Warnsystem basierend auf dem **ESP32-S2 Mini**, dem **Benewake TF02-Pro Lidar-Sensor** und einem runden **GC9A01 Farbdisplay**. Das System misst in Echtzeit den Abstand zu Hindernissen oder vorausfahrenden Fahrzeugen und zeigt diesen flackerfrei an.

> **Status:** Phase 1 (Fahrrad-Tacho) ist softwareseitig einsatzbereit, Platinen-Layout (2-lagig, RM 2,54mm) ist in Produktion. Phase 2 (Auto-Variante via OBDII) ist in der Konzeptionsphase.

---

## 🚀 Features

- **Präzise Messung:** Bis zu 40 Meter Reichweite im Außenbereich mit dem TF02-Pro (Infrarot-Lidar).
- **Optimiertes Display-Design:** Große, zentrierte Zahlenanzeige auf einem runden GC9A01-Display (perfekt für Fahrrad-Cockpits).
- **Flackerfreie Anzeige:** Intelligente Update-Logik im Code überschreibt nur veränderte Zahlenwerte (schwarzer Text-Overlay statt `fillScreen`).
- **Power-Save:** Mechanischer VCC-Trennschalter integriert (z.B. für Fahrten ohne Messbedarf bei Nacht).
- **Hardware-Sicherheit:** 2-lagiges, streng entflochtenes Platinenlayout im Standard-Rastermaß (2,54 mm).

---

## 🛠️ Hardware-Komponenten

- **Mikrocontroller:** Lolin ESP32-S2 Mini
- **Lidar-Sensor:** Benewake TF02-Pro (UART-Version)
- **Display:** GC9A01 (Rundes 1.28" TFT, SPI-Schnittstelle)
- **Spannungsregler:** Recom-Modul (5V VBUS-Speisung für den Lidar)
- **Layout-Software:** Sprint-Layout 6.0 (`*.lay6`-Datei direkt im Repository)

---

## 📌 Pin-Belegung (ESP32-S2 Mini)

Das Layout wurde für eine optimale, kreuzungsfreie Leitungsführung auf zwei Layern (Top/Bottom) optimiert, wobei ausschließlich die **äußeren Pinreihen** des S2 Mini genutzt werden.

| Peripherie | Pin-Name | ESP32-S2 GPIO | PIN auf Leiterplatte |
| :--- | :--- | :--- | :--- |
| **Strom** | VCC (5V) | VBUS | VBUS |
| **Display** | GND | GND | GND/13 |
| **Display** | RST | **GPIO 5** | 8 |
| **Display** | CS | **GPIO 12** | 9 |
| **Display** | DC | **GPIO 33** | 10 |
| **Display** | SDA (MOSI) | **GPIO 37** | 11 |
| **Display** | SCL (CLK) | **GPIO 39** | 12 |
| **Display** | VCC 3,3V | **3V3** | 14 |
| **Lidar** | RX (Daten vom Sensor) | **GPIO 18** | 
| **Backup** | TX (Optional) | **GPIO 16** | 

---

## 💻 Software-Installation

### 1. Benötigte Bibliotheken (Arduino IDE)
Installiere die folgenden Bibliotheken über den Bibliotheksverwalter (`Strg + Umschalt + I`):
- `TFMPlus` (von Bud Ryerson)
- `Adafruit GC9A01A` (inkl. Abhängigkeiten wie `Adafruit GFX` und `Adafruit BusIO`)

### 2. Code hochladen
1. Öffne die Datei `lidar.ino` in der Arduino IDE.
2. Wähle als Board **Lolin S2 Mini** aus.
3. Verbinde das Board per USB (Hinweis: Der serielle Starttext verpufft beim Booten über den Native USB-CDC manchmal, die Funktionalität ist jedoch voll gegeben).
4. Klicke auf **Upload**.

---

## 🔮 Ausblick: Phase 2 (Automobil-Erweiterung)

Geplant ist eine Erweiterung des Systems für den Einsatz im Auto:
- **Sensor-Upgrade:** Lidar mit bis zu 150m Reichweite.
- **OBDII-Integration:** Abgreifen der Echtzeit-Geschwindigkeit via Bluetooth (OBDLink MX+).
- **Dynamische Warnung:** Automatische Berechnung des Sicherheitsabstands nach der Formel $\text{Abstand} = \text{Geschwindigkeit} / 2$.
- **Web-Konfiguration:** ESP32-Access-Point zur Justierung des Scheiben-Offsets (Abstand Frontscheibe zu Stoßstange).
