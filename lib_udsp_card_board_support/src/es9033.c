/**
 * @file es9033.c
 * @brief Implementation of ES9033 DAC initialization and register operations.
 * @author Christoph Kiener
 * @copyright GPL-3.0
 * @see https://github.com/crsknr/hw_udsp-card (Hardware repository)
 */

#include <platform.h>
#include <xclib.h>
#include <xs1.h>

#include <stdio.h>

#include "debug_print.h"
#include "i2c.h"

#include "es9033.h"

/**
 * @brief Write a register to the ES9033 DAC.
 * @param i2c_ctx Pointer to the I2C context for communication.
 * @param reg The register address to write to.
 * @param val The value to write to the register.
 * @return 0 on success, -1 on failure.
 **/
static inline int es9033_reg_write(i2c_master_t *i2c_ctx, uint8_t reg, uint8_t val)
{
	i2c_regop_res_t ret;
	uint8_t addr;

	if (reg <= ES9033_REG_MASTER_TRIM)
	{
		addr = ES9033_I2C_DEVICE_ADDR;
	}
	else if (ES9033_REG_RESET_PLL1 <= reg && reg <= ES9033_REG_PLL8)
	{
		addr = ES9033_I2C_DEVICE_ADDR_SS;
	}
	else
	{
		debug_printf("ES9033: Reg 0x%x\n is not writable", reg);
		return -1;
	}

	ret = write_reg(i2c_ctx, addr, reg, val);

	if (ret != I2C_REGOP_SUCCESS)
	{
		debug_printf("ES9033: Failed to write reg 0x%x val 0x%x\n", reg, val);
		return -1;
	}

	return 0;
}

int es9033_init(i2c_master_t *i2c_ctx)
{
	uint8_t ret = 0;

	// Set GPIO1/MCLK to input, Invert CLKHV phase for better DNR
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_RESET_PLL1,
							ES9033_BIT_GPIO1_SDB_SYNC |
								ES9033_BIT_PLL_CLKHV_PHASE);

	// Bypass PLL, Disable 10k DVDD shunt to ground, Set PLL input MUX to MCLK, Enable PLL input MUX
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_PLL2,
							ES9033_BIT_PLL_BYPASS |
								ES9033_BIT_DVDD_SHUNTB |
								ES9033_BIT_EN_PLL_CLKIN);

	ret |= es9033_reg_write(i2c_ctx, 202, 0x40);

	delay_milliseconds(1);

	// Set the MCLK/FS rate, 64fs, 49.152MHz/192kHz -> divide by 2
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_DAC_CLOCK_CONFIG, 0x01);

	// Set the PNEG charge pump clock frequency to 768kHz
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_CP_CLOCK_DIV, 7);

	// Enable the TDM decoder (ES9033_REG_SYS_MODE_CONFIG) -> on by default
	// Enable TDM slave mode (ES9033_REG_INPUT_CONFIG) -> on by default
	// Set 2 TDM slots per frame (ES9033_REG_TDM_CONFIG1) -> on by default
	// Set to I2S format (ES9033_REG_TDM_CONFIG2) -> on by default
	// Set TDM_CH1_LINE_SEL = 0, TDM_CH2_SLOT_SEL = 1 (ES9033_REG_TDM_SLOT_CONFIG) -> on by default

	// Set THD compensation (ES9033_REG_THD_COMP...) -> on by default
	// Enable automute (ES9033_REG_AUTOMUTE_TIME) -> on by default
	// DRE force (ES9033_REG_DRE_FORCE) -> on by default

	// Toggle DAC clock resync to line up all the clocks in the DAC core for best analog performance
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_RESYNC_CONFIG,
							ES9033_BIT_SYNC_DAC_CLK_DIV);
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_RESYNC_CONFIG,
							ES9033_BIT_DOP_CLK_RESYNC |
								ES9033_BIT_VOL_THD_RESYNC |
								ES9033_BIT_FIR_RESYNC |
								ES9033_BIT_FS_RESYNC);
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_RESYNC_CONFIG, 0);

	// Enable audio, Enable interpolation and modulator clock, Enable analog section
	ret |= es9033_reg_write(i2c_ctx, ES9033_REG_SYSTEM_CONFIG,
							ES9033_BIT_ENABLE_ANALOG_DAC_CH1 |
								ES9033_BIT_ENABLE_ANALOG_DAC_CH2 |
								ES9033_BIT_ENABLE_NSMOD |
								ES9033_BIT_ENABLE_DAC |
								ES9033_BIT_AMP_MODE_REG);

	delay_microseconds(10);

	if (ret)
	{
		debug_printf("ES9033: Error during configuration\n");
		return -1;
	}

	return 0;
}
