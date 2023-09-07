/*
 * ADC.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Mostafa Hisham
 *      Layer : MCAL
 *      SWC   : ADC-IMPLEMENTATION
 */
#include<Std_Types.h>
#include<Macros.h>
#include<Registers.h>
#include<ADC.h>
#include<ADC_Private.h>
#include<ADC_Confg.h>

void(*ADCAsynch_CallBack)(void) = NULL;
u8* ADC_Reading = NULL;
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	ADCAsynch_CallBack();
	/*Disable ADC Conversion complete interrupt */
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}
void ADC_Init(void)
{
	/*choose reference type */
#if REFERNCE_TYPE == ADC_REF_AREF
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif REFERNCE_TYPE == ADC_REF_AVCC
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif REFERNCE_TYPE == ADC_REF_INT
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
	#error "Unknown Reference Type"
#endif
	/* choose adjust type */
#if ADJUST_TYPE == ADC_LEFT_ADJUST
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADJUST_TYPE ==ADC_RIGHT_ADJUST
	 CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
	#error"Unknown adjust type"
#endif
#if TRIGGER_TYPE == TRIGGER_ENABLE
	SET_BIT(ADCSRA,ADCSRA_ADATE);
#elif TRIGGER_TYPE == TRIGGER_DISABLE
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
#endif
	/* ADC interrupt status */
#if ADC_INTERRUPT_MODE  == ADC_INTERRUPT_ENABLE
		SET_BIT(ADCSRA,ADCSRA_ADIE);
#elif ADC_INTERRUPT_MODE == ADC_INTERRUPT_DISABLE
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
#else
	#error"Undefined interrupt mode"
#endif
		ADCSRA = (ADCSRA & ADC_PRESCALER_MASK) | (PRESCALER_TYPE);
	/*ADC Peripheral Enable*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}
u16 ADC_AnalogReadSynchronous(u8 channel)
{
	u16 ADC;
	ADMUX =(ADMUX & 0XE0) |(channel & 0x07);
	/* Start Conversion */
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	/* Polling until the conversion flag is set */
	while(GET_BIT(ADCSRA,ADCSRA_ADIF)== 0);
	/*CLEAR THE CONVERSION FLAG */
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	/* return adc DATA */
#if ADJUST_TYPE ==ADC_RIGHT_ADJUST
	ADC = ADCL;
	ADC |= (ADCH<<8);
#elif ADJUST_TYPE == ADC_LEFT_ADJUST
	ADC = ADCH;
#endif
	return ADC;
}

u16 ADC_AnalogReadASynchronous(u8 channel,void(*ADC_PTR)(void))
{  	u16 ADC;
	if( ADC_PTR != NULL)
	{
	// INTIALIZE THE CALL BACK NOTIFICATION FUNCTION
		ADCAsynch_CallBack = ADC_PTR;

		ADMUX =(ADMUX & 0XE0) |(channel & 0x07);
		//	 Start Conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			ADC = ADCL;
			ADC |= (ADCH<<8);
			return ADC;
	}
}
