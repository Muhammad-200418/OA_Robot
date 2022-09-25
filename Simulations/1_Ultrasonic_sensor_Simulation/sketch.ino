// Includeing Libraries
#include "NewPing.h"

// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
//Defining Triggers/Echo pins for sonars
#define Left_Trigger_Pin A14
#define Left_Echo_Pin A15

#define Cen_Left_Trigger_Pin A14
#define Cen_Left_Echo_Pin A15

#define Cen_Trigger_Pin 22
#define Cen_Echo_Pin A1

#define Cen_Right_Trigger_Pin A14
#define Cen_Right_Echo_Pin A15

#define Right_Trigger_Pin A14
#define Right_Echo_Pin A15

// Maximum distance we want to ping for (in centimeters).
#define Max_Distance 300	

// NewPing setup of pins and maximum distance.
NewPing Left_Sonar(Left_Trigger_Pin, Left_Echo_Pin, Max_Distance);
NewPing Cen_Left_Sonar(Cen_Left_Trigger_Pin, Cen_Left_Echo_Pin, Max_Distance);
NewPing Cen_Sonar(Cen_Trigger_Pin, Cen_Echo_Pin, Max_Distance);
NewPing Cen_Right_Sonar(Cen_Right_Trigger_Pin, Cen_Right_Echo_Pin, Max_Distance);
NewPing Right_Sonar(Right_Trigger_Pin, Right_Echo_Pin, Max_Distance);


void setup() {
	Serial.begin(9600);
}

void loop() {
  Cen_sonar_ping();
}
void Left_sonar_ping() {
  Serial.print("This is the left Sonar. Distance = ");
	Serial.print(Left_Sonar.ping_cm());
	Serial.println(" cm");
	delay(500);
}
void Cen_Left_sonar_ping() {
  Serial.print("This is the Center left Sonar. Distance = ");
	Serial.print(Cen_Left_Sonar.ping_cm());
	Serial.println(" cm");
	delay(500);
}
void Cen_sonar_ping() {
  Serial.print("This is the Cenetr Sonar. Distance = ");
	Serial.print(Cen_Sonar.ping_cm());
	Serial.println(" cm");
	delay(10);
}
void Cen_Right_sonar_ping() {
  Serial.print("This is the Center Right Sonar. Distance = ");
	Serial.print(Cen_Right_Sonar.ping_cm());
	Serial.println(" cm");
	delay(500);
}
void Right_sonar_ping() {
  Serial.print("This is the Right Sonar. Distance = ");
	Serial.print(Right_Sonar.ping_cm());
	Serial.println(" cm");
	delay(500);
}

