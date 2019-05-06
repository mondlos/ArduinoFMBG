# ArduinoFMBG
![ArduinoFMBG Logo](Materialien/logoSmall.png)

Dieses Projekt ist im Rahmen meiner 5. Prüfungskomponente für das Abitur in Berlin entstanden. 

Referenzfach: Physik\
Bezugsfach: Informatik

Ziel war es, eine multifunktionale Plattform für den Einsatz von Arduino-Sensoren im Physikunterricht zu schaffen.

## Funktionsumfang
Die Messbox unterstützt folgende Sensoren
1. Temperatur/;Luftfeuchtigkeit (basiert auf DHT-11)
2. Hallsensor (Messung der magnetischen Flussdichte, basiert auf UGN3503)
3. h-Bestimmung Simulation (viele Einstellmöglichkeiten, mein Favorit)
4. Pendel (einstellbare Erkennungsdistanz, basiert auf HC-SR04)
5. Schall (Schalldruck und unbewerteter Schalldruckpegel)
6. Luftdruck (basiert auf BMP180-Modul)
7. Spannungsteiler (interaktive Übung zum Thema Spannungsteiler)
8. Kondensator (Kapazität, Funktionsgleichung)


Man kann über I2C weitere Daten an die Messbox schicken (für externe Sensoren) 

## Abhängigkeiten

| Bibliothek    | Autor      | Funktion    |
| ------------- |:-------------:| :-----:|
| [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)    | [adafruit](https://github.com/adafruit)      | Grafikbiblitohek für Adafruit-LCDs    |
| [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)    | [adafruit](https://github.com/adafruit)      | Bedienung von SSD1306-LCDs
| [Adafruit Sensor](https://github.com/adafruit/Adafruit_Sensor)      | [adafruit](https://github.com/adafruit)      | Basis für BMP180 und DHT11   |
|[BigNumber (mein Fork)](https://github.com/leonardoInf/BigNumber)     | [nickgammon](https://github.com/nickgammon)     | speicherintensive Berechnungen    |
| [BMP180 Breakout](https://github.com/sparkfun/BMP180_Breakout_Arduino_Library)     | [sparkfun](https://github.com/sparkfun)     | Bedienung des BMP180   |
|[DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)     |  [adafruit](https://github.com/adafruit)   |  Bedienung des DHT11   |
[HC-SR04](https://github.com/Martinsos/arduino-lib-hc-sr04)     | [Martinos](https://github.com/Martinsos)     | Bedienung des HC-SR04     |
| [Keypad](https://github.com/Chris--A/Keypad)     | [Chris--A](https://github.com/Chris--A) | Navigation mit dem Keypad |

##### Hinweis: 
Standardmäßig wird ein 16x2 LiquidCrystal-LCD verwendet.\
Adafruit GFX und Adafruit SSD1306 werden nur benötigt, wenn man ein I2C-LCD einsetzen möchte. 

