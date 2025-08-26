#include "git.h"
// ����豸�����ļ�
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "key.h"
#include "relay.h"
#include "usart.h"
#include "key.h"
#include "L298N.h"
#include "oled.h"
#include "dht11.h"
#include "adc.h"
#include "HC_SR04.h"
#include "usart2.h"

Data_TypeDef Data_init;						  // �豸���ݽṹ��
Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��
Device_Satte_Typedef device_state_init;		  // �豸״̬
Check_Hight_Typedef check_hight_init;		  // �߶�
DHT11_Data_TypeDef DHT11_Data;

void errorLog(U8 num)
{
	while (1)
	{
		printf("ERROR%d\r\n", num);
	}
}
// ��ȡGPS��λ��Ϣ
void parseGpsBuffer()
{
	char *subString;
	char *subStringNext;
	char i = 0;
	char usefullBuffer[2];
	if (Save_Data.isGetData)
	{
		Save_Data.isGetData = false;
		for (i = 0; i <= 6; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
					errorLog(1); // ��������
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					switch (i)
					{
					case 1:
						memcpy(Save_Data.UTCTime, subString, subStringNext - subString);
						break; // ��ȡUTCʱ��
					case 2:
						memcpy(usefullBuffer, subString, subStringNext - subString);
						break; // ��ȡUTCʱ��
					case 3:
						memcpy(Save_Data.latitude, subString, subStringNext - subString);

						break; // ��ȡγ����Ϣ
					case 4:
						memcpy(Save_Data.N_S, subString, subStringNext - subString);
						break; // ��ȡN/S
					case 5:
						memcpy(Save_Data.longitude, subString, subStringNext - subString);
						break; // ��ȡ������Ϣ
					case 6:
						memcpy(Save_Data.E_W, subString, subStringNext - subString);
						break; // ��ȡE/W

					default:
						break;
					}

					subString = subStringNext;
					Save_Data.isParseData = true;
					if (usefullBuffer[0] == 'A')
					{
						device_state_init.location_state = 1;
						Save_Data.isUsefull = true;
					}

					else if (usefullBuffer[0] == 'V')
						Save_Data.isUsefull = false;

					// if (Save_Data.latitude > 0 && Save_Data.longitude > 0)
					// {
					// }
				}
				else
				{
					errorLog(2); // ��������
				}
			}
		}
	}
}
F32 longitude_sum, latitude_sum;
U8 longitude_int, latitude_int;
void printGpsBuffer()
{
	// ת��Ϊ����
	longitude_sum = atof(Save_Data.longitude);
	latitude_sum = atof(Save_Data.latitude);
	// printf("ά�� = %.5f %.5f\r\n",longitude_sum,latitude_sum);
	// ����
	longitude_int = longitude_sum / 100;
	latitude_int = latitude_sum / 100;

	// ת��Ϊ��γ��
	longitude_sum = longitude_int + ((longitude_sum / 100 - longitude_int) * 100) / 60;
	latitude_sum = latitude_int + ((latitude_sum / 100 - latitude_int) * 100) / 60;
	device_state_init.location_state = 1;
	if (Save_Data.isParseData)
	{
		Save_Data.isParseData = false;

		// printf("Save_Data.UTCTime = %s\r\n", Save_Data.UTCTime);
		if (Save_Data.isUsefull)
		{
			Save_Data.isUsefull = false;
		}
		else
		{
			// printf("GPS DATA is not usefull!\r\n");
		}
	}
}
// ��ȡ���ݲ���
void Read_Data()
{
	Read_DHT11(&DHT11_Data); // ��ȡ��ʪ������
	Data_init.temperatuer = DHT11_Data.temp_int + DHT11_Data.temp_deci * 0.01;
	Data_init.humidity = DHT11_Data.humi_int + DHT11_Data.humi_deci * 0.01;
	Data_init.somg = Smog_Trans_Concentration(); // ��ȡ����Ũ��
	// ��ȡ��γ��
	parseGpsBuffer();
	// ������γ��
	printGpsBuffer();

	//����������
	if(Data_init.somg > threshold_value_init.threshold_somg_min){
		Beep=1;
	}else{
	 Beep=0;
	}
}
// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *threshold_value, Device_Satte_Typedef *device_state, Check_Hight_Typedef *check_hight)
{

	// threshold_value->threshold_light_min = 80;
	// threshold_value->threshold_humi_min = 100;
	threshold_value->threshold_somg_min = 400;
	// threshold_value->threshold_temperatuer_max = 25;
	// threshold_value->threshold_temperatuer_min = 28;



	return MY_SUCCESSFUL;
}
// ����OLED��ʾ��������
mySta Update_oled_massage()
{
	char str[50];
	u8 i;
	if (Data_init.Page == 0)
	{
		sprintf(str, "Temp: %.2f", Data_init.temperatuer);
		OLED_ShowString(0, 0, (unsigned char *)str, 16);
		sprintf(str, "Humi: %.2f", Data_init.humidity);
		OLED_ShowString(0, 16, (unsigned char *)str, 16);
		sprintf(str, "Somg: %04d", Data_init.somg);
		OLED_ShowString(0, 32, (unsigned char *)str, 16);
	}
	else if (Data_init.Page == 1)
	{
		
//			// ��ȡ����
//		car_dics_init.car_rigth_dics = (Get_SR04_Distance1() * 331) * 1.0/1000;
//		car_dics_init.car_run_dics = (Get_SR04_Distance2() * 331) * 1.0/1000;
//		car_dics_init.car_left_dics = (Get_SR04_Distance3() * 331) * 1.0/1000;
//		// ��ʾ�����ģʽ
//		if (car_dics_init.car_left_dics < 99999)
//		{
//			sprintf(str, "dis:%05d", car_dics_init.car_left_dics);
//		}

//		OLED_ShowString(0, 0, (unsigned char *)str, 16);
//		if (car_dics_init.car_run_dics < 99999)
//		{
//			sprintf(str, "dis:%05d", car_dics_init.car_run_dics);
//		}

//		OLED_ShowString(0, 16, (unsigned char *)str, 16);
//		if (car_dics_init.car_rigth_dics < 99999)
//		{
//			sprintf(str, "dis:%05d", car_dics_init.car_rigth_dics);
//		}

		// ����

		sprintf(str, "LON:%.6f", longitude_sum);
		OLED_ShowString(0, 0, (unsigned char *)str, 16);
		// γ��

		sprintf(str, "LAT:%.6f", latitude_sum);
		OLED_ShowString(0, 16, (unsigned char *)str, 16);
		OLED_Refresh(); // ������ʾ

		if (car_init.car_state == 1)
		{
			sprintf(str, "mode:   manual ");
		}
		else
			sprintf(str, "mode: automatic");
		OLED_ShowString(0, 32, (unsigned char *)str, 16);
	}
	OLED_Refresh(); // ������ʾ
	return MY_SUCCESSFUL;
}

