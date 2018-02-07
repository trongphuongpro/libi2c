#include <I2C.h>

volatile uint8_t tranCount;
volatile uint8_t recCount;
volatile uint8_t SLAVE_RecBuffer[32];
volatile uint8_t SLAVE_TranBuffer[32];

void I2C_master_init() {
	TWSR = 0x00;
	TWBR = _100KHz;
	TWCR = (1 << TWEN) | (1 << TWEA);
}

void I2C_slave_init() {
	TWSR = 0x00;
	TWCR = (1 << TWIE) | (1 << TWEN) | (1 << TWEA);
}

void I2C_address(uint8_t address) {
	TWAR = address << 1;
}

uint8_t I2C_read_start(uint8_t address) {
	TWCR = I2C_START;
	while ((TWCR & (1 << TWINT)) == 0x00) {
		// wait for interrupt flag
	}
	
	I2C_transmit((address << 1) + I2C_READ);
	return 0;
}

uint8_t I2C_write_start(uint8_t address) {
	TWCR = I2C_START;
	while ((TWCR & (1 << TWINT)) == 0x00) {
		// wait for interrupt flag
	}
	
	I2C_transmit((address << 1) + I2C_WRITE);
	return 0;
}

uint8_t I2C_stop() {
	TWCR = I2C_STOP;
	return 0;
}

uint8_t I2C_transmit(uint8_t data) {
	TWDR = data;
	TWCR = I2C_SEND;
	while ((TWCR & (1 << TWINT)) == 0x00) {
		// wait for interrupt flag
	}
	return 0;
}

uint8_t I2C_receive() {
	TWCR = I2C_READACK;
	while ((TWCR & (1 << TWINT)) == 0x00) {
		// wait for interrupt flag
	}
	
	return TWDR;
}

uint8_t I2C_lastReceive() {
	TWCR = I2C_READNACK;
	while ((TWCR & (1 << TWINT)) == 0x00) {
		// wait for interrupt flag
	}
	
	return TWDR;
}
/*
ISR(TWI_vect) {
	uint8_t status = TWSR;
	switch (status) {
		case SLAVE_REC_ADDRESS_MATCH:	TWCR |= (1 << TWINT) | (1 << TWEA);
										recCount = 97;
										break;
		case SLAVE_REC_DATA_ACK:
		case SLAVE_REC_DATA_NACK:		SLAVE_RecBuffer[recCount++] = TWDR;
										TWCR |= (1 << TWINT) | (1 << TWEA);
										break;
		case SLAVE_REC_STOP:			TWCR |= (1 << TWINT) | (1 << TWEA);
										break;
	
		case SLAVE_TRS_ADDRESS_MATCH:	tranCount = 0;
										TWDR = SLAVE_TranBuffer[tranCount++];
										TWCR |= (1 << TWINT) | (1 << TWEA);
										break;
		case SLAVE_TRS_DATA_ACK:		TWDR = SLAVE_TranBuffer[tranCount++];
										TWCR |= (1 << TWINT) | (1 << TWEA);
										break;
		case SLAVE_TRS_DATA_NACK:
		case SLAVE_TRS_LAST:		 	TWCR |= (1 << TWINT) | (1 << TWEA);
										break;
		default: break;
		
	}
}
*/
