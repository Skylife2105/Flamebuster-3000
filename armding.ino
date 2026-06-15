#include <SCServo.h>
#include <ESP32Servo.h>

#define RX_PIN 16
#define TX_PIN 17
#define SPRAY_SERVO_PIN 2

SMS_STS myservo; 
Servo mySprayServo;

void setup() {
  Serial.begin(115200);
  Serial2.begin(1000000, SERIAL_8N1, RX_PIN, TX_PIN);
  myservo.pSerial = &Serial2;

  for(int i = 1; i <= 4; i++) {
    myservo.EnableTorque(i, 1);
  }

  mySprayServo.setPeriodHertz(50);
  mySprayServo.attach(SPRAY_SERVO_PIN, 500, 2400);
  mySprayServo.write(90); 
  
  Serial.println("System bereit. Drücke 'H' für Startposition (Home).");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read(); 
    
    // --- Arm-Steuerung ---
    if (cmd == '1') myservo.WritePosEx(1, 2047, 1000, 50);
    if (cmd == '2') myservo.WritePosEx(1, 1000, 1000, 50);
    if (cmd == '3') myservo.WritePosEx(2, 2047, 1000, 50);
    if (cmd == '4') myservo.WritePosEx(2, 1000, 1000, 50);
    if (cmd == '5') myservo.WritePosEx(3, 2047, 1000, 50);
    if (cmd == '6') myservo.WritePosEx(3, 1000, 1000, 50);
    if (cmd == '7') myservo.WritePosEx(4, 2047, 1000, 50);
    if (cmd == '8') myservo.WritePosEx(4, 1000, 1000, 50);
    
    // --- Düsen-Steuerung ---
    if (cmd == '9') mySprayServo.write(0);
    if (cmd == '0') mySprayServo.write(180);

    // --- Home-Position (Taste H) ---
    if (cmd == 'H' || cmd == 'h') {
      Serial.println("Fahre in Startposition...");
      // Alle Servos auf Mittelstellung (2047)
      myservo.WritePosEx(1, 2047, 1000, 50);
      myservo.WritePosEx(2, 2047, 1000, 50);
      myservo.WritePosEx(3, 2047, 1000, 50);
      myservo.WritePosEx(4, 2047, 1000, 50);
      mySprayServo.write(90); // Düse auf Mitte
    }
  }
}