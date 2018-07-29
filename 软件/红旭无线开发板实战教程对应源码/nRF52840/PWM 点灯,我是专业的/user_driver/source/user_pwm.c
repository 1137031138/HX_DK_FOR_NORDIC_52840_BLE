/**
* @file         user_pwm.c
* @brief        pwm��صĺ�������
* @details      �û�����ѡ��ʹ�����pwm����Ӳ��pwmȥ�����Լ�������
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/07/28, ��ʼ���汾\n
*/

/* =============
ͷ�ļ�����
 =============*/

#include "user_pwm.h"
#include "user_log.h"
#include "nrf_drv_clock.h"
/* =============
ȫ�ֱ�������
 =============*/

#if SOFTWARE_PWM
/* ����һ��ʹ��TIMER1ʵ��PWM��ʵ�� */
APP_PWM_INSTANCE(PWM,1);
#endif

#if HARDWARE_PWM
/* ����һ��Ӳ��PWM��ʵ�� */
static nrfx_pwm_t gs_m_nrfx_pwm = NRFX_PWM_INSTANCE(0);
/* ���岻ͬ��ռ�ձ�ֵ */
static nrf_pwm_values_common_t duty_values [] = 
{
  0,                          ///< 0%
  200,                        ///< 20%  
  400,                        ///< 40%
  600,                        ///< 60%    
  800,                        ///< 80%
  1000,                       ///< 100%
};
#endif

#if LOW_POWER_PWM
static low_power_pwm_t gs_m_low_power_pwm;
APP_TIMER_DEF(gs_m_low_power_pwm_app_timer_id);
#endif
/* =============
��������
 =============*/

/**
 * ��ʼ����Ƶʱ��
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/29, ��ʼ���汾\n
 */
static void lfclk_init(void)
{
    uint32_t err_code;
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}

/**
 * pwm��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 */

void user_pwm_init(void)
{
  ret_code_t err_code;
  #if SOFTWARE_PWM
    /* ������PWM�������ǣ�KHz,�����PIN��BROAD_LED */
    app_pwm_config_t app_pwm_config = APP_PWM_DEFAULT_CONFIG_1CH(1000UL, BROAD_LED);
    /* ��ʼ�����PWM */
    err_code = app_pwm_init(&PWM,&app_pwm_config,NULL);
    NRF_LOG_INFO("app_pwm_init is %d\n",err_code);
    /* ʹ�����PWM */
    app_pwm_enable(&PWM);
    /* ����PWM��ռ�ձ�Ϊ10% */
    while(app_pwm_channel_duty_set(&PWM,0,10) == NRF_ERROR_BUSY);
  #endif
  #if HARDWARE_PWM    
    nrfx_pwm_config_t nrfx_pwm_config = 
    {
      .output_pins = 
      {
        BROAD_LED,
        NRFX_PWM_PIN_NOT_USED,
        NRFX_PWM_PIN_NOT_USED,
        NRFX_PWM_PIN_NOT_USED,
      },
      .irq_priority = APP_IRQ_PRIORITY_LOW,
      .base_clock   = NRF_PWM_CLK_1MHz,
      .count_mode   = NRF_PWM_MODE_UP,
      .top_value    = 1000,                       ///< ��PWM������Ϊ1KHz
      .load_mode    = NRF_PWM_LOAD_COMMON,
      .step_mode    = NRF_PWM_STEP_AUTO
    };
    err_code = nrfx_pwm_init(&gs_m_nrfx_pwm,&nrfx_pwm_config,NULL);
    NRF_LOG_INFO("nrfx_pwm_init is %d\n",err_code);
     
    nrf_pwm_sequence_t const s_m_seq =
    {
      .values.p_common = duty_values,
      .length          = NRF_PWM_VALUES_LENGTH(duty_values),
      .repeats         = 0,
      .end_delay       = 0
    };
    /* �ظ�3��duty_values��ָ����ռ�ձ�,��󱣳����һ��ռ�ձȵ�ֵ��100% */
    nrfx_pwm_simple_playback(&gs_m_nrfx_pwm, &s_m_seq, 3, 0);
  #endif

  #if LOW_POWER_PWM
    lfclk_init();
    err_code = app_timer_init();
    NRF_LOG_INFO("app_timer_init is %d\n",err_code);
    low_power_pwm_config_t s_m_low_power_pwm_config = 
    {
      .active_high = false,
      .period      = UINT8_MAX,                         ///< ������255/32768,125Hz
      .p_port      = NRF_P1,
      .bit_mask    = BROAD_LED_MASK,
      .p_timer_id  = &gs_m_low_power_pwm_app_timer_id,
    };
    err_code = low_power_pwm_init((&gs_m_low_power_pwm), &s_m_low_power_pwm_config, NULL);    
    NRF_LOG_INFO("low_power_pwm_init is %d\n",err_code);

    err_code = low_power_pwm_duty_set(&gs_m_low_power_pwm, UINT8_MAX*0.5);                                                 
    NRF_LOG_INFO("low_power_pwm_duty_set is %d\n",err_code);

    err_code = low_power_pwm_start(&gs_m_low_power_pwm, BROAD_LED_MASK);
    NRF_LOG_INFO("low_power_pwm_start is %d\n",err_code);

  #endif

}