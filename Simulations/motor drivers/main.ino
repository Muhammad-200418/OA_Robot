/*
    Currently Pins are set to random 
    which will be configured after
    running some tests
*/

// 1 Forward Motor
int MOTORA = 9;        // speed control
int MOTORA_IN1 = 8; // spin dir
int MOTORA_IN2 = 7; // spin dir

// 2 Forward Motor
int MOTORA2 = 10;
int MOTORA2_IN1 = 1;
int MOTORA2_IN2 = 2;

// 1 Backward Motor
int MOTORB = 3;        // speed control 
int MOTORB_IN1 = 5; // spin dir
int MOTORB_IN2 = 4; // spin dir

// 2 Backward Motor
int MOTORB2 = 4;
int MOTORB2_IN1 = 11;
int MOTORB2_IN2 = 12;

void setMotorPins()
{
    pinMode(MOTORA, OUTPUT);
    pinMode(MOTORA2, OUTPUT);
    pinMode(MOTORB, OUTPUT);
    pinMode(MOTORB2, OUTPUT);

    pinMode(MOTORA_IN1, OUTPUT);
    pinMode(MOTORA_IN2, OUTPUT);
    pinMode(MOTORA2_IN1, OUTPUT);
    pinMode(MOTORA2_IN2, OUTPUT);

    pinMode(MOTORB_IN1, OUTPUT);
    pinMode(MOTORB_IN2, OUTPUT);
    pinMode(MOTORB2_IN1, OUTPUT);
    pinMode(MOTORB2_IN2, OUTPUT);

    // by default they are set to low
}

void turnOnAllMotors(int speed, bool forward){
    if(speed<0 || speed > 255){
        return
    }

    analogWrite(MOTORA, speed);
    analogWrite(MOTORA2, speed);
	analogWrite(MOTORB, speed);
    analogWrite(MOTORB2, speed);
    if(forward){
        digitalWrite(MOTORA_IN1, HIGH);
	    digitalWrite(MOTORA_IN2, LOW);
        digitalWrite(MOTORA2_IN1, HIGH);
	    digitalWrite(MOTORA2_IN2, LOW);

	    digitalWrite(MOTORB_IN1, HIGH);
	    digitalWrite(MOTORB_IN2, LOW);
        digitalWrite(MOTORB2_IN1, HIGH);
	    digitalWrite(MOTORB2_IN2, LOW);
        return;
    }
    digitalWrite(MOTORA_IN1, LOW);
    digitalWrite(MOTORA_IN2, HIGH);
    digitalWrite(MOTORA2_IN1, LOW);
    digitalWrite(MOTORA2_IN2, HIGH);

    digitalWrite(MOTORB_IN1, LOW);
    digitalWrite(MOTORB_IN2, HIGH);
    digitalWrite(MOTORB2_IN1, LOW);
    digitalWrite(MOTORB2_IN2, HIGH);
    return;
}

void turnOnMotor(bool motorB, int speed, bool forward)
{
    if(speed<0 || speed > 255){
        return
    }
    if (motorB)
    {
        analogWrite(MOTORB, speed); // set peed
        analogWrite(MOTORB2, speed);
        if (forward)
        {
            // 3 high 4 low
            digitalWrite(MOTORB_IN1, HIGH);
            digitalWrite(MOTORB_IN2, LOW);
            digitalWrite(MOTORB2_IN1, HIGH);
            digitalWrite(MOTORB2_IN2, LOW);            
            return;
        }
        digitalWrite(MOTORB_IN1, LOW);
        digitalWrite(MOTORB_IN2, HIGH);
        digitalWrite(MOTORB2_IN1, LOW);
        digitalWrite(MOTORB2_IN2, HIGH);
        return;
    }
    analogWrite(MOTORA, speed);
    analogWrite(MOTORA2, speed);
    if (forward)
    {
        digitalWrite(MOTORA_IN1, HIGH);
        digitalWrite(MOTORA_IN2, LOW);
        digitalWrite(MOTORA2_IN1, HIGH);
        digitalWrite(MOTORA2_IN2, LOW); 
        return;
    }
    digitalWrite(MOTORA_IN1, LOW);
    digitalWrite(MOTORA_IN2, HIGH);
    digitalWrite(MOTORA2_IN1, HIGH);
    digitalWrite(MOTORA2_IN2, LOW); 
    return;
}

void setup()
{
    setMotorPins(); // sets up pins once
}

void loop()
{
    turnOnMotor(true, 255, true); // test

}