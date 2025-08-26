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

#define HEGHT 1000	 // �߶���ֵ
#define TIME_OVER 10 // ����Ͱ�Զ��ر�ʱ�䣨10�룩

// �Զ���ִ�н������
typedef enum
{
	MY_SUCCESSFUL = 0x01, // �ɹ�
	MY_FAIL = 0x00		  // ʧ��

} mySta; // �ɹ���־λ

typedef enum
{
	OPEN = 0x01, // ��
	CLOSE = 0x00 // �ر�

} On_or_Off_TypeDef; // �ɹ���־λ

typedef enum
{
	DERVICE_SEND = 0x00, // �豸->ƽ̨
	PLATFORM_SEND = 0x01 // ƽ̨->�豸

} Send_directino; // ���ͷ���

typedef struct
{

	U8 Page;		  // ����
	U8 light;		  // ����
	U8 soil_humidity; // ����ʪ��
	U16 somg;		  // ����Ũ��
	F32 temperatuer;  // �¶�
	F32 humidity;	  // ʪ��

} Data_TypeDef; // ���ݲ����ṹ��

typedef struct
{
	U8 threshold_temp_min;			// �����¶�
	U8 threshold_humi_min;			// ����ʪ��
	U8 threshold_light_min;			// ����
	U8 threshold_soil_humidity_max; // ����ʪ��
	U8 threshold_soil_humidity_min; // ����ʪ��
	F32 threshold_somg_max;			// ����Ũ��
	F32 threshold_somg_min;			// ����Ũ��
	F32 threshold_temperatuer_max;	// �¶�
	F32 threshold_temperatuer_min;	// �¶�

} Threshold_Value_TypeDef; // ���ݲ����ṹ��

typedef struct
{
	
	U8 massgae_wanning; // �绰����
	U8 location_state;	// ��λ

} Device_Satte_Typedef; // ״̬�����ṹ��

typedef struct
{
	U8 check_A; // �߶�1
	U8 check_B; // �߶�2
	U8 check_C; // �߶�3
	U8 check_D; // �߶�4

} Check_Hight_Typedef; // ��������������ѹ����

// ��ȡ���ݲ���
void Read_Data(void);
// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *threshold_value, Device_Satte_Typedef *device_state, Check_Hight_Typedef *check_hight);
// ����OLED��ʾ��������
mySta Update_oled_massage(void);
// �����豸״̬
mySta Update_Device_Massage(Device_Satte_Typedef *device_state);
// ����Ƿ����
mySta Check_Rubbish_Massage(Check_Hight_Typedef *hight_data);
// �Զ����
void Check_Key_ON_OFF(void);
// �Զ��رն��

#endif
