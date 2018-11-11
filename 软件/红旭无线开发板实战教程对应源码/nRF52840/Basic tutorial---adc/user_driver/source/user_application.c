/**
* @file         user_application.c
* @brief        ʵ���û��߼�������صĺ�������
* @details      �û������Լ�д����������Nordic����������ʵ���Զ���Ĺ���
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/08/19, ��ʼ���汾\n
*/

/*
===========================
ͷ�ļ�����
=========================== 
*/

#include "user_application.h"

/* ���ADC��ֵ�Ļ��� */
static nrf_saadc_value_t m_buffer_pool[1]; 
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
                  Helon_Chan, 2018/11/11, ��ʼ���汾\n
 */
static void user_saadc_event_handler(nrfx_saadc_evt_t const *p_event)
{
  ret_code_t err_code;
 char float_str[80]={0};   
  float adc_value;

  switch (p_event->type)
  {
    /* ת����ɣ�����ж�·ADC�ɼ������ʱ��ʾ��·�ɼ���ɣ�
        ��ADCֵ���ж���·��Ҫ�����ٴΣ�����ֻ��һ·����ֻ��һ·��ֵ */
    case NRF_DRV_SAADC_EVT_DONE:
      /* ֻ��ת��һ��ͨ�������������4��ͨ���������4���Դ����� */
      err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, 1);
      NRF_LOG_INFO("nrf_drv_saadc_buffer_convert is %d\n", err_code);

      adc_value = p_event->data.done.p_buffer[0] * 3.6 / 16384;     

      /* ������Nordic�Դ��Ĵ�ӡ������������ֻ����С�������λ��
         ���ﲻʹ�ã�����������ʹ�û����˽� */
      // NRF_LOG_INFO("adc_value is " NRF_LOG_FLOAT_MARKER " voltage \n",
//                   NRF_LOG_FLOAT(adc_value));

      /* ����С�����4λ,���ﻹ��Ҫ�ڹ�����Ŀ��ʹ��float,�������sprintf�����ò��� */
      sprintf(float_str, "VDD voltage is %.4f\n", adc_value);
      /* �����õ�VDD��ѹֵ */
      NRF_LOG_INFO("%s\n", float_str);
      break;
    default:
      break;
  }
}

/**
 * �������������������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
static void user_multi_click_handler(uint8_t button_no, uint8_t *click_counts)
{
  switch(button_no)
  {
    case BUTTON1:
      NRF_LOG_INFO("click counts is %d\n",*click_counts);
      *click_counts = 0;
      /* ÿ���а�������������һ��ADC���� */
      user_adc_sample_start();
      break;
    default:
      break;
  }
}

/**
 * ��������������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
static void user_long_pressed_handler(uint8_t button_no)
{
  switch(button_no)
  {
    case BUTTON1:
      NRF_LOG_INFO("gpio%d long pressed\n",button_no);      
      break;
    default:
      break;
  }
}
/**
 * �û�Ӧ�ó�ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
void user_application_init(void)
{
  /* log������ʼ��  */
  log_init();
  user_button_timer_init();
  user_multi_click_init(user_multi_click_handler,user_long_pressed_handler,BUTTON_COUNTS);
  user_adc_init(user_saadc_event_handler,m_buffer_pool);  
}