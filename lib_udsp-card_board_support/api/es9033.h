/**
 * @file es9033.h
 * @brief ES9033 DAC register definitions and initialization.
 * @author Christoph Kiener
 * @copyright GPL-3.0
 * @see https://github.com/crsknr/hw_udsp-card (Hardware repository)
 */

#pragma once

#include "i2c.h"

/** @defgroup ES9033_Registers ES9033 Registers
 *  @brief Register definitions and initialization for the ES9033 DAC.
 *  @{
 */

/**
 * @name ES9033 Device I2C Address
 * @{
 */
#define ES9033_I2C_DEVICE_ADDR (0x96 >> 1)    // R/W and R-only registers. A system clock must be present. (0x90, 0x92, 0x94, 0x96)
#define ES9033_I2C_DEVICE_ADDR_SS (0x9E >> 1) // W-only registers. No system clock necessary. (098, 0x9A, 0x9C, 0x9E)
/** @} */

/**
 * @name System Configuration Register (0x00) (R/W)
 * @{
 */
#define ES9033_REG_SYSTEM_CONFIG 0x00
#define ES9033_BIT_SOFT_RESET (1 << 7)            // (0) Performs soft reset to digital core except for the PLL Registers
#define ES9033_BIT_ENABLE_2X_MODE (1 << 6)        // (0) Enables 2x mode for 768k sample rate
#define ES9033_BIT_ENABLE_ANALOG_DAC_CH2 (1 << 5) // (1) Enables analog DAC for channel 2
#define ES9033_BIT_ENABLE_ANALOG_DAC_CH1 (1 << 4) // (1) Enables analog DAC for channel 1
#define ES9033_BIT_ENABLE_NSMOD (1 << 3)          // (1) Enables NSMOD clock
#define ES9033_BIT_ENABLE_DAC (1 << 2)            // (1) Enables DAC interpolation path clock
#define ES9033_BIT_AMP_MODE_REG (1 << 1)          // (0) Sets system mode: power down / HIFI
/** @} */

/**
 * @name System Mode Configuration Register (0x01) (R/W)
 * @{
 */
#define ES9033_REG_SYS_MODE_CONFIG 0x01
#define ES9033_BIT_ENABLE_DOP_DECODE (1 << 2) // (0) Enables DoP decode
#define ES9033_BIT_ENABLE_DSD_DECODE (1 << 1) // (0) Enables DSD decode
#define ES9033_BIT_ENABLE_TDM_DECODE (1 << 0) // (1) Enables TDM decode
/** @} */

/**
 * @name DAC Clock Configuration Register (0x02) (R/W)
 * @{
 */
#define ES9033_REG_DAC_CLOCK_CONFIG 0x02
#define ES9033_BIT_SELECT_IDAC_HALF (1 << 6)    // (0) Half clock divide value
#define ES9033_MASK_SELECT_IDAC_NUM (0x3F << 0) // (7) Whole number divide value + 1
/** @} */

/**
 * @name Master Clock Configuration Register (0x03) (R/W)
 * @{
 */
#define ES9033_REG_MASTER_CLOCK_CONFIG x03
#define ES9033_BIT_SELECT_MENC_HALF (1 << 7)    // (0) Half clock divide value
#define ES9033_MASK_SELECT_MENC_NUM (0x7F << 0) // (7) Whole number divide value + 1
/** @} */

/**
 * @name CP Clock Divider Register (0x04) (R/W)
 * @{
 */
#define ES9033_REG_CP_CLOCK_DIV 0x04 // (31) Clock divider for CP clock source
/** @} */

/**
 * @name Interrupt Mask Positive Register (0x09-0x0A) (R/W)
 * @{
 */
#define ES9033_REG_INTERRUPT_MASK_P_LSB 0x09
#define ES9033_REG_INTERRUPT_MASK_P_MSB 0x0A
#define ES9033_BIT_INPUT_DATA_TYPE_MASKP_MASK (0x03 << 14)         // (0) See Datasheet
#define ES9033_BIT_TDM_DATA_VALID_FLAG_MASKP (1 << 13)             // (0) See Datasheet
#define ES9033_BIT_CLK_AVALID_FLAG_MASKP (1 << 12)                 // (0) See Datasheet
#define ES9033_BIT_RWS_REFERENCE_COUNTER_FULL_FLAG_MASKP (1 << 11) // (0) See Datasheet
#define ES9033_BIT_BCK_WS_FAILED_FLAG_MASKP (1 << 10)              // (0) See Datasheet
#define ES9033_BIT_DOP_VALID_MASKP (1 << 8)                        // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH2_MASKP (1 << 7)                    // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH1_MASKP (1 << 6)                    // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH2_MASKP (1 << 5)                     // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH1_MASKP (1 << 4)                     // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH2_MASKP (1 << 3)                // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH1_MASKP (1 << 2)                // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH2_MASKP (1 << 1)                      // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH1_MASKP (1 << 0)                      // (0) See Datasheet
/** @} */

/**
 * @name Interrupt Mask Negative Register (0x0B-0x0C) (R/W)
 * @{
 */
#define ES9033_REG_INTERRUPT_MASK_N_LSB 0x0B
#define ES9033_REG_INTERRUPT_MASK_N_MSB 0x0C
#define ES9033_MASK_INPUT_DATA_TYPE_MASKN (0x03 << 14)             // (0) See Datasheet
#define ES9033_BIT_TDM_DATA_VALID_FLAG_MASKN (1 << 13)             // (0) See Datasheet
#define ES9033_BIT_CLK_AVALID_FLAG_MASKN (1 << 12)                 // (0) See Datasheet
#define ES9033_BIT_RWS_REFERENCE_COUNTER_FULL_FLAG_MASKN (1 << 11) // (0) See Datasheet
#define ES9033_BIT_BCK_WS_FAILED_FLAG_MASKN (1 << 10)              // (0) See Datasheet
#define ES9033_BIT_DOP_VALID_MASKN (1 << 8)                        // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH2_MASKN (1 << 7)                    // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH1_MASKN (1 << 6)                    // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH2_MASKN (1 << 5)                     // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH1_MASKN (1 << 4)                     // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH2_MASKN (1 << 3)                // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH1_MASKN (1 << 2)                // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH2_MASKN (1 << 1)                      // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH1_MASKN (1 << 0)                      // (0) See Datasheet
/** @} */

