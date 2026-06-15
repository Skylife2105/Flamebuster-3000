#include <SCServo.h>

// Pins definieren (Verbinde diese mit dem Bus Servo Adapter)
#define RX_PIN 16 // Verbinde mit TX des Adapters
#define TX_PIN 17 // Verbinde mit RX des Adapters

SMS_STS myservo; 

void setup() {
  Serial.begin(115200);
  Serial2.begin(1000000, SERIAL_8N1, RX_PIN, TX_PIN);
  myservo.pSerial = &Serial2;

  // Aktiviere Drehmoment für die ersten drei Gelenke
  for(int i = 1; i <= 3; i++) {
    myservo.EnableTorque(i, 1);
  }
  
  Serial.println("System bereit. Drehmoment für ID 1, 2 und 3 aktiviert.");
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read(); 
    
    // Servo 1
    if (cmd == '1') myservo.WritePosEx(1, 2047, 1000, 50);
    if (cmd == '2') myservo.WritePosEx(1, 1000, 1000, 50);
    
    // Servo 2
    if (cmd == '3') myservo.WritePosEx(2, 2047, 1000, 50);
    if (cmd == '4') myservo.WritePosEx(2, 1000, 1000, 50);
    
    // Servo 3
    if (cmd == '5') myservo.WritePosEx(3, 2047, 1000, 50);
    if (cmd == '6') myservo.WritePosEx(3, 1000, 1000, 50);
    
    // Neuer Servo 4
    if (cmd == '7') {
      Serial.println("Bewege Servo 4 auf Position 2047");
      myservo.WritePosEx(4, 1000, 1000, 50);
    }
    if (cmd == '8') {
      Serial.println("Bewege Servo 4 auf Position 1000");
      myservo.WritePosEx(4, 2047, 1000, 50);
    }
  }
}