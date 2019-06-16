#include "i2c.h"

#define RESISTANCE 100000

// MEASURED WIPER RESISTANCE TABLE [wiper_index][MCP_index]
extern float Rw_value[2][6];

// ADRESSES TABLE
extern uint8_t MCP4661_addr[6];

// MEMORY MAP
#define VOLATILE_WIPER_0_ADDR 0x00
#define VOLATILE_WIPER_1_ADDR 0x01
#define NONVOLATILE_WIPER_0_ADDR 0x02
#define NONVOLATILE_WIPER_1_ADDR 0x03
#define TCON_REG_ADDR 0x04
#define STATUS_REG_ADDR 0x05
#define EEPROM_1_ADDR 0x06
#define EEPROM_2_ADDR 0x07
#define EEPROM_3_ADDR 0x08
#define EEPROM_4_ADDR 0x09
#define EEPROM_5_ADDR 0x0A
#define EEPROM_6_ADDR 0x0B
#define EEPROM_7_ADDR 0x0C
#define EEPROM_8_ADDR 0x0D
#define EEPROM_9_ADDR 0x0E
#define EEPROM_10_ADDR 0x0F

// COMMANDS

#define WRITE_CMD 0
#define INCREMENT_CMD 1
#define DECREMENT_CMD 2
#define READ_CMD 3

void MCP4661_SetResistance(uint8_t pot_number,float value,uint8_t wiper_index);
float MCP4661_ReadResistance(uint8_t pot_number,uint8_t wiper_index);
void MCP4661_SetWiper(uint8_t pot_number,uint8_t value,uint8_t wiper_index);
uint16_t MCP4661_ReadWiper(uint8_t pot_number,uint8_t wiper_index);
