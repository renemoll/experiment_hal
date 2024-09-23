#ifndef STM32F7xx_HAL_CONF_H
#define STM32F7xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

#if !defined(HSE_VALUE)
#define HSE_VALUE 16000000UL
#endif

#if !defined(HSE_STARTUP_TIMEOUT)
#define HSE_STARTUP_TIMEOUT 100UL
#endif

#if !defined(MSI_VALUE)
#define MSI_VALUE 4000000UL
#endif

#if !defined(HSI_VALUE)
#define HSI_VALUE 16000000UL
#endif

#if !defined(HSI48_VALUE)
#define HSI48_VALUE 48000000UL
#endif

#if !defined(LSI_VALUE)
#define LSI_VALUE 32000UL
#endif

#if !defined(LSE_VALUE)
#define LSE_VALUE 32768UL
#endif

#if !defined(LSE_STARTUP_TIMEOUT)
#define LSE_STARTUP_TIMEOUT 5000UL
#endif

#if !defined(EXTERNAL_SAI1_CLOCK_VALUE)
#define EXTERNAL_SAI1_CLOCK_VALUE 48000UL
#endif

#define VDD_VALUE 3300UL
#define TICK_INT_PRIORITY (15UL)
#define USE_RTOS 0U
#define PREFETCH_ENABLE 1U

#define USE_HAL_ADC_REGISTER_CALLBACKS \
  0U /* ADC register callback disabled       */
#define USE_HAL_COMP_REGISTER_CALLBACKS \
  0U /* COMP register callback disabled      */
#define USE_HAL_CORDIC_REGISTER_CALLBACKS \
  0U /* CORDIC register callback disabled    */
#define USE_HAL_CRYP_REGISTER_CALLBACKS \
  0U /* CRYP register callback disabled      */
#define USE_HAL_DAC_REGISTER_CALLBACKS \
  0U /* DAC register callback disabled       */
#define USE_HAL_DCMI_REGISTER_CALLBACKS \
  0U /* DCMI register callback disabled      */
#define USE_HAL_DMA2D_REGISTER_CALLBACKS \
  0U /* DMA2D register callback disabled     */
#define USE_HAL_DSI_REGISTER_CALLBACKS \
  0U /* DSI register callback disabled       */
#define USE_HAL_FDCAN_REGISTER_CALLBACKS \
  0U /* FDCAN register callback disabled     */
#define USE_HAL_FMAC_REGISTER_CALLBACKS \
  0U /* FMAC register callback disabled      */
#define USE_HAL_HASH_REGISTER_CALLBACKS \
  0U /* HASH register callback disabled      */
#define USE_HAL_HCD_REGISTER_CALLBACKS \
  0U /* HCD register callback disabled       */
#define USE_HAL_GFXMMU_REGISTER_CALLBACKS \
  0U /* GFXMMU register callback disabled    */
#define USE_HAL_GFXTIM_REGISTER_CALLBACKS \
  0U /* GFXTIM register callback disabled    */
#define USE_HAL_GPU2D_REGISTER_CALLBACKS \
  0U /* GPU2D register callback disabled     */
#define USE_HAL_I2C_REGISTER_CALLBACKS \
  0U /* I2C register callback disabled       */
#define USE_HAL_IWDG_REGISTER_CALLBACKS \
  0U /* IWDG register callback disabled      */
#define USE_HAL_IRDA_REGISTER_CALLBACKS \
  0U /* IRDA register callback disabled      */
#define USE_HAL_JPEG_REGISTER_CALLBACKS \
  0U /* JPEG register callback disabled      */
#define USE_HAL_LPTIM_REGISTER_CALLBACKS \
  0U /* LPTIM register callback disabled     */
#define USE_HAL_LTDC_REGISTER_CALLBACKS \
  0U /* LTDC register callback disabled      */
#define USE_HAL_MDF_REGISTER_CALLBACKS \
  0U /* MDF register callback disabled       */
#define USE_HAL_MMC_REGISTER_CALLBACKS \
  0U /* MMC register callback disabled       */
#define USE_HAL_NAND_REGISTER_CALLBACKS \
  0U /* NAND register callback disabled      */
#define USE_HAL_NOR_REGISTER_CALLBACKS \
  0U /* NOR register callback disabled       */
#define USE_HAL_OPAMP_REGISTER_CALLBACKS \
  0U /* MDIO register callback disabled      */
#define USE_HAL_OTFDEC_REGISTER_CALLBACKS \
  0U /* OTFDEC register callback disabled    */
#define USE_HAL_PCD_REGISTER_CALLBACKS \
  0U /* PCD register callback disabled       */
#define USE_HAL_PKA_REGISTER_CALLBACKS \
  0U /* PKA register callback disabled       */
#define USE_HAL_RAMCFG_REGISTER_CALLBACKS \
  0U /* RAMCFG register callback disabled    */
#define USE_HAL_RNG_REGISTER_CALLBACKS \
  0U /* RNG register callback disabled       */
#define USE_HAL_RTC_REGISTER_CALLBACKS \
  0U /* RTC register callback disabled       */
#define USE_HAL_SAI_REGISTER_CALLBACKS \
  0U /* SAI register callback disabled       */
#define USE_HAL_SD_REGISTER_CALLBACKS \
  0U /* SD register callback disabled        */
#define USE_HAL_SDRAM_REGISTER_CALLBACKS \
  0U /* SDRAM register callback disabled     */
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS \
  0U /* SMARTCARD register callback disabled */
#define USE_HAL_SMBUS_REGISTER_CALLBACKS \
  0U /* SMBUS register callback disabled     */
#define USE_HAL_SPI_REGISTER_CALLBACKS \
  0U /* SPI register callback disabled       */
#define USE_HAL_SRAM_REGISTER_CALLBACKS \
  0U /* SRAM register callback disabled      */
#define USE_HAL_TIM_REGISTER_CALLBACKS \
  0U /* TIM register callback disabled       */
#define USE_HAL_TSC_REGISTER_CALLBACKS \
  0U /* TSC register callback disabled       */
#define USE_HAL_UART_REGISTER_CALLBACKS \
  0U /* UART register callback disabled      */
#define USE_HAL_USART_REGISTER_CALLBACKS \
  0U /* USART register callback disabled     */
#define USE_HAL_WWDG_REGISTER_CALLBACKS \
  0U /* WWDG register callback disabled      */
#define USE_HAL_OSPI_REGISTER_CALLBACKS \
  0U /* OSPI register callback disabled      */

#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f7xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f7xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f7xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f7xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f7xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

/* Exported macro ------------------------------------------------------------*/
#ifdef USE_FULL_ASSERT
/**
 * @brief  The assert_param macro is used for function's parameters check.
 * @param  expr: If expr is false, it calls assert_failed function
 *         which reports the name of the source file and the source
 *         line number of the call that failed.
 *         If expr is true, it returns no value.
 * @retval None
 */
#define assert_param(expr) \
  ((expr) ? (void)0U : assert_failed((uint8_t*)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* stm32f7xx_HAL_CONF_H */
