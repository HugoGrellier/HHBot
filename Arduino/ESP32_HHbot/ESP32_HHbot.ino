/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.


//to connect in bluetooth you need to launch the esp32, Then Enable your smartphone bluetooth, launch a scan on your phone than launch a scan on the app and connect

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
#include <BLE2902.h>
#include <SPI.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <TFT_eSPI.h>       // Hardware-specific library
#include <ros.h>
#include <std_msgs/String.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

String value;
String send_ble = "2";

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

VL53L0X sensor;


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      pCharacteristic->setValue(send_ble.c_str());

      if (value.length() > 0) {
        value = "";
        for (int i = 0; i < value.length(); i++){
          //Serial.print(value[i]);
          value = value + value[i];
        }

        //Serial.println("*********");
        //Serial.print("value = ");
        //Serial.println(value);
      }
    }
};

void setup_TFT_SPI(){
  tft.init();

  tft.fillScreen(TFT_BLACK);
  
  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 0, 4);

  // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // We can now plot text on screen using the "print" class
  tft.println("Intialised default\n");

  delay(5000);
}

void setup_BLE()
{


  BLEDevice::init("HHbot 3000");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}


void setup_TOF()
{
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  setup_TFT_SPI();
  setup_TOF();
  setup_BLE();
}



void loop()
{ 
  tft.setCursor(0, 0, 4);
  int range = sensor.readRangeContinuousMillimeters();
  tft.println("                                              ");
  tft.setCursor(0, 0, 4);
  tft.println(range);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  tft.println();
  if (value == "beer_launch"){
    tft.setCursor(6, 0, 4);
    tft.println("serving beer");
    Serial.print("serving beer");
  }
  delay(500);
  send_ble = (String) range;
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
}
