/**
* @file         user_timer.h
* @brief        PPI+��ʱ��1����غ����������Լ���صĺ궨��
* @QQ Group     671139854
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/10/27, ��ʼ���汾\n
*/
#ifndef USER_TIMER_H
#define USER_TIMER_H


/* 
=============
ͷ�ļ�����
=============
*/
#include "nrf_drv_timer.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_gpiote.h"

/* 
=============
��������
=============
*/
/**
 * timer1��ʼ������
 * @param[in]   p_instance:��ʾ��ʱ����ID
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
void user_timer_init(nrfx_timer_t const * const  p_instance);


/**
 * �ص�Timer1
 * @param[in]   p_instance:��ʾ��ʱ����ID
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
void user_timer_stop(nrfx_timer_t const * const  p_instance);


#endif
