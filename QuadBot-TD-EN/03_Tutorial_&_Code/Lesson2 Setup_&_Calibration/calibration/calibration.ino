// Locate the initial position of legs 
// RegisHsu 2015-09-09

#include <ESP32Servo.h>  

Servo servo[12];

//define servos' ports
const int servo_pin[12] = {18,  5, 19, 2,  4, 15, 33, 25, 32, 27, 14, 13};
const int offset[4][3] =    {{ 3,  10,  11}, { 10,  10,  5}, { 0,  0,  0}, { -5,  5, 5}};

void setup()
{
  Serial.begin(9600);
  //initialize all servos
  for (int i = 0; i < 12; i++)
  {
      servo[i].attach(servo_pin[i], 500, 2500);
      delay(20);
  }
  for (int i = 0; i < 12; i++)
  {
      servo[i].write(90);
      delay(20);
  }
}

void loop(void)
{
  while(Serial.available() > 0)
  {
    char command = Serial.read();
    // SERVO Set command
    if ( command == 'S' || command == 's' )  // 'S' is Servo Command "S,Servo_no,Angle"
    {
      Serial.print(command);
      Serial.print(',');
      int servoNo = Serial.parseInt();
      Serial.print(servoNo);
      Serial.print(',');
      int servoAngle = Serial.parseInt();
      Serial.print(servoAngle);
      Serial.println();

//      if ( 0 <= servoNo &&  servoNo < MAX_SERVO_NUM+1 )
      {
        // Single Servo Move
        servo[servoNo].write(90+servoAngle);

        // Wait Servo Move
        delay(300); // 180/60(°/100msec）=300(msec)
      }
    }  // SERVO Set END  
  }
}
