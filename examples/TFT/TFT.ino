#include "AXS15231B.h"
#include <Arduino.h>

bool result = false;
void setup() {
    Serial.begin(115200);
    Serial.println("sta\n");

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    axs15231_init();

    Serial.println("end\n");
}

extern uint32_t transfer_num;
extern size_t lcd_PushColors_len;

#define RECT_W 24
#define RECT_H 100

bool first_flag = true;

void loop() {
    if (first_flag) {
        uint16_t data1[RECT_W * RECT_H];
        for (uint16_t i = 0; i < sizeof(data1)/sizeof(data1[0]); i++) {
            data1[i] = 0b1111100000000000;
        }
        lcd_PushColors(0, 0, RECT_W, RECT_H, (uint16_t *)data1);
        first_flag = false;
    }
    
    delay(1);
}