/**
 * @name Interrupt Clear Register (0x0D-0x0E) (R/W)
 * @{
 */
#define ES9033_REG_INTERRUPT_CLEAR_LSB 0x0D
#define ES9033_REG_INTERRUPT_CLEAR_MSB 0x0E
#define ES9033_MASK_INPUT_DATA_CLEAR (0x03 << 14)                  // (0) See Datasheet
#define ES9033_BIT_TDM_DATA_VALID_CLEAR (1 << 13)                  // (0) See Datasheet
#define ES9033_BIT_CLK_AVALID_FLAG_CLEAR (1 << 12)                 // (0) See Datasheet
#define ES9033_BIT_RWS_REFERENCE_COUNTER_FULL_FLAG_CLEAR (1 << 11) // (0) See Datasheet
#define ES9033_BIT_BCK_WS_FAILED_FLAG_CLEAR (1 << 10)              // (0) See Datasheet
#define ES9033_BIT_DOP_VALID_CLEAR (1 << 8)                        // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH2_CLEAR (1 << 7)                    // (0) See Datasheet
#define ES9033_BIT_SOFT_RAMP_CH1_CLEAR (1 << 6)                    // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH2_CLEAR (1 << 5)                     // (0) See Datasheet
#define ES9033_BIT_DRE_FLAG_CH1_CLEAR (1 << 4)                     // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH2_CLEAR (1 << 3)                // (0) See Datasheet
#define ES9033_BIT_AUTOMUTE_FLAG_CH1_CLEAR (1 << 2)                // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH2_CLEAR (1 << 1)                      // (0) See Datasheet
#define ES9033_BIT_VOL_MIN_CH1_CLEAR (1 << 0)                      // (0) See Datasheet
/** @} */

/**
 * @name Analog Control Configuration Register (0x0F) (R/W)
 * @{
 */
#define ES9033_REG_ANALOG_CTRL_CONFIG 0x0F
#define ES9033_BIT_AMP_PDB_ON_SS (1 << 6)       // (1) DAC amp power control for soft ramp on normal mute
#define ES9033_BIT_AMP_PDB_CLK_INVALID (1 << 5) // (1) DAC amp power control for soft ramp on abnormal mute
#define ES9033_BIT_LP_DAC_REG (1 << 1)          // (0) Enable low power mode for DAC regulator
#define ES9033_BIT_EN_FCB (1 << 0)              // (0) Disable fast charge for VREF_L & VREF_R
/** @} */

/**
 * @name Linedriver Control Register (0x10) (R/W)
 * @{
 */
#define ES9033_REG_LDRV_CTRL 0x10
#define ES9033_BIT_ENB_OCP_LDRV_CH2 (1 << 7) // (0) Disable line driver over current protection for channel 2
#define ES9033_BIT_ENB_OCP_LDRV_CH1 (1 << 6) // (0) Disable line driver over current protection for channel 1
/** @} */

/**
 * @name Analog Control Override Register (0x13) (R/W)
 * @{
 */
#define ES9033_REG_ANALOG_CONTROL_OVERRIDE 0x13
#define ES9033_BIT_TRIB_DAC_CH2 (1 << 7) // (1) Disable tri-state for DAC channel 2
#define ES9033_BIT_TRIB_DAC_CH1 (1 << 6) // (1) Disable tri-state for DAC channel 1
/** @} */

/**
 * @name GPIO Configuration Register (0x18) (R/W)
 * @{
 */
#define ES9033_REG_GPIO_CONFIG 0x18
#define ES9033_BIT_INVERT_GPIO1 (1 << 7)  // (0) Invert GPIO1
#define ES9033_BIT_GPIO1_WK_EN (1 << 6)   // (0) Enable GPIO1 weak keeper
#define ES9033_BIT_GPIO1_SDB (1 << 5)     // (0) Enable GPIO1
#define ES9033_BIT_GPIO1_OE (1 << 4)      // (0) Set GPIO1 direction
#define ES9033_MASK_GPIO1_CFG (0x0F << 0) // (0) GPIO1 configuration mask. See Datasheet
/** @} */

/**
 * @name GPIO Configuration 2 Register (0x19) (R/W)
 * @{
 */
#define ES9033_REG_GPIO_CONFIG2 0x19
#define ES9033_BIT_GPIO_OR_SS_RAMP (1 << 7)   // (0) See Datasheet
#define ES9033_BIT_GPIO_OR_VOL_MIN (1 << 6)   // (0) See Datasheet
#define ES9033_BIT_GPIO_OR_AUTOMUTE (1 << 5)  // (0) See Datasheet
#define ES9033_BIT_GPIO_AND_SS_RAMP (1 << 4)  // (0) See Datasheet
#define ES9033_BIT_GPIO_AND_VOL_MIN (1 << 3)  // (0) See Datasheet
#define ES9033_BIT_GPIO_AND_AUTOMUTE (1 << 2) // (0) See Datasheet
#define ES9033_BIT_GPIO_READ (1 << 0)         // (0) Allows GPIO1 to be read
/** @} */

