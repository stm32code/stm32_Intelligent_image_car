#include "git.h"

#include "dht11.h"

#include "adc.h"
#include "bh1750.h"

DHT11_Data_TypeDef DHT11_Data;

Data_TypeDef Data_init;
/**************************************************************************************
 * 描  述 : 获取数据参数
 * 入  参 : 8
 * 返回值 : uint8_t
 **************************************************************************************/
void Read_Data(Data_TypeDef *Device_Data)
{
	Read_DHT11(&DHT11_Data); // 获取温湿度数据

	// Device_Data->somg = 6000 - Smog_Trans_Concentration(); // 获取烟雾数据
	Device_Data->light = getValue(); // 获取光感强度
}
