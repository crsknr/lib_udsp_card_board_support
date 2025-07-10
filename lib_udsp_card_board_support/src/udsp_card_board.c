/**
 * @file udsp_card_board.c
 * @brief Hardware initialization implementation for the uDSP-Card
 * @author Christoph Kiener
 * @copyright GPL-3.0
 * @see https://github.com/crsknr/hw_udsp-card (Hardware repository)
 */

#include "udsp_card_board.h"
#include "es9033.h"
#include "i2c.h"
#include "sw_pll.h"

int udsp_card_devices_init()
{
    port_t gpio_out_port = UDSP_CARD_PORT_GPIO_OUT;
    port_t gpio_in_port = UDSP_CARD_PORT_GPIO_IN;
    i2c_master_t i2c_ctx;

    int ret = 0;

    sw_pll_fixed_clock(MASTER_CLOCK_FREQUENCY);
    delay_milliseconds(100);

    i2c_master_init(&i2c_ctx, UDSP_CARD_PORT_SYS_SCL, 0, 0, UDSP_CARD_PORT_SYS_SDA, 0, 0, 100);

    port_enable(gpio_out_port);
    port_out(gpio_out_port, UDSP_CARD_GPIO_OUT_DAC_EN | UDSP_CARD_GPIO_OUT_LED_0);

    ret |= es9033_init(&i2c_ctx);

    return ret;
}

void udsp_card_pll_init()
{
    sw_pll_fixed_clock(MASTER_CLOCK_FREQUENCY);
}