/**
 * @name GPIO Input Enable Register (0x1A) (R/W)
 * @{
 */
#define ES9033_REG_INPUT_ENABLE 0x1A
#define ES9033_BIT_GPIO_AMP_MODE (1 << 1) // (0) See Datasheet
#define ES9033_BIT_GPIO_SEL (1 << 0)      // (0) See Datasheet
/** @} */

/**
 * @name PWM1 Count Register (0x1B) (R/W)
 * @{
 */
#define ES9033_REG_PWM1_COUNT 0x1B // (0) Set PWM1 count value in terms of SYS_CLK periods
/** @} */

/**
 * @name PWM1 Frequency Register (0x1C-0x1D) (R/W)
 * @{
 */
#define ES9033_REG_PWM1_FREQUENCY_LSB 0x1C // (0) Set PWM1 frequency in terms of SYS_CLK divisions
#define ES9033_REG_PWM1_FREQUENCY_MSB 0x1D // (0)
/** @} */

/**
 * @name PWM2 Count Register (0x1E) (R/W)
 * @{
 */
#define ES9033_REG_PWM2_COUNT 0x1E // (0) Set PWM2 count value in terms of SYS_CLK periods
/** @} */

/**
 * @name PWM2 Frequency Register (0x1F-0x20) (R/W)
 * @{
 */
#define ES9033_REG_PWM2_FREQUENCY_LSB 0x1F // (0) Set PWM2 frequency in terms of SYS_CLK divisions
#define ES9033_REG_PWM2_FREQUENCY_MSB 0x20 // (0)
/** @} */

/**
 * @name PWM3 Count Register (0x21) (R/W)
 * @{
 */
#define ES9033_REG_PWM3_COUNT 0x21 // (0) Set PWM3 count value in terms of SYS_CLK periods
/** @} */

/**
 * @name PWM3 Frequency Register (0x22-0x23) (R/W)
 * @{
 */
#define ES9033_REG_PWM3_FREQUENCY_LSB 0x22 // (0) Set PWM3 frequency in terms of SYS_CLK divisions
#define ES9033_REG_PWM3_FREQUENCY_MSB 0x23 // (0)
/** @} */

/**
 * @name Input Configuration Register (0x24) (R/W)
 * @{
 */
#define ES9033_REG_INPUT_CONFIG 0x24
#define ES9033_BIT_AUTO_FS_DETECT (1 << 7)    // (1) Automatically tune CLK_DAC/CLK_IDAC to input sample rate
#define ES9033_BIT_DSD_NEGEDGE (1 << 6)       // (0) DSD data is latched on the negative edge of DSD_CLK
#define ES9033_BIT_DSD_MASTER_MODE (1 << 5)   // (0) DSD master mode. DSD_CLK outputs from DATA_CLK
#define ES9033_BIT_TDM_MASTER_MODE (1 << 4)   // (0) TDM master mode. Master BCK and WS output from DATA_CLK and DATA1
#define ES9033_BIT_ENABLE_PDM (1 << 3)        // (0) Enable PDM playback
#define ES9033_MASK_INPUT_SEL (0x03 << 1)     // (0) Selects input data when AUTO_INPUT_SELECT is disabled
#define ES9033_BIT_INPUT_SEL_TDM (0x00 << 1)  //     Select TDM input
#define ES9033_BIT_INPUT_SEL_DSD (0x01 << 1)  //     Select DSD input
#define ES9033_BIT_INPUT_SEL_DoP (0x02 << 1)  //     Select DoP input
#define ES9033_BIT_AUTO_INPUT_SELECT (1 << 0) // (0) Automatically select between DSD and TDM input
/** @} */

/**
 * @name Master Mode Configuration Register (0x25) (R/W)
 * @{
 */
#define ES9033_REG_MASTER_MODE_CONFIG 0x25
#define ES9033_BIT_AUTO_FS_DETECT_BLOCK_2XMODE (1 << 7) // (0) Automatic 2x mode disable. Do not set 2x mode when CLK_DAC/CLK_IDAC is 64
#define ES9033_BIT_BCK_DIV1 (1 << 6)                    // (0) Set BCK to 128fs. Otherwise BCK <= 64fs
#define ES9033_BIT_WS_IDLE (1 << 5)                     // (0) Set WS to high when WS is idle
#define ES9033_MASK_FRAME_LENGTH (0x03 << 3)            // (0) Set bit length in each TDM channel in master mode
#define ES9033_BIT_FRAME_LENGTH_32BIT (0x00 << 3)       //     32-bit frame length
#define ES9033_BIT_FRAME_LENGTH_16BIT (0x02 << 3)       //     16-bit frame length
#define ES9033_BIT_WS_PULSE_MODE (1 << 2)               // (0) Set WS to pulse mode
#define ES9033_BIT_WS_INVERT (1 << 1)                   // (0) Invert WS
#define ES9033_BIT_BCK_INVERT (1 << 0)                  // (1) Invert BCK or DSD_CLK
/** @} */

/**
 * @name TDM Configuration Register 1 (0x26) (R/W)
 * @{
 */
#define ES9033_REG_TDM_CONFIG1 0x26
#define ES9033_BIT_RESYNC (1 << 7)            // (0) Force TDM decoder to resync
#define ES9033_MASK_WS_SCALE (0x07 << 4)      // (0) Set BCK/WS ratio by scaling master WS
#define ES9033_BIT_WS_SCALE_NONE (0x00 << 4)  //     No scaling
#define ES9033_BIT_WS_SCALE_DIV2 (0x01 << 4)  //     Divide by 2
#define ES9033_BIT_WS_SCALE_DIV4 (0x02 << 4)  //     Divide by 4
#define ES9033_BIT_WS_SCALE_DIV8 (0x03 << 4)  //     Divide by 8
#define ES9033_BIT_WS_SCALE_DIV16 (0x04 << 4) //     Divide by 16
#define ES9033_MASK_CH_NUM (0x0F << 0)        // (1) Total TDM slot number per frame = TDM_CH_NUM + 1
/** @} */

