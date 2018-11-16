#include <ESP8266SerialLibrary.h>

//#define CAYENNE_DEBUG       // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTESP8266Shield.h>

// WiFi network info.
char ssid[] = "Krester";
char wifiPassword[] = "johnwick";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "$USERNAME";
char password[] = "$PASSWORD";
char clientID[] = "$ID";
// Set ESP8266 Serial object. In this example we use the Serial1 hardware serial which is available on boards like the Arduino Mega.
#define EspSerial Serial1

ESP8266 wifi(&EspSerial);
int sensorPin=A0;
int val=0;
void setup()
{
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(115200);
  delay(10);

  Cayenne.begin(username, password, clientID, wifi, ssid, wifiPassword);
}

void loop()
{
 delay(5000);
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  
  val =(analogRead(sensorPin));
  Cayenne.virtualWrite(0, val);
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
