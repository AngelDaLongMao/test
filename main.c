#include "sys.h"//头文件都发在这个里
u16 length;	//定义一些变量显示值
u16 setting=0;
u16 ring=0;
u8 degree[4]={0,1,2,3};
u8 ZI[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
char A1[4]={'!',':'};
void oled_show(u16 key1);
void oled_showdegree(u16 key);
int main(void)
{	 u16 key=0;
	 u16 key1=0;
	 delay_init();//延时函数初始化
	// KEY_Init();//初始化按键
	 OLED_Init(); //初始化oled
	 OLED_Clear();
	 LED_Init();//初始化部分引脚
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	 uart_init(9600);	 	//串口初始化为9600
	 Hcsr04Init(); 			//初始化超声波测距
	 key=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	 key1=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
	 while(1) 	   
	 {	 
	 key=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
	 key1=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
		 if(key==1)
		 {
			 setting =1+setting;
			 LED0=!LED0;
			 delay_ms(100);
		 }
		 else if(key1==0)
		 {
			 setting =0;
			 LED0=!LED0;
			 delay_ms(100);
		 }
		 length = Hcsr04GetLength();//超声波测距的距离
		 printf("%d\r\n",length);
		 oled_show(0);//显示 当前圈数：
		 OLED_ShowNum(80,0,ring,1,16);
		 oled_show(1);//显示 当前圈数：
		 OLED_ShowNum(80,2,setting,1,16);
		 if(length<10)//有目标通过时。圈数加1
		  {   
			  ring=ring+1;
			  LED0=!LED0;//用来查看是否实现加1
			  if(ring<setting)
			  {
			  delay_ms(700);
			  }				  
			 else if(ring==setting)
			  {
			   LAMP1=1;
			   LAMP2=1;
			  OLED_ShowNum(80,0,ring,1,16);
			  PAout(8)=1;//蜂鸣器响一段时间，圈数自动清零
			  delay_ms(1000);
			  PAout(8)=0;
			  delay_ms(500);  
			  LAMP1=0;
			  LAMP2=0;
			  ring=0;	  
			  }
			 

	     }
 }
}

void oled_show(u16 key1)
{	      switch(key1)
			{				 
				case 0:	//显示 当前圈数：
				 OLED_ShowCHinese(0,0,0);
				 OLED_ShowCHinese(16,0,1);
				 OLED_ShowCHinese(32,0,2);
				 OLED_ShowCHinese(48,0,3);
				 OLED_ShowChar(64,0,A1[1],16);	
					break;
				case 1: //显示 设定圈数：
				 OLED_ShowCHinese(0,2,ZI[4]);
				 OLED_ShowCHinese(16,2,ZI[5]);
				 OLED_ShowCHinese(32,2,ZI[2]);
				 OLED_ShowCHinese(48,2,ZI[3]);
				 OLED_ShowChar(64,2,A1[1],16);	
					break;
				case 3:	//	 
//				OLED_ShowCHinese(0,0,ZI[4]);
//				OLED_ShowCHinese(16,0,ZI[5]);
//				OLED_ShowCHinese(32,0,ZI[6]);
//				OLED_ShowCHinese(48,0,ZI[7]);
//				OLED_ShowChar(66,0,A1[1],16);
					break;
				case 4:	// 				
				    break;
	 	   }
}
void oled_showdegree(u16 key)//显示 光亮等级
{
	if(key)
		{			
			switch(key)
			{				 
				case KEY0_PRES:	//光强等级 1
					TIM_SetCompare2(TIM3,700);
				    OLED_ShowNum(102,0,ZI[1],1,16);
					break;
				case KEY1_PRES:	//光强等级 2
					TIM_SetCompare2(TIM3,400);
				    OLED_ShowNum(102,0,ZI[2],1,16);
					break;
				case KEY2_PRES:	//光强等级 3
					TIM_SetCompare2(TIM3,0);
					OLED_ShowNum(102,0,ZI[3],1,16);
					break;
				case WKUP_PRES:	//光强等级 0
					TIM_SetCompare2(TIM3,900);
					OLED_ShowNum(102,0,ZI[0],1,16);
					break;
			}
		}else delay_ms(10); 
}