/**
 * @name TDM Configuration Register 2 (0x27) (R/W)
 * @{
 */
#define ES9033_REG_TDM_CONFIG2 0x27
#define ES9033_BIT_LJ_MODE (1 << 7)            // (0) Enable TDM LJ mode
#define ES9033_BIT_VALID_EDGE (1 << 6)         // (0) TDM WS valid edge
#define ES9033_BIT_VALID_PULSE_LEN (0x3F << 0) // (1) Data valid pulse length adjustment
/** @} */

/**
 * @name TDM Configuration Register 3 (0x28) (R/W)
 * @{
 */
#define ES9033_REG_TDM_CONFIG3 0x28
#define ES9033_BIT_PDM_NEG_FIRST (1 << 7)      // (0) PDM data edge polarity. 0 = ch1/2 -> positive/negative, 1 = ch2/1 -> positive/negative
#define ES9033_MASK_BIT_WIDTH (0x03 << 5)      // (0) Set bit width of TDM data
#define ES9033_BIT_BIT_WIDTH_32BIT (0x00 << 5) //     32-bit data width
#define ES9033_BIT_BIT_WIDTH_24BIT (0x01 << 5) //     24-bit data width
#define ES9033_BIT_BIT_WIDTH_16BIT (0x02 << 5) //     16-bit data width
#define ES9033_BIT_DATA_LATCH_ADJ (0x1F << 0)  // (0) Sets the position of the start bit within each TDM slot Can be moved +ve or -ve relative to MSB
/** @} */

/**
 * @name TDM Slot Configuration Register (0x2A) (R/W)
 * @{
 */
#define ES9033_REG_TDM_SLOT_CONFIG 0x2A
#define ES9033_MASK_CONFIG_CH2_SLOT_SEL (0x0F << 4) // (1) CH2 data slot selection. CH2 receives data from Mth slot. M = TDM_CH2_SLOT_SEL + 1
#define ES9033_MASK_CONFIG_CH1_SLOT_SEL (0x0F << 0) // (1) CH1 data slot selection. CH1 receives data from Nth slot. N = TDM_CH1_SLOT_SEL + 1
/** @} */

/**
 * @name TDM Resync Configuration Register (0x2C) (R/W)
 * @{
 */
#define ES9033_REG_RESYNC_CONFIG 0x2C
#define ES9033_BIT_CP_PDB_ON_MUTE (1 << 6)   // (1) Enable CP power down on mute
#define ES9033_BIT_SYNC_DAC_CLK_DIV (1 << 4) // (0) Clock divider will be reset at every negative edge of WS
#define ES9033_BIT_DOP_CLK_RESYNC (1 << 3)   // (0) DoP clock divider will be reset at every negative edge of WS
#define ES9033_BIT_VOL_THD_RESYNC (1 << 2)   // (0) DoP clock generator will be reset at every negative edge of WS
#define ES9033_BIT_FIR_RESYNC (1 << 1)       // (0) FIR filters will be reset at every negative edge of WS
#define ES9033_BIT_FS_RESYNC (1 << 0)        // (0) FS clock generator will be reset at every negative edge of WS
/** @} */

/**
 * @name DSD 2DB Down Control Register (0x2D) (R/W)
 * @{
 */
#define ES9033_REG_DSD_2DB_DOWN 0x2D
#define ES9033_BIT_DSD_2DB_DOWN_ENABLE (1 << 7) // (1) Scale down DSD data by 2dB to match PCM data
/** @} */

/**
 * @name Volume 1 Control Register (0x2E) (R/W)
 * @{
 */
#define ES9033_REG_VOLUME1 0x2E // (0) Volume control for channel 1 in 0.5dB steps. 0x00: 0dB, 0xFF: -127.5dB
/** @} */

/**
 * @name Volume 2 Control Register (0x2F) (R/W)
 * @{
 */
#define ES9033_REG_VOLUME2 0x2F // (0) Volume control for channel 2 in 0.5dB steps. 0x00: 0dB, 0xFF: -127.5dB
/** @} */

/**
 * @name DAC Volume Up Rate Register (0x30) (R/W)
 * @{
 */
#define ES9033_REG_DAC_VOL_UP_RATE 0x30 // (150) Value by which the old VOLUME value is incremented to reach the new VOLUME value Valid from 0 (instant) to 255 (fastest)
/** @} */

/**
 * @name DAC Volume Down Rate Register (0x31) (R/W)
 * @{
 */
#define ES9033_REG_DAC_VOL_DOWN_RATE 0x31 // (150) Value by which the old VOLUME value is decremented to reach the new VOLUME value Valid from 0 (instant) to 255 (fastest)
/** @} */

/**
 * @name DAC Volume Down Rate Fast Register (0x32) (R/W)
 * @{
 */
#define ES9033_REG_DAC_VOL_DOWN_RATE_FAST 0x32 // (0) Value by which the old VOLUME value is decremented to reach the new VOLUME value Valid from 0 (instant) to 255 (fastest). Only used during abnormal mute
/** @} */

/**
 * @name Mute Control Register (0x33) (R/W)
 * @{
 */
