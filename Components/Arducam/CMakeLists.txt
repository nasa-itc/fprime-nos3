####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
#ITC Changes
include_directories("../../../../../components/arducam/fsw/shared/") #device.h
include_directories("../../../../../components/arducam/fsw/standalone/") #device_cfg.h
include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")
include_directories("../../../../../components/arducam/fsw/fprime/platform_inc") #platform_cfg.h

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Arducam.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Arducam.cpp"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/arducam/fsw/shared/cam_device.c"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

set(MOD_DEPS
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}
#     Add your dependencies here
)

register_fprime_module()
