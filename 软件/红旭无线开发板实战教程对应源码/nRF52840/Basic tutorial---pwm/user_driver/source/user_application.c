/**
* @file         user_application.c
* @brief        ʵ���û��߼�������صĺ�������
* @details      �û������Լ�д����������Nordic����������ʵ���Զ���Ĺ���
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/07/28, ��ʼ���汾\n
*/

/* 
=============
ͷ�ļ�����
=============
*/

#include "user_application.h"

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
 void user_app_init(void)
 {
   user_log_init();
   user_pwm_init();
 }