#define ES9033_REG_MUTE_CTRL 0x33
#define ES9033_BIT_FORCE_VOLUME (1 << 7)        // (0) Volume update control
#define ES9033_BIT_DAC_USE_MONO_VOLUME (1 << 6) // (0) Use mono volume for both channels
#define ES9033_BIT_RUN_VOLUME (1 << 5)          // (0) Toggle RUN_VOLUME to update volumes set by VOLUME1- VOLUME8
#define ES9033_BIT_DAC_INVERT_CH2 (1 << 3)      // (0) Invert the output on CH2 at the input to NSMOD
#define ES9033_BIT_DAC_INVERT_CH1 (1 << 2)      // (0) Invert the output on CH1 at the input to NSMOD
#define ES9033_BIT_DAC_MUTE_CH2 (1 << 1)        // (0) Mute CH2
#define ES9033_BIT_DAC_MUTE_CH1 (1 << 0)        // (0) Mute CH1
/** @} */

/**
 * @name Filter Configuration Register (0x34) (R/W)
 * @{
 */
#define ES9033_REG_FILTER_CONFIG 0x34
#define ES9033_BIT_AUTO_CH_DETECT (1 << 7)     // (0) Auto detect BCK/FRAME ratio to determine the number of TDM channels
#define ES9033_BIT_BYPASS_DEEMPH (1 << 6)      // (1) Disable de-emphasis filter conrol for CH1/2 only
#define ES9033_BIT_PEAK_FILTER (1 << 4)        // (0) Enable DRE peak filter
#define ES9033_MASK_SEL_DEEMPH (0x03 << 2)     // (1) Select de-emphasis filter for sample rates
#define ES9033_BIT_SEL_DEEMPH_32K (0x00 << 2)  //     32kHz
#define ES9033_BIT_SEL_DEEMPH_44K1 (0x01 << 2) //     44.1kHz
#define ES9033_BIT_SEL_DEEMPH_48K (0x02 << 2)  //     48kHz
#define ES9033_MASK_FILTER_SHAPE (0x07 << 0)   // (0) Select the 8x interpolation FIR filter shape
#define ES9033_BIT_FILTER_SHAPE_1 (0x00 << 0)  //     Minimum phase
#define ES9033_BIT_FILTER_SHAPE_2 (0x01 << 0)  //     Linear phase apodizing
#define ES9033_BIT_FILTER_SHAPE_3 (0x02 << 0)  //     Linear phase fast roll-off
#define ES9033_BIT_FILTER_SHAPE_4 (0x03 << 0)  //     Linear phase fast roll-off low ripple
#define ES9033_BIT_FILTER_SHAPE_5 (0x04 << 0)  //     Linear phase slow roll-off
#define ES9033_BIT_FILTER_SHAPE_6 (0x05 << 0)  //     Minimum phase fast roll-off
#define ES9033_BIT_FILTER_SHAPE_7 (0x06 << 0)  //     Minimum phase slow roll-off
#define ES9033_BIT_FILTER_SHAPE_8 (0x07 << 0)  //     Minimum phase slow roll-off low dispersion
/** @} */

/**
 * @name Data Path Control Register (0x36) (R/W)
 * @{
 */
#define ES9033_REG_DATAPATH_CONTROL 0x36
#define ES9033_BIT_BYPASS_FIR_4X (1 << 1) // (0) Bypass 4x interpolation FIR filter
#define ES9033_BIT_BYPASS_FIR_2X (1 << 0) // (0) Bypass 2x interpolation FIR filter
/** @} */

/**
 * @name THD COMP C2 CH1 Register (0x37-0x38) (R/W)
 * @{
 */
#define ES9033_REG_THD_COMP_C2_CH1_LSB 0x37 // (360) THD compensation C2 for channel 1
#define ES9033_REG_THD_COMP_C2_CH1_MSB 0x38
/** @} */

/**
 * @name THD Compensation C3 CH1 Register (0x39-0x3A) (R/W)
 * @{
 */
#define ES9033_REG_THD_COMP_C3_CH1_LSB 0x39 // (141) THD compensation C3 for channel 1
#define ES9033_REG_THD_COMP_C3_CH1_MSB 0x3A
/** @} */

/**
 * @name THD Compensation C2 CH2 Register (0x3B-0x3C) (R/W)
 * @{
 */
#define ES9033_REG_THD_COMP_C2_CH2_LSB 0x3B // (360) THD compensation C2 for channel 2
#define ES9033_REG_THD_COMP_C2_CH2_MSB 0x3C
/** @} */

/**
 * @name THD Compensation C3 CH2 Register (0x3D-0x3E) (R/W)
 * @{
 */
#define ES9033_REG_THD_COMP_C3_CH2_LSB 0x3D // (141) THD compensation C3 for channel 2
#define ES9033_REG_THD_COMP_C3_CH2_MSB 0x3E
/** @} */

/**
 * @name Automute Time Register (0x3F-0x40) (R/W)
 * @{
 */
#define ES9033_REG_AUTOMUTE_TIME_LSB 0x3F
#define ES9033_REG_AUTOMUTE_TIME_MSB 0x40
#define ES9033_BIT_AUTOMUTE_RAMP_TO_GROUND (1 << 15) // (1) When ramped to minimum volume during normal mute, allow soft ramp to ground for power saving
#define ES9033_BIT_AUTOMUTE_WAIT_ON_DRE (1 << 14)    // (1) Automute is flagged when automute condition is met and DRE is engaged
#define ES9033_BIT_AUTOMUTE_EN_CH2 (1 << 12)         // (1) Enable automute for channel 2
#define ES9033_BIT_AUTOMUTE_EN_CH1 (1 << 11)         // (1) Enable automute for channel 1
#define ES9033_MASK_AUTOMUTE_TIME (0x07FF << 0)      // (15) Amount of time in seconds the audio must remain below AUTOMUTE_LEVEL before an automute condition is flagged. Valid from 0 (disabled) to 11'h7FF (fastest), where 11'h001 is the slowest. t = 128fs*(2^18/AUTOMUTE_TIME)
/** @} */

