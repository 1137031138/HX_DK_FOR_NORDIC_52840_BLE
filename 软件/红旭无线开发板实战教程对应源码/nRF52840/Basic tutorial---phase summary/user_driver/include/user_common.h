/**
* @file         user_common.h
* @brief        ������C�ļ��õ��Ĺ����ı������ߺ������ߺ�����ȵ�
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/12/30, ��ʼ���汾\n
*/
#ifndef USER_COMMON_H
#define USER_COMMON_H


/* 
=============
�궨��
=============
*/
#define COMMON_R_LED_NUMBER         26               ///< LED��Ӧ��GPIOΪP0.26
#define COMMON_G_LED_NUMBER         15               ///< LED��Ӧ��GPIOΪP1.15
#define COMMON_B_LED_NUMBER         13               ///< LED��Ӧ��GPIOΪP1.13
#define DEFAULT_BLINK_FREQUENCY     1000             ///< ��λms

/* 
=============
�ⲿ��������
=============
*/
extern uint8_t led_color;
extern uint8_t pwm_duty_cycle;
extern uint32_t blink_frequency;


#endif //USER_COMMON_H