#include "AXS15231B.h"
#include <Arduino.h>

uint16_t data1[128] = {
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,

    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,

    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,

    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,

    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,

    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, 
    (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111, (uint16_t) 0b0000000000011111,
};

extern uint8_t test1_180640_map[];
extern uint8_t test2_180640_map[];
extern uint8_t test3_180640_map[];
extern uint8_t test4_180640_map[];

static uint16_t fill_mem_all[TFT_WIDTH * TFT_HEIGHT / 32];

bool result = false;
void setup() {
    Serial.begin(115200);
    Serial.println("sta\n");

    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    axs15231_init();
    delay(1000);
    
    for(int i = 0; i < TFT_WIDTH * TFT_HEIGHT / 32; i+=1) {
        fill_mem_all[i] = 0b0000011111100000;
    }
    lcd_PushColors(0,  0,   9, 359, (uint16_t*)fill_mem_all);

    Serial.println("end\n");
}

extern uint32_t transfer_num;
extern size_t lcd_PushColors_len;
int cont = 0;
void loop() {
    delay(1);
    cont++;

    if(cont >= 1000)
        cont = 0;

    if (transfer_num <= 0 && lcd_PushColors_len <= 0)
    {
        #ifdef LCD_SPI_DMA
            char i = 0;
            while (get_lcd_spi_dma_write())
            {
                i = i >> 1;
                lcd_PushColors(0, 0, 0, 0, NULL);
            }
        #endif

        if(cont == 0) {
            lcd_PushColors(5, 10, 1, 128, (uint16_t *)data1);
        }
    }

    if (transfer_num <= 1 && lcd_PushColors_len > 0) {
        lcd_PushColors(0, 0, 0, 0, NULL);
    }
}