/**
 * @name Automute Level Register (0x41-0x42) (R/W)
 * @{
 */
#define ES9033_REG_AUTOMUTE_LEVEL_LSB 0x41 // (8) Threshold level for automute. 0x0001: -132dB, 0xFFFF: -42dB
#define ES9033_REG_AUTOMUTE_LEVEL_MSB 0x42
/** @} */

/**
 * @name Automute Off Level Register (0x43-0x44) (R/W)
 * @{
 */
#define ES9033_REG_AUTOMUTE_OFF_LEVEL_LSB 0x43 // (10) Threshold level for automute off. 0x0001: -132dB, 0xFFFF: -42dB
#define ES9033_REG_AUTOMUTE_OFF_LEVEL_MSB 0x44
/** @} */

/**
 * @name Soft Ramp Config Register (0x45) (R/W)
 * @{
 */
#define ES9033_REG_SOFT_RAMP_CONFIG 0x45
#define ES9033_BIT_GAIN_18DB_CH2 (1 << 7)      // (0) Set 18dB digital gain for channel 2
#define ES9033_BIT_GAIN_18DB_CH1 (1 << 6)      // (0) Set 18dB digital gain for channel 1
#define ES9033_BIT_SOFT_RAMP_TYPE (1 << 5)     // (0) Set soft ramp type. 0: quadratic, 1: linear
#define ES9033_MASK_SOFT_RAMP_TIME (0x1F << 0) // (2) Time to perform soft start ramp. 0 (minimum) to 20 (maximum)
/** @} */

/**
 * @name DRE Force Register (0x49) (R/W)
 * @{
 */
#define ES9033_REG_DRE_FORCE 0x49
#define ES9033_BIT_DRE_FORCE_CH2 (1 << 7) // (1) Force CH2 into DRE mode even if zero cross has not occurred.
#define ES9033_BIT_DRE_FORCE_CH1 (1 << 6) // (1) Force CH1 into DRE mode even if zero cross has not occurred.
/** @} */

/**
 * @name DRE Gain CH1 Register (0x4A-0x4B) (R/W)
 * @{
 */
#define ES9033_REG_DRE_GAIN_CH1_LSB 0x4A // (0x1A34) DRE gain for channel 1. 0x07FF: 0dB, 0x1A34: 16.33dB, 0x7FFF: 30dB
#define ES9033_REG_DRE_GAIN_CH1_MSB 0x4B
/** @} */

/**
 * @name DRE Gain CH2 Register (0x4C-0x4D) (R/W)
 * @{
 */
#define ES9033_REG_DRE_GAIN_CH2_LSB 0x4C // (0x1A34) DRE gain for channel 2. 0x07FF: 0dB, 0x1A34: 16.33dB, 0x7FFF: 30dB
#define ES9033_REG_DRE_GAIN_CH2_MSB 0x4D
/** @} */

/**
 * @name DRE On Threshold Register (0x4E-0x4F) (R/W)
 * @{
 */
#define ES9033_REG_DRE_ON_THRESH_LSB 0x4E // (0x0CF1) DRE on threshold. 0x0CF1: -48dB, 0xFFFF: -24dB
#define ES9033_REG_DRE_ON_THRESH_MSB 0x4F
/** @} */

/**
 * @name DRE Off Threshold Register (0x50-0x51) (R/W)
 * @{
 */
#define ES9033_REG_DRE_OFF_THRESH_LSB 0x50 // (0x8184) DRE off threshold. 0x8184: -28dB, 0xFFFF: -24dB
#define ES9033_REG_DRE_OFF_THRESH_MSB 0x51
/** @} */

/**
 * @name DRE Decay Rate Register (0x52) (R/W)
 * @{
 */
#define ES9033_REG_DRE_DECAY_RATE 0x52
#define ES9033_BIT_DRE_FORCE_LEVEL (1 << 7)    // (1) Force CH1 + CH2 into DRE mode even if zero cross has not occurred
#define ES9033_BIT_DRE_MIN_PEAK (1 << 5)       // (1) DRE peak detector starting point control. 0: maximum, 1: minimum
#define ES9033_MASK_DRE_DECAY_RATE (0x1F << 0) // (0) DRE decay rate. 0 (fastest) to 31 (slowest)
/** @} */

/**
 * @name DC Offset CH1 Register (0x53-0x54) (R/W)
 * @{
 */
#define ES9033_REG_DC_OFFSET_CH1_LSB 0x53 // (0) DC offset for channel 1. V_offset: (DC_OFFSET/2^24-1) * V_ref
#define ES9033_REG_DC_OFFSET_CH1_MSB 0x54
/** @} */

/**
 * @name DC Offset CH2 Register (0x55-0x56) (R/W)
 * @{
 */
#define ES9033_REG_DC_OFFSET_CH2_LSB 0x55 // (0) DC offset for channel 2. V_offset: (DC_OFFSET/2^24-1) * V_ref
#define ES9033_REG_DC_OFFSET_CH2_MSB 0x56
/** @} */

/**
 * @name DC Ramp Rate Register (0x57) (R/W)
 * @{
 */
#define ES9033_REG_DC_RAMP_RATE 0x57 // (0) Value by which the old DC value is incremented/decremented per sample to reach the new DC value. 0: Instant (default), 1: Slowest, 255: Fastest
/** @} */

/**
 * @name Master Trim Register (0x58) (R/W)
 * @{
 */
#define ES9033_REG_MASTER_TRIM 0x58 // (0) Master trim volume. 0: bypass, 1: -42dB, 255: 0dB
/** @} */

/**
 * @name RESET & PLL Register 1 (0xC0) (W only)
 * @{
 */
