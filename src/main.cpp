#include <Arduino.h>

#include <ESP32Servo.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVO_PIN 4

Servo servo;

#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-5678-1234-abcdefabcdef"

BLECharacteristic *pCharacteristic;

class CommandCallback : public BLECharacteristicCallbacks
{

    void onWrite(BLECharacteristic *pCharacteristic)
    {

        std::string value = pCharacteristic->getValue();

        if (value == "PRESS")
        {

            servo.write(35);

            delay(500);

            servo.write(0);
        }
    }
};

void setup()
{

    Serial.begin(115200);

    servo.setPeriodHertz(50);
    servo.attach(SERVO_PIN);
    servo.attach(4, 1000, 2000);

    servo.write(0);

    BLEDevice::init("NB_POWER");

    BLEServer *server = BLEDevice::createServer();

    BLEService *service =
        server->createService(SERVICE_UUID);

    pCharacteristic =
        service->createCharacteristic(
            CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setCallbacks(new CommandCallback());

    service->start();

    BLEAdvertising *advertising =
        BLEDevice::getAdvertising();

    advertising->start();

    Serial.println("BLE Ready");
}

void loop()
{
    if (Serial.available())
    {
        int angle = Serial.parseInt();

        Serial.print("Angle=");
        Serial.println(angle);

        servo.write(angle);
    }
}
