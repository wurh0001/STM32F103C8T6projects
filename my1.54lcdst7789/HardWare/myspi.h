/**
 * @FilePath     : /my1.54lcdst7789/HardWare/myspi.h
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-02-16 15:50:52
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-20 15:35:58
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#ifndef __MY_SPI_H
#define __MY_SPI_H

#include "stm32f10x.h"                  // Device header

typedef unsigned char uint8_t;
//#define HARDSPI     // 选择使用硬件SPI通信
#define SOFTSPI     // 选择使用模拟SPI通信

    #ifdef SOFTSPI
    /*-------------------------------------以下为模拟SPI的宏定义---------------------------------------------*/
    #define SPI_SCK_H() GPIO_SetBits(GPIOA, GPIO_Pin_5)
    #define SPI_SCK_L() GPIO_ResetBits(GPIOA, GPIO_Pin_5)
    #define SPI_SDA_H() GPIO_SetBits(GPIOA, GPIO_Pin_7)
    #define SPI_SDA_L() GPIO_ResetBits(GPIOA, GPIO_Pin_7)
    #define SPI_RST_H() GPIO_SetBits(GPIOA, GPIO_Pin_2)
    #define SPI_RST_L() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
    #define SPI_DC_H() GPIO_SetBits(GPIOA, GPIO_Pin_3)
    #define SPI_DC_L() GPIO_ResetBits(GPIOA, GPIO_Pin_3)
    #define SPI_CS_H() GPIO_SetBits(GPIOA, GPIO_Pin_4)
    #define SPI_CS_L() GPIO_ResetBits(GPIOA, GPIO_Pin_4)

    void MYSPI_Init(void);
    void SPI_SendByte(uint8_t byte);

    #elif defined HARDSPI
    /*-------------------------------------以下为硬件SPI的宏定义---------------------------------------------*/
    #define SPI_CS_H() GPIO_SetBits(GPIOA, GPIO_Pin_4)
    #define SPI_CS_L() GPIO_ResetBits(GPIOA, GPIO_Pin_4)
    #define SPI_RST_H() GPIO_SetBits(GPIOA, GPIO_Pin_2)
    #define SPI_RST_L() GPIO_ResetBits(GPIOA, GPIO_Pin_2)
    #define SPI_DC_H() GPIO_SetBits(GPIOA, GPIO_Pin_3)
    #define SPI_DC_L() GPIO_ResetBits(GPIOA, GPIO_Pin_3)

    void MYSPI_Init(void);
    void SPI_SendByte(uint8_t Sendbyte);

    #endif

void SPI_Start(void);
void SPI_End(void);

#endif
