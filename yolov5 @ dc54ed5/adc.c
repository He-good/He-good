#include "includes.h"
		   
void ADC1_GPIO_Config(void)  //ADC1引脚初始化配置
{
    GPIO_InitTypeDef GPIO_InitStructure;//GPIO初始化结构体变量
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);//使能ADC1，GPIOA时钟 	  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //指定引脚    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //模拟输入
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化GPIOA
}

void ADC_Config(void) //adc初始化配置
{	
    ADC_InitTypeDef ADC_InitStructure;//ADC初始化结构体变量
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode =	DISABLE; //单通道
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADC转换工作在连续模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//由软件控制转换,不使用外部触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//转换数据右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;//转换通道数为1
    ADC_Init(ADC1, &ADC_InitStructure); //初始化ADC
	
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);//配置ADC时钟为CLK2的8分频,72/8=9MHz
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);//ADC1选择通道1,顺序为1,采样时间239.5个周期
    
    //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);//转换结束后产生中断
    ADC_Cmd(ADC1, ENABLE);//开启ADC1
	
    /*  程序运行于Protues时，校准会导致无限等待，不要校准。运行于实际硬件时，应加以校准
    ADC_ResetCalibration(ADC1); //初始化（复位）ADC1校准寄存器
    while(ADC_GetResetCalibrationStatus(ADC1));//等待ADC1校准初始化完成
    ADC_StartCalibration(ADC1);//开始ADC1校准
    while(ADC_GetCalibrationStatus(ADC1));//等待ADC1校准完成  
    */
}


Int16U Get_Adc(void)  //获得ADC转换值 
{  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//软件启动ADC1的转换		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次转换结果
}

Int16U Get_Adc_Average(Int08U times)//获得指定通道多次AD转换结果的平均值
{
	Int32U temp_val=0;
	Int08U i;
	for(i=0;i<times;i++)	
        temp_val+=Get_Adc();  //累加  
	
	return temp_val/times; //返回平均值
} 	 






















