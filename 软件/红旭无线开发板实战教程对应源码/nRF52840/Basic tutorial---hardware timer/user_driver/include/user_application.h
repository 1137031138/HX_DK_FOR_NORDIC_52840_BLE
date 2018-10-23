/**
* @file         user_application.h
* @brief        pwm��غ����������Լ��궨��
* @author       Helon_Chan
* @website      http://bbs.wireless-tech.cn/
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                    Helon_Chan, 2018/09/08, ��ʼ���汾\n
*/
#ifndef USER_APPLICATION_H
#define USER_APPLICATION_H

/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "nrf_drv_ppi.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_gpio.h"
#include "nrfx_timer.h"
#include "drivers/nrfx_common.h"
/*
===========================
�궨��
=========================== 
*/

#define KEY_NUMBER          13                        ///< ����������ΪP0.13
#define LED_NUMBER          26                        ///< LED������ΪP0.26


/**
 * ��ʼ��ʹ�õ�������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/23, ��ʼ���汾\n
 */
void user_app_init(void);



#endif /* USER_APPLICATION_H */