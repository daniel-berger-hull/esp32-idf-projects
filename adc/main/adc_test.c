
#include <stdio.h>
#include <driver/adc.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include "esp_adc_cal.h"


static char tag[] = "adc1";



static esp_adc_cal_characteristics_t *adc_chars;

void app_main()
{

    ESP_LOGD(tag, ">> adc1");
    adc1_config_width(ADC_WIDTH_12Bit);
//    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_6db);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);

    



    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    
    while(1) {
//        int value = adc1_get_voltage(ADC1_CHANNEL_6);
//        ESP_LOGD(tag, "value: %d", value);


        uint32_t adc_reading = adc1_get_raw((adc1_channel_t)ADC1_CHANNEL_6);
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);

        ESP_LOGD(tag, "value: %d", adc_reading);
        printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
        //printf("Raw: %d\n", adc_reading, voltage);
        
        vTaskDelay(pdMS_TO_TICKS(1000));


        //vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    
    
    
}


