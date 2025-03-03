#ifndef __TF02PRO_H
#define __TF02PRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"  // Kullandığınız seriye göre değiştirin
#include <stdint.h>
#include <stdbool.h>

/**
  * @brief  Sürücü içerisinden erişmek istediğiniz global değişkenler (extern)
  *         Burada sadece 16 bitlik mesafe ve sinyal gücünü açığa çıkarıyoruz.
  */
extern uint16_t g_TF02ProDistance;
extern uint16_t g_TF02ProStrength;

/**
  * @brief  TF02-Pro başlatma fonksiyonu
  * @param  huart: Kullanılacak UART handle'ı (örn. &huart1)
  * @retval None
  */
void TF02Pro_Init(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __TF02PRO_H */
