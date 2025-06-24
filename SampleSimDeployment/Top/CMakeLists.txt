####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
####

#ITC SFTUFF:
find_path(_ITC_CMAKE_MODULES_
NAMES FindITC_Common.cmake
PATHS ${ITC_CMAKE_MODULES}
        ${ITC_DEV_ROOT}/cmake/modules
        $ENV{ITC_DEV_ROOT}/cmake/modules
        /usr/local/cmake/modules
        /usr/cmake/modules)
if(NOT _ITC_CMAKE_MODULES_)
message(WARNING "Unable to find ITC CMake Modules")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${_ITC_CMAKE_MODULES_})

find_package(NOSENGINE REQUIRED QUIET COMPONENTS common transport client uart can i2c spi)

include_directories("../../../../../components/sample/fsw/shared")#sample_device.h
include_directories("../../../../../components/sample/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/sample/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_mag/fsw/standalone/") #device_cfg.h
include_directories("../../../../../components/generic_mag/fsw/shared/")
include_directories("../../../../../components/generic_mag/fsw/fprime/platform_inc")

include_directories("../../../../../fsw/apps/hwlib/fsw/public_inc")

include_directories("../../../../../fsw/apps/hwlib/sim/inc")

include_directories("../../../../../components/generic_star_tracker/fsw/shared")
include_directories("../../../../../components/generic_star_tracker/fsw/standalone") #device_cfg.
include_directories("../../../../../components/generic_star_tracker/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_radio/fsw/shared")
include_directories("../../../../../components/generic_radio/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_radio/fsw/fprime/platform_inc")

include_directories("../../../../../components/arducam/fsw/shared/") #device.h
include_directories("../../../../../components/arducam/fsw/standalone/") #device_cfg.h
include_directories("../../../../../components/arducam/fsw/fprime/platform_inc") #platform_cfg.h
include_directories("../../../../../components/generic_thruster/fsw/shared")
include_directories("../../../../../components/generic_thruster/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_thruster/fsw/fprime/platform_inc")
include_directories("../../../../../components/generic_torquer/fsw/shared")
include_directories("../../../../../components/generic_torquer/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_torquer/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_css/fsw/shared")
include_directories("../../../../../components/generic_css/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_css/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_eps/fsw/shared")
include_directories("../../../../../components/generic_eps/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_eps/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_imu/fsw/shared")
include_directories("../../../../../components/generic_imu/fsw/standalone") #device_cfg.h
include_directories("../../../../../components/generic_imu/fsw/fprime/platform_inc")
include_directories("../../../../../components/generic_fss/fsw/shared")
include_directories("../../../../../components/generic_fss/fsw/standalone/") #device_cfg.h
include_directories("../../../../../components/generic_fss/fsw/fprime/platform_inc")

include_directories("../../../../../components/generic_reaction_wheel/fsw/fprime/platform_inc")
include_directories("../../../../../components/generic_reaction_wheel/fsw/shared")
include_directories("../../../../../components/generic_reaction_wheel/fsw/standalone") #device_cfg.h


set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/instances.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/SampleSimDeploymentPackets.xml"
  "${CMAKE_CURRENT_LIST_DIR}/topology.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/SampleSimDeploymentTopology.cpp"

  #ITC STUFF
  
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/arducam/fsw/shared/cam_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/arducam/fsw/shared/cam_registers.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_torquer/fsw/shared/generic_torquer_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libsocket.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_css/fsw/shared/generic_css_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_fss/fsw/shared/generic_fss_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_mag/fsw/shared/generic_mag_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_star_tracker/fsw/shared/generic_star_tracker_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_radio/fsw/shared/generic_radio_device.c" 
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/sample/fsw/shared/sample_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_thruster/fsw/shared/generic_thruster_device.c"

  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_eps/fsw/shared/generic_eps_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_imu/fsw/shared/generic_imu_device.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../components/generic_reaction_wheel/fsw/shared/generic_reaction_wheel_device.c"
  
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libtrq.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libsocket.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libuart.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libcan.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libi2c.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/libspi.c"
  "${CMAKE_CURRENT_LIST_DIR}/../../../../../fsw/apps/hwlib/sim/src/nos_link.c"
)
set(MOD_DEPS
  Fw/Logger
  Svc/PosixTime
  # Communication Implementations
  Drv/Udp
  Drv/TcpClient

  #ITC Stuff
  ${ITC_Common_LIBRARIES}
  ${NOSENGINE_LIBRARIES}
)

register_fprime_module()