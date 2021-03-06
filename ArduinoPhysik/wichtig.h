// *** Abhängigkeiten     ****
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>        //
#include <HCSR04.h>       //Entfernung (Ultraschall)
#include <SFE_BMP180.h>   //Luftdruck

#include "globals.h"  //KONFIGURATIONEN befinden sich hier
#include "Sensoren.h"
#include "read.h"
// ***

#ifndef I2CLCD
#include <LiquidCrystal.h>
#endif

#ifdef ERWEITERT
#include <Wire.h>
#endif

#ifdef I2CLCD
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#endif

// ***                    ****

#if defined(I2CLCD) && defined(ERWEITERT)
#error "I2C-Erweiterungen mit gleichzeitiger Verwendung von I2C-LCD werden zurzeit nicht unterstützt"
#endif

#if defined(WLAN) && defined(SERIELLE_AUSGABE)
#error "Serielle Ausgabe kollidiert normalerweise mit Kommunikation zum ESP8266, 'z' vor alle Zeichenketten setzen, um dies zu verhindern"
#endif

#if defined(WLAN) && defined(UNO)
#error "Arduino Uno ist hier mit ESP8266 nicht kompatibel"
#endif

#if !defined(I2CLCD) && defined(UNO)
#error "Arduino Uno sollte mit I2CLCD verwendet werden"
#endif

// *** Konstanten und Variablen für die h-Bestimmmung  ***
#ifndef UNO
const BigNumber p_max = 5;  // 5 W/m^2
const BigNumber zero = 0;
const BigNumber eins = 1;
const BigNumber vier = 4;
const BigNumber zehn  = 10;
const BigNumber neunzehn = 19;
const BigNumber vierunddreissig = 34;
const BigNumber hundert = 100;
const BigNumber materialien[][7] = {
      {1.8, 1.94, 2.25, 2.28, 4.2, 4.27, 4.48}, 
      {0.17, 0.29, 0.18, 0.28, 0.30, 0.21, 0.23},
};
const char* symbole[] {
      "Ba", "Cs", "K", "Na", "Al", "Zn", "Cu"
  };
 BigNumber minus_eins;
 BigNumber l_inc;
 BigNumber l_min;
 BigNumber l_max;
 BigNumber h;
 BigNumber c;
 BigNumber elementarladung;
 BigNumber nano;
  int m_index = 0;
  BigNumber ausloesearbeit;
  BigNumber ausbeute;
  BigNumber wellenlaenge;
#endif
//***                                      ****

// *** Globale Variablen (siehe globals.h) ****
char str_result[40];
boolean isactive = false;
boolean tabelle = false;
boolean MessungDurchfuehren = false;
int tolPercent = 5;
int stufeK = 0;
int backK = 0;
int sIndex = 0;
int sIndex2 = 0;
int posK = 0;
boolean allowInput = true;
int index = 0;
// ***                                    ****

// *** Variablen für menue.ino            ****
boolean rcvMode = false;
#ifndef I2CLCD                    
enum{rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#else
Adafruit_SSD1306 lcd = Adafruit_SSD1306(128, 32, &Wire);
#endif

#if defined(WLAN) && !defined(UNO)
const char *optionen[] PROGMEM=  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Hallsensor",
                     "3. h-Bestimmung;Simulation",
                     "4. Pendel",
                     "5. Schall",
                     "6. Luftdruck",
                     "7. Spannungs-;teiler",
                     "8. Kondensator",
                     "9. Wetter"
                    };
     const int anzahlOptionen = 9;
void lokalAusfuehren(){
  switch(index){
    case 0:
      temperatur(); break;
    case 1:
      hallsensor(); break;
    case 2:
      h_bestimmung(); break;
    case 3:
      pendel(); break;
    case 4:
      schall(); break;
    case 5:
      luftdruck(); break;
    case 6:
      spannungsteiler(); break;
    case 7:
      kondensator(); break;
    case 8:
      wetter(); break;
    default:
    ;  
  }    
}
#endif

#if !defined(WLAN) && !defined(UNO)
const char *optionen[] =  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Hallsensor",
                     "3. h-Bestimmung;Simulation",
                     "4. Pendel",
                     "5. Schall",
                     "6. Luftdruck",
                     "7. Spannungs-;teiler",
                     "8. Kondensator",
                    };
                    const int anzahlOptionen = 8;
  #ifdef I2CLCD
    optionen[6] = "8- Spannungsteiler";
  #endif
void lokalAusfuehren(){
  switch(index){
    case 0:
      temperatur(); break;
    case 1:
      hallsensor(); break;
    case 2:
      h_bestimmung(); break;
    case 3:
      pendel(); break;
    case 4:
      schall(); break;
    case 5:
      luftdruck(); break;
    case 6:
      spannungsteiler(); break;
    case 7:
      kondensator(); break;
    default:
    ;  
  }    
}
#endif

#ifdef UNO
const char *optionen[] =  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Luftdruck",
                     "3. Pendel",
                     "4. Schall"
                    };
      const int anzahlOptionen = 5;
void lokalAusfuehren(){
  switch(index){
    case 0:
      temperatur(); break;
    case 1:
      luftdruck(); break;
    case 2:
      pendel(); break;
    case 3:
      schall(); break;
    default:
    ;  
  }    
}
#endif
