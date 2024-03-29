/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lora_at.h
  * @author  MCD Application Team
  * @brief   Header for driver at.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORA_AT_H__
#define __LORA_AT_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "LmHandler.h"
#include "stm32_adv_trace.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/*
 * AT Command Id errors. Note that they are in sync with ATError_description static array
 * in command.c
 */
typedef enum eATEerror
{
  AT_OK = 0,
  AT_ERROR,
  AT_PARAM_ERROR,
  AT_BUSY_ERROR,
  AT_TEST_PARAM_OVERFLOW,
  AT_NO_NET_JOINED,
  AT_RX_ERROR,
  AT_NO_CLASS_B_ENABLE,
  AT_DUTYCYCLE_RESTRICTED,
  AT_CRYPTO_ERROR,
  AT_MAX,
} ATEerror_t;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* AT printf */
#define AT_PRINTF(...)     do{  UTIL_ADV_TRACE_COND_FSend(VLEVEL_OFF, T_REG_OFF, TS_OFF, __VA_ARGS__);}while(0)
#define AT_PPRINTF(...)    do{ } while( UTIL_ADV_TRACE_OK \
                               != UTIL_ADV_TRACE_COND_FSend(VLEVEL_ALWAYS, T_REG_OFF, TS_OFF, __VA_ARGS__) ) /*Polling Mode*/

/* AT Command strings. Commands start with AT */
/* General commands */
#define AT_VER        "+QVER"
#define AT_VL         "+QVL"
#define AT_LTIME      "+QLTIME"
#define AT_RESET      "Z"

/* Context Store */
#define AT_RFS        "+QRFS"
#define AT_CS         "+QCS"

/* Keys, IDs and EUIs management commands */
#define AT_JOINEUI    "+QAPPEUI" /*to match with V1.0.x specification- For V1.1.x "+APPEUI" will be replaced by "+JOINEUI"*/
#define AT_NWKKEY     "+QNWKKEY"
#define AT_APPKEY     "+QAPPKEY"
#define AT_NWKSKEY    "+QNWKSKEY"
#define AT_APPSKEY    "+QAPPSKEY"
#define AT_DADDR      "+QDADDR"
#define AT_DEUI       "+QDEUI"
#define AT_NWKID      "+QNWKID"

/* LoRaWAN join and send data commands */
#define AT_JOIN       "+QJOIN"
#define AT_LINKC      "+QLINKC"
#define AT_SEND       "+QSEND"

/* LoRaWAN network management commands */
#define AT_ADR        "+QADR"
#define AT_DR         "+QDR"
#define AT_BAND       "+QBAND"
#define AT_CLASS      "+QCLASS"
#define AT_DCS        "+QDCS"
#define AT_JN1DL      "+QJN1DL"
#define AT_JN2DL      "+QJN2DL"
#define AT_RX1DL      "+QRX1DL"
#define AT_RX2DL      "+QRX2DL"
#define AT_RX2DR      "+QRX2DR"
#define AT_RX2FQ      "+QRX2FQ"
#define AT_TXP        "+QTXP"
#define AT_PGSLOT     "+QPGSLOT"

/* Radio tests commands */
#define AT_TTONE      "+QTTONE"
#define AT_TRSSI      "+QTRSSI"
#define AT_TCONF      "+QTCONF"
#define AT_TTX        "+QTTX"
#define AT_TRX        "+QTRX"
#define AT_TTH        "+QTTH"
#define AT_TOFF       "+QTOFF"

/* Radio access commands */
#define AT_REGW       "+QREGW"
#define AT_REGR       "+QREGR"

/* LoraWAN Certif command */
#define AT_CERTIF     "+QCERTIF"

/* Information command */
#define AT_BAT        "+QBAT"

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Return AT_OK in all cases
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_return_ok(const char *param);

/**
  * @brief  Return AT_ERROR in all cases
  * @param  param string of the AT command - unused
  * @retval AT_ERROR
  */
ATEerror_t AT_return_error(const char *param);

/* --------------- Application events --------------- */
/**
  * @brief  Event callback on join
  * @param params
  */
void AT_event_join(LmHandlerJoinParams_t *params);

/**
  * @brief  Event callback on received data
  * @param appData
  * @param params
  */
void AT_event_receive(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params);

/**
  * @brief  Event callback on confirmed acknowledge
  * @param  params
  */
