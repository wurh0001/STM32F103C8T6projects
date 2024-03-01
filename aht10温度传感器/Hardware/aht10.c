/**
 * @FilePath     : /aht10温度传感器/Hardware/aht10.c
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-01-29 21:36:39
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-02 23:18:34
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#include <stdint.h>
#include <stdio.h>
#include "MyI2C.h"
#include "delay.h"
#include "aht10.h"

#define AHT10_ADDR 0x70 // AHT10的I2C地址为0x38，但是在STM32中，I2C的地址为7位，所以要左移一位，得到0x70 为写地址，0x71为读地址
#define AHT10_TRIGGER_MEASUREMENT 0xAC  // 触发测量命令
#define AHT10_I2C_ACK 0x00

// struct aht10_data
// {
//     uint8_t status;
//     uint8_t humi_high;
//     uint8_t humi_low;
//     uint8_t humi_temp;
//     uint8_t temp_high;
//     uint8_t temp_low;
// };
// struct aht10_data raw_data;
float cal_data[2];
uint8_t aht10_data[6];

uint8_t Aht10_ViewCalibration(void)
{
    uint8_t status_word = 0;
    uint8_t ack = 0;
    MyI2C_Start();
    MyI2C_SendByte(0x71); // 发送读地址，获取AHT10的状态字
    ack = MyI2C_ReceiveAck();
    status_word = MyI2C_ReceiveByte();   // 读取状态字
    MyI2C_SendAck(AHT10_I2C_ACK);      // 发送非应答信号
    MyI2C_Stop();
    return status_word;
}

void Aht10_InterInit(void)
{
    uint8_t ack = 0;
    MyI2C_Start();
    MyI2C_SendByte(AHT10_ADDR);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0xe1);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0x08);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0x00);
    ack = MyI2C_ReceiveAck();
    MyI2C_Stop();
}

void AHT10_SoftReset(void)
{
    uint8_t ack = 0;
    MyI2C_Start();
    MyI2C_SendByte(AHT10_ADDR);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0xBA);
    ack = MyI2C_ReceiveAck();
    // MyI2C_SendByte(0x00);
    // ack = MyI2C_ReceiveAck();
    MyI2C_Stop();
}

void AHT10_Init(void)
{   
    uint8_t status_word = 0;
    uint8_t repeat_time = 0;
    uint8_t ack = 0;
    DelayMs(40);    // 上电延时40ms
    MyI2C_Init();
    Aht10_InterInit();
    status_word = Aht10_ViewCalibration();
    // printf("status_word:%d----\r\n",status_word);
    while(!(status_word & 0x08))
    {
        // 
        printf("AHT10 init not Calibration\n");
        if(repeat_time == 0)
        {
            Aht10_InterInit();
            status_word = Aht10_ViewCalibration();
            repeat_time++;
            DelayMs(100);
        }
        else if(repeat_time > 0 && repeat_time <= 5)
        {
            Aht10_InterInit();
            status_word = Aht10_ViewCalibration();
            repeat_time++;
            DelayMs(100);
        }
        else
        {
            // 初始化失败
            printf("AHT10 init fail\n");
            break;
        }
    }
    
}

void AHT10_TriggerMeasurement(void)
{
    uint8_t i, ack;
    MyI2C_Start();
    MyI2C_SendByte(AHT10_ADDR);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(AHT10_TRIGGER_MEASUREMENT);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0x33);
    ack = MyI2C_ReceiveAck();
    MyI2C_SendByte(0x00);
    ack = MyI2C_ReceiveAck();
    MyI2C_Stop();
}

struct aht10_data AHT10_ReadData(void)
{
    uint8_t ack;
    struct aht10_data raw_data;
    MyI2C_Start();
    MyI2C_SendByte(0x71);
    ack = MyI2C_ReceiveAck();
    raw_data.status = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    if(raw_data.status & 0x80)
    {
        // printf("AHT10 status need delay 150----\r\n");
        DelayMs(150);
    }
    raw_data.humi_high = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    raw_data.humi_low = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    raw_data.humi_temp = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    raw_data.temp_high = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    raw_data.temp_low = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    MyI2C_Stop();
    return raw_data;

}

void Aht10_ReadData(void)
{
    uint8_t ack;    
    MyI2C_Start();
    MyI2C_SendByte(0x71);
    ack = MyI2C_ReceiveAck();
    aht10_data[0] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    aht10_data[1] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    aht10_data[2] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    aht10_data[3] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    aht10_data[4] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    aht10_data[5] = MyI2C_ReceiveByte();
    MyI2C_SendAck(AHT10_I2C_ACK);
    MyI2C_Stop();

}

void Aht10_CalData(struct aht10_data raw_data)
{
    uint32_t humi = (raw_data.humi_high<<16) | (raw_data.humi_low<<8) | (raw_data.humi_temp & 0xf0);
    humi = humi>>4;
    uint32_t temp = ((raw_data.humi_temp & 0x0f)<<16) | (raw_data.temp_high<<8) | (raw_data.temp_low);
    // printf("humi_raw:%d----\r\n",humi);
    // printf("temp_raw:%d----\r\n",temp);
    float humi_cal, temp_cal;
    humi_cal = ((float)humi/1048576)*100;
    temp_cal = ((float)temp/1048576)*200 - 50;    
    cal_data[0] = humi_cal;
    cal_data[1] = temp_cal;
    
}

void Aht10_CalData02(void)
{
    uint32_t humi = (aht10_data[1]<<16) | (aht10_data[2]<<8) | (aht10_data[3] & 0xf0);
    humi = humi>>4;
    uint32_t temp = ((aht10_data[3] & 0x0f)<<16) | (aht10_data[4]<<8) | (aht10_data[5]);
    // printf("humi_raw:%d----\r\n",humi);
    // printf("temp_raw:%d----\r\n",temp);
    float humi_cal, temp_cal;
    humi_cal = ((float)humi/1048576)*100;
    temp_cal = ((float)temp/1048576)*200 - 50;    
    cal_data[0] = humi_cal;
    cal_data[1] = temp_cal;
}
