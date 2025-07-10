# lib_udsp-card_board_support

`lib_udsp-card_board_support` contains board specific hardware configuration code and simple bring-up sequence for the **uDSP-Card** development board, based on the XMOS XU316. For detailed hardware information, schematics, and PCB files, see the hardware repository: [hw_udsp-card](https://github.com/crsknr/hw_udsp-card)

This repository accompanies the blog post "[uDSP-Card: XCORE.AI Development Board for Portable Applications](https://crsknr.github.io/blog/blog/udsp-card)".

## Getting Started

### 1. Add to Your Project

Add this library to your XMOS project by including it in your CMakeLists.txt:

```cmake
# Add module and set hardware target
set(APP_DEPENDENT_MODULES   "..."
                            "lib_ssh_pu_board_support(1.0.0)"
                            "...")
set(APP_HW_TARGET           udsp-card.xn)
```

### 2. Basic Usage

Simple bring-up example within a main.xc file:

```c
#include <xs1.h>„
#include <platform.h>

#include "ssh_pu_board.h"

int main() {
    // Distribute threads
    par{
        // Tile 0
        on tile[0]: {
            // Initialize the board on thread 0!
            udsp_card_devices_init();
        }

        // Tile 1
        on tile[1]: {
            // Handle some audio I2S app on thread 1
            some_audio_app();
        }
    }
}
```

## Required Tools

* **[XMOS XTC Tool](https://www.xmos.com/software-tools)s**: 15.3.1 or later

## Required Libraries (Dependencies)

* [`lib_logging`](https://github.com/xmos/lib_logging): Logging and debug utilities
* [`lib_sw_pll`](https://github.com/xmos/lib_sw_pll): Software PLL for audio clock generation
* `lib_io_i2c`: C based I²C library

## License

This project is licensed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html).
