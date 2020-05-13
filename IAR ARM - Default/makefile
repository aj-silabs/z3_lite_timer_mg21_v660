################################################################################
# Automatically-generated file. Do not edit!
################################################################################

export WINEDEBUG=-all

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zll-utility-server/subdir.mk
-include zll-scenes-server/subdir.mk
-include zll-on-off-server/subdir.mk
-include zll-level-control-server/subdir.mk
-include zll-identify-server/subdir.mk
-include zll-commissioning-server/subdir.mk
-include zll-commissioning-common/subdir.mk
-include zcl-framework-core/subdir.mk
-include update-tc-link-key/subdir.mk
-include strong-random/subdir.mk
-include simple-main/subdir.mk
-include serial/EFR32/subdir.mk
-include serial/subdir.mk
-include scenes/subdir.mk
-include scan-dispatch/subdir.mk
-include reporting/subdir.mk
-include on-off/subdir.mk
-include nvm3/EFR32/subdir.mk
-include nvm3/subdir.mk
-include network-steering/subdir.mk
-include network-creator-security/subdir.mk
-include network-creator/subdir.mk
-include mbedtls/EFR32/subdir.mk
-include level-control/subdir.mk
-include interpan/subdir.mk
-include identify/subdir.mk
-include heartbeat/subdir.mk
-include hal-library/EFR32/subdir.mk
-include groups-server/subdir.mk
-include green-power-common/subdir.mk
-include green-power-client/subdir.mk
-include find-and-bind-target/subdir.mk
-include external-generated-files/subdir.mk
-include emlib/subdir.mk
-include emdrv/subdir.mk
-include ember-minimal-printf/subdir.mk
-include efr32/subdir.mk
-include debug-jtag/EFR32/subdir.mk
-include debug-basic-library/EFR32/subdir.mk
-include counters/subdir.mk
-include color-control-server/subdir.mk
-include coexistence-stub/EFR32/subdir.mk
-include ccm-encryption/subdir.mk
-include build/obj/subdir.mk
-include build/exe/subdir.mk
-include basic/subdir.mk
-include antenna-stub/subdir.mk
-include aes-cmac/subdir.mk
-include adc/EFR32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(MSA_UPPER_DEPS)),)
-include $(MSA_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S79_DEPS)),)
-include $(S79_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(MSA_DEPS)),)
-include $(MSA_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S79_UPPER_DEPS)),)
-include $(S79_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pre-build main-build

# Main-build Target
main-build: z3_lite_timer_mg21_v660.out

# Tool invocations
z3_lite_timer_mg21_v660.out: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: IAR Linker for ARM'
	ilinkarm $(OBJS) $(USER_OBJS) -o "z3_lite_timer_mg21_v660.out" --config "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/base/hal/micro/cortexm3/efm32/iar-cfg.icf" --config_def LOCAL_STORAGE_BTL=1 --config_def FLASH_SIZE=1048576 --config_def RAM_SIZE=98304 --config_def SIMEEPROM_SIZE=32768 --config_def LOCKBITS_IN_MAINFLASH_SIZE=8192 --config_def EMBER_MALLOC_HEAP_SIZE=0 --config_def HEADER_SIZE=256 --config_def PSSTORE_SIZE=0 --config_def LONGTOKEN_SIZE=0 --no_wrap_diagnostics "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/zigbee-r22-support-stub-library-cortexm3-iar-efr32mg21-rail/zigbee-r22-support-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/install-code-library-cortexm3-iar-efr32mg21-rail/install-code-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-stub-library-cortexm3-iar-efr32mg21-rail/cbke-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-library-dsa-verify-stub-cortexm3-iar-efr32mg21-rail/cbke-library-dsa-verify-stub.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/gp-library-cortexm3-iar-efr32mg21-rail/gp-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/radio/rail_lib/autogen/librail_release/librail_efr32xg21_iar_release.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/debug-extended-stub-library-cortexm3-iar-efr32mg21-rail/debug-extended-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/debug-basic-library-cortexm3-iar-efr32mg21-rail/debug-basic-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-283k1-stub-library-cortexm3-iar-efr32mg21-rail/cbke-283k1-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/end-device-bind-stub-library-cortexm3-iar-efr32mg21-rail/end-device-bind-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/security-library-core-cortexm3-iar-efr32mg21-rail/security-library-core.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-library-dsa-verify-283k1-stub-cortexm3-iar-efr32mg21-rail/cbke-library-dsa-verify-283k1-stub.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/hal-library-cortexm3-iar-efr32mg21-rail/hal-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/packet-validate-stub-library-cortexm3-iar-efr32mg21-rail/packet-validate-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/multi-network-stub-library-cortexm3-iar-efr32mg21-rail/multi-network-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//platform/emdrv/nvm3/lib/libnvm3_CM33_iar.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/sim-eeprom2-to-nvm3-upgrade-stub-library-cortexm3-iar-efr32mg21-rail/sim-eeprom2-to-nvm3-upgrade-stub-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/zigbee-pro-stack-cortexm3-iar-efr32mg21-rail/zigbee-pro-stack.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/zll-library-cortexm3-iar-efr32mg21-rail/zll-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/security-library-link-keys-stub-cortexm3-iar-efr32mg21-rail/security-library-link-keys-stub.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/binding-table-library-cortexm3-iar-efr32mg21-rail/binding-table-library.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-library-dsa-sign-stub-cortexm3-iar-efr32mg21-rail/cbke-library-dsa-sign-stub.a" "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.6//protocol/zigbee/build/cbke-163k1-stub-library-cortexm3-iar-efr32mg21-rail/cbke-163k1-stub-library.a" --entry __iar_program_start --map "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5/z3_lite_timer_mg21_v660/IAR ARM - Default/z3_lite_timer_mg21_v660.map" --log_file "C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5/z3_lite_timer_mg21_v660/IAR ARM - Default/z3_lite_timer_mg21_v660.log" --log initialization,modules,sections,veneers --diag_suppress=Lp012 --redirect _Printf=_PrintfSmallNoMb --redirect _Scanf=_ScanfFullNoMb  
	ielftool --srec --verbose "z3_lite_timer_mg21_v660.out" "z3_lite_timer_mg21_v660.s37"  
	ielftool --ihex --verbose "z3_lite_timer_mg21_v660.out" "z3_lite_timer_mg21_v660.hex"  
	ielftool --bin --verbose "z3_lite_timer_mg21_v660.out" "z3_lite_timer_mg21_v660.bin"
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(MSA_UPPER_DEPS)$(EXECUTABLES)$(OBJS)$(ASM_DEPS)$(S79_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(MSA_DEPS)$(C_DEPS)$(S79_UPPER_DEPS) z3_lite_timer_mg21_v660.out
	-@echo ' '

pre-build:
	-cmd //c 'C:\SILICO~1\SIMPLI~1\v4\DEVELO~1\sdks\GECKO_~1\v2.5\Z3_LIT~1/z3_lite_timer_mg21_v660-prebuild.bat' 'z3_lite_timer_mg21_v660' 'C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5/z3_lite_timer_mg21_v660' 'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

post-build:
	-cmd //c 'C:\SILICO~1\SIMPLI~1\v4\DEVELO~1\sdks\GECKO_~1\v2.5\Z3_LIT~1/z3_lite_timer_mg21_v660-postbuild.bat' 'z3_lite_timer_mg21_v660' 'C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.5/z3_lite_timer_mg21_v660' 'C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.2/arm' 'C:\SiliconLabs\SimplicityStudio\v4'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
