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
#include "user_log.h"
#include "user_application.h"

/*
===========================
ȫ�ֱ���
=========================== 
*/
/* ����timer0��timer1��id */
nrf_drv_timer_t hardware_timer0 = NRF_DRV_TIMER_INSTANCE(0);
nrf_drv_timer_t hardware_timer1 = NRF_DRV_TIMER_INSTANCE(1);



/*
===========================
��������
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

static void user_nrf_drv_gpiote_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  NRF_LOG_INFO("user_nrf_drv_gpiote_evt_handler�� pin is %d,action is %d\n", pin, action);
  NRF_LOG_INFO("Number of button presses is %d\n",
               nrf_drv_timer_capture(&hardware_timer1, NRF_TIMER_CC_CHANNEL1));
}

/**
 * ��ʼ��gpio,�����ö�Ӧ��GPIOΪ���,�ù���δʹ��
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
// static void user_app_gpio_init(void)
// {
//   nrf_gpio_cfg_output(LED_NUMBER);
// }

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
  nrf_drv_gpiote_in_config_t m_gpiote_in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
  nrf_drv_gpiote_out_config_t m_gpiote_out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(true);
  /* ��ʼ��gpiote */
  err_code = nrf_drv_gpiote_init();
  NRF_LOG_INFO("nrf_drv_gpiote_init is %d\n", err_code);

  /* ���ð�����Ӧ��GPIO���ɸߵ�ƽ��͵�ƽʱ������ENVENT */
  err_code = nrf_drv_gpiote_in_init(KEY_NUMBER,
                                    &m_gpiote_in_config,
                                    user_nrf_drv_gpiote_evt_handler);
  NRF_LOG_INFO("nrf_drv_gpiote_in_init is %d\n", err_code);

  /* ����LED�ƶ�Ӧ��GPIO�ڱ�hardware timer0 compare event���ƣ���ÿ����EVENT����GPIO OUT TASKʱ��ȡ����ǰ��LED�� */
  err_code = nrf_drv_gpiote_out_init(LED_NUMBER,&m_gpiote_out_config);
  NRF_LOG_INFO("nrfx_gpiote_out_init is %d\n",err_code);

  /* ʹ��gpiote��in event,������user_nrf_drv_gpiote_evt_handler�ص����� */
  nrf_drv_gpiote_in_event_enable(KEY_NUMBER, true);
  /* ʹ��gpiote��out task */
  nrf_drv_gpiote_out_task_enable(LED_NUMBER);
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
  nrf_ppi_channel_t m_nrf_ppi_channel1,m_nrf_ppi_channel2;
  uint32_t gpiote_evt_addr,gpiote_task_addr;
  uint32_t hardware_timer1_capture_task_addr,hardware_timer0_compare_evt_addr;
  /* ��ʼ��ppi */
  NRF_LOG_INFO("nrf_drv_ppi_init is %d\n", nrf_drv_ppi_init());

  /* ѡ��δʹ�õ�PPIͨ�� */
  err_code = nrf_drv_ppi_channel_alloc(&m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_alloc is %d\n", err_code);

  /* ѡ��δʹ�õ�PPIͨ�� */
  err_code = nrf_drv_ppi_channel_alloc(&m_nrf_ppi_channel2);
  NRF_LOG_INFO("nrf_drv_ppi_channel2_alloc is %d\n", err_code);

  /* ��ȡevent��task�ĵ�ַ */
  gpiote_task_addr = nrf_drv_gpiote_out_task_addr_get(LED_NUMBER);
  hardware_timer0_compare_evt_addr = nrf_drv_timer_compare_event_address_get(&hardware_timer0,
                                                                             NRF_TIMER_CC_CHANNEL0);
  gpiote_evt_addr = nrf_drv_gpiote_in_event_addr_get(KEY_NUMBER);
  hardware_timer1_capture_task_addr = nrf_drv_timer_task_address_get(&hardware_timer1,
                                                                     NRF_TIMER_TASK_COUNT);
  /* ��event��taskͨ��ѡ�е�ppi_channel�������� */
  err_code = nrf_drv_ppi_channel_assign(m_nrf_ppi_channel1,
                                        hardware_timer0_compare_evt_addr,
                                        gpiote_task_addr);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_assign is %d\n", err_code);

  err_code = nrf_drv_ppi_channel_assign(m_nrf_ppi_channel2,
                                        gpiote_evt_addr,
                                        hardware_timer1_capture_task_addr);
  NRF_LOG_INFO("nrf_drv_ppi_channel2_assign is %d\n", err_code);

  /* ʹ��ѡ�е�PPI��ͨ�� */
  err_code = nrf_drv_ppi_channel_enable(m_nrf_ppi_channel1);
  NRF_LOG_INFO("nrf_drv_ppi_channel1_enable is %d\n", err_code);

  err_code = nrf_drv_ppi_channel_enable(m_nrf_ppi_channel2);
  NRF_LOG_INFO("nrf_drv_ppi_channel2_enable is %d\n", err_code);
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
    /* ȡ����ǰ��LED_NUMBER�ĵ�ƽ */
    nrf_gpio_pin_toggle(LED_NUMBER);       
    NRF_LOG_INFO("nrf_gpio_pin_toggle \n");
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
  /* ʹ��hardware timer0 */                                 
  nrf_drv_timer_enable(&hardware_timer0);
}

/**
 * ��ʼ��timer1,���ڼ���
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
static void user_app_timer1_init(void)
{
  nrfx_err_t err_code;

  /* ����hardware timer1�ĳ���Ϊ32bit�ļ����� */
  nrf_drv_timer_config_t m_hardware_timer1_config = NRF_DRV_TIMER_DEFAULT_CONFIG;
  m_hardware_timer1_config.mode = NRF_TIMER_MODE_COUNTER;
  m_hardware_timer1_config.bit_width = NRF_TIMER_BIT_WIDTH_32;

  /* ��ʼ��hardware timer1 */
  err_code = nrf_drv_timer_init(&hardware_timer1,
                                &m_hardware_timer1_config,
                                user_nrf_timer_evt_handler);
  NRF_LOG_INFO("nrf_drv_timer1_init is %d\n", err_code);
  
  /* ʹ��hardware timer1*/
  nrf_drv_timer_enable(&hardware_timer1);
}

/**
 * ��ʼ��ʹ�õ�������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
void user_app_init(void)
{  
  user_app_gpiote_init();
  user_app_timer0_init();
  user_app_timer1_init();
  user_app_ppi_init();
}