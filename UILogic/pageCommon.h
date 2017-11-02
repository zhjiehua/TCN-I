#ifndef _PAGE_COMMON_H_
#define _PAGE_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "string.h"
#include "../HMI/hmi_user_uart.h"
#include "../HMI/hmi_driver.h"
#include "../HMI/cmd_process.h"

/************************************************************************/
/* 页面ID定义                                                           */
/************************************************************************/
#define LOGOPAGE_INDEX					0
#define MAINPAGE_INDEX					1
#define SETUPPAGE_INDEX					2
#define MANUALPAGE_INDEX				3
#define STATUSPAGE_INDEX				4
#define TEMPPARAPAGE_INDEX				5
#define TIMEPARAPAGE_INDEX				6
#define MOTORPARAPAGE_INDEX				7
#define INPUTPAGE_INDEX					8
#define MANUALRAWPAGE_INDEX				9
#define ABOUTPAGE_INDEX					10
	
#define TIPSPAGE_INDEX					11
#define TIPS1PAGE_INDEX					12

#define PERMITPAGE_INDEX				13

/************************************************************************/
/* LOGO页面控件ID                                                         */
/************************************************************************/
#define LOGO_START_BUTTON				1
#define LOGO_STATUS_EDIT				2

/************************************************************************/
/* 主页面控件ID                                                         */
/************************************************************************/
#define MAIN_STATUS1_BUTTON				1
#define MAIN_STATUS2_BUTTON				2
#define MAIN_STATUS3_BUTTON				3
#define MAIN_STATUS4_BUTTON				4
#define MAIN_STATUS5_BUTTON				5
#define MAIN_STATUS6_BUTTON				6
#define MAIN_STATUS7_BUTTON				7
#define MAIN_STATUS8_BUTTON				8
#define MAIN_STATUS9_BUTTON				9
#define MAIN_STATUS10_BUTTON			10
#define MAIN_OUTPUT_EDIT				20

#define MAIN_MANUAL_BUTTON				30

/************************************************************************/
/* 设置页面控件ID                                                         */
/************************************************************************/
#define SETUP_MANUAL_BUTTON				1
#define SETUP_STATUS_BUTTON				2
#define SETUP_TEMPPARA_BUTTON			3
#define SETUP_TIMEPARA_BUTTON			4
#define SETUP_MOTORPARA_BUTTON			5
#define SETUP_INPUT_BUTTON				6
#define SETUP_MANUALRAW_BUTTON			7
#define SETUP_ABOUT_BUTTON				8
#define SETUP_PERMIT_BUTTON				9

#define SETUP_BACK_BUTTON				50

/************************************************************************/
/* 手动页面控件ID                                                       */
/************************************************************************/
#define MANUAL_CLAMP1CW_BUTTON			1
#define MANUAL_CLAMP1CCW_BUTTON			2
#define MANUAL_CLAMP2CW_BUTTON			3
#define MANUAL_CLAMP2CCW_BUTTON			4
#define MANUAL_CUTOFF1CW_BUTTON			5
#define MANUAL_CUTOFF1CCW_BUTTON		6
#define MANUAL_CUTOFF2CW_BUTTON			7
#define MANUAL_CUTOFF2CCW_BUTTON		8
#define MANUAL_SEPARATECW_BUTTON		9
#define MANUAL_SEPARATECCW_BUTTON		10
#define MANUAL_DISLOCATECW_BUTTON		11
#define MANUAL_DISLOCATECCW_BUTTON		12
#define MANUAL_HEATINGUP_BUTTON			13
#define MANUAL_HEATINGDOWN_BUTTON		14
#define MANUAL_HEATON_BUTTON			15

#define MANUAL_SETUP_BUTTON				16

#define MANUAL_BACK_BUTTON				50

/************************************************************************/
/* 状态页面控件ID                                                       */
/************************************************************************/
#define STATUS_TEMPCUTOFF1_EDIT			1
#define STATUS_TEMPCUTOFF2_EDIT			2
#define STATUS_TEMPFUSING_EDIT			3
#define STATUS_CUTOFF1_BUTTON			10
#define STATUS_CUTOFF2_BUTTON			11
#define STATUS_AUTO_BUTTON				12
#define STATUS_RESET_BUTTON				13

