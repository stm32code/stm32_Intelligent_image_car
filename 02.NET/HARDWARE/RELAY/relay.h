#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"

#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_CLK RCC_APB2Periph_GPIOB
#define BEEP_GPIO_PIN GPIO_Pin_8

#define RELAY1_GPIO_PORT GPIOB
#define RELAY1_GPIO_CLK RCC_APB2Periph_GPIOB
#define RELAY1_GPIO_PIN GPIO_Pin_12

/* 直接操作寄存器的方法控制IO */
#define digitalHi(p, i) \
    {                   \
        p->BSRR = i;    \
    } // 输出为高电平
#define digitalLo(p, i) \
    {                   \
        p->BRR = i;     \
    } // 输出低电平d
#define digitalToggle(p, i) \
    {                       \
        p->ODR ^= i;        \
    } // 输出反转状态

#define RELAY1_TOGGLE digitalToggle(RELAY1_GPIO_PORT, RELAY1_GPIO_PIN)
#define RELAY1_OFF digitalLo(RELAY1_GPIO_PORT, RELAY1_GPIO_PIN)
#define RELAY1_ON digitalHi(RELAY1_GPIO_PORT, RELAY1_GPIO_PIN)

#define BEEP_TOGGLE digitalToggle(BEEP_GPIO_PORT, BEEP_GPIO_PIN)
#define BEEP_OFF digitalLo(BEEP_GPIO_PORT, BEEP_GPIO_PIN)
#define BEEP_ON digitalHi(BEEP_GPIO_PORT, BEEP_GPIO_PIN)

void RELAY_GPIO_Config(void);

#endif /* __RELAY_H */
