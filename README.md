
智能图像小车
硬件端：
1.	ESP32-can获取图像并传输到APP端
2.	使用PWM的方式控制小车的转速
3.	获取周围的环境数据
4.	自动避障功能
5.	添加GPS信息获取功能

APP端：
1.	接收图像信息显示到APP端
2.	显示小车的基本信息
3.	显示环境数据
4.	显示环境数据以及经纬度；
5.	有害气体弹框提示

协议对接：
设备->APP
{ “longitude”:“float”, “latitude”:“float”,“temp”:“float”,“humi”:“float”, “humi”:“float”, “somg”:“int”}
