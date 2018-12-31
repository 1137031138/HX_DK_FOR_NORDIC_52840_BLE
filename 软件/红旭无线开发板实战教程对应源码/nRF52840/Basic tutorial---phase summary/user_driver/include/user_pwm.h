/**
* @file         user_pwm.h
* @brief        pwm��غ����������Լ��궨��
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/07/28, ��ʼ���汾\n
*/
#ifndef USER_PWM_H
#define USER_PWM_H

/* 
=============
ͷ�ļ�����
=============
*/
#include "app_pwm.h"
#include "user_log.h"
#include "nrf_drv_clock.h"
#include "user_common.h"
/* 
=============
�궨��
=============
*/
#if HX_LOG_UART_ENABLED
#define NRF_LOG_INFO(...)
#endif

/* 
=============
��������
=============
*/

/**
 * pwm��ʼ������,ͨ��Timer1����PWM����,Ĭ�ϵ�PWMռ�ձ�Ϊ�ٷ�֮5
 * @param[in]   color:ָ��LED����ɫ��������ο�user_common.hͷ�ļ�
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/12/30, ������Ӳ��PWM��Ӳ����ʱ������PWM�ĳ�ʼ������\n            
 *              Ver0.0.3:
                  Helon_Chan, 2018/12/31, ʹ��Ӳ��PWM,������RTC�Լ�Ӳ��PWM\n
 */
void user_pwm_init(uint32_t color,app_pwm_duty_t duty);

/**
 * ȡ����ʼ��app_pwm
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n           
*/
void user_pwm_uninit(void);

/**
 * ����PWM��ռ�ձ�
 * @param[in]   duty:��Ҫ���õ�ռ�ձȣ���λΪ�ٷֱȣ�%��
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n           
*/
void user_set_pwm_duty_cycle(app_pwm_duty_t duty);

#endif  //USER_PWM_H