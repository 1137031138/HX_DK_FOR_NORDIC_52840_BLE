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
 * adc�¼��ص�������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/10, ��ʼ���汾\n
 */
static void nrf_drv_saadc_event_handler(nrfx_saadc_evt_t const *p_event)
{
  ret_code_t err_code;
  switch (p_event->type)
  {
    /* ת����ɣ�����ж�·ADC�ɼ������ʱ��ʾ��·�ɼ���ɣ�
    ��ADCֵ���ж���·��Ҫ�����ٴΣ�����ֻ��һ·����ֻ��һ·��ֵ */
    case NRFX_SAADC_EVT_DONE:      
      char float_str[80];      
      err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, 1);
      NRF_LOG_INFO("nrf_drv_saadc_buffer_convert is %d\n", err_code);

      /* ����С�����4λ */
      sprintf(float_str, "VDD voltage is %.4f\n", (float)((p_event->data.done.p_buffer[0] * 3.6) / 4096));
      /* �����õ�VDD��ѹֵ */
      NRF_LOG_INFO("%s\n", float_str);
      break;
  }
}

/**
 * adc��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/10, ��ʼ���汾\n
 */
void user_adc_init(void)
{
  ret_code_t err_code;
  nrf_drv_saadc_config_t m_nrf_drv_saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
  nrf_saadc_channel_config_t m_nrf_saadc_channel_config = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_VDD);
  /* ʹ��Bustģʽ */
  m_nrf_saadc_channel_config.burst = NRF_SAADC_BURST_ENABLED;

  /* ���ó�Ҫ���Ե�AN��ΪVDD */
  err_code = nrf_drv_saadc_channel_init(&m_nrf_saadc_channel_config);
  NRF_LOG_INFO("nrf_drv_saadc_channel_init is %d\n",err_code);

  /* ע��adc���¼��ص������� */
  err_code = nrf_drv_saadc_init(&m_nrf_drv_saadc_config,nrf_drv_saadc_event_handler);
  NRF_LOG_INFO("nrf_drv_saadc_init is %d\n",err_code);
  
}