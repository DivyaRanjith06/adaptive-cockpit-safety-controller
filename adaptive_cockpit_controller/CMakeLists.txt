# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(adaptive_cockpit_controller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(adaptive_cockpit_controller

    adaptive_cockpit_controller.c

    hal/gpio_driver.c
    hal/adc_driver.c
    hal/interrupt_driver.c
    hal/watchdog_driver.c

    app/sensor_manager.c
    app/risk_engine.c
    app/state_machine.c
    app/interrupt_manager.c
    app/watchdog_manager.c

    services/telemetry_service.c
)

pico_set_program_name(adaptive_cockpit_controller "adaptive_cockpit_controller")
pico_set_program_version(adaptive_cockpit_controller "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(adaptive_cockpit_controller 0)
pico_enable_stdio_usb(adaptive_cockpit_controller 1)

# Add the standard library to the build
target_link_libraries(adaptive_cockpit_controller
        pico_stdlib
        hardware_adc)

# Add the standard include files to the build
target_include_directories(adaptive_cockpit_controller PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/config
    ${CMAKE_CURRENT_LIST_DIR}/services
)

pico_add_extra_outputs(adaptive_cockpit_controller)

