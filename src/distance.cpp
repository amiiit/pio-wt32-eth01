#include <Arduino_ESP32_OTA.h>

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

double measureDistance(int trigPin, int echoPin) {
  // Clears the trigPin
  // digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);

  Serial.print("Duration ");
  Serial.println(duration);


  // // Calculate the distance
  double distanceCm = duration * SOUND_SPEED / 2;

  // // Convert to inches
  double distanceInch = distanceCm * CM_TO_INCH;

  // // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  
  return distanceCm;
}