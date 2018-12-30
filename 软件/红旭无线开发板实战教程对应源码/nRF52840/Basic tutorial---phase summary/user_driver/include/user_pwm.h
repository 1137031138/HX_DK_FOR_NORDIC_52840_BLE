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
#include "low_power_pwm.h"
#include "user_log.h"

/* 
=============
�궨��
=============
*/

#define SOFTWARE_PWM            0                               ///< ʹ��Ӳ����ʱ������PWM����
#define HARDWARE_PWM            0                               ///< ʹ��Ӳ����PWM����PWM����
#define LOW_POWER_PWM           1                               ///< ʹ��RTC(32768Hz)����PWM����

#if HX_LOG_UART_ENABLED
#define NRF_LOG_INFO(...)
#endif

#define BROAD_LED               26
#define BROAD_LED_MASK          1<<BROAD_LED
/* 
=============
��������
=============
*/

/**
 * pwm��ʼ������,ͨ��Ӳ��Timer1����PWM���Σ�Ĭ�ϲ�ʹ��APP_PWM
 * @param[in]   p_instance:ָ��app_pwm_t��ʵ��ָ��
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
*               Ver0.0.2:
                  Helon_Chan, 2018/12/30, ������Ӳ��PWM��RTC��ʱ������PWM�ĳ�ʼ������\n            
 */

void user_pwm_init(void);


#endif  //USER_PWM_H