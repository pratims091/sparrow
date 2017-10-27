/*Sparrow 1.2(An autonomous obstacle avoider) Build by Pratim Sarangi, 2014*/

#include <Servo.h> //Include the servo library to use the head servo
#include <NewPing.h>//Include the NewPing library to use the US HC SR-04

#define USTrigger 8//Ultra sonic trigger pin
#define USEcho 9//Ultra sonic echo pin
#define MaxDistance 200 //Maximum distance to be measure by the ultra sonic senesor

int LeftMotorForward = 2;//Pin A1 of L293D motor driver board to digital pin 2 of Arduino
int LeftMotorReverse = 3;//Pin A2 of L293D motor driver board to digital pin 3 of Arduino
int RightMotorForward = 5;//Pin B1 of L293D motor driver board to digital pin 5 of Arduino
int RightMotorReverse = 4;//Pin A2 of L293D motor driver board to digital pin 4 of Arduino
unsigned int Time; // For measuring Distance
unsigned int distance; //Distance read by the sensor


int LeftDistance = 0;
int RightDistance = 0;
int object = 20;             //Distance at which the robot should look for another route       

NewPing sonar(USTrigger, USEcho, MaxDistance); //Activating the ultra sonic sensor

Servo HeadServo;

void setup ()//This block happens once on startup
{
  Serial.begin(9600);
  //Here we are setting the pin modes. As we will sending out signals from the pins we set them as outputs
  pinMode(LeftMotorForward,OUTPUT);
  pinMode(LeftMotorReverse,OUTPUT);
  pinMode(RightMotorForward,OUTPUT);
  pinMode(RightMotorReverse,OUTPUT);
  HeadServo.attach(6);//Head servo is now attached to pin 6
  HeadServo.write(90);//Moving the head to the front
  delay(700);//Wait for the head to get there
}
void loop()//This block repeats itself while the Arduino is turned on
{
  scan();   //Go to the scan function to start the scannig the distance
  Serial.println("Front distance = ");
  Serial.print(distance);
  if(distance > object)//If no obstacle is detected
  {                         
     MoveForward();             //Then sparrow moves forward
  }
  else //If obstacle is detected
  {    
    Halt();    //Stop
    FindRoute();//Find for new route
  }
}
 
void MoveForward()
{  
    Serial.println("");
    Serial.println("Moving forward");
    digitalWrite(LeftMotorForward,HIGH);
    digitalWrite(LeftMotorReverse,LOW);
    digitalWrite(RightMotorForward,HIGH);
    digitalWrite(RightMotorReverse,LOW);
    return;
 }
 
void FindRoute()
{
  Halt();     //stop
  Serial.println("There's an obstacle!");
  Reverse();                                      //Go backwards
  LookLeft();                                    //Go to subroutine LookLeft
  LookRight();                                  //Go to subroutine LookRight
                                      
  if ( LeftDistance > RightDistance ) //If there is left side distance is greater than the right side 
  {
    TurnLeft(); //Make a left turn
  }
 else //If there is right side distance is greater than the left side 
 {
   TurnRight(); //Make a right turn
 }
}

void Reverse() //Reverse gear ;-)
{
  Serial.println("");
  Serial.println("Moving Reverse");
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorReverse,HIGH);
  digitalWrite(RightMotorForward,LOW);
  digitalWrite(RightMotorReverse,HIGH);
  delay(900); //Halt the program unless Sparrow reverse himself
  Halt();
  return;
}

void Halt ()//This function works as Sparrow's Break 
{
  Serial.println("");
  Serial.println("Stopping");
  digitalWrite(LeftMotorForward,LOW);
  digitalWrite(LeftMotorReverse,LOW);
  digitalWrite(RightMotorForward,LOW);
  digitalWrite(RightMotorReverse,LOW);
  delay(500);                          //wait after stopping
  return;
}
 
void LookLeft() //Turns Sparrow's head to the left
{
  HeadServo.write(160); //Rotating the head
  delay(700); //Wait till servo moves the head
  scan();  //Look out for obstacle
  LeftDistance = distance;
  Serial.println("Left distance = ");
  Serial.print(distance);
  HeadServo.write(90); //Moves the head to the center position
  delay(700);          //Wait for the servo to get there
  return;
}

void LookRight () //Turns Sparrow's head to the right
{
  HeadServo.write(20); //Rotating the head
  delay(700);    //Wait till servo moves the head     
  scan();  //Look out for obstacle
  RightDistance = distance;
  Serial.println("Right distance = ");
  Serial.print(distance);
  HeadServo.write(90);    //Moves the head to the center position                              
  delay(700);            //wait for the servo to get there
  return;
}

void TurnLeft () // Turns sparrow to the left
{
  Serial.println("");
  Serial.println("Moving left");
  digitalWrite(LeftMotorForward,HIGH);       
  digitalWrite(LeftMotorReverse,LOW);      
  digitalWrite(RightMotorForward,LOW);
  digitalWrite(RightMotorReverse,HIGH);
  delay(700);                     // wait for Sparrow to make the turn
  Halt();
  return;
}

void TurnRight () // Turns sparrow to the right
{
  Serial.println("");
  Serial.println("Moving right");
  digitalWrite(LeftMotorForward,LOW);       
  digitalWrite(LeftMotorReverse,HIGH);    
  digitalWrite(RightMotorForward,HIGH);
  digitalWrite(RightMotorReverse,LOW);
  delay(700);                              // Wait for the robot to make the turn
  Halt();
  return;
}
void scan()            //This function determines the distance things are away from the ultrasonic sensor
{
  Serial.println("");
  Serial.println("Scanning....");
  Time = sonar.ping(); 
  distance = Time / US_ROUNDTRIP_CM;
  delay(500);
}
