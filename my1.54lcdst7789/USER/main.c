#include "stm32f10x.h"                  // Device header
#include "tft1_54.h"
#include "delay.h"

int main()
{
    DelayInit();
    TFT_Init();
    TFT_Clear_Full(WHITE);
    while(1)
    {
        TFT_DisplayAsciiStr(10, 10, "Abcdefg", BLACK);
        TFT_Clear_Full(RED);
        DelayS(1);    
        TFT_DisplayStraightLine(20, 80, 25, 120, RED);    
        DelayS(1); 
        TFT_Clear_Full(GREEN);
    }
    return 0;
}
