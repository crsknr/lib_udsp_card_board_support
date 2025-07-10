set(LIB_NAME lib_udsp_card_board_support)
set(LIB_VERSION 1.0.0)
set(LIB_INCLUDES api)
set(LIB_COMPILER_FLAGS -Os -g)
set(LIB_DEPENDENT_MODULES   "lib_logging(3.2.0)"
                            "lib_sw_pll(2.2.0)"
                            "lib_io_i2c(1.0.0)")

XMOS_REGISTER_MODULE()
