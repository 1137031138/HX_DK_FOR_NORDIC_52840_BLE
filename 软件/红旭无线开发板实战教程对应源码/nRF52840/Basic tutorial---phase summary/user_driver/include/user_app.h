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
#include "user_multi_click.h"

/* 
=============
��������
=============
*/
#if HX_LOG_UART_ENABLED
#define HX_PRINTF(format, ...) user_customer_printf(format, ##__VA_ARGS__)
#define NRF_LOG_INFO(...)
#else
#define HX_PRINTF(...)
#endif

/* 
=============
�ṹ������
=============
*/

/* �����˵��ṹ�� */
typedef struct
{
  uint8_t current_menu : 4;
  uint8_t secondary_submenu : 4;  
} modular_test_menu_t;

/* �˵�������ö�� */
enum em_submenu_action
{
  // PRIMARY_SUBMENU,                          ///< һ���Ӳ˵�
  // SECONDARY_SUBMENU,                        ///< �����Ӳ˵�
  // THREE_LEVEL_SUBMENU,                      ///< �����Ӳ˵�    
  BACK_TO_UPPER_MENU,                       ///< ������һ�β˵�  
  EXIT_PRIMARY_MENU,                        ///< �˳���ǰ��һ���Ӳ˵�
};

/* �Ӳ˵�ö�� */
enum em_submenu
{
  MAIN_MENU = 1,                            ///< ���˵�
  PRIMARY_BUTTON = 2,                       ///< ����һ���Ӳ˵�
  PRIMARY_LED = 3,                          ///< LEDһ���Ӳ˵�
  PRIMARY_ADC = 4,                          ///< ADCһ���Ӳ˵�
  PRIMARY_PWM_MEASURE = 5,                  ///< PWM����һ���Ӳ˵�  
  SECONDARY_PPI = 6,                        ///< LED�Ķ����Ӳ˵�PPI
  SECONDARY_PWM = 7,                        ///< LED�Ķ����Ӳ˵�PWM
  SECONDARY_TIMER = 8,                      ///< LED�Ķ����Ӳ˵�TIMER  
  SECONDARY_RGB = 9,                        ///< LED�Ķ����Ӳ˵�RGB 
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