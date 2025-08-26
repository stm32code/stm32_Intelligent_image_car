#include "relay.h"

u8 StateRELAY1 = 0;

void RELAY_GPIO_Config(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK | RELAY1_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = RELAY1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BEEP_GPIO_PIN;
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStructure);

	GPIO_ResetBits(RELAY1_GPIO_PORT, RELAY1_GPIO_PIN);
	GPIO_ResetBits(BEEP_GPIO_PORT, BEEP_GPIO_PIN);
}
