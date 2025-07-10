/**
 * @file udsp_card_board.h
 * @brief XCORE.AI pin mappings and configuration for the uDSP-Card.
 * @author Christoph Kiener
 * @copyright GPL-3.0
 * @see https://github.com/crsknr/hw_udsp-card (Hardware repository)
 */

#pragma once

/** @defgroup GPIO_Resources GPIO Port Resources
 *  @brief GPIO input and output ports.
 *  @{
 */
#define UDSP_CARD_PORT_GPIO_IN XS1_PORT_4A
#define UDSP_CARD_PORT_GPIO_OUT XS1_PORT_4C
/** @} */

/** @defgroup I2C_Resources I2C Port Resources
 *  @brief I2C bus ports for system communication.
 *  @{
 */
#define UDSP_CARD_PORT_SYS_SCL XS1_PORT_1N
#define UDSP_CARD_PORT_SYS_SDA XS1_PORT_1O
/** @} */

/** @defgroup SPI_Resources SPI Port Resources
 *  @brief SPI bus interface ports and IRQ.
 *  @{
 */
#define UDSP_CARD_PORT_SPI_CLK XS1_PORT_1I
#define UDSP_CARD_PORT_SPI_MOSI XS1_PORT_1J
#define UDSP_CARD_PORT_SPI_MISO XS1_PORT_1L
#define UDSP_CARD_PORT_SPI_CS XS1_PORT_4E
#define UDSP_CARD_PORT_SPI_IRQ XS1_PORT_4F
/** @} */

/** @defgroup I2S_Resources I2S Port and Clock Resources
 *  @brief I2S audio interface and clock blocks.
 *  @{
 */
#define UDSP_CARD_PORT_MCLK XS1_PORT_1D
#define UDSP_CARD_PORT_I2S_LRCLK XS1_PORT_1C
#define UDSP_CARD_PORT_I2S_BCLK XS1_PORT_1B
#define UDSP_CARD_PORT_I2S_D0 XS1_PORT_1A
#define UDSP_CARD_PORT_I2S_D1 XS1_PORT_1M
#define UDSP_CARD_PORT_I2S_D2 XS1_PORT_1N
#define UDSP_CARD_PORT_I2S_D3 XS1_PORT_1O
#define UDSP_CARD_PORT_I2S_D4 XS1_PORT_1P
#define UDSP_CARD_CLKBLK_I2S_BCLK XS1_CLKBLK_4
#define UDSP_CARD_CLKBLK_MCLK XS1_CLKBLK_5
/** @} */

/** @defgroup PDM_Resources PDM Port and Clock Resources
 *  @brief PDM microphone clocking and data interfaces.
 *  @{
 */
#define UDSP_CARD_PORT_PDM_CLK XS1_PORT_1F
#define UDSP_CARD_PORT_PDM_DATA XS1_PORT_4C
#define UDSP_CARD_CLKBLK_PDM_A XS1_CLKBLK_2
#define UDSP_CARD_CLKBLK_PDM_B XS1_CLKBLK_3
/** @} */

/** @defgroup USB_Resources USB Clock and Port Resources
 *  @brief USB audio master clock interface.
 *  @{
 */
#define UDSP_CARD_PORT_MCLK_COUNT XS1_PORT_16B
#define UDSP_CARD_PORT_MCLK_IN_USB XS1_PORT_1M
#define UDSP_CARD_CLKBLK_AUDIO_MCLK_USB XS1_CLKBLK_1
/** @} */

/** @defgroup GPIO_Pin_Definitions GPIO Pin Bitmask Definitions
 *  @brief Bitmask values for GPIO input and output pins.
 *  @{
 */
#define UDSP_CARD_GPIO_IN_IMU_IRQ_1 (1 << 0)
#define UDSP_CARD_GPIO_IN_IMU_IRQ_2 (1 << 1)
#define UDSP_CARD_GPIO_IN_BUTTON_0 (1 << 2)
#define UDSP_CARD_GPIO_IN_BUTTON_1 (1 << 3)

#define UDSP_CARD_GPIO_OUT_SPI_EN_N (1 << 0)
#define UDSP_CARD_GPIO_OUT_DAC_EN (1 << 1)
#define UDSP_CARD_GPIO_OUT_LED_0 (1 << 2)
#define UDSP_CARD_GPIO_OUT_LED_1 (1 << 3)
/** @} */

/** @defgroup Audio_Defines Audio and Clock Configuration
 *  @brief Audio frequency settings and I2S/PDM data layout.
 *  @{
 */
#define MASTER_CLOCK_FREQUENCY 49152000
#define AUDIO_CLOCK_FREQUENCY 192000
#define PDM_CLOCK_FREQUENCY 3072000
#define PDM_MICS_PORT 8
#define PDM_MICS 8
#define I2S_LINES 5
#define I2S_CHANS_PER_FRAME 2
#define I2S_DATA_BITS 32
/** @} */

/**
 * @brief Initialize devices on the uDSP-Card. Sets up the system clock,
 * initializes I2C communication, enables/configures the DAC (ES9033) and turns on LED0.
 *
 * @return 0 on success, non-zero on failure.
 */
int udsp_card_devices_init();

/**
 * @brief Configure the system PLL with a fixed master clock frequency.
 */
void udsp_card_pll_init();
