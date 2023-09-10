/*
 * KeyPad_4x3_CB.h
 *
 *  Created on: Sep 10, 2023
 *      Author: Celil BAYRAKDAR
 */

#ifndef INC_KEYPAD_4X3_CB_H_
#define INC_KEYPAD_4X3_CB_H_



#endif /* INC_KEYPAD_4X3_CB_H_ */
#include "stm32f4xx_hal.h"
#include <stdbool.h>

// Sabit değişkenler ve typedefleri tanımlıyoruz
typedef struct
{
	GPIO_TypeDef* IN0_Port;
	GPIO_TypeDef* IN1_Port;
	GPIO_TypeDef* IN2_Port;
	GPIO_TypeDef* IN3_Port;
	GPIO_TypeDef* OUT0_Port;
	GPIO_TypeDef* OUT1_Port;
	GPIO_TypeDef* OUT2_Port;

	uint16_t	IN0pin;
	uint16_t	IN1pin;
	uint16_t	IN2pin;
	uint16_t	IN3pin;
	uint16_t	OUT0pin;
	uint16_t	OUT1pin;
	uint16_t	OUT2pin;
}
Keypad_WiresTypeDef;

//FONKSİYONLAR NE İŞE YARAR?
//Fonksiyon(1): KeyPad'in pin ve portlarını set eder
void Keypad4x4_Init(Keypad_WiresTypeDef  *KeypadWiringStruct);
//Fonksiyon(2): Sütunların pin konumunu alır
static void Keypad4x4_FindPins_positions(void);
//Fonksiyon(3): Sütun numarasını değiştirir
static void Keypad4x4_ChangeColomn(uint8_t colNum_0_to_3);
//Fonksiyon(4): Basılan Tuşu okur
void Keypad4x4_ReadKeypad(bool keys[12]);
//Fonksiyon(5): Karakter alır
char* Keypad4x4_GetChar(uint8_t keypadSw);

/*
 * Detayları KeyPad_4x3.c Dosyasının içinde var
 */
