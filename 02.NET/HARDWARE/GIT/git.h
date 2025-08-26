#ifndef __GIT_H
#define __GIT_H
#include "stdio.h"

typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned int U32;
typedef signed int S32;
typedef float F32;

// 自定义执行结果类型
typedef enum
{
	MY_SUCCESSFUL = 0x01, // 成功
	MY_FAIL = 0x00		  // 失败

} mySta; // 成功标志位

typedef enum
{
	OPEN = 0x01, // 打开
	CLOSE = 0x00 // 关闭

} On_or_Off_TypeDef; // 成功标志位

typedef enum
{
	DERVICE_SEND = 0x00, // 设备->平台
	PLATFORM_SEND = 0x01 // 平台->设备

} Send_directino; // 发送方向

typedef struct
{
	U8 light;		  // 光照
	U8 temperatuer;	  // 温度
	U8 humidity;	  // 湿度
	U8 soil_humidity; // 土壤湿度
	F32 somg;		  // 烟雾浓度

} Data_TypeDef; // 数据参数结构体

typedef struct
{
	U8 led_state;		  // LED状态
	U8 hot_led_state;	  // 供暖灯状态
	U8 fan_state;		  // 风扇状态
	U8 water_pump1_state; // 水泵一状态
	U8 water_pump2_state; // 水泵二状态

} Device_Satte_Typedef; // 状态参数结构体

/**************************************************************************************
 * 描  述 : 获取数据参数
 * 入  参 : 8
 * 返回值 : uint8_t
 **************************************************************************************/
void Read_Data(Data_TypeDef *Data);

#endif