#define ES9033_REG_RESET_PLL1 0xC0
#define ES9033_BIT_AO_SOFT_RESET (1 << 7)   // (0) Soft reset slave registers
#define ES9033_BIT_PLL_SOFT_RESET (1 << 6)  // (0) Soft reset synchronous slave registers
#define ES9033_MASK_PLL_VCO_I (0x07 << 3)   // (0) PLL VCO current setting mask -> 0x06 for normal operation
#define ES9033_BIT_GPIO1_SDB_SYNC (1 << 1)  // (0) Enable GPIO1 shutdown
#define ES9033_BIT_PLL_CLKHV_PHASE (1 << 0) // (1) Set Digital/analog DAC clock phase. 0: inverted, 1: normal
/** @} */

/**
 * @name PLL Register 2 (0xC1) (W only)
 * @{
 */
#define ES9033_REG_PLL2 0xC1
#define ES9033_BIT_PLL_BYPASS (1 << 7)             // (0) Bypass PLL
#define ES9033_BIT_DVDD_SHUNTB (1 << 6)            // (0) Disable DVDD shunt to ground (10k)
#define ES9033_BIT_SEL_1V_DREG (1 << 5)            // (0) Set DVDD to 1V
#define ES9033_MASK_PLL_HVREG_VREF_SEL (0x07 << 2) // (0) Set PLL HVREG VREF voltage -> 0x01: 1.6V for normal operation
#define ES9033_BIT_SEL_PLL_IN (1 << 1)             // (0) Select PLL input. 0: MCLK, 1: BCK
#define ES9033_BIT_EN_PLL_CLKIN (1 << 0)           // (0) Enable PLL input clock
/** @} */

/**
 * @name PLL Register 3 (0xC2) (W only)
 * @{
 */
#define ES9033_REG_PLL3 0xC2
#define ES9033_BIT_AUTO_LOCK_EN (1 << 2) // (0) Allow PLL to relock when PLL lock is lost and there are 256 valid PLL input clock cycles
/** @} */

/**
 * @name PLL Register 4 (0xC3) (W only)
 * @{
 */
#define ES9033_REG_PLL4 0xC3
#define ES9033_MASK_PLL_CP_BIAS_SEL (0x07 << 5)   // (0) PLL charge pump bias mask -> 0x03 for normal operation
#define ES9033_MASK_PLL_PFD_DELAY_SEL (0x03 << 3) // (0) PLL internal delay mask -> 0x03 for normal operation
#define ES9033_BIT_PLL_VCO_FLIMIT_PD (1 << 2)     // (0) Disable VCO frequency limit -> 1 for normal operation
#define ES9033_BIT_PLL_VCO_PDB (1 << 1)           // (0) Enable PLL VCO
#define ES9033_BIT_PLL_CP_PDB (1 << 0)            // (0) Enable PLL charge pump
/** @} */

/**
 * @name PLL Register 5 (0xC4) (W only)
 * @{
 */
#define ES9033_REG_PLL5 0xC4
#define ES9033_MASK_PLL_VCO_BAND_CTRL (0x07 << 5)   // (0) PLL VCO frequency band mask -> 0x03 for normal operation
#define ES9033_MASK_PLL_VCO_IB_AMP_CTRL (0x03 << 0) // (0) PLL VCO V/I bias current mask -> 0x02 for normal operation
/** @} */

/**
 * @name PLL Register 6 (0xC5-0xC7) (W only)
 * @{
 */
#define ES9033_REG_PLL6_LSB 0xC5 // (0) PLL clock feedback divider. 2^25/n
#define ES9033_REG_PLL6_MID 0xC6
#define ES9033_REG_PLL6_MSB 0xC7
/** @} */

/**
 * @name PLL Register 7 (0xC8-0xCA) (W only)
 * @{
 */
#define ES9033_REG_PLL7_LSB 0xC8
#define ES9033_REG_PLL7_MID 0xC9
#define ES9033_REG_PLL7_MSB 0xCA
#define ES9033_BIT_PLL_REG_PDB_HV (1 << 23)            // (0) Enable PLL HV-regulator
#define ES9033_BIT_PLL_REG_PDB_1V2 (1 << 22)           // (0) Enable PLL 1.2V regulator
#define ES9033_BIT_PLL_LOW_BW (1 << 19)                // (0) Set PLL low bandwidth mode -> 1 for normal operation
#define ES9033_BIT_PLL_CLK_OUT_DIV_PHASE_EN (1 << 18)  // (0) Tune the PLL clock output divider phase according to PLL_CLK_OUT_DIV_PHASE
#define ES9033_MASK_PLL_CLK_OUT_DIV_PHASE (0x0F << 14) // (0) PLL clock output divider phase mask
#define ES9033_MASK_PLL_CLK_OUT_DIV (0x0F << 10)       // (0) PLL clock output divider mask + 1
#define ES9033_MASK_PLL_CLK_IN_DIV (0x1FF << 1)        // (0) PLL clock input divider mask + 1
#define ES9033_BIT_PLL_FB_DIV_LOAD (1 << 0)            // (0) Writes 1 then write 0 to load CLK_FB_DIV
/** @} */

/**
 * @name PLL Register 8 (0xCB) (W only)
 * @{
 */
#define ES9033_REG_PLL8 0xCB
#define ES9033_BIT_PLL_DIG_RSTB (1 << 5)     // (0) Reset PLL digital block -> 1 for normal operation
#define ES9033_BIT_PLL_VCO_DIODE_EN (1 << 4) // (0) Enable VCO diode -> 1 for normal operation
/** @} */

/**
 * @name System Read Register (0xE0) (R only)
 * @{
 */
#define ES9033_REG_SYS_READ 0xE0
#define ES9033_MASK_SYS_MODES (0x03 << 3)
#define ES9033_BIT_SYS_ADDR1 (1 << 2)
#define ES9033_BIT_SYS_ADDR0 (1 << 1)
/** @} */

