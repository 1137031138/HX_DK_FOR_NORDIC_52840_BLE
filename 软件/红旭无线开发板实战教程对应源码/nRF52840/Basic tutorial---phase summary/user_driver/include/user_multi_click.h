/**
* @file         user_multi_click.h
* @brief        ������صĺ��������Լ��궨��
* @details      ������صĺ��������Լ�һЩ�ṹ���������
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                    Helon_Chan, 2018/08/19, ��ʼ���汾\n
*/
#ifndef USER_MULTI_CLICK_H
#define USER_MULTI_CLICK_H

/*
===========================
ͷ�ļ�����
=========================== 
*/
#include "app_button.h"
#include "sdk_common.h"
#include "app_timer.h"
#include "user_log.h"
#include "nrf_drv_clock.h"
/*
===========================
�궨��
=========================== 
*/
#define BUTTON_COUNTS               1                           ///< ��������
#define BUTTON1                     13                          ///< ������Ӧ��GPIO��
#define TIMER_FOR_LONG_PRESSED      5000                        ///< ������ʱ��,��λΪms

#if HX_LOG_UART_ENABLED
#define NRF_LOG_INFO(...)
#endif
/*
===========================
��������
=========================== 
*/
typedef void (*user_multi_click_handler_t)(uint8_t button_no,uint8_t *click_counts);

typedef void (*user_long_pressed_handler_t)(uint8_t button_no);

/*
===========================
�ṹ�����
=========================== 
*/
typedef struct
{
  uint8_t is_long_press : 1;
  uint8_t click_counts;
  app_button_cfg_t app_button_cfg[BUTTON_COUNTS];
  user_multi_click_handler_t user_multi_click_handler;
  user_long_pressed_handler_t user_long_pressed_handler;
} user_multi_click_t;

/*
===========================
��������
=========================== 
*/


/** 
* ��䰴���ĳ����������Լ�����Ĵ�����
* @param[in]   multi_click_handler    ����䵥��������Ĵ�����
* @param[in]   long_pressed_handler   ����䳤��������
* @param[in]   button_counts          ����������
* @retval      NRF_SUCCESS            ����ʾ��ʼ���ɹ�������ֵ���ʼ��ʧ��
* @note        ��ʼ������֮ǰ�����ȳ�ʼ��app_timerʱ��,��Ϊ�õ���������ʱ 
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n 
*/

ret_code_t user_multi_click_init(user_multi_click_handler_t multi_click_handler,user_long_pressed_handler_t long_pressed_handler,uint8_t button_counts);

/** 
* ������ʱ���õ���ʱ�ӳ�ʼ����һ��Ҫuser_multi_click_init֮ǰ���øú��������򰴼�������������
* @param[in]   null
* @retval      NRF_SUCCESS����ʾ��ʼ���ɹ�������ֵ���ʼ��ʧ��
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/26, ��ʼ���汾\n 
*/
ret_code_t user_button_timer_init(void);

#endif /* USER_MULTI_CLICK_H */