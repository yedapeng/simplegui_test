#ifndef _INCLUDE_MAPPING_H_
#define _INCLUDE_MAPPING_H_


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-	GPIO�˿ڼĴ�����������											-*/
/*-	��ʽһ															-*/
/*-	ʹ��ʾ����														-*/
/*-	#define	KEY		PA_IN(0)										-*/
/*-	#define	LED		PB_OUT(1)										-*/
/*-																	-*/
/*-	��																-*/
/*-																	-*/
/*-	#define LED		BIT_ADDR(GPIOA_ODR_Addr,0)						-*/
/*-	#define	KEY		BIT_ADDR(GPIOA_IDR_Addr,1) 						-*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

//GPIO�Ĵ�������ַ����
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//�˿�����Ĵ�����ַӳ��
#define GPIOA_ODR_Addr		(GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr		(GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr		(GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr		(GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr		(GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr		(GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr		(GPIOG_BASE+12) //0x40011E0C    
//�˿�����Ĵ�����ַӳ��
#define GPIOA_IDR_Addr		(GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr		(GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr		(GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr		(GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr		(GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr		(GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr		(GPIOG_BASE+8) //0x40011E08 
 
//GPIO�˿ڲ����궨��
//GPIO A
#define PA_OUT(n)			BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PA_IN(n)			BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 
//GPIO B
#define PB_OUT(n)			BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PB_IN(n)			BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 
//GPIO C
#define PC_OUT(n)			BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PC_IN(n)			BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 
//GPIO D
#define PD_OUT(n)			BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PD_IN(n)			BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 
//GPIO E
#define PE_OUT(n)			BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PE_IN(n)			BIT_ADDR(GPIOE_IDR_Addr,n)  //����
//GPIO F
#define PF_OUT(n)			BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PF_IN(n)			BIT_ADDR(GPIOF_IDR_Addr,n)  //����
//GPIO G
#define PG_OUT(n)			BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PG_IN(n)			BIT_ADDR(GPIOG_IDR_Addr,n)  //����


/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-	GPIO�˿ڼĴ�����������											-*/
/*-	��ʽ��															-*/
/*-	ʹ��ʾ����														-*/
/*-	#define LED1	BIT_BAND(&GPIOB->ODR,0)							-*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/

/****************�ڶ���λ������Ч�ʵͣ���ʹ�÷��㣬IO ���Էǲ��������磺 LED = !LED)****************/

#ifndef HWREG
#define HWREG(x)  (*((volatile unsigned long *)(x)))
#endif
#ifndef HWREGBITW
#define HWREGBITW(x, b) HWREG( ((unsigned long)(x) & 0xF0000000) | 0x02000000 | (((unsigned long)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#endif

#define BIT_BAND(A,B) HWREGBITW(A,B)

#endif   
