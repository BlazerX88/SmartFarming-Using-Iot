// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "BITSFORGE-KOCHI";
char wifiPassword[] = "wpass3055";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "77d6b3a0-4aef-11ea-84bb-8f71124cfdfb";
char password[] = "e4fa84df47acc24b77ef42a3e7153d58548fc1b4";
char clientID[] = "1607c9b0-4afa-11ea-a38a-d57172a4b4d4";

unsigned long lastMillis = 0;
String latitude;
//String longitude;

void setup() {
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
 if(Serial.available()>0)
 {
  if(Serial.read()=='$')
  {
     latitude=Serial.readStringUntil(',');
     //longitude=Serial.readStringUntil('*');
  }
 }
  Cayenne.virtualWrite(1,latitude.toInt());
 // Cayenne.virtualWrite(1,longitude.toFloat());
}
CAYENNE_IN(2)
{
  int button=getValue.asInt();
  if(button==0)
  {
    Serial.print("$A*");
  }
  else
  {
    Serial.print("$B*");
  }
}
