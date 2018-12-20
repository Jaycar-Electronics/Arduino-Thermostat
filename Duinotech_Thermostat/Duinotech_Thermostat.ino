#include <SimpleDHT.h>

SimpleDHT11 sensor;                 //constructor for SimpleDHT11 object
int leds[8]={2,3,4,5,6,7,8,9};      //array for pins, green LED's are first 4, red LED's are next 4
int setpoint=29;                    //if too many LED's are showing, increase this

void setup() {
  for(int i=0;i<8;i++){             //set the LED pins to outputs and LOW (off)
    pinMode(leds[i],OUTPUT);
    digitalWrite(leds[i],LOW);
  }
  pinMode(13,OUTPUT);               //relay pin is output, turn off
  digitalWrite(13,LOW);
}

void loop() {
  byte t=0;                                 //variables for temperature and humidity
  byte h=0;
  if(sensor.read(11,&t,&h,NULL)==0){        //read the sensors
    if(t>setpoint){digitalWrite(13,HIGH);}  //update the output if it's a valid reading
    if(t<setpoint){digitalWrite(13,LOW);}
    t=t-setpoint+4;
    for(int i=0;i<8;i++){
      if(t<i){
        digitalWrite(leds[i],LOW);          //light up the right LED's
      }else{
        digitalWrite(leds[i],HIGH);        
      }
    }
  }
  delay(1200);                              //wait a bit because sensor can read once/second
}
