/**
* @file         user_application.h
* @brief        pwm��غ����������Լ��궨��
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/07/28, ��ʼ���汾\n
*/
#ifndef USER_APPLICATION_H
#define USER_APPLICATION_H

/* 
=============
ͷ�ļ�����
=============
*/
#include "user_log.h"
#include "user_pwm.h"
#include "user_timer.h"
#include "user_gpiote.h"
#include "user_ppi.h"
#include "nrf_gpio.h"
/* 
=============
�궨��
=============
*/



/*
=============
��������
=============
*/
/**
 * app��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/26, ��ʼ���汾\n
 */
 void user_app_init(void);
 
#endif