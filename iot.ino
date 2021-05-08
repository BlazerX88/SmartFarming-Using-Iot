#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

#define uploadDelay 1   //in minutes
#define analogInPin A0
// Network Parameters
const char* ssid     = "BITSFORGE-KOCHI";
const char* password = "wpass3055";
//const char* ssid     = "KSUM GUESTS";
//const char* password = "QAZwsx@123";

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1060599;
char* readAPIKey = "U64YN3SMMFA6X70Q";
char* writeAPIKey = "QIKYOID6AQ4TL16G";
long count = 0;
int fiveSec = 0,minutes = 0;
float sensorValue;
bool uploadFlag = false;
WiFiClient client;  
String temp,hum,moist;            
void setup() {
 Serial.begin(115200);
Serial.println("Start");

connectWiFi();
pinMode(2,OUTPUT);

 
// Read the constants at startup.
//aConst = readTSData( channelID, aField );
//bConst = readTSData( channelID, bField );
//cConst = readTSData( channelID, cField );
}

void loop() {
  String vIN,vOUT,cIN,cOUT,loadCurrent;
if(Serial.available()){
  if(Serial.read()=='$'){
   temp  = Serial.readStringUntil(',');
   hum = Serial.readStringUntil(',');
   moist = Serial.readStringUntil(',');
   //cOUT = Serial.readStringUntil(',');
   //loadCurrent=Serial.readStringUntil('*');

   if(uploadFlag){
    uploadFlag = false;
    write2TSData( channelID,1,temp,2,hum,3,moist);
   }
  } 
}
if((millis() - count) >= 5000){
  count = millis();
  fiveSec++;
 // Serial.println("Five");
  if(fiveSec >= 12){
    minutes++;
    fiveSec = 0;
  }
  if(minutes >= uploadDelay){minutes = 0;fiveSec = 0;uploadFlag = true;}
}

 
 }

    int connectWiFi(){
    WiFi.begin( ssid, password );
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println( "Connected" );
    ThingSpeak.begin( client );
}

// Use this function if you want to write a single field
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}
//use this function if you want multiple fields simultaneously
int write2TSData( long TSChannel, unsigned int TSField1, String field1Data, unsigned int TSField2, String field2Data, unsigned int TSField3, String field3Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
  //ThingSpeak.setField( TSField4, field4Data );
  //ThingSpeak.setField( TSField5, field5Data );


  Serial.println("F1 Data: "+field1Data);
  Serial.println("F2 Data: "+field2Data);
  Serial.println("F3 Data: "+field3Data);
  //Serial.println("F4 Data: "+field4Data);
  //Serial.println("F5 Data: "+field5Data);

  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}

 float mapp(int p,int q,int r,int s,float t)
   {
    int fromlow=p; //
    int fromhigh=q;
    int tolow=r;
    int tohigh=s;
    int a=fromhigh-fromlow;
    int b=tohigh-tolow;
    float c=a/b;
    float u=(((t-fromlow)*b/((a+(tolow))))+tolow);
    return u;
   }
