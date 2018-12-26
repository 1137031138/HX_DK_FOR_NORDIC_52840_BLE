/**
* @file         user_ppi.c
* @brief        ʵ��ppi������صĺ�������
* @author       Helon_Chan
* @website      http://bbs.wireless-tech.cn/
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                    Helon_Chan, 2018/12/26, ��ʼ���汾\n
*/

/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "user_ppi.h"
/*
===========================
ȫ�ֱ���
=========================== 
*/
static nrf_ppi_channel_t gs_m_nrf_ppi_channel;
nrf_drv_timer_t hardware_timer0 = NRF_DRV_TIMER_INSTANCE(0);

/**
 * ��ʼ��gpiote
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
static void user_app_gpiote_init(void)
{
  nrfx_err_t err_code;
  nrf_drv_gpiote_out_config_t m_gpiote_out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
  /* ��ʼ��gpiote */
  err_code = nrf_drv_gpiote_init();
  NRF_LOG_INFO("nrf_drv_gpiote_init is %d\n", err_code);


  /* ����LED�ƶ�Ӧ��GPIO�ڱ�hardware timer0 compare event���ƣ���ÿ����EVENT����GPIO OUT TASKʱ��ȡ����ǰ��LED�� */
  err_code = nrf_drv_gpiote_out_init(LED_NUMBER,&m_gpiote_out_config);
  NRF_LOG_INFO("nrfx_gpiote_out_init is %d\n",err_code);

  /* ����gpiote��out task */
  nrf_drv_gpiote_out_task_disable(LED_NUMBER);
}

/**
 * ��ʼ��ppi
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */

static void user_app_ppi_init(void)
{
  nrfx_err_t err_code;
  nrf_ppi_channel_t m_nrf_ppi_channel1;
  uint32_t gpiote_evt_addr,gpiote_task_addr;
  uint32_t hardware_timer0_compare_evt_addr;
  /* ��ʼ��ppi */
  NRF_LOG_INFO("nrf_drv_ppi_init is %d\n", nrf_drv_ppi_init());

  /* ѡ��δʹ�õ�PPIͨ�� */
  err_code = nrf_drv_ppi_channel_alloc(&m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_alloc is %d\n", err_code);


  /* ��ȡevent��task�ĵ�ַ */
  gpiote_task_addr = nrf_drv_gpiote_out_task_addr_get(LED_NUMBER);
  hardware_timer0_compare_evt_addr = nrf_drv_timer_compare_event_address_get(&hardware_timer0,
                                                                             NRF_TIMER_CC_CHANNEL0);

  /* ��event��taskͨ��ѡ�е�ppi_channel�������� */
  err_code = nrf_drv_ppi_channel_assign(m_nrf_ppi_channel1,
                                        hardware_timer0_compare_evt_addr,
                                        gpiote_task_addr);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_assign is %d\n", err_code);


  /* ʹ��ѡ�е�PPI��ͨ�� */
  err_code = nrf_drv_ppi_channel_enable(m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_enable is %d\n", err_code);

}
/**
 * hardware timer0��event�ص�����,�ù��̲����ô˻ص�����
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */

static void user_nrf_timer_evt_handler(nrf_timer_event_t event_type, void *p_context)
{    
  switch (event_type)
  {
  case NRF_TIMER_EVENT_COMPARE0:
    
    break;            
  default:
    break;
  }
}

/**
 * ��ʼ��timer0,���ڶ�ʱ
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
static void user_app_timer0_init(void)
{
  nrfx_err_t err_code;
  uint32_t timer_ms_tick;
  /* ʹ��NRFX_TIMER_DEFAULT_CONFIG����hardware timer0ΪĬ�ϵ����ò��� */
  nrf_drv_timer_config_t m_hardware_timer0_config = NRF_DRV_TIMER_DEFAULT_CONFIG;

  /* ��ʼ��hardware timer0 */
  err_code = nrf_drv_timer_init(&hardware_timer0,
                                &m_hardware_timer0_config,
                                user_nrf_timer_evt_handler);
  NRF_LOG_INFO("nrf_drv_timer0_init is %d\n", err_code);
  /* 1.����hardware timer0��NRF_TIMER_CC_CHANNEL0ͨ��ÿһ�����event,������clear task 
     2.ÿһ��ͻص�һ���û��Զ���Ļص�������user_nrf_timer_evt_handler,��ǰfalse������
  */
  timer_ms_tick = nrf_drv_timer_ms_to_ticks(&hardware_timer0, 1000);
  NRF_LOG_INFO("nrf_drv_timer_ms_to_ticks is %d\n", timer_ms_tick);
  nrf_drv_timer_extended_compare(&hardware_timer0,
                                 NRF_TIMER_CC_CHANNEL0,
                                 timer_ms_tick,
                                 NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                 false);
  /* ����hardware timer0 */                                   
  nrf_drv_timer_disable(&hardware_timer0);
}

/**
 * ��ʼ��gpiote+timer0+ppi
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/26, ��ʼ���汾\n
 */

void user_gpiote_timer0_init(void)
{
  user_app_gpiote_init();
  user_app_timer0_init();    
  user_app_ppi_init();
}