// �����豸״̬
mySta Update_Device_Massage(Device_Satte_Typedef *device_state)
{
	// ���в���ִֻ��һ�Σ���Լϵͳ��Դ

	return MY_SUCCESSFUL;
}

// ��ⰴ���Ƿ���
static U8 num_on = 0;
static U8 key_old = 0;
void Check_Key_ON_OFF()
{
	U8 key;
	key = KEY_Scan(1);
	// ����һ�εļ�ֵ�Ƚ� �������ȣ������м�ֵ�ı仯����ʼ��ʱ
	if (key != 0 && num_on == 0)
	{
		key_old = key;
		num_on = 1;
	}
	if (key != 0 && num_on >= 1 && num_on <= Key_Scan_Time) // 25*10ms
	{
		num_on++; // ʱ���¼��
	}
	if (key == 0 && num_on > 0 && num_on < Key_Scan_Time) // �̰�
	{
		switch (key_old)
		{
		case KEY1_PRES:
			printf("Key1_Short\n");
			if (car_init.car_state == 1)
			{
				car_init.car_state = 2;
			}
			else
			{
				car_init.car_state = 1;
			}
			break;

		default:
			break;
		}
		num_on = 0;
	}
	else if (key == 0 && num_on >= Key_Scan_Time) // ����
	{
		switch (key_old)
		{
		case KEY1_PRES:
			OLED_Clear();
			if (Data_init.Page == 0)
			{
				Data_init.Page = 1;
			}
			else
				Data_init.Page = 0;

			break;

		default:
			break;
		}
		num_on = 0;
	}
}
