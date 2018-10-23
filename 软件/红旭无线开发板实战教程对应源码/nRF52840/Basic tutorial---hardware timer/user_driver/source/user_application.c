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
nrf_drv_timer_t hardware_timer0 = NRF_DRV_TIMER_INSTANCE(0);
nrf_drv_timer_t hardware_timer1 = NRF_DRV_TIMER_INSTANCE(1);
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

static void user_nrf_drv_gpiote_evt_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  NRF_LOG_INFO("user_nrfx_gpiote_evt_handler pin is %d,action is %d\n", pin, action);
}

/**
 * ��ʼ��gpio,�����ö�Ӧ��GPIOΪ���
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
static void user_app_gpio_init(void)
{
  nrf_gpio_cfg_output(NRF_GPIO_PIN_MAP(0,26));
}

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
  // ret_code_t err_code;
  // nrf_drv_gpiote_in_config_t m_gpiote_in_config = GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);

  // /* ����LED�ƶ�Ӧ��GPIO�ڵ�������ƽ�仯ʱ������ENVENT */
  // err_code = nrf_drv_gpiote_in_init(LED_NUMBER, &m_gpiote_in_config, user_nrf_drv_gpiote_evt_handler);
  // NRF_LOG_INFO("nrf_drv_gpiote_in_init is %d\n", err_code);

  // /* ʹ��gpiote��in event */
  // nrf_drv_gpiote_in_event_enable(LED_NUMBER, true);
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
  // nrf_ppi_channel_t m_nrf_ppi_channel;

  // /* ѡ��δʹ�õ�PPIͨ�� */
  // nrf_drv_ppi_channel_alloc(&m_nrf_ppi_channel);
  // /* ��event��taskͨ��ѡ�е�ppi_channel�������� */
  // nrf_drv_ppi_channel_assign(m_nrf_ppi_channel,
  //                            nrf_drv_gpiote_in_event_addr_get(LED_NUMBER),
  //                            nrf_drv_timer_capture_task_address_get(&hardware_timer1,NRF_TIMER_CC_CHANNEL1));
  // /* ʹ��ѡ�е�PPI��ͨ�� */
  // nrf_drv_ppi_channel_enable(m_nrf_ppi_channel);
}
/**
 * hardware timer��event�ص�����
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */

static void user_nrf_timer_evt_handler(nrf_timer_event_t event_type, void *p_context)
{  
  static uint32_t previous_timer_couts = 0;  
  switch (event_type)
  {
  case NRF_TIMER_EVENT_COMPARE0:
    /* ȡ����ǰ��LED_NUMBER�ĵ�ƽ */
    nrf_gpio_pin_toggle(LED_NUMBER);
    NRF_LOG_INFO("nrf_gpio_pin_toggle \n");
    break;
  case NRF_TIMER_TASK_CAPTURE1:
    NRF_LOG_INFO("current task - previous task = %d us\n",
                 nrf_drv_timer_capture_get(&hardware_timer1, NRF_TIMER_CC_CHANNEL1) - previous_timer_couts);
    previous_timer_couts = nrf_drv_timer_capture_get(&hardware_timer1, NRF_TIMER_CC_CHANNEL1);             
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
  /* ʹ��NRFX_TIMER_DEFAULT_CONFIG����hardware timerΪĬ�ϵ����ò��� */
  nrf_drv_timer_config_t m_hardware_timer0_config = NRF_DRV_TIMER_DEFAULT_CONFIG;

  /* ��ʼ��hardware timer */
  err_code = nrf_drv_timer_init(&hardware_timer0,
                                &m_hardware_timer0_config,
                                user_nrf_timer_evt_handler);
  NRF_LOG_INFO("nrf_drv_timer_init is %d\n", err_code);
  /* 1.����hardware timer0��NRF_TIMER_CC_CHANNEL0ͨ��ÿһ�����event,������clear task 
     2.ÿһ��ͻص�һ���û��Զ���Ļص�������user_nrf_timer_evt_handler
  */
  timer_ms_tick = nrf_drv_timer_ms_to_ticks(&hardware_timer0, 1000);
  NRF_LOG_INFO("nrf_drv_timer_ms_to_ticks is %d\n", timer_ms_tick);
  nrf_drv_timer_extended_compare(&hardware_timer0,
                                 NRF_TIMER_CC_CHANNEL0,
                                 timer_ms_tick,
                                 NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                 true);
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
  /* ����hardware timer1�ĳ���Ϊ32bit�ļ����� */
  nrf_drv_timer_config_t m_hardware_timer1_config = NRF_DRV_TIMER_DEFAULT_CONFIG;
  m_hardware_timer1_config.mode = NRF_TIMER_MODE_COUNTER;
  m_hardware_timer1_config.bit_width = NRF_TIMER_BIT_WIDTH_32;
  /* ��ʼ��hardware timer1 */
  nrf_drv_timer_init(&hardware_timer1, &m_hardware_timer1_config, user_nrf_timer_evt_handler);
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
  user_app_gpio_init();
  // user_app_gpiote_init();
  user_app_timer0_init();
  // user_app_ppi_init();
}