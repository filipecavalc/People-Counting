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

String message = "";

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

  message = Serial.readString();
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  }
  
  if(message != ""){
    MQTT.publish(TOPICO_PUBLISH, message.c_str());
  }
  message = "";
}
