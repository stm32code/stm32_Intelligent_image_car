package com.example.esp_car.been

data class Receive(
    var Location_state: String? = null,
    var longitude: String? = null,
    var latitude: String? = null,
    var temp: String? = null,
    var humi: String? = null,
    var somg: String? = null
)
