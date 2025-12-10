#####
# 'deployment' Deployment:
#
# This registers the 'deployment' deployment to the build system. 
# Custom components that have not been added at the project-level should be added to 
# the list below.
#
#####

###
# Topology and Components
###

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

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

# include_directories("../../../../components/sample/fsw/shared")#sample_device.h
# include_directories("../../../../components/sample/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/sample/fsw/fprime/platform_inc")

# include_directories("../../../../fsw/apps/hwlib/fsw/public_inc")

# include_directories("../../../../fsw/apps/hwlib/sim/inc")

# include_directories("../../../../components/generic_star_tracker/fsw/shared")
# include_directories("../../../../components/generic_star_tracker/fsw/standalone/") #device_cfg.
# include_directories("../../../../components/generic_star_tracker/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_radio/fsw/shared")
# include_directories("../../../../components/generic_radio/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_radio/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_torquer/fsw/shared")
# include_directories("../../../../components/generic_torquer/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_torquer/fsw/fprime/platform_inc")
# include_directories("../../../../components/generic_css/fsw/shared")
# include_directories("../../../../components/generic_css/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_css/fsw/fprime/platform_inc")
# include_directories("../../../../components/generic_fss/fsw/shared/src")
# include_directories("../../../../components/generic_fss/fsw/standalone/") #device_cfg.h
# include_directories("../../../../components/generic_fss/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_eps/fsw/shared")
# include_directories("../../../../components/generic_eps/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_eps/fsw/fprime/platform_inc")

# include_directories("../../../../components/arducam/fsw/shared/") #device.h
# include_directories("../../../../components/arducam/fsw/standalone/") #device_cfg.h
# include_directories("../../../../components/arducam/fsw/fprime/platform_inc") #platform_cfg.h
# include_directories("../../../../components/generic_thruster/fsw/shared")
# include_directories("../../../../components/generic_thruster/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_thruster/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_imu/fsw/shared")
# include_directories("../../../../components/generic_imu/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_imu/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_mag/fsw/shared")
# include_directories("../../../../components/generic_mag/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_mag/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_reaction_wheel/fsw/shared")
# include_directories("../../../../components/generic_reaction_wheel/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/generic_reaction_wheel/fsw/fprime/platform_inc")

# include_directories("../../../../components/novatel_oem615/fsw/shared")
# include_directories("../../../../components/novatel_oem615/fsw/standalone") #device_cfg.h
# include_directories("../../../../components/novatel_oem615/fsw/fprime/platform_inc")

# include_directories("../../../../components/generic_adcs/fsw/fprime/src")
# include_directories("../../../../components/generic_adcs/fsw/shared")


set(SOURCE_FILES 
"${CMAKE_CURRENT_LIST_DIR}/Main.cpp"

#ITC STUFF
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/arducam/fsw/shared/cam_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/arducam/fsw/shared/cam_registers.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_torquer/fsw/shared/generic_torquer_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_fss/fsw/shared/generic_fss_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/sample/fsw/shared/sample_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_css/fsw/shared/generic_css_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_star_tracker/fsw/shared/generic_star_tracker_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_radio/fsw/shared/generic_radio_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_eps/fsw/shared/generic_eps_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_thruster/fsw/shared/generic_thruster_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/novatel_oem615/fsw/shared/novatel_oem615_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_adcs/fsw/shared/generic_adcs_utilities.c"

# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_imu/fsw/shared/generic_imu_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_mag/fsw/shared/generic_mag_device.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_reaction_wheel/fsw/shared/generic_reaction_wheel_device.c"

# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libtrq.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libsocket.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libuart.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libcan.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libi2c.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libspi.c"
# "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/nos_link.c" 
)



set(MOD_DEPS 
    ${FPRIME_CURRENT_MODULE}/Top
    ${ITC_Common_LIBRARIES}
    ${NOSENGINE_LIBRARIES}
)

register_fprime_deployment(
    # SOURCES
    #     "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
    # DEPENDS
    #     ${FPRIME_CURRENT_MODULE}_Top
)

