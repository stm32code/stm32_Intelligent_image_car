#include "delay.h"
#include "led.h"
// 网络设备驱动
#include "esp8266.h"
// 初始化PB5和PE5为输出口.并使能这两个口的时钟
// LED IO初始化
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(Relay_GPIO_CLK|RCC_APB2Periph_GPIOC, ENABLE); // 使能端口时钟C

	GPIO_InitStructure.GPIO_Pin = Relay_GPIO_PIN;	  // 端口配置, 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO口速度为50MHz
	GPIO_Init(Relay_GPIO_PORT, &GPIO_InitStructure);  // 推挽输出 ，IO口速度为50MHz

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	  // 端口配置, 推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);  // 推挽输出 ，IO口速度为50MHz

	
	LED = OFF;
}
/**
 * @brief  MQTT操作LED模块
 * @param  无
 * @retval 无
 */
void Mqtt_LED(char *Tips, int Cmd)
{

	ESP8266_Clear(); // 清空缓存
	// printf("cmd:%d",Cmd);
	switch (Cmd)
	{
	case 1:
		LED = ON;
		// OneNet_SendMqtt();          //上传订阅的主题里

		break;

	case 0:
		LED = OFF;
		//	OneNet_SendMqtt();          //上传订阅的主题里

		break;
	default:
		/* 如果不是指定指令字符，打印提示信息 */
		// OneNet_Publish(Tips, "ERROR:2");

		break;
	}
	return;
}
/*********************************************************************************
 * @Function	:	系统设置PB3和PB4为普通IO口
 * @Input		:	deviceSta,设备状态
 * @Output		: 	None
 * @Return		: 	None
 * @Others		: 	JTAG调试方式会受影响
 * @Date			:  2020-04-22
 **********************************************************************************/
void System_PB34_setIO(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 打开AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}
