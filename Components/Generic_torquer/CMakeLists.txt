####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
include_directories("../../../../../components/generic_torquer/fsw/shared/") #device.h
include_directories("../../../../../components/generic_torquer/fsw/standalone/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_torquer/fsw/fprime/platform_inc") #platform_cfg.h

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_torquer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_torquer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_torquer/fsw/shared/generic_torquer_device.c"
  "${CMAKE_CURRENT_LIST_DIR}../../../../../apps/hwlib/fsw/linux/libtrq.c"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Add your dependencies here
# )

register_fprime_module()
