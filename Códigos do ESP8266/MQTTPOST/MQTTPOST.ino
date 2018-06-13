#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "";     // replace with your wifi ssid
const char *pass =  "";     // replace with your wpa2 key

const char* TOPICO_PUBLISH  = "";
const char* ID_MQTT         = "";
const char* BROKER_MQTT     = ""; //broker URL MQTT
int BROKER_PORT             = ; // MQTT broker port

WiFiClient espClient; // creates espClient object
PubSubClient MQTT(espClient); // Instantiate the MQTT Client by passing the espClient object

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pass);
  Serial.print("Starting connection ");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.connect(ID_MQTT);

}

void loop() {
  //waiting for the Serial port buffer to receive the data
  while(Serial.available() == 0){
  }

  //check if the internet connection is ok
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
  }
  
  //verifies that the connection with mqtt is ok
  if(MQTT.state() == -3){
    MQTT.connect(ID_MQTT);
  }
  
  //checks the serial port buffer and reads until the buffer is empty
  while(Serial.available() > 0){
    //reads the buffer until the first line break
    Serial.println(MQTT.publish(TOPICO_PUBLISH, Serial.readStringUntil('\n').c_str()));
  }
  
}
