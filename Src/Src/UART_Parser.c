/*
 * UART_Parser.c
 *
 *  Created on: 16 cze 2019
 *      Author: Bartek
 */

#include "UART_Parser.h"
#include "MCP4661.h"
uint8_t receivedData;
extern uint8_t measureFlag;
static parserstate_t parser_state = PARSED;
uint16_t ADC_Mask;
uint8_t ok_msg[] = "OK!\n\r";
void UART_Parse(uint8_t input)
{


	uint8_t tmp[2];
	static uint8_t msg[3];
	//static uint8_t parser_lock = 0;
	static uint8_t cmd = 0xff;

	if(parser_state == PARSED)
	{
		msg[0] = input;				// first byte / one byte command
		cmd = (msg[0] >> 4) & 0x0F;
		parser_state = CMD_OK;
	}


	if(parser_state == ONE_MORE)	// second byte (2 bytes command) / third byte (3 bytes command)
	{
		msg[2] = input;
		parser_state = READY;

	}

	if(parser_state == TWO_MORE)   // second byte (3 bytes command)
	{
		msg[1] = input;
		parser_state = ONE_MORE;
		goto exit;
	}


		switch(cmd)
		{
		case SET_DEFAULTS_CMD:
			break;
		case SET_GAIN_CMD:
			if(parser_state == CMD_OK)
			{
				parser_state = ONE_MORE;
				goto exit;
			}
			else if(parser_state == READY)
			{
				uint8_t channelNumber = (msg[0] & 0x0F)>>4;
				uint8_t potNumber = (channelNumber/2);

				MCP4661_SetWiper(msg[2],potNumber,channelNumber%2);
				HAL_UART_Transmit_DMA(&huart1,ok_msg,sizeof(ok_msg));
				parser_state = PARSED;
			}
			break;
		case READ_GAIN_CMD:
			if(parser_state == CMD_OK)
						{

							uint8_t channelNumber = (msg[0] & 0x0F)>>4;
							uint8_t potNumber = (channelNumber/2);

							uint8_t wiperRead = MCP4661_ReadWiper(potNumber,channelNumber%2);

							HAL_UART_Transmit_DMA(&huart1,&wiperRead,sizeof(wiperRead));
							parser_state = PARSED;
						}
			break;
		case REACALIBRATE_CMD:
			break;
		case SET_CHANNELS_CMD:
			if(parser_state == CMD_OK)
			{
				parser_state = ONE_MORE;
				goto exit;
			}
			else if(parser_state == READY)
			{
				ADC_Mask = 0;
				ADC_Mask = ((msg[0] & 0x0F)<<8) | msg[2];
				HAL_UART_Transmit_DMA(&huart1,ok_msg,sizeof(ok_msg));
				parser_state = PARSED;
			}
			break;
		case READ_CHANNELS_CMD:
			if(parser_state == READY)
			{
				tmp[0] = ADC_Mask>>8;
				tmp[1] = (uint8_t)(ADC_Mask & 0x00FF);
				HAL_UART_Transmit_DMA(&huart1,tmp,2);
				parser_state = PARSED;
			}
			break;
		case ENABLE_DSP_CMD:
			break;
		case DISABLE_DSP_CMD:
			break;
		case SET_DSP_COEFF_CMD:
			break;
		case START_MEAS_CMD:
			if(parser_state == CMD_OK)
			{
				measureFlag = 1;
				parser_state = PARSED;
			}
			break;
		case STOP_MEAS_CMD:
			if(parser_state == CMD_OK)
						{
				__disable_irq();
							measureFlag = 0;
							parser_state = PARSED;
				__enable_irq();
						}
			break;
		}
		exit:
		asm("nop");
}

void UART_Send()
{
	extern uint16_t adcValue[13];
	uint8_t adc[2];

	if(measureFlag)
	{
		adc[0] = adcValue[0]>>8;
		adc[1] = (uint8_t)(adcValue[0]& 0x00FF);
		HAL_UART_Transmit_DMA(&huart1,adc,sizeof(adc));
	}

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UART_Parse(receivedData);
	HAL_UART_Receive_IT(&huart1, &receivedData, 1);

}