#define STATUS_BACK_BUTTON				50

/************************************************************************/
/* 温度参数页面控件ID                                                   */
/************************************************************************/
#define TEMPPARA_CUTOFF1KP_EDIT			1
#define TEMPPARA_CUTOFF1KI_EDIT			2
#define TEMPPARA_CUTOFF1KD_EDIT			3
#define TEMPPARA_CUTOFF2KP_EDIT			4
#define TEMPPARA_CUTOFF2KI_EDIT			5
#define TEMPPARA_CUTOFF2KD_EDIT			6
#define TEMPPARA_CUTOFF1TEMP_EDIT		7
#define TEMPPARA_CUTOFF2TEMP_EDIT		8
#define TEMPPARA_FUSINGTEMP_EDIT		9
#define TEMPPARA_FUSINGHOLDINGTEMP_EDIT	10
#define TEMPPARA_CUTOFF1TEMPCRL_BUTTON	11
#define TEMPPARA_CUTOFF2TEMPCRL_BUTTON	12
#define TEMPPARA_FUSINGTEMPCRL_BUTTON	13

#define TEMPPARA_BACK_BUTTON			50

/************************************************************************/
/* 时间参数页面控件ID                                                   */
/************************************************************************/
#define TIMEPARA_CLAMP1DELAY_EDIT		1
#define TIMEPARA_CLAMP2DELAY_EDIT		2
#define TIMEPARA_CUTOFF1DELAY_EDIT		3
#define TIMEPARA_CUTOFF2DELAY_EDIT		4
#define TIMEPARA_CUTOFFRETURN_EDIT		5
#define TIMEPARA_CUTOFF_EDIT			6
#define TIMEPARA_FUSING_EDIT			7
#define TIMEPARA_JOINT_EDIT				8
#define TIMEPARA_HEATINGUPDELAY_EDIT	9
#define TIMEPARA_HEATINGDOWNDELAY_EDIT	10

#define TIMEPARA_BACK_BUTTON			50

/************************************************************************/
/* 电机参数页面控件ID                                                   */
/************************************************************************/
#define MOTORPARA_DISLOCATERETURN_EDIT	1
#define MOTORPARA_DISLOCATESPEED_EDIT	2
#define MOTORPARA_HEATINGUPSPEED_EDIT	3
#define MOTORPARA_HEATINGDOWNSPEED_EDIT	4
#define MOTORPARA_CUROFF1HEATVOL_EDIT	5
#define MOTORPARA_CUROFF2HEATVOL_EDIT	6
#define MOTORPARA_FUSINGHEATVOL_EDIT	7

#define MOTORPARA_BACK_BUTTON			50

/************************************************************************/
/* 输入点页面控件ID                                                       */
/************************************************************************/
#define INPUT_CLAMP1ORIGIN_BUTTON		1
#define INPUT_CLAMP1LIMIT_BUTTON		2
#define INPUT_CLAMP2ORIGIN_BUTTON		3
#define INPUT_CLAMP2LIMIT_BUTTON		4
#define INPUT_COTOFF1ORIGIN_BUTTON		5
#define INPUT_COTOFF1LIMIT_BUTTON		6
#define INPUT_COTOFF2ORIGIN_BUTTON		7
#define INPUT_COTOFF2LIMIT_BUTTON		8
#define INPUT_SAPERATEORIGIN_BUTTON		9
#define INPUT_SAPERATELIMIT_BUTTON		10
#define INPUT_DISLACATEORIGIN_BUTTON	11
#define INPUT_DISLACATELIMIT_BUTTON		12
#define INPUT_HEATORIGIN_BUTTON			13
#define INPUT_HEATLIMIT_BUTTON			14
#define INPUT_EMERGENCY_BUTTON			15
#define INPUT_AUTOSTART_BUTTON			16

#define INPUT_BACK_BUTTON				50

