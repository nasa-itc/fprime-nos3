####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/generic_radio/fsw/cfs/src")
include_directories("../../../../../components/generic_radio/support/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_radio/fsw/cfs/platform_inc")
include_directories("../../../../../components/generic_radio/fsw/cfs/mission_inc")
# include_directories("../../../../../fsw/cfe/modules/core_api/fsw/inc/") #cfe_endian.h
# include_directories("../../../../../fsw/osal/src/os/inc/") #common_types.h
# include_directories("../../../../../fsw/osal/") #osconfig.h
# # include_directories("../../../../../fsw/osal/") #osconfig.h




set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_radio.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_radio.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_radio/fsw/cfs/src/generic_radio_device.c" 
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_radio/fsw/src/generic_radio_app.c"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_radio/support/device_cfg.h"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/fsw/public_inc/hwlib.h"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_radio/fsw/platform_inc/generic_radio_platform_cfg.h"

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
