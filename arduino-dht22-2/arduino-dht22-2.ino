// This sketch started as an Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// Modified (with new behavior) by John M. Wargo

#include "DHT.h"

#define DHTPIN 2 // The pin the sensor is connected to
#define LEDPIN 3 // the pin the LED is connected to

// Uncomment the line for the specific hardware you're using
// commenting out the remaining lines
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// constants used to determine the trigger direction
// greater or less than the trigger value
const int LESS_THAN = 0;
const int GREATER_THAN = 1;

// set this value to the temperature you want to
// trigger the LED on/off
const int TRIGGER_TEMP = 72; // Degrees F
// Trigger direction: trigger the LED when the temp is...
const int TRIGGER_DIRECTION = GREATER_THAN;
//const int TRIGGER_DIRECTION = LESS_THAN;
// Valid options are GREATER_THAN or LESS_THAN

// Create DHT sensor object for the specific hardware
// configuration we're using
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // initialize the serial communication link between the
  // Arduino device and the computer system running the Serial Monitor
  Serial.begin(9600);
  Serial.println("DHT Temperature Monitor");

  Serial.println("Validating sketch configuration");
  // check to make sure trigger direction is a valid value
  if ((TRIGGER_DIRECTION < LESS_THAN) || (TRIGGER_DIRECTION > GREATER_THAN)) {
    Serial.println("Invalid value for TRIGGER_DIRECTION, please fix the sketch and try again");
    // The code is broken, so loop infinitely
    while (true);
    // the sketch gets stuck here, and never blinks the LED.
  }
  Serial.println("Configuration validated");

  // configure the LED pin for output mode
  pinMode(LEDPIN, OUTPUT);

  // Initialize the dht object
  dht.begin();

  // blink the LED twice so you can tell the sketch is working.
  blinkLED(2, 250);
}

void loop() {

  // Wait two seconds between measurements
  delay(2000);

  // ==========================================================================
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // ==========================================================================

  // Read temperature in degrees Fahrenheit
  float currTemp = dht.readTemperature(true);
  // To work in degrees Celsius, do the following:
  //float currTemp = dht.readTemperature(false);
  // or you can use this alternate method:
  //float currTemp = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(currTemp);
  Serial.println(" degrees");

  // Make sure the sketch was able to read values 
  // from the sensor before continuing. 
  // The return exits the loop (try again)
  if (isnan(currTemp))  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // If we got here, we've got a valid temp reading, 
  // so we can do something with it.
  if (TRIGGER_DIRECTION < GREATER_THAN) {
    // Then we're doing a less than option, so check to
    // see if the current temp is less than the trigger temp and 
    // write the appropriate value to the output pin
    digitalWrite(LEDPIN, (currTemp < TRIGGER_TEMP) ? HIGH : LOW);
  } else {
    // Otherwise, we're doing a greater than option, so check to
    // see if the current temp is greater than the trigger temp and
    // write the appropriate value to the output pin
    digitalWrite(LEDPIN, (currTemp > TRIGGER_TEMP) ? HIGH : LOW);
  }

}

void blinkLED(int loopCount, int duration) {
  for (int i = 1; i <= loopCount; i++) {
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LEDPIN, HIGH);
    // wait for a duration milliseconds
    delay(duration);
    // turn the LED off by making the voltage LOW
    digitalWrite(LEDPIN, LOW);
    // wait for a duration milliseconds
    delay(duration);
  }
}
