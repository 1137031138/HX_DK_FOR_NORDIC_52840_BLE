/**
* @file         user_log.c
* @brief        log��صĺ�������
* @details      �û�����ѡ��ʹ��ͨ��UART��ӡlog��Ϣ����RTT��ӡlog��Ϣ
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/06/09, ��ʼ���汾\n
*/
/* =============
ͷ�ļ�����
 =============*/
#include "user_log.h"

/**
 * log��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 */
 void log_init(void)
 {
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
    NRF_LOG_DEFAULT_BACKENDS_INIT();
 }