void AT_event_confirm(LmHandlerTxParams_t *params);

/**
  * @brief  Event callback on class updated
  * @param  deviceClass
  */
void AT_event_ClassUpdate(DeviceClass_t deviceClass);

/**
  * @brief  Event callback on beacon status updated
  * @param  params
  */
void AT_event_Beacon(LmHandlerBeaconParams_t *params);

void AT_event_OnNvmDataChange(LmHandlerNvmContextStates_t state);

void AT_event_OnStoreContextRequest(void *nvm, uint32_t nvm_size);

void AT_event_OnRestoreContextRequest(void *nvm, uint32_t nvm_size);

/* --------------- General commands --------------- */
/**
  * @brief  Print the version of the AT_Slave FW
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_version_get(const char *param);

/**
  * @brief  Get the verbose level
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_verbose_get(const char *param);

/**
  * @brief  Set the verbose level
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_verbose_set(const char *param);

/**
  * @brief  Get the local time in UTC format
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_LocalTime_get(const char *param);

/**
  * @brief  Trig a reset of the MCU
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_reset(const char *param);

/* --------------- Context Store commands --------------- */
/**
  * @brief  Restore factory settings in Eeprom
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_restore_factory_settings(const char *param);

/**
  * @brief  Store current settings in Eeprom
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_store_context(const char *param);

/* --------------- Keys, IDs and EUIs management commands --------------- */
/**
  * @brief  Print Join Eui
  * @param  param string of the AT command
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinEUI_get(const char *param);

/**
  * @brief  Set Join Eui
  * @param  param string of the AT command
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinEUI_set(const char *param);

/**
  * @brief  Print Network Key
  * @param  param string of the AT command
  * @retval AT_OK
  */
ATEerror_t AT_NwkKey_get(const char *param);

/**
  * @brief  Set Network Key
  * @param  param string of the AT command
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_NwkKey_set(const char *param);

/**
  * @brief  Print Application Key
  * @param  param string of the AT command
  * @retval AT_OK
  */
ATEerror_t AT_AppKey_get(const char *param);

/**
  * @brief  Set Application Key
  * @param  param string of the AT command
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_AppKey_set(const char *param);

/**
  * @brief  Print Network Session Key
  * @param  param string of the AT command
  * @retval AT_OK
  */
ATEerror_t AT_NwkSKey_get(const char *param);

/**
  * @brief  Set Network Session Key
  * @param  param String pointing to provided DevAddr
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_NwkSKey_set(const char *param);

/**
  * @brief  Print Application Session Key
  * @param  param string of the AT command
  * @retval AT_OK
  */
ATEerror_t AT_AppSKey_get(const char *param);

/**
  * @brief  Set Application Session Key
  * @param  param String pointing to provided DevAddr
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_AppSKey_set(const char *param);

/**
  * @brief  Print the DevAddr
  * @param  param String pointing to provided DevAddr
  * @retval AT_OK
  */
ATEerror_t AT_DevAddr_get(const char *param);

/**
  * @brief  Set DevAddr
  * @param  param String pointing to provided DevAddr
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DevAddr_set(const char *param);

/**
  * @brief  Print Device EUI
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_DevEUI_get(const char *param);

/**
  * @brief  Set Device EUI
  * @param  param string of the AT command
  * @retval AT_OK if OK
  */
ATEerror_t AT_DevEUI_set(const char *param);

/**
  * @brief  Print the Network ID
  * @param  param String pointing to provided parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_NetworkID_get(const char *param);

/**
  * @brief  Set the Network ID
  * @param  param String pointing to provided parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_NetworkID_set(const char *param);

/* --------------- LoRaWAN join and send data commands --------------- */
/**
  * @brief  Join a network
  * @param  param String parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Join(const char *param);

/**
  * @brief  Piggyback a Link Check Request to the next uplink
  * @param  param String parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Link_Check(const char *param);

/**
  * @brief  Print last received message
  * @param  param String parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Send(const char *param);

/* --------------- LoRaWAN network management commands --------------- */
/**
  * @brief  Print Adaptive Data Rate setting
  * @param  param String pointing to provided ADR setting
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_ADR_get(const char *param);

/**
  * @brief  Set Adaptive Data Rate setting
  * @param  param String pointing to provided ADR setting
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_ADR_set(const char *param);

/**
  * @brief  Print Data Rate
  * @param  param String pointing to provided rate
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DataRate_get(const char *param);

/**
  * @brief  Set Data Rate
  * @param  param String pointing to provided rate
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DataRate_set(const char *param);

/**
  * @brief  Print actual Active Region
  * @param  param string of the AT command - unused
  * @retval AT_OK
  */
