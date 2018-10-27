/**
* @file         user_application.c
* @brief        ʵ���û��߼�������صĺ�������
* @details      �û������Լ�д����������Nordic����������ʵ���Զ���Ĺ���
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/07/28, ��ʼ���汾\n
*/

/* 
=============
ͷ�ļ�����
=============
*/

#include "user_application.h"

/* 
=============
ȫ�ֱ�������
=============
*/
/* ����һ��timer1��ID */
nrf_drv_timer_t m_nrf_drv_timer1_id = NRF_DRV_TIMER_INSTANCE(1);

/* 
=============
��������
=============
*/


/**
 * �����Ȳ��Գ�ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
static void user_app_gpiote_in_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  static uint32_t previous_timer_counts = 0;
  /* ͳ��20�μ��� */
  static uint32_t calculate_counts = 0;
  /* �����������,����´�ʱ��ʱ�� */
  if(nrf_gpio_pin_read(GPIOTE_IN_PIN))
  {
    previous_timer_counts = nrf_drv_timer_capture_get(&m_nrf_drv_timer1_id,
                                                      NRF_TIMER_CC_CHANNEL1);
  }
  /* ������½��أ����õ�ǰ��ʱ���ȥ������ʱ��ʱ�� */
  else
  {
    /* ��������Ϊ�ٶȹ���,ʹ�ô��ڴ�ӡ������쳣,�ù���ʹ��RTT��ӡ��� */
    NRF_LOG_INFO("pluse width is %d us\n",
                 nrf_drv_timer_capture_get(&m_nrf_drv_timer1_id, NRF_TIMER_CC_CHANNEL1) - previous_timer_counts);
  }
  if (calculate_counts > 30)
  {
    nrf_drv_gpiote_in_event_disable(GPIOTE_IN_PIN);
  }
  calculate_counts++;
}
/**
 * �����Ȳ��Գ�ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
static void user_app_measure_pluse_width_init(void)
{
  uint32_t gpio_in_evt_addr = nrf_drv_gpiote_in_event_addr_get(GPIOTE_IN_PIN);
  uint32_t nrf_drv_timer_capture_task_addr = nrf_drv_timer_capture_task_address_get(&m_nrf_drv_timer1_id,
                                                                                    NRF_TIMER_CC_CHANNEL1);
  user_gpiote_init(user_app_gpiote_in_evt_handler);    
  user_ppi_init(gpio_in_evt_addr,nrf_drv_timer_capture_task_addr);
  user_timer_init(&m_nrf_drv_timer1_id);
  user_pwm_init();
}

/**
 * app��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/26, ��ʼ���汾\n
 */
void user_app_init(void)
{
  user_log_init();
  user_app_measure_pluse_width_init();  
}