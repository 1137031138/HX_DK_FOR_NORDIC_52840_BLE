/**
* @file         user_gpiote.h
* @brief        gpiote����غ�������
* @details      ʹ��gpiote�����������ȵ���غ��������Լ���صĺ궨��
* @author       Helon_Chan
* @QQ Group     671139854
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/10/27, ��ʼ���汾\n
*/

#ifndef USER_GPIOTE_H
#define USER_GPIOTE_H

/* 
=============
ͷ�ļ�����
=============
*/

#include "nrf_drv_gpiote.h"

/* 
=============
�궨��
=============
*/
#define GPIOTE_IN_PIN         31        ///<���PIN�����ڽ���PWM�����룬�Ӷ�����GPIO��IN_EVENT

/* 
=============
��������
=============
*/

/**
 * gpiote��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/07/28, ��ʼ���汾\n
 */
void user_gpiote_init(nrf_drv_gpiote_evt_handler_t evt_handler);

#endif