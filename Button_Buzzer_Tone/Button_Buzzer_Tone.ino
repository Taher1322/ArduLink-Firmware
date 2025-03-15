/*
  Multiple tone player

  Plays multiple tones on multiple pins in sequence

  circuit:
  - three 8 ohm speakers on digital pins 6, 7, and 8

  created 8 Mar 2010
  by Tom Igoe
  based on a snippet from Greg Borenstein

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMultiple
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 9;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (buttonState)
  {
    Serial.println("Button Pressed ");
    // turn off tone function for pin 8:
    noTone(5);
    // play a note on pin 6 for 200 ms:
    tone(5, 440, 200);
    delay(200);

    // turn off tone function for pin 6:
    noTone(5);
    // play a note on pin 7 for 500 ms:
    tone(5, 494, 500);
    delay(500);

    // turn off tone function for pin 7:
    noTone(5);
    // play a note on pin 8 for 300 ms:
    tone(5, 523, 300);
    delay(300);
  }
}
