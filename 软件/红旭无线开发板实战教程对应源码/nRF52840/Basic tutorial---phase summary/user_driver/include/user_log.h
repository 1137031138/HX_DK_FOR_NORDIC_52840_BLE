/**
* @file         user_log.h
* @brief        log�������������  
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/06/09, ��ʼ���汾\n
*/
#ifndef USER_LOG_H
#define USER_LOG_H

/* 
=============
ͷ�ļ�����
=============
*/
#include "nrf_drv_uart.h"
#include "app_error.h"
#include <stdio.h>
#include <stdarg.h>

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
 * uart��ʼ������
 * @param[in]   nrf_drv_uart:����ʵ��
 * @param[in]   nrf_uart_event_handler:uart�¼��ص�������
  * @param[in]   rx_buffer:uart��rx������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/11/28, ȫ�����ʹ�ùٷ���logģ�飬ֱ������
 */
void user_uart_init(nrf_drv_uart_t *nrf_drv_uart,
										nrf_uart_event_handler_t nrf_uart_event_handler,										
										uint8_t *rx_buffer);


#endif  //USER_LOG_H