
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
 
float left_distance_final;
float cenleft_distance_final;
float cen_distance_final;
float cenright_distance_final;
float right_distance_final;
int count;
// int us_distance[5];
int sensors_reading[5];

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

  // int us_distance[5] = {us_sensors()};
  // Serial.print(us_distance[1]);
  us_sensors();
  for(int i=0; i <5; i++){
    Serial.print(sensors_reading[i]);
    Serial.print(" ");
  }
}
 
int us_sensors() {
  for (int iter = 0; iter< 31; iter++) {
    // Serial.print(iter);
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
          left_distance_final = left_distance_final + left_distance;

          digitalWrite(cenlefttrigPin, LOW);
          cenleft_time = pulseIn(cenleftechoPin, HIGH);
          cenleft_distance = cenleft_time * 0.034/2;
          cenleft_distance_final = cenleft_distance_final + cenleft_distance;

          digitalWrite(centrigPin, LOW);
          cen_time = pulseIn(cenechoPin, HIGH);
          cen_distance = cen_time * 0.034/2;
          cen_distance_final = cen_distance_final + cen_distance;

          digitalWrite(cenrighttrigPin, LOW);
          cenright_time = pulseIn(cenrightechoPin, HIGH);
          cenright_distance = cenright_time * 0.034/2;
          cenright_distance_final = cenright_distance_final + cenright_distance;

          digitalWrite(righttrigPin, LOW);
          right_time = pulseIn(rightechoPin, HIGH);
          right_distance = right_time * 0.034/2;
          right_distance_final = right_distance_final + right_distance;


          count = count + 1;
          /*
            distance = time * speed of sound
            speed of sound is 340 m/s => 0.034 cm/us
          */
          // Serial.print("Average Distance of left sensor is: ");
          // Serial.print(left_distance_final/count);
          // Serial.println(" cm, Left sensor"); 
          
          // Serial.print("Average Distance of cenleft_distance is: ");
          // Serial.print(cenleft_distance_final/count);
          // Serial.println(" cm, Center Left sensor"); 

          // Serial.print("Average Distance of cen_distance_final sensor is: ");
          // Serial.print(cen_distance_final/count);
          // Serial.println(" cm, Center sensor"); 

          // Serial.print("Average Distance of cen right sensor is: ");
          // Serial.print(cenright_distance_final/count);
          // Serial.println(" cm, Center Right sensor"); 

          // Serial.print("Average Distance of right_distance_final sensor is: ");
          // Serial.print(right_distance_final/count);
          // Serial.println(" cm, Right sensor"); 

          // Serial.print("Distance: ");
          // Serial.print(left_distance);
          // Serial.println(" cm, Left sensor");

          // Serial.print("Distance: ");
          // Serial.print(cenleft_distance);
          // Serial.println(" cm, Center Left sensor");

          // Serial.print("Distance: ");
          // Serial.print(cen_distance);
          // Serial.println(" cm, Center sensor");

          // Serial.print("Distance: ");
          // Serial.print(cenright_distance);
          // Serial.println(" cm, Center Right sensor");
          
          // Serial.print("Distance: ");
          // Serial.print(right_distance);
          // Serial.println(" cm, Right sensor");
          _sensorState = TRIG_LOW;
        } break;
        
    }//end switch
  
  }//end loop
  // sensors_reading[5] = {left_distance_final/count,cenleft_distance_final/count,cen_distance_final/count,,};
  sensors_reading[0] = left_distance_final/count;
  sensors_reading[1] = cenleft_distance_final/count;
  sensors_reading[2] = cen_distance_final/count;
  sensors_reading[3] = cenright_distance_final/count;
  sensors_reading[4] = right_distance_final/count;

  left_distance_final = 0;

  cenleft_distance_final = 0;

  cen_distance_final = 0;

  cenright_distance_final = 0;

  right_distance_final = 0;

  count = 0;

  
  // return &sensors_reading;
}

void loop(){
  us_sensors();
  for(int i=0; i <5; i++){
    Serial.print(sensors_reading[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
}

