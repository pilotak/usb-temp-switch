#include <SoftwareSerial.h>
#include "MeteoFunctions.h"
#include <dht.h>

SoftwareSerial pc = SoftwareSerial(SERIAL_RX, SERIAL_TX);
MeteoFunctions calc;
dht DHT;

char rx_buf[4] = {0};
uint8_t rx_buf_index = 0;
unsigned long previous_millis = 0;

void readTemp() {
    int status = DHT.read22(TEMP_PIN);

    if (status == DHTLIB_OK) {
#if defined(CELSIUS)
        float temp = DHT.temperature;
        pc.print("t=");
        pc.println(temp, 1);

#elif defined(FAHRENHEIT)
        float temp = calc.c_f(DHT.temperature);
        pc.print("t=");
        pc.println(temp, 1);
#endif

        pc.print("h=");
        pc.println(DHT.humidity, 1);

    } else {
        pc.println("ERROR");
    }
}

void setup() {
    pinMode(OUT_PIN, OUTPUT);
    pc.begin(SERIAL_SPEED);

    pc.print("f=");
    pc.print(FW_VERSION);
    pc.print("b=");
    pc.print(HW_VER);

    pc.println("d=0"); // in case of restart, let PC know we are off
    readTemp();
}

void loop() {
    while (pc.available()) {
        rx_buf[rx_buf_index] = pc.read();

        if (rx_buf_index == 0 && rx_buf[rx_buf_index] == 'd') {
            rx_buf_index++;

        } else if (rx_buf_index == 1 && rx_buf[rx_buf_index] == '=') {
            rx_buf_index++;

        } else if (rx_buf_index == 2 && (rx_buf[rx_buf_index] == '0' || rx_buf[rx_buf_index] == '1')) {
            if (rx_buf[rx_buf_index] == '0') {
                digitalWrite(OUT_PIN, LOW);

            } else {
                digitalWrite(OUT_PIN, HIGH);
            }

            pc.println(rx_buf); // send confirmation

            rx_buf_index = 0;
            memset(rx_buf, 0, sizeof(rx_buf));

        } else {
            rx_buf_index = 0;
        }
    }

    unsigned long current_millis = millis();

    // prevent sending when reading serial
    if (rx_buf_index == 0 && current_millis - previous_millis >= TEMP_INTERVAL) {
        previous_millis = current_millis;
        readTemp();
    }
}
