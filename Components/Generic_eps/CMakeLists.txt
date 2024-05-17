####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/generic_eps/fsw/src")
include_directories("../../../../../components/generic_eps/support/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_eps/fsw/platform_inc")

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_eps.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_eps.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_eps/fsw/src/generic_eps_device.c"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_eps/support/device_cfg.h"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/fsw/public_inc/hwlib.h"
  # "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_eps/fsw/platform_inc/generic_eps_platform_cfg.h"
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
