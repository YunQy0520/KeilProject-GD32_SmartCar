/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Communication
  * @{
  */

/** @defgroup Communication_Exported_Types
  * @{
  */

/** 
  * @brief  SendData enumeration  
  */

typedef enum
{ 
  Send_Temperature = 0x54,
	Send_Hz = 0x48,
	Send_ms = 0x6D,
	Send_Voltage = 0x56,
	Send_Current = 0x43,
	Send_Mode = 0x4D,
	Send_Output = 0x4F
}SendData_TypeDef;

/**
  * @}
  */

/** @defgroup Communication_Exported_Macros
  * @{
  */ 

#define FRAMEWARE_VERSION 0x10
#define DEVICE_ADDRESS 0x06
#define MAX_FRAME_LENGTH 8

/**
  * @}
  */

/** @defgroup Communication_Exported_Functions
  * @{
  */

unsigned char Sum_Check(const unsigned char *dat, unsigned char len);
void Data_Analysis(unsigned char *data);
void UnpackFrame(unsigned char *frame);
void Framing(unsigned char byte);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __COMMUNICATION_H */

/***** (C) YUNQY 2023 *****END OF FILE*****/
