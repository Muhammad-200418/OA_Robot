/*
  :Version 1.0
  :Author: Shahzaib Ali
  :Date: 03/10/2022
*/

// 1>.Vcc provides power for the module
// 2>.Ground
// 3>.SCL used for providing clock pulse for I2C Communication
// 4>.SDA used for transferring Data through I2C communication
// 5>.XDA optional SDA pin
// 6>.XCL optional SCL pin
// 7>.INT interrupt pin

#include <basicMPU6050.h> 

basicMPU6050<> imu;

struct GyroResult{
  float X;
  float Y;
  float Z;
};

void setup() {
  // Set registers - Always required
  imu.setup();

  // Initial calibration of gyro
  imu.setBias();

  // Start console
  Serial.begin(38400);
}

void loop() {
   // Update gyro calibration 
  imu.updateBias();
 
  //-- Scaled and calibrated output:  
  
  GyroResult res = readValues();
  Serial.println("X: "+String(res.X));
  Serial.println("Y: "+String(res.Y));
  Serial.println("Z: "+String(res.Z));
  // Serial.println(imu.temp());

};

GyroResult readValues(){  
  GyroResult result = {imu.gx(),imu.gy(),imu.gz()};
  return result;
}

// serial print variable type lol for debugging like a pro
void types(String a) { Serial.println("it's a String"); }
void types(int a) { Serial.println("it's an int"); }
void types(char *a) { Serial.println("it's a char*"); }
void types(float a) { Serial.println("it's a float"); }
void types(bool a) { Serial.println("it's a bool"); }