#include <workouts.h>

#include <Time.h>
#include <TimeLib.h>
#include <string>

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"


#define _cs   17  // goes to TFT CS
#define _dc   16  // goes to TFT DC
#define _mosi 23  // goes to TFT MOSI
#define _sclk 18  // goes to TFT SCK/CLK
#define _rst  5   // goes to TFT RESET
#define _miso     // Not connected
//       3.3V     // Goes to TFT LED  
//       3.3v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd        

// Use hardware SPI
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _rst);

// If using software SPI change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

void setup() {
  Serial.begin(115200);
  Serial.println("ILI9341 Test!");

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLUE);
  tft.setTextSize(3);
  tft.println("ILI9341 Test!");
  delay(1000);
  tft.fillScreen(ILI9341_BLACK);

  tft.drawLine(0,50,230,50,ILI9341_WHITE);      // title partition
  tft.drawLine(230,0,230,240,ILI9341_WHITE);    // right partition
  tft.drawLine(230,120,320,120,ILI9341_WHITE);  // right partition divided upper lower
  tft.drawLine(0,190,230,190,ILI9341_WHITE);    // lower partition
}

void loop() {
  displayTitle();
//  hello("Class");
//  delay(500);
//  goodbye("Adam");
//  delay(500);
  displayCurrentDate();
  displayTime();
  animatePowerClean(4);
}

unsigned long displayTitle() {
  // print "Workout of the Day" at top of screen
  tft.setCursor(7, 15);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.print("Workout of the Day");
}

unsigned long animatePowerClean(int reps) {
  const unsigned char* const bitmaps[6] = {PowerClean1, PowerClean2, PowerClean3, PowerClean4, PowerClean5, PowerClean1};
  tft.fillRect(0, 51, 229, 129, ILI9341_BLACK);
  for (int i = 0; i < reps; i++) {
    for (int j = 0; j < 6; j++) {
      tft.fillRect(50, 55, 130, 130, ILI9341_BLACK);
      tft.drawBitmap(50, 55, bitmaps[j], 130, 130, ILI9341_WHITE);
      if (j == 0) {
        delay(2000);
      }
      else {
        delay(1000);
      }
    }
//    tft.fillRect(0, 51, 229, 129, ILI9341_BLACK);
  }
}

unsigned long displayCurrentDate() { 
  time_t t = now();

  String monthShortName[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
  String daysOfWeek[7] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
  String mth = monthShortName[month(now()) - 1];
  String wkdy = daysOfWeek[weekday(now()) - 1];
  String currentDay;
  if (day()+9 > 9) {
    currentDay = String(day()+9);
  }
  else {
    currentDay = "0" + String(day());
  }
  
//  tft.setCursor(253,5);
//  tft.setTextColor(ILI9341_GREEN);
//  tft.setTextSize(3);
//  tft.println(wkdy);
//  delay(10000);
  
  // print Month shortname
  tft.setTextColor(ILI9341_PINK);
  tft.setCursor(251, 5);
  tft.setTextSize(3);
  tft.println(mth);

  // print Day of Month
  tft.setCursor(250, 30);
  tft.setTextSize(5);
  tft.println(currentDay);

  // print Weekday shortname
  tft.setTextColor(ILI9341_YELLOW);
  tft.setCursor(251, 70);
  tft.setTextSize(3);
  tft.println(wkdy);

  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(235, 125);
  tft.setTextSize(3);
  tft.print(year());
}

unsigned long displayTime() {
  tft.setCursor(237, 100);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("12:34");
  tft.setTextSize(1);
  tft.print(" PM");
}

