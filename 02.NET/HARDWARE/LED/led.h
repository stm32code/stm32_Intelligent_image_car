#ifndef __LED_H
#define __LED_H
#include "sys.h"

/* 定义LED连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define Relay_GPIO_PORT GPIOA               /* GPIO端口 */
#define Relay_GPIO_CLK RCC_APB2Periph_GPIOA /* GPIO端口时钟 */
#define Relay_GPIO_PIN GPIO_Pin_8

#define Read_State GPIO_ReadInputDataBit(Relay_GPIO_PORT, Relay_GPIO_PIN)
#define LED PAout(8) // LED接口
#define Beep PCout(8) // LED接口
#define OFF 1
#define ON 0

void LED_Init(void); // 初始化
void Mqtt_LED(char *Tips, int Cmd);
/*********************************************************************************
 * @Function	:	系统设置PB3和PB4为普通IO口
 * @Input		:	deviceSta,设备状态
 * @Output		: 	None
 * @Return		: 	None
 * @Others		: 	JTAG调试方式会受影响
 * @Date			:  2020-04-22
 **********************************************************************************/
void System_PB34_setIO(void);
#endif
