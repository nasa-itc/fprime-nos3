####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/generic_imu/fsw/shared")
include_directories("../../../../../components/generic_imu/fsw/standalone/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/generic_imu/fsw/fprime/platform_inc")
include_directories("../../../../../components/generic_imu/fsw/fprime/mission_inc")
include_directories("../../../../../components/generic_imu/fsw/fprime/src") 


set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Generic_imu.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Generic_imu.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_imu/fsw/shared/generic_imu_device.c" #need to fix undeclared errors
  
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
