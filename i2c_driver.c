
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
#include "i2c.h"
#define LEDPORT GPIOE
#define LED GPIO15
#define PCA_9532 0xc0
#define CONTROL_REG 0x12
struct pca_regs
{
	uint8_t INPUT0;
	uint8_t INPUT1;
	uint8_t PSC0;
	uint8_t PWM0;
	uint8_t PSC1;
	uint8_t PWM1;
	uint8_t LS0;
	uint8_t LS1;
	uint8_t LS2;
	uint8_t LS3;
} led_driver;

static void gpio_setup(void)
{
	/* Enable GPIO clock. */
	rcc_periph_clock_enable(RCC_GPIOE);
	rcc_periph_clock_enable(RCC_GPIOB);

	/* Set GPIO12 (in GPIO port C) to 'output push-pull'. */
	gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL, LED);
}

static void rcc_setup(void)
{
	rcc_clock_setup_in_hse_25mhz_out_72mhz();
	/* rcc_set_ppre1(RCC_CFGR_PPRE1_HCLK_DIV2);	 */
}


int main(void)
{
	led_driver.PSC0 = 100; // 1.5Hz
	led_driver.PWM0 = 84;	// 33%
	led_driver.PSC1 = 100;
	led_driver.PWM1 = 64;	//25%
	led_driver.LS0 = 0x15;
	led_driver.LS1 = 0xa0;
	led_driver.LS2 = 0xfe;
	led_driver.LS3 = 0;
	
	gpio_setup();
	rcc_setup();
	i2c1_setup();
	
	i2c1_write(PCA_9532, CONTROL_REG, &led_driver.PSC0, 8);
	
	while (1);
	
	return 0;
}
