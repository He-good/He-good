#include "includes.h"
		   
void ADC1_GPIO_Config(void)  //ADC1���ų�ʼ������
{
    GPIO_InitTypeDef GPIO_InitStructure;//GPIO��ʼ���ṹ�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1��GPIOAʱ�� 	  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //ָ������    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //ģ������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��GPIOA
}

void ADC_Config(void) //adc��ʼ������
{	
    ADC_InitTypeDef ADC_InitStructure;//ADC��ʼ���ṹ�����
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode =	DISABLE; //��ͨ��
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADCת������������ģʽ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��,��ʹ���ⲿ����
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
    ADC_InitStructure.ADC_NbrOfChannel = 1;//ת��ͨ����Ϊ1
    ADC_Init(ADC1, &ADC_InitStructure); //��ʼ��ADC
	
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADCʱ��ΪCLK2��8��Ƶ,72/8=9MHz
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);//ADC1ѡ��ͨ��1,˳��Ϊ1,����ʱ��239.5������
    
    //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);//ת������������ж�
    ADC_Cmd(ADC1, ENABLE);//����ADC1
	
    /*  ����������Protuesʱ��У׼�ᵼ�����޵ȴ�����ҪУ׼��������ʵ��Ӳ��ʱ��Ӧ����У׼
    ADC_ResetCalibration(ADC1); //��ʼ������λ��ADC1У׼�Ĵ���
    while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼��ʼ�����
    ADC_StartCalibration(ADC1);//��ʼADC1У׼
    while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���  
    */
}


Int16U Get_Adc(void)  //���ADCת��ֵ 
{  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	//�������ADC1��ת��		 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ת�����
}

Int16U Get_Adc_Average(Int08U times)//���ָ��ͨ�����ADת�������ƽ��ֵ
{
	Int32U temp_val=0;
	Int08U i;
	for(i=0;i<times;i++)	
        temp_val+=Get_Adc();  //�ۼ�  
	
	return temp_val/times; //����ƽ��ֵ
} 	 






















