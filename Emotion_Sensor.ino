#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550; 
PulseSensorPlayground pulseSensor;

//pulse wave
#define NZEROS 8
#define NPOLES 8
#define GAIN   2.998077659e+01
#define GAIN1  2.059100943e+13
float xv[NZEROS+1], yv[NPOLES+1];
unsigned long int milli_time;    //variable to hold the time
float voltage,opv,opv1,ip;         //variable to hold the voltage form A0
int count=0;

#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

const int GSR=A1;
int sensorValue=0;
int gsr_average=0;
//unsigned long int milli_time; 

//#include <dht.h>
//#define DHT11_PIN 7

int previous=60;
int myBPM = 0;

void setup(void) 
{ 
 Serial.begin(9600); 
 Serial.println("LABEL,Computer Time,Heart Rate,Body Temperature,GSR, Pulse"); 
 sensors.begin(); 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold); 
  if (pulseSensor.begin()) {
      
  }
  for ( int i=0 ; i<9; i++ )
   {
    xv[i]=0;
    yv[i]=0;
   }
} 

/*void Room_Temperature_Function()
{
  dht DHT;
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
}*/
void Body_Temperature_Function()
{
  sensors.requestTemperatures(); // Send the command to get temperature readings  
 Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
}

void Heart_Rate_Function() {
  myBPM = pulseSensor.getBeatsPerMinute(); // Update global myBPM with the current heart rate
  if (pulseSensor.sawStartOfBeat()) {
    previous = myBPM;
  }
  Serial.print(myBPM); // Print myBPM
}

void Skin_Conductance_Function()
{
  long sum=0;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
  gsr_average = sum/10;
   Serial.print(gsr_average);
}

//pulse wave code

void Pulse_Wave()
{
  milli_time = millis();
  ip=analogRead(A5);
  voltage = (5.0 * ip) / 1023.0;
  opv = filterloop(voltage);
  //Serial.print(milli_time);
  //Serial.print(",");
 // Serial.print(voltage);
  Serial.print(opv);
 // Serial.print(",");
}
float filterloop(float ipv)
  { for (;;)
      {  xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; xv[4] = xv[5]; xv[5] = xv[6]; xv[6] = xv[7]; xv[7] = xv[8]; 
        xv[8] = ipv / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; yv[4] = yv[5]; yv[5] = yv[6]; yv[6] = yv[7]; yv[7] = yv[8]; 
        yv[8] =   (xv[0] + xv[8]) - 4 * (xv[2] + xv[6]) + 6 * xv[4]
                     + ( -0.1572575620 * yv[0]) + ( -0.2314246263 * yv[1])
                     + (  0.7190311952 * yv[2]) + (  1.0610321243 * yv[3])
                     + ( -1.3817661995 * yv[4]) + ( -1.7156352979 * yv[5])
                     + (  1.2305708310 * yv[6]) + (  1.4753463815 * yv[7]);
        opv = yv[8];
        return(opv);
      }
  }

void loop() {
   Serial.print("DATA, TIME,");

   Heart_Rate_Function();
   
   Serial.print(",");
   Body_Temperature_Function();

  //Serial.print(",");
  //Room_Temperature_Function();

  Serial.print(",");
  Skin_Conductance_Function();
   
  Serial.print(",");
  Pulse_Wave();

  if (myBPM >= 85 && myBPM <= 125)
    Serial.print("HAPPY");
  else if (myBPM >= 80 && myBPM <= 90)
    Serial.print("SAD");
  else if (myBPM >= 65 && myBPM <= 79)
    Serial.print("RELAXED");
  else if (myBPM >= 125)
    Serial.print("ANGRY");
  
  Serial.println();

  delay(500); 

}
