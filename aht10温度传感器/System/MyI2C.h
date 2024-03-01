/**
 * @FilePath     : /aht10温度传感器/System/MyI2C.h
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-01-29 21:51:59
 * @Version      : 0.0.1
 * @LastEditTime : 2024-01-31 21:23:56
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#ifndef __MYI2C_H
#define __MYI2C_H

// #include "stm32f10x.h"
// #include "Delay.h"

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif
