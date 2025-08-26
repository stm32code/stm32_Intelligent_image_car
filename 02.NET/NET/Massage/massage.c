#include "massage.h"
// 网络设备
#include "esp8266.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "git.h"
#include "L298N.h"

// 解析json数据
mySta massage_parse_json(char *message)
{

	char *dataPtr = NULL;

	char numBuf[10];
	int num = 0;

	dataPtr = strchr(message, ':'); // 搜索':'

	if (dataPtr != NULL) // 如果找到了
	{
		dataPtr++;
		while (*dataPtr >= '0' && *dataPtr <= '9') // 判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;

		num = atoi((const char *)numBuf); // 转为数值形式
		// printf("%d\n", num);
		if (strstr((char *)message, "speed")) // 搜索"redled"
		{
			car_init.car_speed = num; // 设置小车速度
			car_init.car_stop = 1;	  // 置位
		}
		else if (strstr((char *)message, "mode")) // 前进
		{
			car_init.car_state = num;
		}
		else if (strstr((char *)message, "run")) // 前进
		{
			car_init.car_run = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "back")) // 后退
		{
			car_init.car_back = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "r_left")) // 前左转
		{
			car_init.car_run_left = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "r_right")) // 后右转
		{
			car_init.car_run_right = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "b_left")) // 后左转
		{
			car_init.car_back_left = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "b_right")) // 后右转
		{
			car_init.car_back_right = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "left")) // 左转
		{
			car_init.car_left = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
		else if (strstr((char *)message, "right")) // 右转
		{
			car_init.car_right = num + chack_time;
			car_init.car_stop = 1; // 置位
		}
	}
	// printf("%s\n", message);
	return MY_SUCCESSFUL;
}
