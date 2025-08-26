#ifndef __ESP8266_H_
#define __ESP8266_H_

#include "sys.h"
#include "git.h"

#define REV_OK 0   // 接收完成标志
#define REV_WAIT 1 // 接收未完成标志
//  引脚定义
#define ESP_RST_GPIO_CLK RCC_APB2Periph_GPIOB
#define ESP_RST_GPIO_PORT GPIOB
#define ESP_RST_GPIO_PIN GPIO_Pin_8

//  引脚定义
#define ESP_CONNET_GPIO_CLK RCC_APB2Periph_GPIOB
#define ESP_CONNET_GPIO_PORT GPIOB
#define ESP_CONNET_GPIO_PIN GPIO_Pin_9

#define Connect_Net GPIO_ReadInputDataBit(ESP_CONNET_GPIO_PORT, ESP_CONNET_GPIO_PIN)

void Net_Reset(void);
void ESP_Init(void);
void Usart3_Init(unsigned int baud);
void ESP8266_Clear(void);

void ESP8266_SendData(unsigned char *data, unsigned short len);

unsigned char *ESP8266_Get(unsigned short timeOut);
void Usart3_SendString(unsigned char *str, unsigned short len);

#endif
