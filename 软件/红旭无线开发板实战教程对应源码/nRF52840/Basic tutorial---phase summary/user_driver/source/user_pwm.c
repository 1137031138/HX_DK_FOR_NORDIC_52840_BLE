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

/* 
=============
ͷ�ļ�����
=============
*/
#include "user_pwm.h"

/* 
=============
ȫ�ֱ�������
=============
*/
APP_TIMER_DEF(gs_m_low_power_pwm_app_timer_id);
low_power_pwm_t gs_m_low_power_pwm;
low_power_pwm_config_t s_m_low_power_pwm_config =
    {
        .active_high = false,
        .period = UINT8_MAX,                              ///< ������255/32768,125Hz
        .p_port = NRF_P0,                                 ///< �����Ҫ�����PWM����P1����˴�Ҫ���NRF_P1
        .bit_mask = BROAD_LED_MASK,
        .p_timer_id = &gs_m_low_power_pwm_app_timer_id,
};

/* 
=============
��������
=============
*/

/**
 * pwm��ʼ������,ͨ��32.768Khz����PWM���Σ�Ĭ�ϲ�ʹ��APP_PWM
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
*               Ver0.0.2:
                  Helon_Chan, 2018/12/30, ������Ӳ��PWM��Ӳ����ʱ������PWM�ĳ�ʼ������\n            
 */

void user_pwm_init(void)
{
  ret_code_t err_code;
  err_code = low_power_pwm_init((&gs_m_low_power_pwm), &s_m_low_power_pwm_config, NULL);
  NRF_LOG_INFO("low_power_pwm_init is %d\n", err_code);
}