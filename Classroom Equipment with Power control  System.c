#define BLYNK_TEMPLATE_ID "TMPL31O6yG4XZ"
#define BLYNK_TEMPLATE_NAME "Power Saving"
#define BLYNK_AUTH_TOKEN "xi5rLeLzICMYcO3E3-GdjJt9LRfOE5Sv"
// Your WiFi Credentials.
// Set password to "" for open networks.
char ssid[] = "phoenixiot1234";  // type your wifi name
char pass[] = "phoenixiot1234";  // type your wifi password

// define the GPIO connected with Sensors & LEDs

#define RAIN_SENSOR   D4  //D1

#define RED_LED       D8 //D7
#define WIFI_LED      16 //D0

//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 #include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int RAIN_SENSOR_Value = 0;
bool isconnected = false;
char auth[] = "xi5rLeLzICMYcO3E3-GdjJt9LRfOE5Sv";

 
#define VPIN_BUTTON_2    V1

BlynkTimer timer;

void checkBlynkStatus() { // called every 2 seconds by SimpleTimer
  getSensorData();
  isconnected = Blynk.connected();
  if (isconnected == true) {
    digitalWrite(WIFI_LED, LOW);
    sendSensorData();
    //Serial.println("Blynk Connected");
  }
  else{
    digitalWrite(WIFI_LED, HIGH);
    Serial.println("Blynk Not Connected");
  }
}

void getSensorData()
{
 
  RAIN_SENSOR_Value = digitalRead(RAIN_SENSOR);
   if (RAIN_SENSOR_Value == 0 ){
    lcd.clear();
lcd.setCursor(0,0);
  lcd.print("     WELCOME    ");
  lcd.setCursor(0,1);
  lcd.print("    STUDENTS    ");
  delay(500);
  
    digitalWrite(RED_LED, HIGH);
    delay(2000);
  }
  else{
    lcd.clear();
lcd.setCursor(0,0);
  lcd.print("   ALL OF YOU   ");
  lcd.setCursor(0,1);
  lcd.print("   THANK YOU    ");
 
    digitalWrite(RED_LED, LOW);
  }
}

void sendSensorData()
{  
  if (RAIN_SENSOR_Value == 0 )
  {
   
   
    Blynk.virtualWrite(VPIN_BUTTON_2, "STUDENTS INSIDE");
     delay(2000);
  }
  else if (RAIN_SENSOR_Value == 1 )
  {
    Blynk.virtualWrite(VPIN_BUTTON_2, "GLASS ROOM EMPTY");
  } 
}

void setup()
{
  Serial.begin(9600);
 
lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  SMART POWER   ");
  lcd.setCursor(0,1);
  lcd.print("    SAVING      ");
     delay(2000);
     lcd.clear();
  pinMode(RAIN_SENSOR, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(WIFI_LED, OUTPUT);


  digitalWrite(RED_LED, LOW);
  digitalWrite(WIFI_LED, HIGH);

  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  Blynk.config(auth);
  delay(1000);
}

void loop()
{
  Blynk.run();
  timer.run();
}