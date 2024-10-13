#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;
const int relayPin = 13; // Pin where the relay is connected

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Ensure relay pin is set as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
    // Set the time and date(YYYY, MM, DD, HH, MM, SS)
  rtc.adjust(DateTime(2024, 6, 28,13, 20, 00));
  
  Serial.println("RTC setup complete");
}

void loop() {
  DateTime now = rtc.now();

  // Print time and date for debugging purposes
  Serial.print("Current Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" Date: ");
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.year(), DEC);

  // Check if current time matches the trigger times
  if (now.hour() == 11 && now.minute() == 00 && now.second() == 10) {
    digitalWrite(relayPin, LOW); // Turn on the relay
    Serial.println("Relay ON");
  }
  
  if (now.hour() == 11 && now.minute() == 00 && now.second() == 20) {
    digitalWrite(relayPin, HIGH); // Turn off the relay
    Serial.println("Relay OFF");
  }

  delay(1000);  // Delay 1 second between readings
}
