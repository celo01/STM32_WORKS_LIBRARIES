/*
 * KeyPad_4x3.c
 *
 *  Created on: Sep 10, 2023
 *      Author: Celil BAYRAKDAR
 */
//KÜTÜPHANE DEĞİŞKENLERİ

#include "KeyPad_4x3_CB.h"

static Keypad_WiresTypeDef KeypadStruct;	//Tuş takımı için pin çıkışı değişkenleri

static uint8_t OutPositions[2];		//sütunlar için kullanıldığı için 3 eleman seçtik
//
static char *Keypad_keys[12] =		// 12 tuş olduğundan eleman dizinin içi 12
{
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"*",
	"0",
	"#",
									//klavyedeki tuşları tanımladık
};


/***** FONKSİYON TANIMLARI *****/
//Fonksiyon(1): KeyPad'in pin ve portlarını set eder
void Keypad4x4_Init(Keypad_WiresTypeDef  *KeypadWiringStruct)
{
	//Adım(1): Tuşları kütüphaneye kopyaladık
	KeypadStruct = *KeypadWiringStruct;
	//Adım(2): 3 Çıkış pininin konumlarını bul
	Keypad4x4_FindPins_positions();
	//Adım(3): Çıkış pinlerini reset etmek için başlatır
	KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
	KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
	KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);


	HAL_GPIO_WritePin(KeypadStruct.OUT0_Port, KeypadStruct.OUT0pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KeypadStruct.OUT1_Port, KeypadStruct.OUT1pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(KeypadStruct.OUT2_Port, KeypadStruct.OUT2pin, GPIO_PIN_SET);

}

//Function(2): Bu fonskiyon pinlerin bağlı olduğu konumu bulmaya yarıyor
static void Keypad4x4_FindPins_positions(void)
{
	uint8_t idx=0;
	for(idx=0; idx<12; idx++)			//0'dan 12'ye tek tek hangi tuş olduğunu bylması için for ile saydırıyoruz
	{
		if(((KeypadStruct.OUT0pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[0] = idx;		//eğer ilk sütundaysa
		}
		if(((KeypadStruct.OUT1pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[1] = idx;		//eğer ikinci sütundaysa
		}
		if(((KeypadStruct.OUT2pin>>idx)&0x0001) == 0x0001)
		{
			OutPositions[2] = idx;		//eğer üçüncü sütundaysa
		}

	}
}

//Fonksiyon(3): Bu fonksiyon Sütün numarasını değiştirmek için
static void Keypad4x4_ChangeColomn(uint8_t colNum_0_to_2)
{
	if(colNum_0_to_2==0)					// BU Döngü out0 durumunu kontrol eder
	{
		KeypadStruct.OUT0_Port->OTYPER &= ~(1UL << OutPositions[0]);

		//out1 ve out2 serbest bırakıldı
		KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
		KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);

	}
	else if(colNum_0_to_2==1)			    // BU Döngü out1 durumunu kontrol eder
	{
		KeypadStruct.OUT1_Port->OTYPER &= ~(1UL << OutPositions[1]);

		//out0 ve out2 serbest bırakıldı
		KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
		KeypadStruct.OUT2_Port->OTYPER |= (1UL << OutPositions[2]);

	}
	else if(colNum_0_to_2==2)				// BU Döngü out2 durumunu kontrol eder
	{
		KeypadStruct.OUT2_Port->OTYPER &= ~(1UL << OutPositions[2]);

		//out0 ve out1 serbest bırakıldı
		KeypadStruct.OUT0_Port->OTYPER |= (1UL << OutPositions[0]);
		KeypadStruct.OUT1_Port->OTYPER |= (1UL << OutPositions[1]);
	}

}

//Fonksiyon(4):Bu fonksiyon Pin okuması yapar
void Keypad4x4_ReadKeypad(bool keys[12])
{
	//Adım(1): 1. Sütünu açıp satırları kontrol eder (klavyedeki 1-4-7-yıldız)
	Keypad4x4_ChangeColomn(0);
	keys[0] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[3] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[6] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[9] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

	//Adım(2): 2. Sütünu açıp satırları kontrol eder (klavyedeki 2-5-8-0)
	Keypad4x4_ChangeColomn(1);
	keys[1] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[4] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[7] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[10] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

	//Adım(3): 3. Sütünu açıp satırları kontrol eder (klavyedeki 3-6-9-kare)
	Keypad4x4_ChangeColomn(2);
	keys[2] = HAL_GPIO_ReadPin(KeypadStruct.IN0_Port, KeypadStruct.IN0pin);
	keys[5] = HAL_GPIO_ReadPin(KeypadStruct.IN1_Port, KeypadStruct.IN1pin);
	keys[8] = HAL_GPIO_ReadPin(KeypadStruct.IN2_Port, KeypadStruct.IN2pin);
	keys[11] = HAL_GPIO_ReadPin(KeypadStruct.IN3_Port, KeypadStruct.IN3pin);

}
//Fonksiyon(5): Karakteri alır
char* Keypad4x4_GetChar(uint8_t keypadSw)
{
	return Keypad_keys[keypadSw];
}
