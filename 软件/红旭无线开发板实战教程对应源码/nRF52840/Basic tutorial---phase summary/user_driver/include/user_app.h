/**
* @file         user_app.h
* @brief        Ӧ�ò㺯�����������  
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/12/02, ��ʼ���汾\n
*/
#ifndef USER_APP_H
#define USER_APP_H

/* 
=============
ͷ�ļ�����
=============
*/
#include "user_log.h"

/* 
=============
��������
=============
*/
#if HX_LOG_UART_ENABLED
#define HX_PRINTF(format, ...) user_customer_printf(format, ##__VA_ARGS__)
#else
#define HX_PRINTF(...)
#endif

/* 
=============
�ṹ������
=============
*/
/* led�����Ӳ˵��ṹ�� */
typedef struct
{
  uint8_t ppi_secondary_submenu : 1;
  uint8_t timer_secondary_submenu : 1;
  uint8_t pwm_secondary_sumenu : 1;  
  uint8_t led_primary_submenu : 1;
} led_menu_t;

/* �����˵��ṹ�� */
typedef struct
{
  uint8_t button_submenu : 1;  
  uint8_t adc_sumenu : 1;
  uint8_t pluse_width_measure_submenu : 1;
  uint8_t main_menu : 1;
  led_menu_t led_menu;
} modular_test_menu_t;

/* ��������˳��Ӳ˵���ö�� */
enum em_submenu_action
{
  ENTER,
  EXIT,
};

/* �Ӳ˵�ö�� */
enum em_submenu
{
  MAIN_MENU,
  PRIMARY_BUTTON,
  PRIMARY_LED,
  PRIMARY_ADC,
  PRIMARY_PWM_MEASURE,
  SECONDARY_PPI,
  SECONDARY_PWM,
  SECONDARY_TIMER,
};
/* 
=============
��������
=============
*/
/**
 * Ӧ�ò��ʼ��
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/2, ��ʼ���汾\n
 */
void user_app_init(void);

/**
 * ����ӳ�䴮��
 * @param[in]   format������ĸ�ʽ
 * @retval      ...���ɱ䳤�ȵĲ���
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/2, ��ʼ���汾\n
 */
void user_customer_printf(char *format, ...);

/**
 * ���˵���Ϣ��ʾ
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
void main_menu_display(void);

#endif