//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : Evk123
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : 2.23��OLED �ӿ���ʾ����(STM32F103ZEϵ��IIC)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PD6��SCL��
//              SDA   ��PD7��SDA��            
//              ----------------------------------------------------------------
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
  {	u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
	//		delay_ms(8000);
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear()  	; 
	
		t=' ';
		OLED_ShowCHinese(0,0,0);//��
				OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//԰
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
	while(1) 
	{		
OLED_Clear();
	   OLED_ShowString(0,0,"0.91OLEDTEST",8);
		 OLED_ShowString(0,1,"0123456789AB",8);
			delay_ms(1000);
	  	delay_ms(1000);
	  	delay_ms(1000);
	 	  OLED_Clear();
	   OLED_ShowString(0,0,"0.91OLEDTEST",16);
			delay_ms(1000);
	  	delay_ms(1000);
	  	delay_ms(1000);
	 	  OLED_Clear();
		 OLED_ShowString(0,0,"0123456789AB",16);

			delay_ms(1000);
	  	delay_ms(1000);
	  	delay_ms(1000);
	 	  OLED_Clear();
		OLED_ShowCHinese(4,1,0);//��
		OLED_ShowCHinese(22,1,1);//��
		OLED_ShowCHinese(40,1,2);//԰
		OLED_ShowCHinese(58,1,3);//��
		OLED_ShowCHinese(76,1,4);//��
		OLED_ShowCHinese(94,1,5);//��
		OLED_ShowCHinese(112,1,6);//��
			delay_ms(1000);
	  	delay_ms(1000);
	  	delay_ms(1000);
			OLED_Clear();
	OLED_DrawBMP(0,0,128,8,BMP1);
			delay_ms(1000);
			delay_ms(1000);
	  	delay_ms(1000);
			 OLED_Clear();

	}	  
	
}
	