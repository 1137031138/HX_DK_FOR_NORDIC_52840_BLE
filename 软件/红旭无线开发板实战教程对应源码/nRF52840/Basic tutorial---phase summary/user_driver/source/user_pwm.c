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
/* ����һ��ʹ��TIMER1ʵ��PWM��ʵ�� */
APP_PWM_INSTANCE(PWM,1);
/* ���pwm��ռ�ձȣ�Ĭ��Ϊ�ٷ�֮5 */
uint8_t pwm_duty_cycle = 5;

/* 
=============
��������
=============
*/

/**
 * pwm��ʼ������,ͨ��Timer1����PWM����,Ĭ�ϵ�PWMռ�ձ�Ϊ�ٷ�֮5
 * @param[in]   color:ָ��LED����ɫ��������ο�user_common.hͷ�ļ�
 * @param[in]   duty :ָ��PWM��ռ�ձȣ���λΪ�ٷֱȣ�%��
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/12/30, ������Ӳ��PWM��Ӳ����ʱ������PWM�ĳ�ʼ������\n            
 *              Ver0.0.3:
                  Helon_Chan, 2018/12/31, ʹ��Ӳ��PWM,������RTC�Լ�Ӳ��PWM\n
 */
void user_pwm_init(uint32_t color,app_pwm_duty_t duty)
{
  ret_code_t err_code;
  led_color = color;
  /* ������PWM�������ǣ�KHz,�����PIN��BROAD_LED */
  app_pwm_config_t app_pwm_config = APP_PWM_DEFAULT_CONFIG_1CH(1000UL, led_color);
  /* ��ʼ�����PWM */
  err_code = app_pwm_init(&PWM, &app_pwm_config, NULL);
  NRF_LOG_INFO("app_pwm_init is %d\n", err_code);
  /* ʹ�����PWM */
  app_pwm_enable(&PWM);

  pwm_duty_cycle = duty;
  /* ����PWM��ռ�ձ�Ϊ5% */
  while (app_pwm_channel_duty_set(&PWM, 0, duty) == NRF_ERROR_BUSY)
    ;
}


/**
 * ����PWM��ռ�ձ�
 * @param[in]   duty:��Ҫ���õ�ռ�ձȣ���λΪ�ٷֱȣ�%��
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n           
*/
void user_set_pwm_duty_cycle(app_pwm_duty_t duty)
{
  /* ����PWM��ռ�ձ� */
  pwm_duty_cycle = duty;
  while (app_pwm_channel_duty_set(&PWM, 0, duty) == NRF_ERROR_BUSY);
}

/**
 * ȡ����ʼ��app_pwm
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n           
*/
void user_pwm_uninit(void)
{
  /* ȡ����ʼ��APP_PWM���� */
  app_pwm_uninit(&PWM);  
}