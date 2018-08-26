/**
* @file         user_application.c
* @brief        ʵ���û��߼�������صĺ�������
* @details      �û������Լ�д����������Nordic����������ʵ���Զ���Ĺ���
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/08/19, ��ʼ���汾\n
*/

/*
===========================
ͷ�ļ�����
=========================== 
*/

#include "user_application.h"

/*
===========================
��������
=========================== 
*/


/**
 * �������������������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
void user_multi_click_handler(uint8_t button_no, uint8_t *click_counts)
{
  switch(button_no)
  {
    case BUTTON1:
      NRF_LOG_INFO("click counts is %d\n",*click_counts);
      *click_counts = 0;
      break;
    default:
      break;
  }
}

/**
 * ��������������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
void user_long_pressed_handler(uint8_t button_no)
{
  switch(button_no)
  {
    case BUTTON1:
      NRF_LOG_INFO("gpio%d long pressed\n",button_no);      
      break;
    default:
      break;
  }
}
/**
 * �û�Ӧ�ó�ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n
 */
void user_application_init(void)
{
  /* log������ʼ��  */
  log_init();
  user_button_timer_init();
  user_multi_click_init(user_multi_click_handler,user_long_pressed_handler,BUTTON_COUNTS);
  NRF_LOG_INFO("/******************************************************************************/\n");
  NRF_LOG_INFO("                         Welcome to multi click demo project                    \n");
  NRF_LOG_INFO("                         website :bbs.wireless-tech.cn                          \n");
  NRF_LOG_INFO("                         QQ Group:671139854                                     \n");
  NRF_LOG_INFO("                         Author  :wireless-tech                                 \n");
  NRF_LOG_INFO("/******************************************************************************/\n");
}