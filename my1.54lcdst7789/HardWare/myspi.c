/**
 * @FilePath     : /my1.54lcdst7789/HardWare/myspi.c
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-02-16 15:50:44
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-24 17:05:04
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/
// #include "stm32f10x.h"                  // Device header
#include "myspi.h"

void SPI_Start(void)
{
    SPI_CS_L();
}

void SPI_End(void)
{
    SPI_CS_H();
}



#ifdef SOFTSPI

    void MYSPI_Init(void)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        SPI_CS_H();   //SPI1 CS空闲
        SPI_RST_H();  //复位空闲
        SPI_DC_H();   //数据/命令选择空闲
        SPI_SCK_H();  //时钟空闲
        SPI_SDA_H();  //数据空闲
    }

    void SPI_SendByte(uint8_t Sendbyte)
    {
        uint8_t i;
        // SPI_CS_L();
        SPI_SCK_L();
        for(i = 0; i < 8; i++)
        {
            SPI_SCK_L();
            if(Sendbyte & 0x80)
            {
                SPI_SDA_H();
            }
            else
            {
                SPI_SDA_L();
            }
            Sendbyte <<= 1;
            SPI_SCK_H();
            SPI_SCK_L();
        }
    }

#elif defined HARDSPI
    void MYSPI_Init(void)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);    //使能SPI1时钟
        SPI_InitTypeDef SPI_InitStructure;

        SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
        SPI_InitStructure.SPI_Mode = SPI_Mode_Master;    //设置SPI工作模式:设置为主SPI
        SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;    //设置SPI的数据大小:SPI发送接收8位帧结构
        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;    //串行同步时钟的空闲状态为低电平
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;    //串行同步时钟的第一个跳变沿（上升或下降）数据被采样
        SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;    //NSS信号由硬件（NSS管脚）还是软件（SSI位）管理:内部NSS信号有SSI位控制
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;    //256分频
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;    //数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
        SPI_InitStructure.SPI_CRCPolynomial = 7;    //CRC值计算的多项式
        SPI_Init(SPI1, &SPI_InitStructure);
        SPI_Cmd(SPI1, ENABLE);

        // SPI_CS_H();   //SPI1 CS空闲
        SPI_End();
        SPI_RST_H();  //复位空闲
    }

    void SPI_SendByte(uint8_t Sendbyte)
    {
        uint8_t i;
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);    //等待发送区空
        SPI_I2S_SendData(SPI1, Sendbyte);    //通过外设SPI1发送一个byte  数据
        // SPI1->SR &= (1<<0);    //清除发送区空标志
        SPI1->SR;    //清除发送区空标志
        // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);    //等待发送完毕
        // while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
        // i = SPI_I2S_ReceiveData(SPI1);    //清除RXNE标志
    }
#endif






