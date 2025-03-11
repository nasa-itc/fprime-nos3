####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/generic_mag/fsw/shared") #device.c
include_directories("../../../../../components/generic_mag/fsw/standalone/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_mag/fsw/fprime/platform_inc")
include_directories("../../../../../fsw/apps/hwlib/sim/inc")

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_mag.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_mag.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_mag/fsw/shared/generic_mag_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/nos_link.c"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Add your dependencies here
# )

set(MOD_DEPS
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}
)

register_fprime_module()
