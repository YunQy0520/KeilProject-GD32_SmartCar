/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "systick.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t adc_value[6];

/* Private function prototypes -----------------------------------------------*/
static void rcu_config(void);
static void gpio_config(void);
static void dma_config(void);

/* Private functions ---------------------------------------------------------*/

/*!
    \brief      configure the different system clocks
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_config(void)
{
	/* enable GPIOC clock */
	rcu_periph_clock_enable(RCU_GPIOC);
	/* enable DMA clock */
//	rcu_periph_clock_enable(RCU_DMA1);
	/* enable ADC0 clock */
	rcu_periph_clock_enable(RCU_ADC0);
	/* config ADC clock */
	adc_clock_config(ADC_ADCCK_PCLK2_DIV8);
}

/*!
    \brief      configure the GPIO peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gpio_config(void)
{
	/* ADC0: PC5 */
	gpio_mode_set(GPIOC, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_5);
}

/*!
    \brief      configure the DMA peripheral
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dma_config(void)
{
	/* ADC_DMA_channel configuration */
	dma_single_data_parameter_struct dma_single_data_parameter;

	/* ADC DMA_channel configuration */
	dma_deinit(DMA1, DMA_CH0);

	/* initialize DMA single data mode */
	dma_single_data_parameter.periph_addr = (uint32_t)(&ADC_SYNCDATA);
	dma_single_data_parameter.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
	dma_single_data_parameter.memory0_addr = (uint32_t)(adc_value);
	dma_single_data_parameter.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
	dma_single_data_parameter.periph_memory_width = DMA_PERIPH_WIDTH_16BIT;
	dma_single_data_parameter.circular_mode = DMA_CIRCULAR_MODE_ENABLE;
	dma_single_data_parameter.direction = DMA_PERIPH_TO_MEMORY;
	dma_single_data_parameter.number = 6;
	dma_single_data_parameter.priority = DMA_PRIORITY_HIGH;
	dma_single_data_mode_init(DMA1,DMA_CH0, &dma_single_data_parameter);
	dma_channel_subperipheral_select(DMA1, DMA_CH0, DMA_SUBPERI0);

	/* enable DMA channel */
	dma_channel_enable(DMA1, DMA_CH0);
}

/**
  * @brief  Configures the TIM1.
  * @param  psc, arr.
  * @retval None
  */
void adc_config(void)
{
	/* system clocks configuration */
	rcu_config();
	
	/* GPIO configuration */
	gpio_config();
	
	/* DMA configuration */
//	dma_config();
	
	/* reset ADC */
  adc_deinit();
	
	/* configure the ADC sync mode */
	adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT);
//	adc_sync_mode_config(ADC_ALL_ROUTINE_PARALLEL);
//	adc_sync_dma_config(ADC_SYNC_DMA_MODE0);
//	adc_sync_dma_request_after_last_enable();
	/* ADC contineous function disable */
	adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);
	/* ADC scan mode disable */
	adc_special_function_config(ADC0, ADC_SCAN_MODE, DISABLE);
	/* ADC data alignment config */
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
	/* ADC channel length config */
	adc_channel_length_config(ADC0, ADC_ROUTINE_CHANNEL, 1U);

	/* ADC routine channel config */
//	adc_routine_channel_config(ADC0, 0, ADC_CHANNEL_0, ADC_SAMPLETIME_15);
	/* ADC external trigger enable */
//	adc_external_trigger_source_config(ADC0, ADC_ROUTINE_CHANNEL, ADC_EXTTRIG_ROUTINE_T1_CH1);
//	adc_external_trigger_config(ADC0, ADC_ROUTINE_CHANNEL, EXTERNAL_TRIGGER_DISABLE);

	/* enable ADC interface */
	adc_enable(ADC0);
	/* wait for ADC stability */
	delay_1ms(1);
	/* ADC calibration and reset calibration */
	adc_calibration_enable(ADC0);
}

/*!
    \brief      ADC channel sample
    \param[in]  none
    \param[out] none
    \retval     none
*/
uint16_t adc_channel_sample(uint8_t channel)
{
	/* ADC routine channel config */
	adc_routine_channel_config(ADC0, 0U, channel, ADC_SAMPLETIME_15);
	/* ADC software trigger enable */
	adc_software_trigger_enable(ADC0, ADC_ROUTINE_CHANNEL);

	/* wait the end of conversion flag */
	while (!adc_flag_get(ADC0, ADC_FLAG_EOC));
	/* clear the end of conversion flag */
	adc_flag_clear(ADC0, ADC_FLAG_EOC);
	
	/* return regular channel sample value */
	return (adc_routine_data_read(ADC0));
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
