/*
 * vs1003.h
 *
 *  Created on: Mar 6, 2025
 *      Author: Celil BAYRAKDAR
 */

#ifndef APPLICATION_VS1003_VS1003_H_
#define APPLICATION_VS1003_VS1003_H_

#include "main.h"
#include "../degiskenler.h"

#define XCS_HIGH	HAL_GPIO_WritePin(vs_xcs_GPIO_Port, vs_xcs_Pin, GPIO_PIN_SET)
#define XCS_LOW		HAL_GPIO_WritePin(vs_xcs_GPIO_Port, vs_xcs_Pin, GPIO_PIN_RESET)
#define XDCS_HIGH	HAL_GPIO_WritePin(vs_xdc_GPIO_Port, vs_xdc_Pin, GPIO_PIN_SET)
#define XDCS_LOW	HAL_GPIO_WritePin(vs_xdc_GPIO_Port, vs_xdc_Pin, GPIO_PIN_RESET)
#define XRST_HIGH	HAL_GPIO_WritePin(vs_xrst_GPIO_Port, vs_xrst_Pin, GPIO_PIN_SET)
#define XRST_LOW	HAL_GPIO_WritePin(vs_xrst_GPIO_Port, vs_xrst_Pin, GPIO_PIN_RESET)
#define VS_DREQ		HAL_GPIO_ReadPin(vs_dreq_GPIO_Port, vs_dreq_Pin)

/* Commands */
#define VS1053_WRITE_CMD	0x02;
#define VS1053_READ_CMD		0x03;




uint8_t VS1053_Init(void);
void VS1053_Reset(void);
bool VS1053_SoftReset(void);
bool VS1053_SetVolume(uint8_t volumeLeft, uint8_t volumeRight);
bool VS1053_SetMode(uint16_t mode);
bool VS1053_GetMode(uint16_t *mode);
bool VS1053_AutoResync();
bool VS1053_SetDecodeTime(uint16_t time);
bool VS1053_SendEndFill(uint16_t num);
bool VS1053_IsBusy();
bool VS1053_SciWrite(uint8_t address, uint16_t input);
bool VS1053_SciRead(uint8_t address, uint16_t *res);
bool VS1053_SdiWrite(uint8_t input);
bool VS1053_SdiWrite32(uint8_t *input32);
#endif /* APPLICATION_VS1003_VS1003_H_ */




