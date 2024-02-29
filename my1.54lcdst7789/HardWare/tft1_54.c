/**
 * @FilePath     : /my1.54lcdst7789/HardWare/tft1_54.c
 * @Description  :  
 * @Author       : wuu
 * @Date         : 2024-02-17 16:56:42
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-29 22:18:17
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#include "myspi.h"
#include "delay.h"
#include "fonts.h"

#define TFT_COLUMN_NUMBER 240	//TFT屏幕列数
#define TFT_LINE_NUMBER 240		//TFT屏幕行数
#define TFT_COLUMN_OFFSET 0		//TFT屏幕列偏移
#define TFT_LINE_OFFSET 0		//TFT屏幕行偏移
#define TFT_COLUMN_ADDRESS_SETTINGS 0X2A    //列地址设置
#define TFT_ROW_ADDRESS_SETTINGS 0X2B       //行地址设置
#define TFT_MEMORY_WRITE 0X2C               //内存写

void TFT_SendData(uint8_t data)
{
    SPI_DC_H();
    SPI_Start();
    // SPI_SendByte(data);
	SPI_SendByte(data);
    SPI_End();
}

void TFT_SendCmd(uint8_t cmd)
{
    SPI_DC_L();
    SPI_Start();
    // SPI_SendByte(cmd);
	SPI_SendByte(cmd);
    SPI_End();
}

void TFT_Init(void)
{
	MYSPI_Init();
    // SPI_SCK_L();
	SPI_RST_L();
	DelayMs(1000);
	SPI_RST_H();
	DelayMs(1000);
	TFT_SendCmd(0x11); // Sleep Out
	DelayMs(120);		// DELAY120ms
	//--------------------------------ST7789S Frame rate setting----------------------------------//
	TFT_SendCmd(0x2a);	 // Column address set
	TFT_SendData(0x00); // start column
	TFT_SendData(0x00);
	TFT_SendData(0x00); // end column
	TFT_SendData(0xef);

	TFT_SendCmd(0x2b);	 // Row address set
	TFT_SendData(0x00); // start row
	TFT_SendData(0x28);
	TFT_SendData(0x01); // end row
	TFT_SendData(0x17);

	TFT_SendCmd(0xb2); // Porch control
	TFT_SendData(0x0c);
	TFT_SendData(0x0c);
	TFT_SendData(0x00);
	TFT_SendData(0x33);
	TFT_SendData(0x33);

	TFT_SendCmd(0x20); // Display Inversion Off

	TFT_SendCmd(0xb7);	 // Gate control
	TFT_SendData(0x56); // 35
	//---------------------------------ST7789S Power setting--------------------------------------//
	TFT_SendCmd(0xbb);	 // VCOMS Setting
	TFT_SendData(0x18); // 1f

	TFT_SendCmd(0xc0); // LCM Control
	TFT_SendData(0x2c);

	TFT_SendCmd(0xc2); // VDV and VRH Command Enable
	TFT_SendData(0x01);

	TFT_SendCmd(0xc3);	 // VRH Set
	TFT_SendData(0x1f); // 12

	TFT_SendCmd(0xc4); // VDV Setting
	TFT_SendData(0x20);

	TFT_SendCmd(0xc6); // FR Control 2
	TFT_SendData(0x0f);
	// TFT_SendCmd(0xca);
	// TFT_SendData(0x0f);
	// TFT_SendCmd(0xc8);
	// TFT_SendData(0x08);
	// TFT_SendCmd(0x55);
	// TFT_SendData(0x90);
	TFT_SendCmd(0xd0);	 // Power Control 1
	TFT_SendData(0xa6); // a4
	TFT_SendData(0xa1);
	//--------------------------------ST7789S gamma setting---------------------------------------//

	TFT_SendCmd(0xe0);
	TFT_SendData(0xd0);
	TFT_SendData(0x0d);
	TFT_SendData(0x14);
	TFT_SendData(0x0b);
	TFT_SendData(0x0b);
	TFT_SendData(0x07);
	TFT_SendData(0x3a);
	TFT_SendData(0x44);
	TFT_SendData(0x50);
	TFT_SendData(0x08);
	TFT_SendData(0x13);
	TFT_SendData(0x13);
	TFT_SendData(0x2d);
	TFT_SendData(0x32);

	TFT_SendCmd(0xe1); // Negative Voltage Gamma Contro
	TFT_SendData(0xd0);
	TFT_SendData(0x0d);
	TFT_SendData(0x14);
	TFT_SendData(0x0b);
	TFT_SendData(0x0b);
	TFT_SendData(0x07);
	TFT_SendData(0x3a);
	TFT_SendData(0x44);
	TFT_SendData(0x50);
	TFT_SendData(0x08);
	TFT_SendData(0x13);
	TFT_SendData(0x13);
	TFT_SendData(0x2d);
	TFT_SendData(0x32);

	TFT_SendCmd(0x36); // Memory data access control
	TFT_SendData(0x00);

	TFT_SendCmd(0x3A);	 // Interface pixel format
	TFT_SendData(0x55); // 65K
	// TFT_SendData(0x66);			//262K  RGB 6 6 6

	TFT_SendCmd(0xe7); // SPI2 enable    启用2数据通道模式
	TFT_SendData(0x00);

	TFT_SendCmd(0x21); // Display inversion on
	TFT_SendCmd(0x29); // Display on
}

/**
 * @brief        : 设置TFT显示区域 调用该函数后，再发送数据（颜色），将显示在设置的区域
 * @param         {uint16_t} x0: 列起始地址
 * @param         {uint16_t} y0: 列结束地址
 * @param         {uint16_t} x1: 行起始地址
 * @param         {uint16_t} y1: 行结束地址
 * @return        {*}
**/
void TFT_SetAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint16_t x = x0, y = x1;
    TFT_SendCmd(TFT_COLUMN_ADDRESS_SETTINGS); // Column address set
    TFT_SendData(x >> 8);  //依次发送列起始地址的高8位和低8位
    TFT_SendData(x & 0xff);
    TFT_SendData(y >> 8);  //一次发送列结束地址的高8位和低8位
    TFT_SendData(y & 0xff);
    x = y0, y = y1;
    TFT_SendCmd(TFT_ROW_ADDRESS_SETTINGS); // Row address set
    TFT_SendData(x >> 8);
    TFT_SendData(x & 0xff);
    TFT_SendData(y >> 8);
    TFT_SendData(y & 0xff);
    TFT_SendCmd(TFT_MEMORY_WRITE); // Memory write 
}

