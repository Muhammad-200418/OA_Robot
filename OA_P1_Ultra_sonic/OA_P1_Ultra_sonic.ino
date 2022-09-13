// // Includeing Libraries
// #include "NewPing.h"

// // Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
// //Defining Triggers/Echo pins for sonars
// #define Left_Trigger_Pin A14
// #define Left_Echo_Pin A15

// #define Cen_Left_Trigger_Pin A14
// #define Cen_Left_Echo_Pin A15

// #define Cen_Trigger_Pin A14
// #define Cen_Echo_Pin A15

// #define Cen_Right_Trigger_Pin A14
// #define Cen_Right_Echo_Pin A15

// #define Right_Trigger_Pin A14
// #define Right_Echo_Pin A15

// // Maximum distance we want to ping for (in centimeters).
// #define Max_Distance 100	

// // NewPing setup of pins and maximum distance.
// NewPing Left_Sonar(Left_Trigger_Pin, Left_Echo_Pin, Max_Distance);
// NewPing Cen_Left_Sonar(Cen_Left_Trigger_Pin, Cen_Left_Echo_Pin, Max_Distance);
// NewPing Cen_Sonar(Cen_Trigger_Pin, Cen_Echo_Pin, Max_Distance);
// NewPing Cen_Right_Sonar(Cen_Right_Trigger_Pin, Cen_Right_Echo_Pin, Max_Distance);
// NewPing Right_Sonar(Right_Trigger_Pin, Right_Echo_Pin, Max_Distance);


// void setup() {
// 	Serial.begin(9600);
// }

// void loop() {
// 	// Serial.print("Distance = ");
// 	// Serial.print(sonar.ping_cm());
// 	// Serial.println(" cm");
// 	// delay(500);
// }
// void Left_sonar_ping() {
//   Serial.print("This is the left Sonar. Distance = ");
// 	Serial.print(Left_Sonar.ping_cm());
// 	Serial.println(" cm");
// 	delay(500);
// }
// void Cen_Left_sonar_ping() {
//   Serial.print("This is the Center left Sonar. Distance = ");
// 	Serial.print(Cen_Left_Sonar.ping_cm());
// 	Serial.println(" cm");
// 	delay(500);
// }
// void Cen_sonar_ping() {
//   Serial.print("This is the Cenetr Sonar. Distance = ");
// 	Serial.print(Cen_Sonar.ping_cm());
// 	Serial.println(" cm");
// 	delay(500);
// }
// void Cen_Right_sonar_ping() {
//   Serial.print("This is the Center Right Sonar. Distance = ");
// 	Serial.print(Cen_Right_Sonar.ping_cm());
// 	Serial.println(" cm");
// 	delay(500);
// }
// void Right_sonar_ping() {
//   Serial.print("This is the Right Sonar. Distance = ");
// 	Serial.print(Right_Sonar.ping_cm());
// 	Serial.println(" cm");
// 	delay(500);
// }

// This Is the old code. Sensors failed to operate normally once installed.
// Therfore we are going to switch to a new code ofund on the internet.

/*
  :Version 1.0
  :Author: Dragos Calin
  :Email: dragos@intorobotics.com
  :License: BSD
  :Date: 06/04/2020
*/
 
 
/*define the sensor's pins*/
uint8_t trigPin = 3;
uint8_t echoPin = 2;
 
unsigned long timerStart = 0;
int TIMER_TRIGGER_HIGH = 10;
int TIMER_LOW_HIGH = 2;
 
float timeDuration, distance;
 
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
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
 
  /*Switch between the ultrasonic sensor states*/
  switch (_sensorState) {
    /* Start with LOW pulse to ensure a clean HIGH pulse*/
    case TRIG_LOW: {
        digitalWrite(trigPin, LOW);
        startTimer();
        if (isTimerReady(TIMER_LOW_HIGH)) {
          _sensorState = TRIG_HIGH;
        }
      } break;
      
    /*Triggered a HIGH pulse of 10 microseconds*/
    case TRIG_HIGH: {
        digitalWrite(trigPin, HIGH);
        startTimer();
        if (isTimerReady(TIMER_TRIGGER_HIGH)) {
          _sensorState = ECHO_HIGH;
        }
      } break;
 
    /*Measures the time that ping took to return to the receiver.*/
    case ECHO_HIGH: {
        digitalWrite(trigPin, LOW);
        timeDuration = pulseIn(echoPin, HIGH);
        /*
           distance = time * speed of sound
           speed of sound is 340 m/s => 0.034 cm/us
        */
        Serial.print("Distance measured is: ");
        Serial.print(timeDuration * 0.034 / 2);
        Serial.println(" cm");
        _sensorState = TRIG_LOW;
      } break;
      
  }//end switch
  
}//end loop