ATEerror_t AT_Region_get(const char *param);

/**
  * @brief  Set Active Region
  * @param  param string of the AT command
  * @retval AT_OK if OK
  */
ATEerror_t AT_Region_set(const char *param);

/**
  * @brief  Print the Device Class
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DeviceClass_get(const char *param);

/**
  * @brief  Set the Device Class
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DeviceClass_set(const char *param);

/**
  * @brief  Get ETSI Duty Cycle parameter
  * @param  param String pointing to provided param
  * @retval AT_OK
  */
ATEerror_t AT_DutyCycle_get(const char *param);

/**
  * @brief  Set ETSI Duty Cycle parameter
  * @param  param String pointing to provided Duty Cycle value
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_DutyCycle_set(const char *param);

/**
  * @brief  Print the delay between the end of the Tx and the Join Rx Window 1
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinAcceptDelay1_get(const char *param);

/**
  * @brief  Set the delay between the end of the Tx and the Join Rx Window 1
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinAcceptDelay1_set(const char *param);

/**
  * @brief  Print the delay between the end of the Tx and the Join Rx Window 2
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinAcceptDelay2_get(const char *param);

/**
  * @brief  Set the delay between the end of the Tx and the Join Rx Window 2
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_JoinAcceptDelay2_set(const char *param);

/**
  * @brief  Print the delay between the end of the Tx and the Rx Window 1
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx1Delay_get(const char *param);

/**
  * @brief  Set the delay between the end of the Tx and the Rx Window 1
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx1Delay_set(const char *param);

/**
  * @brief  Print the delay between the end of the Tx and the Rx Window 2
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2Delay_get(const char *param);

/**
  * @brief  Set the delay between the end of the Tx and the Rx Window 2
  * @param  param String pointing to provided param
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2Delay_set(const char *param);

/**
  * @brief  Print Rx2 window data rate
  * @param  param String pointing to parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2DataRate_get(const char *param);

/**
  * @brief  Set Rx2 window data rate
  * @param  param String pointing to parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2DataRate_set(const char *param);

/**
  * @brief  Print Rx2 window frequency
  * @param  param String pointing to parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2Frequency_get(const char *param);

/**
  * @brief  Set Rx2 window frequency
  * @param  param String pointing to parameter
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_Rx2Frequency_set(const char *param);

/**
  * @brief  Print Transmit Power
  * @param  param String pointing to provided power
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_TransmitPower_get(const char *param);

/**
  * @brief  Set Transmit Power
  * @param  param String pointing to provided power
  * @retval AT_OK if OK, or an appropriate AT_xxx error code
  */
ATEerror_t AT_TransmitPower_set(const char *param);

/**
  * @brief  Get the unicast pingslot periodicity, Data rate and PsFrequency
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_PingSlot_get(const char *param);

/**
  * @brief  Set the unicast pingslot periodicity
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_PingSlot_set(const char *param);

/* --------------- Radio tests commands --------------- */
/**
  * @brief  Start Tx test
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_txTone(const char *param);

/**
  * @brief  Start Rx tone
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_rxRssi(const char *param);

/**
  * @brief  Get Rx or Tx test config
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_get_config(const char *param);

/**
  * @brief  Set Rx or Tx test config
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_set_config(const char *param);

/**
  * @brief  Start Tx LoRa test
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_tx(const char *param);

/**
  * @brief  Start Rx LoRa test
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_rx(const char *param);

/**
  * @brief  Start Tx hopping
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_tx_hopping(const char *param);

/**
  * @brief  stop Rx or Tx test
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_test_stop(const char *param);

/* --------------- Radio access commands --------------- */
/**
  * @brief  Write Radio Register
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_write_register(const char *param);

/**
  * @brief  Read Radio Register
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_read_register(const char *param);

/* --------------- LoraWAN Certif command --------------- */
/**
  * @brief  set the Modem in Certif Mode
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_Certif(const char *param);

/* --------------- Information command --------------- */
/**
  * @brief  Get the battery level
  * @param  param String parameter
  * @retval AT_OK
  */
ATEerror_t AT_bat_get(const char *param);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __LORA_AT_H__ */
