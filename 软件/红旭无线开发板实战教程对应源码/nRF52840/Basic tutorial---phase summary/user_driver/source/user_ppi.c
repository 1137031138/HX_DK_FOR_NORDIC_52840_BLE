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
nrf_drv_timer_t g_m_hardware_timer0 = NRF_DRV_TIMER_INSTANCE(0);
/* �����˸��Ƶ�ʣ�Ĭ��Ϊ1000ms */
uint32_t blink_frequency = DEFAULT_BLINK_FREQUENCY;
/*
===========================
��������
=========================== 
*/

/**
 * hardware timer0��event�ص�����,�ù��̲����ô˻ص�����
 * @param[in]   event_type:�����ûص����¼�����
 * @param[in]   p_context��ָ�򴥷��ûص�ʱ��Я��������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */

static void user_nrf_timer_evt_handler(nrf_timer_event_t event_type, void *p_context)
{    
  /* �ûص�����ʹ�ã�����Ϊ��صĳ�ʼ��������Ҫר��ָ��һ���ص������� */
}

/**
 * ��ʼ��gpiote+timer0+ppi,����LED�˵�֮�Ӳ˵�PPI
 * @param[in]   color             :ѡ��LED����ɫ,����ο�user_common.h��ͷ��
 * @param[in]   blink_interval_ms :ѡ��LED����˸��Ƶ�ʣ���λΪms
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/26, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/12/31, ���ٽ������ܵĺ����ֿ������ˣ�ֱ�Ӽ����ڸú���\n              
 */

void user_gpiote_timer0_ppi_init(uint8_t color, uint32_t blink_interval_ms)
{
  nrf_ppi_channel_t gs_m_nrf_ppi_channel;  
  nrf_drv_gpiote_out_config_t g_m_gpiote_out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);

  nrf_ppi_channel_t g_m_nrf_ppi_channel1;
  uint32_t g_gpiote_evt_addr, g_gpiote_task_addr;
  uint32_t g_hardware_timer0_compare_evt_addr;

  nrfx_err_t err_code;

  led_color = color;
  blink_frequency = blink_interval_ms;
  /**********************************GPIOTE��ʼ��**********************************/  
  /* ��ʼ��gpiote */
  if (!nrf_drv_gpiote_is_init())
    err_code = nrf_drv_gpiote_init();
  NRF_LOG_INFO("nrf_drv_gpiote_init is %d\n", err_code);

  /* ����LED�ƶ�Ӧ��GPIO�ڱ�hardware timer0 compare event���ƣ���ÿ����EVENT����GPIO OUT TASKʱ��ȡ����ǰ��LED�� */
  err_code = nrf_drv_gpiote_out_init(color,&g_m_gpiote_out_config);
  NRF_LOG_INFO("nrfx_gpiote_out_init is %d\n",err_code);

  /**********************************Ӳ����ʱ��0��ʼ��**********************************/
  uint32_t timer_ms_tick;
  /* ʹ��NRFX_TIMER_DEFAULT_CONFIG����hardware timer0ΪĬ�ϵ����ò��� */
  nrf_drv_timer_config_t m_hardware_timer0_config = NRF_DRV_TIMER_DEFAULT_CONFIG;

  /* ��ʼ��hardware timer0 */
  err_code = nrf_drv_timer_init(&g_m_hardware_timer0,
                                &m_hardware_timer0_config,
                                user_nrf_timer_evt_handler);
  NRF_LOG_INFO("nrf_drv_timer0_init is %d\n", err_code);
  /* 1.����hardware timer0��NRF_TIMER_CC_CHANNEL0ͨ��ÿһ�����event,������clear task 
     2.ÿһ��ͻص�һ���û��Զ���Ļص�������user_nrf_timer_evt_handler,��ǰfalse������
  */
  timer_ms_tick = nrf_drv_timer_ms_to_ticks(&g_m_hardware_timer0, blink_interval_ms);
  NRF_LOG_INFO("nrf_drv_timer_ms_to_ticks is %d\n", timer_ms_tick);
  nrf_drv_timer_extended_compare(&g_m_hardware_timer0,
                                 NRF_TIMER_CC_CHANNEL0,
                                 timer_ms_tick,
                                 NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                 false);

  /**********************************ppi��ʼ��**********************************/
  /* ��ʼ��ppi */
  NRF_LOG_INFO("nrf_drv_ppi_init is %d\n", nrf_drv_ppi_init());

  /* ѡ��δʹ�õ�PPIͨ�� */
  err_code = nrf_drv_ppi_channel_alloc(&g_m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_alloc is %d\n", err_code);

  /* ��ȡevent��task�ĵ�ַ */
  g_gpiote_task_addr = nrf_drv_gpiote_out_task_addr_get(color);
  g_hardware_timer0_compare_evt_addr = nrf_drv_timer_compare_event_address_get(&g_m_hardware_timer0,
                                                                             NRF_TIMER_CC_CHANNEL0);
  /* ��event��taskͨ��ѡ�е�ppi_channel�������� */
  err_code = nrf_drv_ppi_channel_assign(g_m_nrf_ppi_channel1,
                                        g_hardware_timer0_compare_evt_addr,
                                        g_gpiote_task_addr);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_assign is %d\n", err_code);

  /* ʹ��ѡ�е�PPI��ͨ�� */
  err_code = nrf_drv_ppi_channel_enable(g_m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_enable is %d\n", err_code);

  /* ʹ��hardware timer0 */
  nrf_drv_timer_enable(&g_m_hardware_timer0);
  /* ʹ��gpiote��out task */
  nrf_drv_gpiote_out_task_enable(color);
}

/**
 * ȡ����ʼ��gpiote+timer0+ppi
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n          
 */

void user_gpiote_timer0_ppi_uninit(void)
{
  /**********************************ȡ��GPIOTE��ʼ��**********************************/
  nrfx_err_t err_code;

  /* ȡ����ʼ��gpiote */
  if (nrf_drv_gpiote_is_init())
  {
    nrf_drv_gpiote_uninit();    
  }

  /**********************************ȡ��Ӳ����ʱ��0��ʼ��**********************************/
  /* ȡ����ʼ��hardware timer0 */
  nrf_drv_timer_uninit(&g_m_hardware_timer0);

  /**********************************ȡ��ppi��ʼ��**********************************/
  /* ȡ����ʼ��ppi */
  nrf_drv_ppi_uninit();
}