/**
 * @brief        : TFT清屏，或者填充整个屏幕
 * @param         {uint16_t} color: 清屏颜色或者填充颜色
 * @return        {*}
**/
void TFT_Clear_Full(uint16_t color)
{
    uint16_t i, j;
    TFT_SetAddr(0, 0, TFT_COLUMN_NUMBER - 1, TFT_LINE_NUMBER - 1);
    for (i = 0; i < TFT_COLUMN_NUMBER; i++)
    {
        for (j = 0; j < TFT_LINE_NUMBER; j++)
        {
            TFT_SendData(color >> 8);
            TFT_SendData(color);
        }
    }
}

void TFT_DisplayAscii(uint16_t x, uint16_t y, uint8_t ascii, uint16_t color)
{
	uint8_t i, j;
	uint8_t temp;
	uint16_t y0 = y;
	ascii = ascii - ' ';
	TFT_SetAddr(x, y, x + 8 - 1, y + 16 - 1);
	for(i = 0; i < 16; i++)
	{
		temp = ASCII_Table_8x16[ascii * 16 + i];
		for(j = 0; j < 8; j++)
		{
			if(temp & 0x80)
			{
				TFT_SendData(color >> 8);
				TFT_SendData(color);
			}
			else
			{
				TFT_SendData((~color) >> 8);
				TFT_SendData(~color);
			}
			temp <<= 1;
		}
	}
}

