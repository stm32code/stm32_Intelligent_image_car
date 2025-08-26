package com.example.esp_car.Utils

object Common {

//    var SOCKET_IP = "192.168.43.126" //连接IP地址
    var SOCKET_IP = "192.168.4.1" //连接IP地址
    var SOCKET_PORT = "8000" //连接端口号

    var SOCKET_CONNET = false //是否连接

    const val SOCKET_CONNET_OK = 403 //连接成功

    const val SOCKET_CONNET_ERROR = 400 //连接错误

    const val SOCKET_SEND_DATA = 401 //发送消息

    const val SOCKET_SEND_ERROR = 405 //发送失败

    const val SOCKET_RECEIVE_DATA = 402 //接收到消息

    const val SOCKET_RECEIVE_ERROR = 404 //接收错误

    var SOCKET_BUSY = false //是否在忙

    var CAR_SPEED = "{speed:10"
    var CAR_DIRECTION = ""

}
