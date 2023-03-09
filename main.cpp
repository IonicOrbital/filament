#include <Arduino.h>

const float PI = 3.14159;
const float MIN_RADIUS = 1.75;
const float MEDIUM_RADIUS = 2.85;
const float MAX_RADIUS = 3.0;

const int EXTRUDER_PIN = 3;
const int SENSOR_PIN = A0;

void setup() {
  pinMode(EXTRUDER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  float radius = analogRead(SENSOR_PIN) * 5.0 / 1024.0; // convert sensor reading to voltage
  radius = radius * 3.3 / 5.0; // convert voltage to radius (assuming linear relationship)
  
  float length = 100.0; // example length in mm
  float volume = PI * radius * radius * length;

  float speed;
  if (radius <= MIN_RADIUS) {
    speed = 20.0; // mm/s
  } else if (radius <= MEDIUM_RADIUS) {
    speed = 15.0; // mm/s
  } else {
    speed = 10.0; // mm/s
  }

  float time = volume / speed;

  analogWrite(EXTRUDER_PIN, 255); // start extruding
  delay(time * 1000); // wait for extrusion to finish
  analogWrite(EXTRUDER_PIN, 0); // stop extruding

  Serial.print("Radius: ");
  Serial.print(radius);
  Serial.print(" mm, Volume: ");
  Serial.print(volume);
  Serial.print(" mm^3, Speed: ");
  Serial.print(speed);
  Serial.print(" mm/s, Time: ");
  Serial.print(time);
  Serial.println(" s");

  delay(500); // wait before taking next reading
}

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}
