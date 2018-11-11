/**
* @file         user_adc.h
* @brief        adc��صĺ����������ߺ궨��
* @details      adc��صĺ����������ߺ궨��
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/11/10, ��ʼ���汾\n
*/
#ifndef USER_ADC_H
#define USER_ADC_H
/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "nrf_drv_saadc.h"
#include "user_log.h"
/*
===========================
��������
=========================== 
*/

/**
 * adc��ʼ������
 * @param[in]   nrf_drv_saadc_event_handler:adc�¼��ص�������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/10, ��ʼ���汾\n
 */
void user_adc_init(nrfx_saadc_event_handler_t nrf_drv_saadc_event_handler,
                   nrf_saadc_value_t *m_nrf_saadc_value);

/**
 * ��ʼadc����
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/11, ��ʼ���汾\n
 */
void user_adc_sample_start(void);

#endif
