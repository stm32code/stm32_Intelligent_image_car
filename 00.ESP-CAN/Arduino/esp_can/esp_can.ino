#include "esp_camera.h"
#include <WiFi.h>

// Select camera model
// #define CAMERA_MODEL_WROVER_KIT
// #define CAMERA_MODEL_ESP_EYE
// #define CAMERA_MODEL_M5STACK_PSRAM
// #define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER

#include "camera_pins.h"

const char *ssid = "WIFI_For";
const char *password = "12345678";
const IPAddress ip(192, 168, 4, 1);
const IPAddress gateway(192, 168, 4, 1);
const IPAddress subnet(255, 255, 255, 0);

void cameraBegin();      // 相机初始化
int startCameraServer(); // 启动相机服务
void setWifi();
WiFiServer server(8000); // 申明AP对象

void setup()
{
  }

void loop()
{
  
}

/**
 * @brief 配置wifi
 */
void setWifi()
{
 
}
/**
 * @brief 相机初始化
 *
 */
void cameraBegin()
{
    
#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif
}