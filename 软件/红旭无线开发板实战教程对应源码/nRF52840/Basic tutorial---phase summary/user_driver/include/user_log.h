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
#define MAX_FORMAT_BUFFER_SIZE	(255)
#define DBG_ENABLE               1

/**
 * log��ӡ�����ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 */
 void log_init(void);


#endif  //USER_LOG_H