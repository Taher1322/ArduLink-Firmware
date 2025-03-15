#include <DS3231.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);

  // The following lines can be uncommented to set the date and time
  //  rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(23, 04, 00);     // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(06, 06, 2024);   // Set the date to January 1st, 2014
}

void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());

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


  // Wait one second before repeating :)
  delay (1000);
}
