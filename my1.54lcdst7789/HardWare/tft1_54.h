/**
 * @FilePath     : /my1.54lcdst7789/HardWare/tft1_54.h
 * @Description  :  1.54寸屏幕驱动头文件，使用模拟SPI通信
 *                  该屏幕驱动为ST7789驱动，分辨率为240*240，时钟频率最高为62.5MHz
 * @PinDefinition   :   模拟SPI通信,所有引脚都可更改
 *                      1. SCL  -->  PA5  
 *                      2. SDA  -->  PA7
 *                      3. RES  -->  PA2
 *                      4. DC   -->  PA3
 *                      5. CS   -->  PA4
 *                      硬件SPI通信，SCL、SDA、CS不可更改
 *                      1. SCL  -->  PA5
 *                      2. SDA  -->  PA7
 *                      3. RES  -->  PA2
 *                      4. DC   -->  PA3
 *                      3. CS   -->  PA4
 * @Author       : wuu
 * @Date         : 2024-02-17 16:57:02
 * @Version      : 0.0.1
 * @LastEditTime : 2024-02-19 17:06:21
 * @Copyright    : G AUTOMOBILE RESEARCH INSTITUTE CO.,LTD Copyright (c) 2024.
**/

#ifndef _TFT1_54_H
#define _TFT1_54_H

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define PINK 0xF81F
#define ORANGE_RED 0XFA20
#define WHITE 0XFFFF	  //白色

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

void TFT_Init(void);
void TFT_Clear_Full(uint16_t color);
void TFT_DisplayAsciiStr(uint16_t x, uint16_t y, uint8_t *str, uint16_t color);
void TFT_DisplayStraightLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

#endif
