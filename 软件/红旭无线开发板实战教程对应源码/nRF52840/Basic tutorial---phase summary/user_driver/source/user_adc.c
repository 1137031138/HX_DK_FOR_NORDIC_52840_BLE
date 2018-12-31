/**
* @file         user_adc.c
* @brief        adc��صĺ�������
* @details      �û����Ե�������ĺ�������adc����
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/11/10, ��ʼ���汾\n
*/

/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "user_adc.h"

/*
===========================
��������
=========================== 
*/

/**
 * ��ʼadc����
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/11, ��ʼ���汾\n
 */
void user_adc_sample_start(void)
{
  nrfx_err_t err_code;
  // while (nrf_drv_saadc_is_busy())
  //   ;
  err_code = nrf_drv_saadc_sample();
  NRF_LOG_INFO("nrf_drv_saadc_sample is %d\n", err_code);
}

/**
 * adc��ʼ������
 * @param[in]   nrf_drv_saadc_event_handler:adc�¼��ص�������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/10, ��ʼ���汾\n
 */
void user_adc_init(nrfx_saadc_event_handler_t nrf_drv_saadc_event_handler,
                   nrf_saadc_value_t *m_nrf_saadc_value)
{
  ret_code_t err_code;
  nrf_drv_saadc_config_t m_nrf_drv_saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
  nrf_saadc_channel_config_t m_nrf_saadc_channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_VDD);
  /* ʹ��Bustģʽ */
  m_nrf_saadc_channel_config.burst = NRF_SAADC_BURST_ENABLED;

  /* ���ó�Ҫ���Ե�AN��ΪVDD,���ڵ�0ͨ�� */
  err_code = nrf_drv_saadc_channel_init(0, &m_nrf_saadc_channel_config);
  NRF_LOG_INFO("nrf_drv_saadc_channel_init is %d\n", err_code);

  /* ע��adc���¼��ص������� */
  err_code = nrf_drv_saadc_init(&m_nrf_drv_saadc_config, nrf_drv_saadc_event_handler);
  NRF_LOG_INFO("nrf_drv_saadc_init is %d\n", err_code);

  /* ����һ�����������ڴ��adcֵ */
  err_code = nrf_drv_saadc_buffer_convert(m_nrf_saadc_value, 1); 
  NRF_LOG_INFO("nrf_drv_saadc_buffer_convert is %d\n", err_code);
}