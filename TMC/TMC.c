// use TMC4671 API

#include "tmc/ic/TMC4671/TMC4671.h"


void init(){
	// Motor type &  PWM configuration
	tmc4671_writeInt(0, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0x00030004);
	tmc4671_writeInt(0, TMC4671_PWM_POLARITIES, 0x00000000);
	tmc4671_writeInt(0, TMC4671_PWM_MAXCNT, 0x00000F9F);
	tmc4671_writeInt(0, TMC4671_PWM_BBM_H_BBM_L, 0x00000A0A);
	tmc4671_writeInt(0, TMC4671_PWM_SV_CHOP, 0x00000007);

	// ADC configuration
	tmc4671_writeInt(0, TMC4671_ADC_I_SELECT, 0x18000100); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_dsADC_MCFG_B_MCFG_A, 0x00100010); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_dsADC_MCLK_A, 0x20000000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_dsADC_MCLK_B, 0x00000000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_dsADC_MDEC_B_MDEC_A, 0x014E014E); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ADC_I0_SCALE_OFFSET, 0x0100815B); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ADC_I1_SCALE_OFFSET, 0x010081CE); // @suppress("Invalid arguments")

	// ABN encoder settings
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_MODE, 0x00000000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_PPR, 0x00001000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_COUNT, 0x00000CAD); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, 0x00000000); // @suppress("Invalid arguments")

	// Limits
	tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_LIMITS, 0x000003E8); // @suppress("Invalid arguments")

	// PI settings
	tmc4671_writeInt(0, TMC4671_PID_TORQUE_P_TORQUE_I, 0x01000100); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_PID_FLUX_P_FLUX_I, 0x01000100); // @suppress("Invalid arguments")

}


int main(void) {
	init();

	// ===== ABN encoder test drive =====

	// Init encoder (mode 0)
	tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000008); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, 0x00000000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000001); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_PHI_E_EXT, 0x00000000); // @suppress("Invalid arguments")
	tmc4671_writeInt(0, TMC4671_UQ_UD_EXT, 0x000007D0);
	wait(1000);
	tmc4671_writeInt(0, TMC4671_ABN_DECODER_COUNT, 0x00000000);

	// Feedback selection
	tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000003);
	tmc4671_writeInt(0, TMC4671_VELOCITY_SELECTION, 0x00000009);

	// Switch to torque mode
	tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000001);

	// Rotate right
	tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0x03E80000);
	wait(3000);

	// Rotate left
	tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0xFC180000);
	wait(3000);

	// Stop
	tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0x00000000);

	return 0;
}
