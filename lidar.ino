#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include <TFMPlus.h>

// ----------------------------------------------------
// PIN-KONFIGURATION (Exakt wie in deinem Layout!)
// ----------------------------------------------------
#define TFT_RST  5   // Linke Außenbahn
#define TFT_CS   12  // Rechte Außenbahn
#define TFT_DC   33  // Rechte Außenbahn
#define TFT_SDA  37  // Rechte Außenbahn (MOSI)
#define TFT_SCL  39  // Rechte Außenbahn (SCK)

#define LIDAR_RX 18  // Linke Außenbahn (Empfang vom TF02-Pro)
#define LIDAR_TX -1  // Nicht verbunden / Deaktiviert

// ----------------------------------------------------
// OBJEKT-DEKLARATIONEN
// ----------------------------------------------------
// Eigenen SPI-Bus für die zugewiesenen Pins erstellen
SPIClass customSPI(FSPI); 

// Display-Objekt mit den Custom-Pins initialisieren
Adafruit_GC9A01A tft(&customSPI, TFT_DC, TFT_CS, TFT_RST);

// Lidar-Objekt initialisieren
TFMPlus lidar;
HardwareSerial LidarSerial(1); // Nutzt die zweite serielle Einheit (UART1)

// Variablen für die Anzeige-Logik
int letzterAbstand = -1;

void setup() {
  // Seriellen Monitor für den PC starten
  Serial.begin(115200);
  delay(500);
  Serial.println("System-Start: TF02-Pro & GC9A01");

  // 1. SPI-Pins für dein Layout umleiten und SPI starten
  customSPI.begin(TFT_SCL, -1, TFT_SDA, TFT_CS); 

  // 2. Display initialisieren
  tft.begin();
  tft.setRotation(0); // 0-3 ausprobieren, falls die Zahl später auf dem Kopf steht
  tft.fillScreen(GC9A01A_BLACK); // Bildschirm leeren (schwarz)

  // Einen statischen Rahmen oder eine Einheit malen (wird nur 1x gezeichnet)
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(2);
  tft.setCursor(105, 160); // Zentriert im unteren Bereich des runden Displays
  tft.print("cm");

  // 3. Lidar-Schnittstelle starten (TF02-Pro läuft standardmäßig auf 115200 Baud)
  LidarSerial.begin(115200, SERIAL_8N1, LIDAR_RX, LIDAR_TX);
  delay(20);
  lidar.begin(&LidarSerial);
  Serial.println("Lidar initialisiert.");
}

void loop() {
  int16_t abstandRaw = 0;
  int16_t fluxRaw = 0;   // Signalstärke
  int16_t tempRaw = 0;   // Sensortemperatur

  // Daten vom TF02-Pro abfragen
  if (lidar.getData(abstandRaw, fluxRaw, tempRaw)) {
    
    // Nur aktualisieren, wenn sich der Wert geändert hat (verhindert Flackern!)
    if (abstandRaw != letzterAbstand) {
      
      // Alten Text mit der Hintergrundfarbe (Schwarz) überschreiben = Unsichtbar machen
      tft.setTextColor(GC9A01A_BLACK);
      tft.setTextSize(7); // Riesige Schriftgröße für die Zahl
      tft.setCursor(50, 90); // Startposition für die Zahl
      if (letzterAbstand < 100) tft.print(" "); // Ausrichtung bei zweistelligen Werten
      tft.print(letzterAbstand);

      // Neuen Abstandswert in Weiß zeichnen
      tft.setTextColor(GC9A01A_WHITE);
      tft.setTextSize(7);
      tft.setCursor(50, 90);
      if (abstandRaw < 100) tft.print(" ");
      tft.print(abstandRaw);

      // Wert für den nächsten Durchlauf merken
      letzterAbstand = abstandRaw;

      // Debug-Ausgabe auf dem PC-Monitor
      // SO MUSS ES SEIN:
      Serial.print("Abstand: ");
      Serial.print(abstandRaw);
      Serial.println(" cm");
    }
  }
  
  delay(50); // Kurze Pause (20 Messungen pro Sekunde reichen völlig aus)
}
