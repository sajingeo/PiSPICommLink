#include <SPI.h>
#include <Wire.h>


/**
*@brief      setup all peripherals for the Arduino (atmega328)
*/

const int dataReadyPin = 6;
const int chipSelectPin = 7;

int recByte=0;

int startFlag=0;
int stopFlag=0;
int digitalFlag=0;
int analogFlag=0;
int chNumber=0;
int analogReading=0;
int digitalReadFlag=0;
int readData=0;

void setup() {
  
  // start serial comm for i2c only
  Serial.begin(9600);
 
    // join i2c bus with address #4
   // Wire.begin(4);
  
   // start the SPI library:
   //SPI.begin();

  // initalize the  data ready and chip select pins:
  //pinMode(dataReadyPin, INPUT);
  //pinMode(chipSelectPin, OUTPUT);

}

void loop() {
  // reset all flags to 0
//startFlag=0;
//stopFlag=0;
//digitalFlag=0;
//analogFlag=0;
  //Serial.print("not started\n");
  // put your main code here, to run repeatedly: 
  if(Serial.available()>0){
       // store received byte
        recByte=Serial.read();
       // Serial.println(recByte, DEC);
        if(recByte=='0')
        {
          Serial.print("started");
          startFlag=1;
        }
        
        else if((recByte=='1')&&(startFlag==1))
        {
          digitalFlag=1;
        }
        else if((recByte=='2')&&(startFlag==1))
        {
          analogFlag=1;
        }
        else if((recByte=='3')&&(startFlag==1))
        {
          digitalReadFlag=1;
        }
        else
        {
          Serial.print("Invalid!\n");
        }
        
        if((startFlag==1)&&(digitalFlag==1))
        {
          Serial.print("Digital Write\n");
          
          Serial.flush();
          
          while(Serial.available()==0);
          DDRD|=(Serial.parseInt()|0xf0);
          Serial.print("wrote DDR value\n");
          
          while(Serial.available()==0);
          PORTD|=(Serial.parseInt()|0xf0);
          Serial.print("wrote PORT value\n");
          
          digitalFlag=0;
          startFlag=0;
        }
        else if((startFlag==1)&&(analogFlag==1))
        {
          Serial.print("Analog\n");
          Serial.flush();
         
          while(Serial.available()==0);
          
          chNumber=Serial.parseInt();
          Serial.print("reading ch:");
          Serial.println(chNumber);
          
          analogReading=analogRead(chNumber);
          
          Serial.println(analogReading);
          
          analogFlag=0;
          startFlag=0;
        }
        
        if((startFlag==1)&&(digitalReadFlag==1))
        {
          Serial.print("Digital Read\n");
          
          Serial.flush();
        
          readData=PIND;
          Serial.print("pin value=");
          Serial.println(readData);
         
          digitalReadFlag=0;
          startFlag=0;
        }
        
  
  }
}
