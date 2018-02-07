/* I2C library */
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef sbi
	#define sbi(port, bit)	(port) |= (1 << bit)
#endif
#ifndef cbi
	#define cbi(port, bit)	(port) &= ~(1 << bit)
#endif

#define SLAVE   1
// common funtions
void I2C_master_init();
void I2C_slave_init();

// STATUS CODE FOR SLAVE USE
// SLAVE RECEIVER
#define SLAVE_REC_ADDRESS_MATCH		0x60
#define SLAVE_REC_MATCH				0x68
#define SLAVE_REC_DATA_ACK			0x80
#define SLAVE_REC_DATA_NACK			0x88
#define SLAVE_REC_STOP				0xA0

// SLAVE TRANSMITTER
#define SLAVE_TRS_ADDRESS_MATCH		0xA8
#define SLAVE_TRS_MATCH				0xB0
#define SLAVE_TRS_DATA_ACK			0xB8
#define SLAVE_TRS_DATA_NACK			0xC0
#define SLAVE_TRS_LAST				0xC8

// Functions for SLAVE
void I2C_address(uint8_t);

extern volatile uint8_t tranCount;
extern volatile uint8_t recCount;
extern volatile uint8_t SLAVE_RecBuffer[];
extern volatile uint8_t SLAVE_TranBuffer[];

// STATUS CODE FOR MASTER USE

#define _100KHz			32
#define I2C_READ		1
#define I2C_WRITE		0
#define I2C_START		(1 << TWINT) | (1 << TWEN) | (1 << TWSTA)
#define I2C_STOP		(1 << TWINT) | (1 << TWEN) | (1 << TWSTO)
#define I2C_CLEARINT	(1 << TWINT) | (1 << TWEN)
#define I2C_READACK		(1 << TWINT) | (1 << TWEN) | (1 << TWEA)
#define I2C_READNACK	(1 << TWINT) | (1 << TWEN)
#define I2C_SEND		(1 << TWINT) | (1 << TWEN)

// MASTER TRANSMITTER
#define START_SENT					0x08
#define RESTART_SENT				0x10
#define MASTER_TRS_SLA_ACK			0x18
#define MASTER_TRS_SLA_NACK			0x20
#define MASTER_TRS_DATA_ACK			0x28
#define MASTER_TRS_DATA_NACK		0x30

// MASTER RECEIVER
#define MASTER_REC_SLA_ACK			0x40
#define MASTER_REC_SLA_NACK			0x48
#define MASTER_REC_DATA_ACK			0x50
#define MASTER_REC_DATA_NACK		0x58

// Functions for MASTER
uint8_t I2C_read_start(uint8_t);
uint8_t I2C_write_start(uint8_t);
uint8_t I2C_stop();
uint8_t I2C_transmit(uint8_t);
uint8_t I2C_receive();
uint8_t I2C_lastReceive();

