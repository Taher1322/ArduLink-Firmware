#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);

}

void loop() {
  //  display.clearDisplay();
  //  display.setTextSize(1);
  //  display.setTextColor(WHITE);
  //  display.setCursor(0, 11);
  //  // Display static text
  //  display.print("TIMESTAMP:");
  //  display.print("01:11:12");
  //  display.setCursor(3, 0);
  //  display.print("MOISTURE:");
  //  display.print("650");
  //  display.display();
  //  delay(2000);


  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("HUMIDITY:");
  display.setCursor(60, 0);
  display.print(60);
  display.print("%");
  
  display.setCursor(0, 8);
  display.print("TEMPERATURE:");
  display.setCursor(75, 8);
  display.print(25.9);
  display.print("C");
  
  display.setCursor(0, 16);
  display.print("SOIL TEMP:");
  display.setCursor(75, 16);
  display.print(21.6);
  display.print("C");
  
  display.setCursor(0, 24);
  display.print("SOIL MOIST:");
  display.setCursor(75, 24);
  display.print(650);
  //display.print("C");
  display.display();

}
