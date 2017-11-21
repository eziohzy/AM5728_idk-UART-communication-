################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: PRU Compiler'
	"/opt/ti/ccsv6/tools/compiler/ti-cgt-pru_2.2.0/bin/clpru" -v3 --include_path="/opt/ti/ccsv6/tools/compiler/ti-cgt-pru_2.2.0/include" --include_path="../../../../include" --include_path="../../../../include/am572x_2_0" -g --define=pru0 --define=am4379 --define=icss1 --define=am5728 --diag_wrap=off --diag_warning=225 --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

pru_uart_init.obj: ../pru_uart_init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: PRU Compiler'
	"/opt/ti/ccsv6/tools/compiler/ti-cgt-pru_2.2.0/bin/clpru" -v3 --include_path="/opt/ti/ccsv6/tools/compiler/ti-cgt-pru_2.2.0/include" --include_path="../../../../include" --include_path="../../../../include/am572x_2_0" -g --define=pru0 --define=am4379 --define=icss1 --define=am5728 --diag_wrap=off --diag_warning=225 --display_error_number --endian=little --hardware_mac=on --preproc_with_compile --preproc_dependency="pru_uart_init.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


