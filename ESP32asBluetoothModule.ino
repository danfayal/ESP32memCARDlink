
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// UUIDs  UART  service Nordic BLE
#define UART_SERVICE_UUID     "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_CHAR_WRITE_UUID  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define UART_CHAR_NOTIFY_UUID "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// buffer UART size
// #define UART_BUFFER_SIZE 130 // debug



// UART2 pin ESP32
#define RX2_PIN 16
#define TX2_PIN 17

BLECharacteristic *pNotifyCharacteristic;
bool deviceConnected = false;
HardwareSerial hwSerial(2);  // UART2

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
  }
};

class RxCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) override {
    std::string rx = pChar->getValue();
    if (!rx.empty()) {
      hwSerial.write((uint8_t*)rx.data(), rx.length());  // repass UART command to Arduino
    }
  }
};

void setup() {
  Serial.begin(115200);
  hwSerial.begin(115200, SERIAL_8N1, RX2_PIN, TX2_PIN);

  BLEDevice::init("ESP32-MemCARDuino");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService *pService = pServer->createService(UART_SERVICE_UUID);

  BLECharacteristic *pWriteCharacteristic = pService->createCharacteristic(
    UART_CHAR_WRITE_UUID,
    BLECharacteristic::PROPERTY_WRITE
  );
  pWriteCharacteristic->setCallbacks(new RxCallbacks());

  pNotifyCharacteristic = pService->createCharacteristic(
    UART_CHAR_NOTIFY_UUID,
    BLECharacteristic::PROPERTY_NOTIFY
  );
  pNotifyCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();

  //Serial.println("BLE UART Bridge ready."); //debug
}

void loop() {
  if (deviceConnected && hwSerial.available() >= 130) {// ACK + byte + checksum = 130? well...works for me.
    
    uint8_t buf[130];
    size_t len = hwSerial.readBytes(buf, 130);
    pNotifyCharacteristic->setValue(buf, len);
    pNotifyCharacteristic->notify();

  }

  delay(1);  // for BLE take a breath.
}