target_sources(${FPRIME_CURRENT_MODULE} PRIVATE 
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/arducam/fsw/shared/cam_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/arducam/fsw/shared/cam_registers.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_torquer/fsw/shared/generic_torquer_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_fss/fsw/shared/generic_fss_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/sample/fsw/shared/sample_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_css/fsw/shared/generic_css_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_star_tracker/fsw/shared/generic_star_tracker_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_radio/fsw/shared/generic_radio_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_eps/fsw/shared/generic_eps_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_thruster/fsw/shared/generic_thruster_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/novatel_oem615/fsw/shared/novatel_oem615_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_adcs/fsw/shared/generic_adcs_utilities.c"
    
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_imu/fsw/shared/generic_imu_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_mag/fsw/shared/generic_mag_device.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../components/generic_reaction_wheel/fsw/shared/generic_reaction_wheel_device.c"
    
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libtrq.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libsocket.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libuart.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libcan.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libi2c.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/libspi.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../../../fsw/apps/hwlib/sim/src/nos_link.c" 
)

target_include_directories(${FPRIME_CURRENT_MODULE} PRIVATE
    "../../../../components/sample/fsw/shared"
    "../../../../components/sample/fsw/standalone"
    "../../../../components/sample/fsw/fprime/platform_inc"
    
    "../../../../fsw/apps/hwlib/fsw/public_inc"
    
    "../../../../fsw/apps/hwlib/sim/inc"
    
    "../../../../components/generic_star_tracker/fsw/shared"
    "../../../../components/generic_star_tracker/fsw/standalone/"
    "../../../../components/generic_star_tracker/fsw/fprime/platform_inc"
    
    "../../../../components/generic_radio/fsw/shared"
    "../../../../components/generic_radio/fsw/standalone" 
    "../../../../components/generic_radio/fsw/fprime/platform_inc"
    
    "../../../../components/generic_torquer/fsw/shared"
    "../../../../components/generic_torquer/fsw/standalone"
    "../../../../components/generic_torquer/fsw/fprime/platform_inc"
    "../../../../components/generic_css/fsw/shared"
    "../../../../components/generic_css/fsw/standalone"
    "../../../../components/generic_css/fsw/fprime/platform_inc"
    "../../../../components/generic_fss/fsw/shared/src"
    "../../../../components/generic_fss/fsw/standalone/"
    "../../../../components/generic_fss/fsw/fprime/platform_inc"
    
    "../../../../components/generic_eps/fsw/shared"
    "../../../../components/generic_eps/fsw/standalone"
    "../../../../components/generic_eps/fsw/fprime/platform_inc"
    
    "../../../../components/arducam/fsw/shared/"
    "../../../../components/arducam/fsw/standalone/"
    "../../../../components/arducam/fsw/fprime/platform_inc"
    "../../../../components/generic_thruster/fsw/shared"
    "../../../../components/generic_thruster/fsw/standalone"
    "../../../../components/generic_thruster/fsw/fprime/platform_inc"
    
    "../../../../components/generic_imu/fsw/shared"
    "../../../../components/generic_imu/fsw/standalone"
    "../../../../components/generic_imu/fsw/fprime/platform_inc"
    
    "../../../../components/generic_mag/fsw/shared"
    "../../../../components/generic_mag/fsw/standalone"
    "../../../../components/generic_mag/fsw/fprime/platform_inc"
    
    "../../../../components/generic_reaction_wheel/fsw/shared"
    "../../../../components/generic_reaction_wheel/fsw/standalone"
    "../../../../components/generic_reaction_wheel/fsw/fprime/platform_inc"

    "../../../../components/novatel_oem615/fsw/shared"
    "../../../../components/novatel_oem615/fsw/standalone"
    "../../../../components/novatel_oem615/fsw/fprime/platform_inc"
    
    "../../../../components/generic_adcs/fsw/fprime/src"
    "../../../../components/generic_adcs/fsw/shared"


)