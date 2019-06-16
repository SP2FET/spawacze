/*
 * MCP4661.c
 *
 *  Created on: 16 cze 2019
 *      Author: Bartek
 */
#include "MCP4661.h"

// ADRESSES
uint8_t MCP4661_addr[6] = {
		0x50,
		0x54,
		0x5C,
		0x58,
		0x56,
		0x52
};

void MCP4661_SetResistance(uint8_t pot_number,float value,uint8_t wiper_index)
{
		uint8_t cmd[2];
		uint8_t wiper_value;

		wiper_value = (256*(value-Rw_value[wiper_index][pot_number]))/RESISTANCE;

		cmd[0] = 0;
		if(wiper_index == 0)
			cmd[0] = (VOLATILE_WIPER_0_ADDR<<4)|(WRITE_CMD<<2);
		else
			cmd[0] = (VOLATILE_WIPER_1_ADDR<<4)|(WRITE_CMD<<2);

		cmd[1] = wiper_value;
		HAL_I2C_Master_Transmit(&hi2c2,MCP4661_addr[pot_number],cmd,2,100);
}

void MCP4661_SetWiper(uint8_t pot_number,uint8_t value,uint8_t wiper_index)
{
		uint8_t cmd[2];



		cmd[0] = 0;
		if(wiper_index == 0)
			cmd[0] = (VOLATILE_WIPER_0_ADDR<<4)|(WRITE_CMD<<2);
		else
			cmd[0] = (VOLATILE_WIPER_1_ADDR<<4)|(WRITE_CMD<<2);

		cmd[1] = value;
		HAL_I2C_Master_Transmit(&hi2c2,MCP4661_addr[pot_number],cmd,2,100);
}

float MCP4661_ReadResistance(uint8_t pot_number,uint8_t wiper_index)
{
	uint8_t cmd;
	uint8_t tmp[2];
	if(wiper_index == 0)
		cmd = (VOLATILE_WIPER_0_ADDR<<4)|(READ_CMD<<2);
	else
		cmd = (VOLATILE_WIPER_1_ADDR<<4)|(READ_CMD<<2);
	HAL_I2C_Master_Transmit(&hi2c2,MCP4661_addr[pot_number],&cmd,1,100);
	//HAL_I2C_Master_Receive(&hi2c2,POT1_ADDR,tmp,2,100);
	// OR I2C_MEMADD = 0...
	HAL_I2C_Mem_Read(&hi2c2,MCP4661_addr[pot_number],cmd,I2C_MEMADD_SIZE_8BIT,tmp,2,100);
	return (float)(((tmp[1]<<8)|tmp[0])*RESISTANCE)/256 + Rw_value[wiper_index][pot_number];
}

uint16_t MCP4661_ReadWiper(uint8_t pot_number,uint8_t wiper_index)
{
	uint8_t cmd;
	uint8_t tmp[2];
	if(wiper_index == 0)
		cmd = (VOLATILE_WIPER_0_ADDR<<4)|(READ_CMD<<2);
	else
		cmd = (VOLATILE_WIPER_1_ADDR<<4)|(READ_CMD<<2);
	HAL_I2C_Master_Transmit(&hi2c2,MCP4661_addr[pot_number],&cmd,1,100);
	//HAL_I2C_Master_Receive(&hi2c2,POT1_ADDR,tmp,2,100);
	// OR I2C_MEMADD = 0...
	HAL_I2C_Mem_Read(&hi2c2,MCP4661_addr[pot_number],cmd,I2C_MEMADD_SIZE_8BIT,tmp,2,100);
	return (tmp[1]<<8)|tmp[0];
}
