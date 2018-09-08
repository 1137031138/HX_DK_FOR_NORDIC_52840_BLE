/**
* @file         user_application.c
* @brief        ʵ���û��߼�������صĺ�������
* @details      �û������Լ�д����������Nordic����������ʵ���Զ���Ĺ���
* @author       Helon_Chan
* @website      http://bbs.wireless-tech.cn/
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                    Helon_Chan, 2018/09/08, ��ʼ���汾\n
*/

/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "user_application.h"
#include "user_log.h"
/*
===========================
�궨��
=========================== 
*/

/**
 * ��in event�ɸߵ�ƽ��͵�ƽʱ,�˻ص������Ӧ
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/09/08, ��ʼ���汾\n
 */

static void user_nrfx_gpiote_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  NRF_LOG_INFO("user_nrfx_gpiote_evt_handler pin is %d,action is %d\n",pin,action);
}


/**
 * ��ʼ��gpiote��ppi
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/09/08, ��ʼ���汾\n
 */

void user_app_gpiote_ppi_init(void)
{
  ret_code_t err_code;  
  nrf_ppi_channel_t m_nrf_ppi_channel;
  nrfx_gpiote_out_config_t m_gpiote_out_config = NRFX_GPIOTE_CONFIG_OUT_TASK_TOGGLE(NRF_GPIOTE_INITIAL_VALUE_HIGH);
  nrfx_gpiote_in_config_t m_gpiote_in_config = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(true);

  uint32_t nrfx_gpiote_out_task_addr;
  uint32_t nrfx_gpiote_in_event_addr;
  /* ��ʼ��gpiote */  
  err_code = nrfx_gpiote_init();    
  NRF_LOG_INFO("nrfx_gpiote_init is %d\n",err_code);
  /* ��ʼ��ppi */
  err_code = nrf_drv_ppi_init();
  NRF_LOG_INFO("nrf_drv_ppi_init is %d\n",err_code);

  /* ����LED�ƶ�Ӧ��GPIO�ڱ�GPIO TASK���ƣ���ÿ����EVENT����TASKʱ��ȡ����ǰ��LED�� */
  err_code = nrfx_gpiote_out_init(LED_NUMBER,&m_gpiote_out_config);
  NRF_LOG_INFO("nrfx_gpiote_out_init is %d\n",err_code);

  /* ���ð�����Ӧ��GPIO�ڵ��ɸߵ�ƽ��͵�ƽʱ������ENVENT */
  err_code = nrfx_gpiote_in_init(KEY_NUMBER,&m_gpiote_in_config,user_nrfx_gpiote_evt_handler);
  NRF_LOG_INFO("nrfx_gpiote_in_init is %d\n",err_code);

  /* ��ȡevent��task�ĵ�ַ */
  nrfx_gpiote_out_task_addr = nrfx_gpiote_out_task_addr_get(LED_NUMBER);
  nrfx_gpiote_in_event_addr = nrfx_gpiote_in_event_addr_get(KEY_NUMBER);

  /* ѡ��δʹ�õ�PPIͨ�� */
  nrfx_ppi_channel_alloc(&m_nrf_ppi_channel);
  /* ��event��taskͨ��ppi_channel0�������� */
  nrfx_ppi_channel_assign(m_nrf_ppi_channel,nrfx_gpiote_in_event_addr,nrfx_gpiote_out_task_addr);
  /* ʹ��ѡ�е�PPI��ͨ�� */
  nrfx_ppi_channel_enable(m_nrf_ppi_channel);
  /* ʹ��gpiote��out task */
  nrfx_gpiote_out_task_enable(LED_NUMBER);
  /* ʹ��gpiote��in event */
  nrfx_gpiote_in_event_enable(KEY_NUMBER,true);
}