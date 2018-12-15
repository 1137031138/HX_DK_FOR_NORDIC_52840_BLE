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
#include "app_uart.h"

/* 
=============
�궨��
=============
*/
#define UART_RX_BUFFER         16               ///< ���ڽ��ջ�������С����λ�ֽ�
#define UART_TX_BUFFER         1024             ///< ���ڷ��ͻ�������С����λ�ֽڡ�ע��Ӧ��4�ֽڶ���
/* 
=============
��������
=============
*/

/**
 * uart��ʼ������ 
 * @param[in]   app_uart_event_handler:uart�¼��ص�������  
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/11/28, ȫ�����ʹ�ùٷ���logģ�飬ֱ������
*               Ver0.0.3:
                  Helon_Chan, 2018/12/15, ��Ϊʹ��driver��uart����ֶ���������ʷ���,ֱ��ʹ�ùٷ���app_uart
 */

void user_log_init(app_uart_event_handler_t app_uart_event_handler);

#endif  //USER_LOG_H