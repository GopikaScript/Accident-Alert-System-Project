#include <SoftwareSerial.h>

SoftwareSerial gsm(7, 8); // RX, TX for GSM module

const int accidentSensor = 2; // Connect vibration sensor or button to pin 2
bool accidentDetected = false;

void setup() {
  pinMode(accidentSensor, INPUT);
  gsm.begin(9600);     // Start GSM module serial
  Serial.begin(9600);  // Debug serial

  delay(1000);
  Serial.println("System Initializing...");
  gsm.println("AT");   // GSM Test
  delay(1000);
  gsm.println("AT+CMGF=1"); // Set SMS to Text Mode
  delay(1000);
}

void loop() {
  int sensorValue = digitalRead(accidentSensor);

  if (sensorValue == HIGH && !accidentDetected) {
    accidentDetected = true;

    Serial.println("Accident Detected!");
    sendSMS();
    delay(5000); // Wait to avoid repeated messages
  }

  if (sensorValue == LOW) {
    accidentDetected = false; // Reset if no accident
  }
}

void sendSMS() {
  gsm.println("AT+CMGS=\"+911234567890\""); // Replace with emergency number
  delay(1000);
  gsm.println("Accident Detected! Please respond immediately. Location: [Insert GPS if available]");
  delay(100);
  gsm.write(26); // CTRL+Z to send the message
  Serial.println("SMS Sent.");
}