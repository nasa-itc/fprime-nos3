####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/generic_fss/fsw/fprime/src")
include_directories("../../../../../components/generic_fss/support/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_fss/fsw/fprime/platform_inc")
include_directories("../../../../../fsw/apps/hwlib/sim/inc")
message(INFO,"${CMAKE_CURRENT_LIST_DIR}")

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_fss.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_fss.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_fss/fsw/fprime/src/generic_fss_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/nos_link.c"

)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

 set(MOD_DEPS
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}

 )

register_fprime_module()
