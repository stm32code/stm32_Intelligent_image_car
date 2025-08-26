package com.example.esp_car.Socket

import android.os.Handler
import android.util.Log
import com.example.esp_car.Utils.Common
import java.lang.Exception
import java.net.Socket

class SocketClientThread(
    private val ip: String,
    private val port: Int,
    private val handler: Handler
) :
    Thread() {
    private var mSocket: Socket? = null
    private var socketDataThread: SocketDataThread? = null
    override fun run() {
        try {
            /**
             * 循环连接1次，如果连接上则直接退出
             */
            for (i in 0..9) {
                mSocket = Socket(ip, port)
                if (mSocket!!.isConnected) {
                    Common.SOCKET_CONNET = true
                    Log.e("Socket连接", "连接成功")
                    socketDataThread = SocketDataThread(mSocket!!, handler)
                    socketDataThread!!.start()
                    handler.sendMessage(handler.obtainMessage(Common.SOCKET_CONNET_OK, ""))
                    break
                }
                sleep(500)
                Log.e("Socket连接", "第" + (i + 1).toString() + "次重连中")
            }
            if (!Common.SOCKET_CONNET) handler.sendMessage(
                handler.obtainMessage(
                    Common.SOCKET_CONNET_ERROR,
                    ""
                )
            )
        } catch (e: Exception) {
            Common.SOCKET_CONNET = false
            Log.e("Socket连接", e.toString())
        }
    }

    /**
     * 发送数据
     *
     * @param data 要发送的数据
     */
    fun SendMessage(data: String?) {
        if (socketDataThread != null) {
            socketDataThread!!.sendMessage(data!!)
        }
    }

    /**
     * 断开连接
     */
    fun Cancel() {
        try {
            socketDataThread!!.Cancel()
            mSocket!!.close() //关闭连接
            Log.e("Socket连接", "关闭成功")
            Common.SOCKET_CONNET = false
        } catch (e: Exception) {
            Common.SOCKET_CONNET = false
            Log.e("Socket断开连接失败", e.toString())
        }
    }
}