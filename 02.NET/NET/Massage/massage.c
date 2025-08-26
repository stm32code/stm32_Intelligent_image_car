#include "massage.h"
// �����豸
#include "esp8266.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "git.h"
#include "L298N.h"

// ����json����
mySta massage_parse_json(char *message)
{

	char *dataPtr = NULL;

	char numBuf[10];
	int num = 0;

	dataPtr = strchr(message, ':'); // ����':'

	if (dataPtr != NULL) // ����ҵ���
	{
		dataPtr++;
		while (*dataPtr >= '0' && *dataPtr <= '9') // �ж��Ƿ����·��������������
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;

		num = atoi((const char *)numBuf); // תΪ��ֵ��ʽ
		// printf("%d\n", num);
		if (strstr((char *)message, "speed")) // ����"redled"
		{
			car_init.car_speed = num; // ����С���ٶ�
			car_init.car_stop = 1;	  // ��λ
		}
		else if (strstr((char *)message, "mode")) // ǰ��
		{
			car_init.car_state = num;
		}
		else if (strstr((char *)message, "run")) // ǰ��
		{
			car_init.car_run = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "back")) // ����
		{
			car_init.car_back = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "r_left")) // ǰ��ת
		{
			car_init.car_run_left = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "r_right")) // ����ת
		{
			car_init.car_run_right = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "b_left")) // ����ת
		{
			car_init.car_back_left = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "b_right")) // ����ת
		{
			car_init.car_back_right = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "left")) // ��ת
		{
			car_init.car_left = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
		else if (strstr((char *)message, "right")) // ��ת
		{
			car_init.car_right = num + chack_time;
			car_init.car_stop = 1; // ��λ
		}
	}
	// printf("%s\n", message);
	return MY_SUCCESSFUL;
}
