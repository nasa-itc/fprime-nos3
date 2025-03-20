####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/arducam/fsw/shared/") #device.h #cam_registers.h
include_directories("../../../../../components/arducam/fsw/standalone/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/arducam/fsw/fprime/platform_inc") #platform_cfg.h
include_directories("../../../../../fsw/apps/hwlib/sim/inc") #nos_link.h

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Arducam.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Arducam.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/arducam/fsw/shared/cam_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/arducam/fsw/shared/cam_registers.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/nos_link.c"

)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

set(MOD_DEPS
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}
#     Add your dependencies here
)

register_fprime_module()
