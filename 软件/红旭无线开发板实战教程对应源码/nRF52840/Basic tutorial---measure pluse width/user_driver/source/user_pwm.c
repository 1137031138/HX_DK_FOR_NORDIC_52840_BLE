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
/* =============
ȫ�ֱ�������
 =============*/
/* ����һ��Ӳ��PWM0��ʵ�� */
static nrf_drv_pwm_t gs_m_nrf_drv_pwm = NRF_DRV_PWM_INSTANCE(0);
/* ���岻ͬ��ռ�ձ�ֵ */
static nrf_pwm_values_common_t duty_values [] = 
{
  800,                        ///< 20%,����ָ���Ǹߵ�ƽռ�ٷ�֮20,������Դ�����
  600,                        ///< 40%
  400,                        ///< 60%    
  200,                        ///< 80%  
};

/* 
=============
��������
=============
*/

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
  /* ʹ��Ĭ�ϵ����ã�����PWM������Ϊ1K,PWM�����ΪBROAD_LED,����3·��ʹ�� */
  nrf_drv_pwm_config_t m_nrf_drv_pwm_config = NRF_DRV_PWM_DEFAULT_CONFIG;
//  m_nrf_drv_pwm_config.output_pins[0] = NRF_DRV_PWM_PIN_INVERTED;
  m_nrf_drv_pwm_config.output_pins[1] = NRF_DRV_PWM_PIN_NOT_USED;
  m_nrf_drv_pwm_config.output_pins[2] = NRF_DRV_PWM_PIN_NOT_USED;
  m_nrf_drv_pwm_config.output_pins[3] = NRF_DRV_PWM_PIN_NOT_USED;

  err_code = nrf_drv_pwm_init(&gs_m_nrf_drv_pwm, &m_nrf_drv_pwm_config, NULL);
  NRF_LOG_INFO("nrf_drv_pwm_init is %d\n", err_code);

  nrf_pwm_sequence_t const c_m_seq =
      {
          .values.p_common = duty_values,
          .length = NRF_PWM_VALUES_LENGTH(duty_values),
          .repeats = 0,
          .end_delay = 0};
  /* �ظ�3��duty_values��ָ����ռ�ձ�,��󱣳����һ��ռ�ձȵ�ֵ��100% */
  err_code = nrf_drv_pwm_simple_playback(&gs_m_nrf_drv_pwm, &c_m_seq, 3, 0);
  NRF_LOG_INFO("nrf_drv_pwm_simple_playback is %d\n", err_code);
}