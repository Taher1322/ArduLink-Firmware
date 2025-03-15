/*DS18B20 One Wire Temperature Sensor with Arduino
   Author: Electrofun
   For more information visit us: www.electrofun.co.in
   Video explanation at: https://www.youtube.com/watch?v=A5jJ-pfji_M&ab_channel=Electrofun
   Download OneWire Library: https://www.arduinolibraries.info/libraries/one-wire
   Download DallasTemperature Library: https://www.arduinolibraries.info/libraries/dallas-temperature

   // Example testing sketch for various DHT humidity/temperature sensors
  // Written by ladyada, public domain

  // REQUIRES the following Arduino libraries:
  // - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
  // - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

*/

//Including the necessary libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"
#include <SD.h>
#include <SPI.h>
#include <DS3231.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

#define DHTPIN 2     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define ONE_WIRE_PIN 5     //Define the Arduino Pin 

#define DEBUG_UART 0

#define BLE_TRANSMIT 1

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONE_WIRE_PIN);    //Setup of instance to communicate with one wire sensor

DallasTemperature sensors(&oneWire);  //Pass one wire reference to Dallas Temperature Library

int sdcardpinCS = 10;
int moisturePin = A0;
int moistureValue = 0;
int ambientPin = A3;
int ambientValue = 0;
float ds18_temperature = 0.0;
float dht_humidity = 0.0;
float dht_temperature = 0.0;

File myFile;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  sensors.begin();
  dht.begin();
  pinMode(moisturePin, INPUT);
  pinMode(ambientPin, INPUT);

  pinMode(sdcardpinCS, OUTPUT);

  // SD Card Initialization
  if (SD.begin())
  {
    if (DEBUG_UART == 1)
      Serial.println("SD card is ready to use.");
  } else
  {
    if (DEBUG_UART == 1)
    {
      Serial.println("SD card initialization failed");
      return;
    }
  }

  // Initialize the rtc object
  rtc.begin();
  
//  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
//    Serial.println(F("SSD1306 allocation failed"));
//    for (;;);
//  }
  delay(2000);


  // The following lines can be uncommented to set the date and time
  //    rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //    rtc.setTime(22, 47, 00);     // Set the time to 12:00:00 (24hr format)
  //    rtc.setDate(06, 12, 2024);   // Set the date to January 1st, 2014
}

void loop() {
  moisture_data();
  delay(100);
  ambient_light_data();
  delay(100);
  ds18b20_data();
  delay(100);
  dht_sensor_data();
  delay(100);
  store_data();
  delay(100);
  bluetooth_transmit();
  //oled_display();

}


void moisture_data()
{
  // read the value from the sensor:
  moistureValue = analogRead(moisturePin);
  if (DEBUG_UART == 1)
  {
    Serial.print("Moisture: ");
    Serial.println(moistureValue);
  }
}

void ambient_light_data()
{
  // read the value from the sensor:
  ambientValue = analogRead(ambientPin);
  if (DEBUG_UART == 1)
  {
    Serial.print("Intensity: ");
    Serial.println(ambientValue);
  }
}

void ds18b20_data()
{
  sensors.requestTemperatures();    //Call and request all sensors in one wire bus

  //Printing the Temperature in Celsius and Fahrenheit
  ds18_temperature = sensors.getTempCByIndex(0);
  if (DEBUG_UART == 1)
  {
    Serial.print("DS18B Temperature: ");
    Serial.println(ds18_temperature);
  }
}

void dht_sensor_data()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  dht_humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  dht_temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  //float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(dht_humidity) || isnan(dht_temperature)) {
    if (DEBUG_UART == 1)
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  }

  if (DEBUG_UART == 1)
  {
    Serial.print(F("Humidity: "));
    Serial.print(dht_humidity);
    Serial.print(F("%  Temperature: "));
    Serial.println(dht_temperature);
  }
}

void store_data()
{
  myFile = SD.open("new.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(rtc.getTimeStr());
    myFile.print(",");
    myFile.print(moistureValue);
    myFile.print(",");
    myFile.print(ambientValue);
    myFile.print(",");
    myFile.print(ds18_temperature);
    myFile.print(",");
    myFile.print(dht_humidity);
    myFile.print(",");
    myFile.print(dht_temperature);
    myFile.println();
    //    myFile.print(",");
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    if (DEBUG_UART == 1)
    {
      Serial.println("error opening test.txt");
    }
  }
}

/*
void oled_display()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("HUMIDITY:");
  display.setCursor(60, 0);
  display.print(dht_humidity);
  display.print("%");

  display.setCursor(0, 8);
  display.print("TEMPERATURE:");
  display.setCursor(75, 8);
  display.print(dht_temperature);
  display.print("C");

  display.setCursor(0, 16);
  display.print("SOIL TEMP:");
  display.setCursor(75, 16);
  display.print(ds18_temperature);
  display.print("C");

  display.setCursor(0, 24);
  display.print("SOIL MOIST:");
  display.setCursor(75, 24);
  display.print(moistureValue);
  display.display();
}
*/

void bluetooth_transmit()
{
  if (BLE_TRANSMIT == 1)
  {
    Serial.print("TIMESTAMP:");
    Serial.print(rtc.getTimeStr());
    Serial.print(",");
    Serial.print("MOISTURE:");
    Serial.print(moistureValue);
    Serial.print(",");
    Serial.print("AMBIENT LIGHT:");
    Serial.print(ambientValue);
    Serial.print(",");
    Serial.print("SOIL TEMP:");
    Serial.print(ds18_temperature);
    Serial.print(",");
    Serial.print("HUMIDITY:");
    Serial.print(dht_humidity);
    Serial.print(",");
    Serial.print("TEMP:");
    Serial.print(dht_temperature);
    Serial.println();
  }
}

