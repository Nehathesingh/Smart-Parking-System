#include <ESP8266WiFi.h>

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
#define US_TO_HOUR 3600000000
#define PARKING_CHARGE_PER_HOUR 50

const int trigPin_1 = 5;
const int echoPin_1 = 4;
const int trigPin_2 = 12;
const int echoPin_2 = 14;

long duration_1;
float distanceCm_1;
float distanceInch_1;
long duration_2;
float distanceCm_2;
float distanceInch_2;

float start_time_1 = -1;
float end_time_1;
float interval_1;
float cost_1;
float start_time_2 = -1;
float end_time_2;
float interval_2;
float cost_2;

void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(trigPin_1, OUTPUT); // Sets the trigPin as an Output
  pinMode(trigPin_2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin_1, INPUT);
  pinMode(echoPin_2, INPUT); // Sets the echoPin as an Input
}

void loop() {
  Serial.println("Hello");
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  duration_1 = pulseIn(echoPin_1, HIGH);

  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  duration_2 = pulseIn(echoPin_2, HIGH);

  distanceCm_1 = duration_1 * SOUND_VELOCITY/2;
  distanceCm_2 = duration_2 * SOUND_VELOCITY/2;

  if(distanceCm_1>20){
    if(start_time_1 != -1){
        end_time_1 = millis();
        interval_1 = (end_time_1-start_time_1)/US_TO_HOUR;
        cost_1 = interval_1*PARKING_CHARGE_PER_HOUR;
        Serial.print("Slot 1 charge: Rs. ");
        Serial.println(cost_1);
        start_time_1 = -1;
    }
    Serial.println("Slot 1 is empty");
  }else{
    Serial.println("Slot 1 is occupied.");
    if(start_time_1 == -1){
        start_time_1 = millis();
    }
  }
  if(distanceCm_2>20){
    if(start_time_2 != -1){
        end_time_2 = millis();
        interval_2 = (end_time_2-start_time_2)/US_TO_HOUR;
        cost_2 = interval_2*PARKING_CHARGE_PER_HOUR;
        Serial.print("Slot 2 charge: Rs. ");
        Serial.println(cost_2);
        start_time_2 = -1;
    }
    Serial.println("Slot 2 is empty");
  }else{
    Serial.println("Slot 2 is occupied.");
    if(start_time_2 == -1){
        start_time_2 = millis();
    }
  }
 
  delay(1000);
}