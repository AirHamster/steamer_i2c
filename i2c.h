#include <stdint.h>
#ifndef I2C_
#define I2C_

//void i2c1_er_isr(void);
//void i2c1_ev_isr(void);
void i2c1_read(uint8_t address, uint8_t reg_addr, uint8_t *data, uint8_t lenth);
void i2c1_write(uint8_t address, uint8_t reg_addr, uint8_t *data, uint8_t lenth);
void i2c1_setup(void);

#endif
