/*
TFT	ESP32
VD33	3.3V
GND	GND
SCL	18
SCA	23
CS	5
RS/DC	2
RST	4

จอยซ้าย (เดินหน้า/ถอยหลัง)
Joystick	ESP32
VRx	ไม่ใช้
VRy	GPIO 35
VCC	3.3V
GND	GND

Joystick	ESP32 จอยขวา (เลี้ยวซ้าย/ขวา)
VRx	GPIO 32
VRy	ไม่ใช้
VCC	3.3V
GND	GND
/*


/*
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

// ------------------- WiFi -------------------
WiFiUDP udp;
const char* ssid = "RobotCar";
const char* password = "12345678";
const char* carIP = "192.168.4.1";  
unsigned int udpPort = 4210;

// ------------------- Joystick -------------------
#define JS1_Y 35   // เดินหน้า/ถอย
#define JS2_X 32   // เลี้ยวซ้าย/ขวา

// ------------------- TFT Display -------------------
#define TFT_CS    5
#define TFT_DC    2
#define TFT_RST   4

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// ------------------- ส่งคำสั่ง + แสดงจอ -------------------
void displayCommand(const char* text, uint16_t colorBG) {
  tft.fillScreen(colorBG);
  tft.setTextColor(ST77XX_WHITE, colorBG);
  tft.setTextSize(3);
  tft.setCursor(10, 20);
  tft.print("CMD:");
  
  tft.setTextSize(4);
  tft.setCursor(10, 80);
  tft.print(text);
}

void sendCmd(char c){
  udp.beginPacket(carIP, udpPort);
  udp.write(c);
  udp.endPacket();

  switch(c){
    case 'F': displayCommand("FORWARD", ST77XX_GREEN); break;
    case 'B': displayCommand("BACK",    ST77XX_RED);   break;
    case 'L': displayCommand("LEFT",    ST77XX_BLUE);  break;
    case 'R': displayCommand("RIGHT",   ST77XX_ORANGE);break;
    default:  displayCommand("STOP",    ST77XX_YELLOW);break;
  }
}

// ------------------- SETUP -------------------
void setup(){
  Serial.begin(115200);

  // TFT init
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Joystick Controller");

  // WiFi
  WiFi.begin(ssid, password);
  tft.setCursor(10, 40);
  tft.print("Connecting WiFi..");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(200);
    tft.print(".");
  }

  udp.begin(udpPort);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 40);
  tft.println("READY!");
}

// ------------------- LOOP -------------------
void loop(){
  int js1y = analogRead(JS1_Y);  // เดินหน้า/ถอย
  int js2x = analogRead(JS2_X);  // ซ้าย/ขวา

  // เดินหน้า
  if(js1y < 1200){
    sendCmd('F');
  }
  // ถอย
  else if(js1y > 3000){
    sendCmd('B');
  }
  // ซ้าย
  else if(js2x < 1200){
    sendCmd('L');
  }
  // ขวา
  else if(js2x > 3000){
    sendCmd('R');
  }
  // หยุด
  else{
    sendCmd('S');
  }

  delay(150);
}
*/