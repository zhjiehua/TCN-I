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
#define MANUALPAGE_INDEX				2
#define PARAMETERPAGE_INDEX				3
#define INPUTPAGE_INDEX					4
#define TEMPERATUREPAGE_INDEX			5
#define TESTPAGE_INDEX					6
	
#define TIPSPAGE_INDEX					7
	
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
#define MAIN_OUTPUT_EDIT				20
#define MAIN_CLEAR_BUTTON				30
#define MAIN_MANUAL_BUTTON				31

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
#define MANUAL_SAPERATECW_BUTTON		9
#define MANUAL_SAPERATECCW_BUTTON		10
#define MANUAL_DISLOCATECW_BUTTON		11
#define MANUAL_DISLOCATECCW_BUTTON		12
#define MANUAL_HEATUP_BUTTON			13
#define MANUAL_HEATDOWN_BUTTON			14
#define MANUAL_HEATON_BUTTON			15
#define MANUAL_CUTOFF1HEATON_BUTTON		16
#define MANUAL_CUTOFF2HEATON_BUTTON		17

#define MANUAL_INPUT_BUTTON				40
#define MANUAL_PARAMETER_BUTTON			41
#define MANUAL_TEMPERATURE_BUTTON		42
#define MANUAL_TEST_BUTTON				43

#define MANUAL_BACK_BUTTON				50
#define MANUAL_FORWARD_BUTTON			51

/************************************************************************/
/* 参数页面控件ID                                                   */
/************************************************************************/
#define PARAMETER_CUTOFFTEMP_EDIT		1
#define PARAMETER_CUTOFFTIME_EDIT		2
#define PARAMETER_FUSINGTEMP_EDIT		3
#define PARAMETER_FUSINGTIME_EDIT		4
#define PARAMETER_JOINTTIME_EDIT		5
#define PARAMETER_CUTOFF1TEMPSTA_EDIT	6
#define PARAMETER_CUTOFF2TEMPSTA_EDIT	7
#define PARAMETER_FUSINGTEMPSTA_EDIT	8
#define PARAMETER_AUTO_BUTTON			9
#define PARAMETER_RESET_BUTTON			10

#define PARAMETER_BACK_BUTTON			50
#define PARAMETER_FORWARD_BUTTON		51

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
#define INPUT_FORWARD_BUTTON			51

/************************************************************************/
/* 温度页面控件ID                                                       */
/************************************************************************/
#define TEMPERATURE_CURVE_GRAPH			1

#define TEMPERATURE_BACK_BUTTON			50
#define TEMPERATURE_FORWARD_BUTTON		51

/************************************************************************/
/* 测试页面控件ID                                                       */
/************************************************************************/
#define TEST_CLAMP1CW_BUTTON			1
#define TEST_CLAMP1CCW_BUTTON			2
#define TEST_CLAMP2CW_BUTTON			3
#define TEST_CLAMP2CCW_BUTTON			4
#define TEST_CUTOFF1CW_BUTTON			5
#define TEST_CUTOFF1CCW_BUTTON			6
#define TEST_CUTOFF2CW_BUTTON			7
#define TEST_CUTOFF2CCW_BUTTON			8
#define TEST_SEPERATECW_BUTTON			9
#define TEST_SEPERATECCW_BUTTON			10
#define TEST_DISPOSCW_BUTTON			11
#define TEST_DISPOSCCW_BUTTON			12
#define TEST_HEATINGUP_BUTTON			13
#define TEST_HEATINGDOWN_BUTTON			14

#define TEST_BACK_BUTTON				50
#define TEST_FORWARD_BUTTON				51

/************************************************************************/
/* 提示页面控件ID                                                      */
/************************************************************************/
#define TIPS_TIPS_EDIT					1
#define TIPS_OK_BUTTON					2

/************************************************************************/
/* 软件版本                                                             */
/************************************************************************/
#define PANEL_VERSION					"9.1.7"
#define VERSION							"0.1.0"

/*
 * 函数声明
 */
void mainPageButtonProcess(uint16 control_id, uint8  state);

void manualPageButtonProcess(uint16 control_id, uint8  state);

void parameterPageButtonProcess(uint16 control_id, uint8  state);
void parameterPageEditProcess(uint16 control_id, uint8 *str);

void inputPageButtonProcess(uint16 control_id, uint8  state);

void temperaturePageButtonProcess(uint16 control_id, uint8  state);

void testPageButtonProcess(uint16 control_id, uint8  state);

void tipsPageButtonProcess(uint16 control_id, uint8  state);

#ifdef __cplusplus
}
#endif

#endif
