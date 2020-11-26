#include "tmc/TMCL.h"


const char *VersionString = MODULE_ID"V307"; // module id and version of the firmware shown in the TMCL-IDE

/* Keep as is! This lines are important for the update functionality. */
#if defined(Landungsbruecke)
	const uint8_t Protection[] __attribute__ ((section(".cfmconfig")))=
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  //Backdoor key
		0xFF, 0xFF, 0xFF, 0xFF,                          //Flash protection (FPPROT)
		0x7E,                                            //Flash security   (FSEC) => nach Image-Generierung manuell auf 0x40 setzen im Image
		0xF9,                                            //Flash option     (FOPT) (NMI ausgeschaltet, EzPort ausgeschaltet, Normal power)
		0xFF,                                            //reserved
		0xFF                                             //reserved
	};

	struct BootloaderConfig {
		uint32_t BLMagic;
		uint32_t drvEnableResetValue;
	};

	// This struct gets placed at a specific address by the linker
	struct BootloaderConfig __attribute__ ((section(".bldata"))) BLConfig;
#endif


int main(void){
	while(1){
	
	}
	return 0;
}
