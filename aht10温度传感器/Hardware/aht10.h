/**
 * @FilePath     : /aht10温度传感器/Hardware/aht10.h
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-01-30 21:20:24
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-02 23:39:41
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#ifndef __AHT10_H
#define __AHT10_H

// #include "MyI2C.h"
// #include "delay.h"
// #include "stm32f10x.h"
extern uint8_t aht10_data[6];
struct aht10_data
{
    uint8_t status;
    uint8_t humi_high;
    uint8_t humi_low;
    uint8_t humi_temp;
    uint8_t temp_high;
    uint8_t temp_low;
};
// extern struct aht10_data raw_data;
extern float cal_data[2];

void AHT10_Init(void);
void AHT10_TriggerMeasurement(void);
void AHT10_SoftReset(void);
void Aht10_ReadData(void);
struct aht10_data AHT10_ReadData(void);
void Aht10_CalData(struct aht10_data raw_data);
void Aht10_CalData02(void);

#endif
