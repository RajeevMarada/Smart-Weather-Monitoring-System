#include<Adafruit_MQTT_Client.h>
#include<ESP8266WiFi.h>
WiFiClient esp;
#include<LiquidCrystal.h>
#include<DHT.h>
DHT dht(10,DHT11);
LiquidCrystal lcd(5,4,0,2,14,12);
#define ssid "Rajeev-2.4GHz"
#define pass "latham36"
#define server "io.adafruit.com"
#define port 1883
#define user "Rajeev_Marada"
#define key "aio_HLDR92agYBnmKjubU5i3StHY79aa"

Adafruit_MQTT_Client mqtt(&esp,server,port,user,key);
Adafruit_MQTT_Publish te(&mqtt,user"/feeds/temp");
Adafruit_MQTT_Publish hu(&mqtt,user"/feeds/humidity");
void setup() 
{
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.clear();
  //lcd.setCursor(5,0);
  //lcd.print("HELLO VRO");
  dht.begin();
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Connecting to Adafruit IO");
  while(mqtt.connect())
  {
    Serial.print(".");
  }
  Serial.println("Connected to Adafruit IO");
  
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  //if(!isnan(temp) && !isnan(hum))
  //{
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
  //}

  if(mqtt.connected())
  {
    te.publish(temp);
    hu.publish(hum);
  }
  else
  {
    Serial.println("Publishing unsuccessful");
  }
  delay(5000);
}
