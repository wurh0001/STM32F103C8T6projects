#include "stm32f10x.h"
// #include "OLED_I2C.h"
#include "delay.h"
#include "aht10.h"
#include "MyI2C.h"
#include <stdio.h>


void Serial_Init(void)
{
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    
    USART_Cmd(USART1, ENABLE);
}
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

int main(void)
{
    uint8_t i;
    
    DelayInit();
    Serial_Init();
    // I2C_Configuration();
    // OLED_Init();
    MyI2C_Init();
    AHT10_Init();
    // AHT10_TriggerMeasurement();
    while(1)
    {
        if(i==5)
        {
        AHT10_SoftReset();
        i = 0;
        }
        i++;
        AHT10_TriggerMeasurement();
        DelayMs(150);
        // struct aht10_data raw_data = AHT10_ReadData();
        // printf("status:%d----\r\n",raw_data.status);
        // Aht10_CalData(raw_data);
        // printf("humi:%f----\n",cal_data[0]);
        // printf("temp:%f----\n",cal_data[1]);
        Aht10_ReadData();
        printf("status:%d----\r\n",aht10_data[0]);
        printf("humi_high:%d----\r\n",aht10_data[1]);
        printf("humi_low:%d----\r\n",aht10_data[2]);
        printf("humi_temp:%d----\r\n",aht10_data[3]);
        printf("temp_high:%d----\r\n",aht10_data[4]);
        printf("temp_low:%d----\r\n",aht10_data[5]);
        Aht10_CalData02();
        printf("humi:%f----\n",cal_data[0]);
        printf("temp:%f----\n",cal_data[1]);
        // DelayS(1);
        // -------------------------------------------
        // OLED_ShowNum(0,0,cal_data[0],0,16);//显示湿度
        // OLED_ShowNum(0,2,cal_data[1],0,16);//显示温度
        // OLED_Fill(0xFF);//全屏点亮
        // DelayS(1);
        // OLED_Fill(0x00);//全屏灭
        // DelayS(1);
        // for(i=0;i<5;i++)
        // {
        //     OLED_ShowCN(22+i*16,0,i);//测试显示中文
        // }
        // DelayS(1);
        // OLED_ShowStr(0,3,"hello world",1);//测试6*8字符
        // OLED_ShowStr(0,4,"Hello World",2);       //测试8*16字符
        // DelayS(1);
        // OLED_CLS();//清屏
        // OLED_OFF();//测试OLED休眠
        // DelayS(1);
        // OLED_ON();//测试OLED休眠后唤醒
        // DelayS(1);
    }
}
