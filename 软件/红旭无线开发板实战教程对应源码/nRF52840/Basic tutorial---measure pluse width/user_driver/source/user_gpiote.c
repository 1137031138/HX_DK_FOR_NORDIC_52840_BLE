/**
* @file         user_gpiote.c
* @brief        gpiote����غ�������
* @details      ʹ��gpiote�����������ȵ���غ�������
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
#include "user_gpiote.h"
#include "user_log.h"
/* 
=============
��������
=============
*/
/**
 * gpiote��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 */
void user_gpiote_init(nrf_drv_gpiote_evt_handler_t evt_handler)
{
  nrfx_err_t error_code;
  nrf_drv_gpiote_in_config_t m_nrf_drv_gpiote_in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
  /* ��ʼ��gpiote */
  error_code = nrf_drv_gpiote_init();
  NRF_LOG_INFO("nrf_drv_gpiote_init is %d\n", error_code);

  /* gpiote�����ʼ�� */
  error_code = nrf_drv_gpiote_in_init(GPIOTE_IN_PIN,&m_nrf_drv_gpiote_in_config,evt_handler);
  NRF_LOG_INFO("nrf_drv_gpiote_in_init is %d\n", error_code);

  /* ʹ��gpiote�����¼� */
  nrf_drv_gpiote_in_event_enable(GPIOTE_IN_PIN,true);
}