/*
 * Steuerung für Feuerlöschroboter:
 * - Taster: Start (Kickstart + Dauerlauf) / Stopp
 * - Potentiometer: Dynamische Leistungsregelung (0-100%)
 */

const int buttonPin = 4;      // Taster an GPIO 4
const int potPin = 1;        // Potentiometer an GPIO 1
const int motorPinRPWM = 2;   // RPWM an GPIO 2

bool isRunning = false;       // Status der Pumpe
bool lastButtonState = HIGH;  // Für Taster-Entprellung

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  ledcAttach(motorPinRPWM, 5000, 8);
  ledcWrite(motorPinRPWM, 0);
}

void loop() {
  // 1. Taster lesen (mit einfacher Entprellung)
  bool currentButtonState = digitalRead(buttonPin);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isRunning = !isRunning; // Toggle Status
    delay(50); // Entprellung
    
    if (isRunning) {
      // Kickstart beim Einschalten
      ledcWrite(motorPinRPWM, 255);
      delay(500);
    } else {
      ledcWrite(motorPinRPWM, 0); // Stoppen
    }
  }
  lastButtonState = currentButtonState;

  // 2. Pumpe steuern (wenn an)
  if (isRunning) {
    // Potentiometer lesen (0-4095) und auf PWM-Bereich (0-255) umrechnen
    int potValue = analogRead(potPin);
    int speed = map(potValue, 0, 4095, 0, 255);
    
    // Untergrenze: Falls das Poti auf 0 steht, aber Pumpe laufen soll,
    // sorgen wir für einen Mindestwert zum Drehen (z.B. 40)
    if (speed < 40) speed = 40; 
    
    ledcWrite(motorPinRPWM, speed);
  }
}