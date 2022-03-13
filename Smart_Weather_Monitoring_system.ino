#include<Adafruit_MQTT_Client.h> //Adafruit IO MQTT Library
#include<ESP8266WiFi.h>
WiFiClient esp;
#include<LiquidCrystal.h>   //LCD library
#include<DHT.h>   //DHT library
DHT dht(10,DHT11);  //Creating an object of type DHT
LiquidCrystal lcd(5,4,0,2,14,12); //Initialising the pins of the LCD (rs,en,D4,D5,D6,D7)
#define ssid "ssid" //provide wifi ssid
#define pass "pass" //provide wifi password
#define server "io.adafruit.com"  //Adafruit IO server
#define port 1883 //MQTT Port
#define user "user_name"  //Adafruit IO username
#define key "aio_HLDR92agYBnmKjubU5i3StHY78az"  //Adafruit IO Secret key

Adafruit_MQTT_Client mqtt(&esp,server,port,user,key); //Creating a client
Adafruit_MQTT_Publish te(&mqtt,user"/feeds/temp");  //accessing publishing feeds
Adafruit_MQTT_Publish hu(&mqtt,user"/feeds/humidity");
void setup() 
{
  

  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.clear();
  dht.begin();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid,pass);  //Connecting to WiFi
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Connecting to Adafruit IO");
  while(mqtt.connect()) //Connecting to Adafruit IO
  {
    Serial.print(".");
  }
  Serial.println("Connected to Adafruit IO");
  
  
  
}

void loop() {

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  Serial.print("Temp = ");
  Serial.println(temp);
  Serial.print("Humidity = ");
  Serial.println(hum);
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.setCursor(0,1);
  lcd.print("Humidity = ");
  lcd.print(hum);

  if(mqtt.connected())  
  {
    te.publish(temp); //Publishing the data to Adafruit IO
    hu.publish(hum);
  }
  else
  {
    Serial.println("Publishing unsuccessful");
  }
  delay(5000);
}