/**
 * @name Chip ID Register (0xE1) (R only)
 * @{
 */
#define ES9033_REG_CHIP_ID 0xE1
/** @} */

/**
 * @name Interrupt State Register (0xE5) (R only)
 * @{
 */
#define ES9033_REG_INTERRUPT_STATE 0xE5
#define ES9033_MASK_SS_FULL_RAMP_INTSTATE (0x03 << 6)
#define ES9033_BIT_DRE_SELECT2_INTSTATE (1 << 5)
#define ES9033_BIT_DRE_SELECT1_INTSTATE (1 << 4)
#define ES9033_MASK_AUTOMUTE_INTSTATE (0x03 << 2)
#define ES9033_MASK_VOL_MIN_INTSTATE (0x03 << 0)
/** @} */

/**
 * @name Interrupt State Register 2 (0xE6) (R only)
 * @{
 */
#define ES9033_REG_INTERRUPT_STATE2 0xE6
#define ES9033_MASK_INPUT_SELECT_OVERRIDE_INTSTATE (0x03 << 6)
#define ES9033_BIT_TDM_DATA_VALID_INT (1 << 5)
#define ES9033_BIT_CLK_AVALID_INT (1 << 4)
#define ES9033_BIT_RWS_REF_CNT_FULL_INT (1 << 3)
#define ES9033_BIT_BCK_WS_FAIL_INT (1 << 2)
#define ES9033_BIT_PLL_LOCKED_R_INT (1 << 1)
#define ES9033_BIT_DOP_VALID_INT (1 << 0)
/** @} */

/**
 * @name Interrupt Source Register (0xE7) (R only)
 * @{
 */
#define ES9033_REG_INTERRUPT_SOURCE 0xE7
#define ES9033_MASK_SS_FULL_RAMP_INTSOURCE (0x03 << 6)
#define ES9033_BIT_DRE_SELECT2_INTSOURCE (1 << 5)
#define ES9033_BIT_DRE_SELECT1_INTSOURCE (1 << 4)
#define ES9033_MASK_AUTOMUTE_INTSOURCE (0x03 << 2)
#define ES9033_BIT_VOL_MIN_INTSOURCE_MASL (0x03 << 0)
/** @} */

/**
 * @name Interrupt Source Register 2 (0xE8) (R only)
 * @{
 */
#define ES9033_REG_INTERRUPT_SOURCE2 0xE8
#define ES9033_MASK_INPUT_SELECT_OVERRIDE_SOURCE (0x03 << 6)
#define ES9033_BIT_TDM_DATA_VALID_SOURCE (1 << 5)
#define ES9033_BIT_CLK_AVALID_SOURCE (1 << 4)
#define ES9033_BIT_RWS_REF_CNT_FULL_SOURCE (1 << 3)
#define ES9033_BIT_BCK_WS_FAIL_SOURCE (1 << 2)
#define ES9033_BIT_PLL_LOCKED_R_SOURCE (1 << 1)
#define ES9033_BIT_DOP_VALID_SOURCE (1 << 0)
/** @} */

/**
 * @name Auto Tuning Read Register (0xEF) (R only)
 * @{
 */
#define ES9033_REG_AUTO_TUNING_READ 0xEF
#define ES9033_BIT_RATIO_VALID (1 << 7)
#define ES9033_BIT_IDAC_DIV_HALF_REG (1 << 6)
#define ES9033_MASK_IDAC_DIV_REG (0x3F << 0)
/** @} */

/**
 * @name GPIO Read Register (0xF0) (R only)
 * @{
 */
#define ES9033_REG_GPIO_READ 0xF0
#define ES9033_BIT_GPIO1_I_READ (1 << 0)
/** @} */

/**
 * @name DAC Status Read Register (0xF1) (R only)
 * @{
 */
#define ES9033_REG_DAC_STATUS_READ 0xF1
#define ES9033_BIT_SS_RAMP_DOWN_CH2 (1 << 7)
#define ES9033_BIT_SS_RAMP_DOWN_CH1 (1 << 6)
#define ES9033_BIT_SS_RAMP_UP_CH2 (1 << 5)
#define ES9033_BIT_SS_RAMP_UP_CH1 (1 << 4)
#define ES9033_BIT_AUTOMUTE_CH2 (1 << 3)
#define ES9033_BIT_AUTOMUTE_CH1 (1 << 2)
#define ES9033_BIT_VOL_MIN_CH2 (1 << 1)
#define ES9033_BIT_VOL_MIN_CH1 (1 << 0)
/** @} */

/**
 * @name DRE Status Read Register (0xF2) (R only)
 * @{
 */
#define ES9033_REG_DRE_STATUS_READ 0xF2
#define ES9033_BIT_TDM_DATA_VALID (1 << 7)
#define ES9033_BIT_DOP_VALID (1 << 6)
#define ES9033_BIT_DRE_DETECT_CH2 (1 << 3)
#define ES9033_BIT_DRE_DETECT_CH1 (1 << 2)
#define ES9033_BIT_DRE_SELECT_CH2 (1 << 1)
#define ES9033_BIT_DRE_SELECT_CH1 (1 << 0)
/** @} */
/** @} */ // End of ES9033_Registers group

/**
 * @brief Initializes the ES9033 DAC with default settings.
 * This function configures the ES9033 for I2S, MCLK = 49.152MHz,
 * fs = 192kHz, DRE enabled, automute enabled.
 *
 * @param i2c_ctx Pointer to the I2C context for communication.
 * @return 0 on success, -1 on failure.
 **/
int es9033_init(i2c_master_t *i2c_ctx);
