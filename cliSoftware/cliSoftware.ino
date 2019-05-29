#include <PID_v1.h>
int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
int fanPin = 3; //Pin used to control the fan
int heaterPin = 9; //Pin used to control the heater


//PID Setup
double Input, Output, Setpoint = 24.0;
double Kp=20, Ki = 1, Kd=100;
PID myPid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() //Serial connection for debuging and sat fan pin's output
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  myPid.SetMode(AUTOMATIC);
}
 
void loop()                     // run over and over again
{
 Input = getTemp();
 myPid.Compute();
 heater();
 Serial.println(getTemp());
 Serial.println(Input);
 Serial.println(Output);
 delay(1000);   //waiting a second
}

void heater(){
  //Spin the fan and turn the heater off based on the temperature
  analogWrite(heaterPin, Output);
  analogWrite(fanPin, (255 - Output));
  delay(50);
}

float getTemp(){
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0;
  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100);
  float tempC = (voltage - 0.5) * 100;
  return tempC;
}

