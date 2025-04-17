
#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "InterruptControl.h"

typedef struct{
	uint32_t AutoReloadValue;
	uint8_t MasterModeSelect;
	uint8_t ClockDivisionSelect;
	uint16_t PrescalerValue;
	uint8_t CenterAlignedModeSelect;
	bool AutoReloadBufferEnable;
	bool Direction; //TimerCountDownModeEnable
	bool InterruptUpdateEnable;
	bool DisableUpdateEvent;
	bool OnePulseModeEnable;
}GPTimer_Config_t;

void Timer_Init(GPTIMR_RegDef_t* TIMER_REGISTER, GPTimer_Config_t TIMER_CONFIG);
void Timer_ClockControl(GPTIMR_RegDef_t* TIMER_REGISTER, uint8_t ENABLE_DISABLE);
void Start_Timer(GPTIMR_RegDef_t* TIMER_REGISTER);
void Stop_Timer(GPTIMR_RegDef_t* TIMER_REGISTER);
void Reset_Timer(GPTIMR_RegDef_t* TIMER_REGISTER);
uint32_t getTimerValue(GPTIMR_RegDef_t* TIMER_REGISTER);

void Timer_Interrupt_Enable_Disable(GPTIMR_RegDef_t* TIMER_REGISTER, uint8_t ENABLE_DISABLE);

uint32_t getTimerAutoReloadValue(GPTIMR_RegDef_t* TIMER_REGISTER);

//CONTROL REGISTER 1 OFFSETS
#define TIMER_CR1_OFFSET_CEN 0
#define TIMER_CR1_OFFSET_UDIS 1
#define TIMER_CR1_OFFSET_URS 2
#define TIMER_CR1_OFFSET_OPM 3
#define TIMER_CR1_OFFSET_DIR 4
#define TIMER_CR1_OFFSET_CMS 5
#define TIMER_CR1_OFFSET_ARPE 7
#define TIMER_CR1_OFFSET_CKD 8

//CONTROL REGISTER 2 OFFSETS
#define TIMER_CR2_OFFSET_CCDS 3
#define TIMER_CR2_OFFSET_MMS 4
#define TIMER_CR2_TI1S 7


#define TIMER_DIER_OFFSET_UIE 0


//SETTINGS FOR
#define TIMER_MMS_RESET 0b000
#define TIMER_MMS_ENABLE 0b001
#define TIMER_MMS_UPDATE 0b010
#define TIMER_MMS_COMPARE_PULSE 0b011
#define TIMER_MMS_COMPARE_OC1REF 0b100
#define TIMER_MMS_COMPARE_OC2REF 0b101
#define TIMER_MMS_COMPARE_OC3REF 0b110
#define TIMER_MMS_COMPARE_OC4REF 0b111

#define TIMER_CKD_MODE_ONE 0b00
#define TIMER_CKD_MODE_TWO 0b01
#define TIMER_CKD_MODE_FOUR 0b10

#define TIMER_CMS_EDGE 0b00
#define TIMER_CMS_MODE_1 0b01
#define TIMER_CMS_MODE_2 0b10
#define TIMER_CMS_MODE_3 0b11

#define TIMER_ARPE_DISABLE 0
#define TIMER_ARPE_ENABLE 1

#define TIMER_DIR_UPCOUNTER 0
#define TIMER_DIR_DOWNCOUNTER 1

#define TIMER_URS_ANY 0
#define TIMER_URS_OVERUNDER 1

#define TIMER_UDIS_ENABLE 0
#define TIMER_UDIS_DISABLE 1

#define TIMER_OPM_OFF 0
#define TIMER_OPM_ON 1

#define TIMER_CEN_DISABLE 0
#define TIMER_CEN_ENABLE 1

#define TIMER_TI1S_CH1 0
#define TIMER_TI1S_ALL 1

#define TIMER_CCDS_CCx 0
#define TIMER_CCDS_UPDATE 1

#define TIMER_UIE_DISABLE 0
#define TIMER_UIE_ENABLE 1






#endif /* TIMER_DRIVER_H_ */