/**
 * @brief   : 在屏幕指定位置显示字符串，字符串以'\0'结束，显示颜色为color
 * @param    {uint16_t} x: 横轴起始位置
 * @param    {uint16_t} y: 纵轴起始位置
 * @param    {uint8_t} *str: 待显示的字符串
 * @param    {uint16_t} color: 字符串的颜色
 * @return   {*}
**/
void TFT_DisplayAsciiStr(uint16_t x, uint16_t y, uint8_t *str, uint16_t color)
{
	uint16_t x0 = x;
	while(*str != '\0')
	{
		TFT_DisplayAscii(x0, y, *str, color);
		x0 += 8;
		str++;
	}
}

// 显示一条直线或者矩形
void TFT_DisplayStraightLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
	int16_t dx, dy;
	uint16_t i, j;
	dx = x1 - x0;
	dy = y1 - y0;
	if(dx >= 0)
	{
		// 竖直线
		if(dx > dy)
		{
			for(j = 0; j < dx; j++)
			{
				for(i = 0; i < dy; i++)
				{
					TFT_SetAddr(x0, y0 + i, x0, y0 + i);
					TFT_SendData(color >> 8);
					TFT_SendData(color);
				}
				x0++;
			}
		}
		// 横线
		else
		{
			for(j = 0; j < dy; j++)
			{
				for(i = 0; i < dx; i++)
				{
					TFT_SetAddr(x0 + i, y0, x0 + i, y0);
					TFT_SendData(color >> 8);
					TFT_SendData(color);
				}
				y0++;
			}
		}
	}
}

// 显示一个矩形
void TFT_DisplayRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t width, uint16_t color)
{
	TFT_DisplayStraightLine(x0, y0, x1, y0 + width, color);
	TFT_DisplayStraightLine(x1 - width, y0 + width, x1, y1, color);
	TFT_DisplayStraightLine(x0, y0, x0, y1, color);
	TFT_DisplayStraightLine(x1, y0, x1, y1, color);
}

// 显示一个圆角矩形
void TFT_DisplayRoundRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t r, uint16_t color)
{
	uint16_t i, j;
	uint16_t dx, dy;
	dx = x1 - x0;
	dy = y1 - y0;
	// 上边
	TFT_DisplayStraightLine(x0 + r, y0, x1 - r, y0, color);
	// 下边
	TFT_DisplayStraightLine(x0 + r, y1, x1 - r, y1, color);
	// 左边
	TFT_DisplayStraightLine(x0, y0 + r, x0, y1 - r, color);
	// 右边
	TFT_DisplayStraightLine(x1, y0 + r, x1, y1 - r, color);
	// 左上角
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < r; j++)
		{
			if(i * i + j * j < r * r)
			{
				TFT_SetAddr(x0 + i, y0 + j, x0 + i, y0 + j);
				TFT_SendData(color >> 8);
				TFT_SendData(color);
			}
		}
	}
	// 右上角
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < r; j++)
		{
			if(i * i + j * j < r * r)
			{
				TFT_SetAddr(x1 - i, y0 + j, x1 - i, y0 + j);
				TFT_SendData(color >> 8);
				TFT_SendData(color);
			}
		}
	}
	// 左下角
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < r; j++)
		{
			if(i * i + j * j < r * r)
			{
				TFT_SetAddr(x0 + i, y1 - j, x0 + i, y1 - j);
				TFT_SendData(color >> 8);
				TFT_SendData(color);
			}
		}
	}
	// 右下角
	for(i = 0; i < r; i++)
	{
		for(j = 0; j < r; j++)
		{
			if(i * i + j * j < r * r)
			{
				TFT_SetAddr(x1 - i, y1 - j, x1 - i, y1 - j);
				TFT_SendData(color >> 8);
				TFT_SendData(color);
			}
		}
	}
}











