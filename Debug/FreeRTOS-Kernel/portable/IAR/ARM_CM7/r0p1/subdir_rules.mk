################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/%.obj: ../FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccs2010/ccs/ccs_base/msp430/include" --include_path="C:/Users/mineb/workspace_ccstheia/RTOS_MSP430FR2433" --include_path="C:/Users/mineb/workspace_ccstheia/RTOS_MSP430FR2433/driverlib/MSP430FR2xx_4xx" --include_path="C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR2433__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/%.obj: ../FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/%.s $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --use_hw_mpy=F5 --include_path="C:/ti/ccs2010/ccs/ccs_base/msp430/include" --include_path="C:/Users/mineb/workspace_ccstheia/RTOS_MSP430FR2433" --include_path="C:/Users/mineb/workspace_ccstheia/RTOS_MSP430FR2433/driverlib/MSP430FR2xx_4xx" --include_path="C:/ti/ccs2010/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR2433__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS-Kernel/portable/IAR/ARM_CM7/r0p1" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


