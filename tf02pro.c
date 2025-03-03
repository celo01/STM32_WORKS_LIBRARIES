#include "tf02pro.h"
#include <string.h>
#include <stdio.h>

/**
  * @brief  Kütüphane içerisindeki global değişkenlerin tanımlanması (tanım yeri).
  *         Başka dosyalarda "extern" ile kullanılacaklar.
  */
uint16_t g_TF02ProDistance = 0; // cm cinsinden
uint16_t g_TF02ProStrength = 0; // 0 - 65535 arası sinyal gücü

/**
  * @brief  TF02-Pro'dan gelen paketleri daha rahat yönetmek için dahili buffer.
  *         9 baytlık veri okuruz (0x59 0x59 başlıklı).
  */
static uint8_t s_lidarRxBuf[9];

/**
  * @brief  TF02-Pro ile haberleşeceğimiz UART handle.
  */
static UART_HandleTypeDef *s_tf02ProHuart = NULL;

/**
  * @brief  TF02-Pro başlatma fonksiyonu
  * @param  huart: Kullanılacak UART handle'ı (örn. &huart1)
  * @retval None
  */
void TF02Pro_Init(UART_HandleTypeDef *huart)
{
    s_tf02ProHuart = huart;

    // İlk kez kesme tabanlı (interrupt) okuma başlat
    HAL_UART_Receive_IT(s_tf02ProHuart, s_lidarRxBuf, 9);
}

/**
  * @brief  UART kesme callback fonksiyonu (HAL kütüphanesi bu fonksiyonu "weak" olarak tanımlar).
  *         Bu yüzden burada yeniden tanımlayarak TF02-Pro'ya gelen verileri yakalıyoruz.
  * @note   main.c'de tekrar tanımlamayın; çakışma olmaması için bu sürücüde dursun.
  * @param  huart: UART handle
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // Hangi UART'tan kesme geldiğini kontrol edelim
    if (huart->Instance == s_tf02ProHuart->Instance)
    {
        // Gelen 9 byte data içinde ilk iki bayt 0x59 0x59 mi?
        if (s_lidarRxBuf[0] == 0x59 && s_lidarRxBuf[1] == 0x59)
        {
            // Checksum hesapla (ilk 8 byte’ın toplamı)
            uint16_t sum = 0;
            for(uint8_t i = 0; i < 8; i++)
            {
                sum += s_lidarRxBuf[i];
            }
            uint8_t checkVal = sum & 0xFF; // alt 8 bit

            // Checksum doğru mu?
            if (checkVal == s_lidarRxBuf[8])
            {
                // Mesafe, Sinyal ve Sıcaklık verilerini ayıkla
                uint16_t dist    = (s_lidarRxBuf[3] << 8) | s_lidarRxBuf[2];
                uint16_t str     = (s_lidarRxBuf[5] << 8) | s_lidarRxBuf[4];
                //uint16_t tempRaw = (s_lidarRxBuf[7] << 8) | s_lidarRxBuf[6];
                //float tempC      = (tempRaw / 8.0f) - 256.0f; // isterseniz kullanabilirsiniz

                // Global değişkenlere aktar
                g_TF02ProDistance = dist;
                g_TF02ProStrength = str;
            }
        }

        // Yeniden 9 baytlık okuma emri ver (kesme tabanlı)
        HAL_UART_Receive_IT(s_tf02ProHuart, s_lidarRxBuf, 9);
    }
}
