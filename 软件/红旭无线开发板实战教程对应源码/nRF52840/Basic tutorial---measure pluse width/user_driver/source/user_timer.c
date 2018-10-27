/**
* @file         user_timer.c
* @brief        ��ʱ��1����غ�������
* @details      ʹ�ö�ʱ�������������ȵ���غ�������
* @author       Helon_Chan
* @QQ Group     671139854
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/10/27, ��ʼ���汾\n
*/

/* 
=============
ȫ�ֱ�������
=============
*/

/* 
=============
ͷ�ļ�����
=============
*/

#include "user_timer.h"
#include "user_log.h"
/* 
=============
��������
=============
*/

/**
 * timer1��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
static void user_timer_event_dummy_handler(nrf_timer_event_t event_type, void *p_context)
{
  ///< do nothing!!!
}

/**
 * timer1��ʼ������
 * @param[in]   p_instance:��ʾ��ʱ����ID
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
void user_timer_init(nrfx_timer_t const * const  p_instance)
{
  nrfx_err_t error_code;
  /* Ĭ�ϵ�����ͨ��sdk_config.h������ */
  nrf_drv_timer_config_t m_nrf_drv_timer_config = NRF_DRV_TIMER_DEFAULT_CONFIG;
  error_code = nrf_drv_timer_init(p_instance,&m_nrf_drv_timer_config,user_timer_event_dummy_handler);
  NRF_LOG_INFO("nrf_drv_timer_init is %d\n",error_code);

  /* ��ʱTimer1��ʱ���Ϳ�ʼ������ÿ��ʱ��tick�ͼ�1 */
  nrf_drv_timer_enable(p_instance);
}

/**
 * �ص�Timer1
 * @param[in]   p_instance:��ʾ��ʱ����ID
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
void user_timer_stop(nrfx_timer_t const * const  p_instance)
{
  nrf_drv_timer_disable(p_instance);
}
