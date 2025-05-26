################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/portasm.S \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_context.S \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_loadstore_handler.S \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vector_defaults.S \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vectors.S 

C_SRCS += \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/FreeRTOS-openocd.c \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port.c \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_common.c \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_systick.c \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_init.c \
../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_overlay_os_hook.c 

C_DEPS += \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/FreeRTOS-openocd.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_common.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_systick.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_init.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_overlay_os_hook.d 

OBJS += \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/FreeRTOS-openocd.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_common.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_systick.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/portasm.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_context.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_init.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_loadstore_handler.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_overlay_os_hook.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vector_defaults.obj \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vectors.obj 

S_UPPER_DEPS += \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/portasm.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_context.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_loadstore_handler.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vector_defaults.d \
./FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vectors.d 

S_UPPER_DEPS__QUOTED += \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\portasm.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_context.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_loadstore_handler.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_vector_defaults.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_vectors.d" 

OBJS__QUOTED += \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\FreeRTOS-openocd.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port_common.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port_systick.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\portasm.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_context.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_init.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_loadstore_handler.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_overlay_os_hook.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_vector_defaults.obj" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_vectors.obj" 

C_DEPS__QUOTED += \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\FreeRTOS-openocd.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port_common.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\port_systick.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_init.d" \
"FreeRTOS-Kernel\portable\ThirdParty\GCC\Xtensa_ESP32\xtensa_overlay_os_hook.d" 

C_SRCS__QUOTED += \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/FreeRTOS-openocd.c" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port.c" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_common.c" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/port_systick.c" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_init.c" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_overlay_os_hook.c" 

S_UPPER_SRCS__QUOTED += \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/portasm.S" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_context.S" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_loadstore_handler.S" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vector_defaults.S" \
"../FreeRTOS-Kernel/portable/ThirdParty/GCC/Xtensa_ESP32/xtensa_vectors.S" 


