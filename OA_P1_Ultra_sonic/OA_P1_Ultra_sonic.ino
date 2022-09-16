
/*
  :Version 1.0
  :Author: Dragos Calin
  :Email: dragos@intorobotics.com
  :License: BSD
  :Date: 06/04/2020
*/
 
/*define the sensor's pins*/
uint8_t lefttrigPin = 53;
uint8_t leftechoPin = A0;

uint8_t cenlefttrigPin = 51;
uint8_t cenleftechoPin = A1;

uint8_t centrigPin = 49;
uint8_t cenechoPin = A2;

uint8_t cenrighttrigPin = 47;
uint8_t cenrightechoPin = A3;

uint8_t righttrigPin = 45;
uint8_t rightechoPin = A4;
 
unsigned long timerStart = 0;
int TIMER_TRIGGER_HIGH = 10;
int TIMER_LOW_HIGH = 2;
 
float left_time;
float cenleft_time;
float cen_time;
float cenright_time;
float right_time;

float left_distance;
float cenleft_distance;
float cen_distance;
float cenright_distance;
float right_distance;
 
/*The states of an ultrasonic sensor*/
enum SensorStates {
  TRIG_LOW,
  TRIG_HIGH,
  ECHO_HIGH
};
 
SensorStates _sensorState = TRIG_LOW;
 
void startTimer() {
  timerStart = millis();
}
 
bool isTimerReady(int mSec) {
  return (millis() - timerStart) < mSec;
}
 
/*Sets the data rate in bits per second and configures the pins */
void setup() {
  Serial.begin(9600);
  pinMode(lefttrigPin, OUTPUT);
  pinMode(leftechoPin, INPUT);

  pinMode(cenlefttrigPin, OUTPUT);
  pinMode(cenleftechoPin, INPUT);
  
  pinMode(centrigPin, OUTPUT);
  pinMode(cenechoPin, INPUT);
  
  pinMode(cenrighttrigPin, OUTPUT);
  pinMode(cenrightechoPin, INPUT);
  
  pinMode(righttrigPin, OUTPUT);
  pinMode(rightechoPin, INPUT);
}
 
void loop() {
 
  /*Switch between the ultrasonic sensor states*/
  switch (_sensorState) {
    /* Start with LOW pulse to ensure a clean HIGH pulse*/
    case TRIG_LOW: {
        digitalWrite(lefttrigPin, LOW);
        digitalWrite(cenlefttrigPin, LOW);
        digitalWrite(centrigPin, LOW);
        digitalWrite(cenrighttrigPin, LOW);
        digitalWrite(righttrigPin, LOW);

        startTimer();
        if (isTimerReady(TIMER_LOW_HIGH)) {
          _sensorState = TRIG_HIGH;
        }
      } break;
      
    /*Triggered a HIGH pulse of 10 microseconds*/
    case TRIG_HIGH: {
        digitalWrite(lefttrigPin, HIGH);
        digitalWrite(cenlefttrigPin, HIGH);
        digitalWrite(centrigPin, HIGH);
        digitalWrite(cenrighttrigPin, HIGH);
        digitalWrite(righttrigPin, HIGH);
        startTimer();
        if (isTimerReady(TIMER_TRIGGER_HIGH)) {
          _sensorState = ECHO_HIGH;
        }
      } break;
 
    /*Measures the time that ping took to return to the receiver.*/
    case ECHO_HIGH: {
        digitalWrite(lefttrigPin, LOW);
        left_time = pulseIn(leftechoPin, HIGH);
        left_distance = left_time * 0.034/2;

        digitalWrite(cenlefttrigPin, LOW);
        cenleft_time = pulseIn(cenleftechoPin, HIGH);
        cenleft_distance = cenleft_time * 0.034/2;

        digitalWrite(centrigPin, LOW);
        cen_time = pulseIn(cenechoPin, HIGH);
        cen_distance = cen_time * 0.034/2;

        digitalWrite(cenrighttrigPin, LOW);
        cenright_time = pulseIn(cenrightechoPin, HIGH);
        cenright_distance = cenright_time * 0.034/2;

        digitalWrite(righttrigPin, LOW);
        right_time = pulseIn(rightechoPin, HIGH);
        right_distance = right_time * 0.034/2;
        /*
           distance = time * speed of sound
           speed of sound is 340 m/s => 0.034 cm/us
        */
        Serial.print("Distance: ");
        Serial.print(left_distance);
        Serial.println(" cm, Left sensor");

        Serial.print("Distance: ");
        Serial.print(cenleft_distance);
        Serial.println(" cm, Center Left sensor");

        Serial.print("Distance: ");
        Serial.print(cen_distance);
        Serial.println(" cm, Center sensor");

        Serial.print("Distance: ");
        Serial.print(cenright_distance);
        Serial.println(" cm, Center Right sensor");
        
        Serial.print("Distance: ");
        Serial.print(right_distance);
        Serial.println(" cm, Right sensor");


        _sensorState = TRIG_LOW;
      } break;
      
  }//end switch
  
}//end loop