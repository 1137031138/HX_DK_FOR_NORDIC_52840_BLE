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

/* =============
ͷ�ļ�����
 =============*/
#include "app_pwm.h"
#include "nrfx_pwm.h"
#include "low_power_pwm.h"
#include "user_log.h"
#include "nrf_drv_clock.h"
#include "nrf52840.h"
/* =============
�궨��
 =============*/

#define SOFTWARE_PWM            0                               ///< ʹ��Ӳ����ʱ������PWM����
#define HARDWARE_PWM            0                               ///< ʹ��Ӳ����PWM����PWM����
#define LOW_POWER_PWM           1                               ///< ʹ��RTC(32768Hz)����PWM����



#define BROAD_LED               26
#define BROAD_LED_MASK          1<<26
/* =============
��������
 =============*/


/**
 * pwm��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 */

void user_pwm_init(void);


#endif  //USER_PWM_H