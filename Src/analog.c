/*
 * analog.c
 *
 *  Created on: 16 cze 2019
 *      Author: Bartek
 */

#include "analog.h"

void start()
{
	 	 DMA1_Stream1 -> PAR = (uint32_t)&(ADC12_COMMON -> CDR);
	     DMA1_Channel1 -> CMAR = (uint32_t)&obuff[0][0];
	     DMA1_Channel1 -> CNDTR = 1 * 1024;
	     DMA1_Channel1 -> CCR = DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_EN | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0 | DMA_CCR_TEIE | (DMA_CCR_PL_Msk);

	     ADC12_COMMON -> CCR = (0b11 << ADC12_CCR_MDMA_Pos) | (0b111 << ADC12_CCR_MULTI_Pos);

	     ADC1 -> CFGR = ADC_CFGR_DMAEN | (0b10 << ADC_CFGR_RES_Pos);
	     ADC1 -> CFGR &= ~(ADC_CFGR_EXTEN_Msk | ADC_CFGR_EXTSEL_Msk);  // software trigger only , converting as fast as possible - change it to your trigger.
	     ADC1 -> CFGR |= ADC_CFGR_CONT;
	     ADC1 -> SMPR1 = 0;
	     ADC1 -> SMPR2 = 0;

	     ADC1 -> SQR1 &= ~(ADC_SQR1_L_Msk);
	     ADC1 -> SQR1 &= ~(ADC_SQR1_SQ1_Msk);
	     ADC1 -> SQR1 |= (1 << ADC_SQR1_SQ1_Pos);

	     ADC2 -> CFGR = ADC_CFGR_DMAEN | (0b10 << ADC_CFGR_RES_Pos);
	     ADC2 -> SMPR1 = 0;
	     ADC2 -> SMPR2 = 0;

	     ADC2 -> SQR1 &= ~(ADC_SQR1_L_Msk);
	     ADC2 -> SQR1 &= ~(ADC_SQR1_SQ1_Msk);
	     ADC2 -> SQR1 |= (1 << ADC_SQR1_SQ1_Pos);
	     ADC1 -> CR |= ADC_CR_ADSTART;
}
