/* Ambient Light Sensor Interfacing with Arduino
   Author: Electrofun
*/

int sensorPin = A2;    // select the input pin for the Ambient TEMT6000 Sensor
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  pinMode(sensorPin, INPUT); //Defining the Sensor pin as Inout
  Serial.begin(9600); //Initializing the Serial Port to Baud rate 9600
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  //Print the received data
  Serial.print("Intensity: ");
  Serial.println(sensorValue);
  delay(1000);
}