/************************************************************************/
/* 手动(无限位点)页面控件ID                                             */
/************************************************************************/
#define MANUALRAW_CLAMP1CW_BUTTON		1
#define MANUALRAW_CLAMP1CCW_BUTTON		2
#define MANUALRAW_CLAMP2CW_BUTTON		3
#define MANUALRAW_CLAMP2CCW_BUTTON		4
#define MANUALRAW_CUTOFF1CW_BUTTON		5
#define MANUALRAW_CUTOFF1CCW_BUTTON		6
#define MANUALRAW_CUTOFF2CW_BUTTON		7
#define MANUALRAW_CUTOFF2CCW_BUTTON		8
#define MANUALRAW_SAPERATECW_BUTTON		9
#define MANUALRAW_SAPERATECCW_BUTTON	10
#define MANUALRAW_DISLOCATECW_BUTTON	11
#define MANUALRAW_DISLOCATECCW_BUTTON	12
#define MANUALRAW_HEATUP_BUTTON			13
#define MANUALRAW_HEATDOWN_BUTTON		14
#define MANUALRAW_HEATON_BUTTON			15
#define MANUALRAW_CUTOFF1HEATON_BUTTON	16
#define MANUALRAW_CUTOFF2HEATON_BUTTON	17

#define MANUALRAW_BACK_BUTTON			50

/************************************************************************/
/* 关于页面控件ID                                                       */
/************************************************************************/
#define ABOUT_VERSION_EDIT				1
#define ABOUT_CLEAROUTPUT_BUTTON		2
#define ABOUT_SAVEASDEFAULT_BUTTON		3
#define ABOUT_RESTOREDEFAULT_BUTTON		4
#define ABOUT_CLEARUSABLETIMES_BUTTON	5

#define ABOUT_BACK_BUTTON				50

/************************************************************************/
/* 提示页面控件ID                                                      */
/************************************************************************/
#define TIPS_TIPS_EDIT					1
#define TIPS_OK_BUTTON					2
#define TIPS_CANCEL_BUTTON				3

/************************************************************************/
/* 许可页面控件ID                                                      */
/************************************************************************/
#define PERMIT_SERIAL_EDIT				1
#define PERMIT_RANDOMCODE_BUTTON		2
#define PERMIT_RANDOMCODE_EDIT			3
#define PERMIT_ACTIVECODE_EDIT			4
#define PERMIT_ACTIVE_BUTTON			5
#define PERMIT_USABLETIMES_EDIT			6

#define PERMIT_BACK_BUTTON				50

/************************************************************************/
/* 软件版本                                                             */
/************************************************************************/
#define PANEL_VERSION					"9.1.7"
#define VERSION							"1.0.0"

/*
 * 函数声明
 */
void logoPageButtonProcess(uint16 control_id, uint8 state);
 
void mainPageButtonProcess(uint16 control_id, uint8 state);

void setupPageButtonProcess(uint16 control_id, uint8 state);

void manualPageButtonProcess(uint16 control_id, uint8 state);

void statusPageButtonProcess(uint16 control_id, uint8 state);
void statusPageEditProcess(uint16 control_id, uint8 *str);

void tempparaPageEditProcess(uint16 control_id, uint8 *str);
void tempparaPageButtonProcess(uint16 control_id, uint8 state);

void timeparaPageEditProcess(uint16 control_id, uint8 *str);
void timeparaPageButtonProcess(uint16 control_id, uint8 state);

void motorparaPageEditProcess(uint16 control_id, uint8 *str);
void motorparaPageButtonProcess(uint16 control_id, uint8 state);

void inputPageButtonProcess(uint16 control_id, uint8 state);

void manualrawPageButtonProcess(uint16 control_id, uint8 state);

void aboutPageButtonProcess(uint16 control_id, uint8 state);

void tips1PageButtonProcess(uint16 control_id, uint8 state);

void permitPageButtonProcess(uint16 control_id, uint8 state);
void permitPageEditProcess(uint16 control_id, uint8 *str);

#ifdef __cplusplus
}
#endif

#endif
