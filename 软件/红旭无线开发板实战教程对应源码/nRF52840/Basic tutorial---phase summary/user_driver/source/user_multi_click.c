/**
* @file         user_multi_click.c
* @brief        ������صĺ�������
* @details      �û�����������ʵ�ֵ���������Լ������Ĵ���
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
#include "user_multi_click.h"

/*
===========================
��̬��������
=========================== 
*/
static void user_button_handler(uint8_t pin_no, uint8_t button_action);

/*
===========================
ȫ�ֱ���
=========================== 
*/
/* ��Ű�����صĲ��� */
static user_multi_click_t gs_m_user_multi_click  = 
{
  .app_button_cfg = 
  {
    {BUTTON1,APP_BUTTON_ACTIVE_LOW,NRF_GPIO_PIN_PULLUP,user_button_handler},
  },
  .user_long_pressed_handler = NULL,
  .user_multi_click_handler  = NULL,
  .click_counts              = 0,
  .is_long_press             = 0,
};

/* ���ڼ�ʱ������timer_id */
APP_TIMER_DEF(g_long_press_timer_id);
/* ���ڼ�ʱ�̰���timer_id */
APP_TIMER_DEF(g_short_press_timer_id);

/*
===========================
��������
=========================== 
*/

/** 
* ����������
* @param[in]   pin_no         ����ʾ���������������ĵ�����
* @param[in]   button_action  ����ʾ�����İ�����״̬�ǰ��»����ͷ�
* @retval      null
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n 
*/

static void user_button_handler(uint8_t pin_no, uint8_t button_action)
{
  switch(pin_no)
  {
    case BUTTON1:
      switch(button_action)
      {
        /* �������� */
        case APP_BUTTON_PUSH:
          NRF_LOG_INFO("APP_BUTTON_PUSH\n");          
          /* ��ʼ������ʱ */
          app_timer_start(g_long_press_timer_id,APP_TIMER_TICKS(TIMER_FOR_LONG_PRESSED),&pin_no);
          /* ��ͣ�̰���ʱ */
          app_timer_stop(g_short_press_timer_id);
          break;
        /* �����ͷ� */
        case APP_BUTTON_RELEASE:
          NRF_LOG_INFO("APP_BUTTON_RELEASE\n");
          /* ��ʼ�̰���ʱ,����ͷ�֮��150ms��û���µİ���������˵���ð����Ѿ���ȫ�ͷ�.ע�����ʱ�����Ը����Լ�����Ҫ���и��� */
          app_timer_start(g_short_press_timer_id,APP_TIMER_TICKS(150),&pin_no);
          /* ��ͣ������ʱ */
          app_timer_stop(g_long_press_timer_id);
          if(gs_m_user_multi_click.is_long_press)
          {
            gs_m_user_multi_click.is_long_press = 0;
            gs_m_user_multi_click.click_counts  = 0;
          }
          else
          {
            gs_m_user_multi_click.click_counts++;
          }
          break;
        default:

          break;
      }
      break;
    default:
      break;
  }
}


/** 
* ��������������
* @param[in]   p_context��������������������ʹ�õĲ��������ﴫ�������Ǿ�����ĸ�����
* @retval      null
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/26, ��ʼ���汾\n 
*/

static void user_long_press_handler(void *p_context)
{
  gs_m_user_multi_click.user_long_pressed_handler(*((uint8_t*)(p_context)));
  gs_m_user_multi_click.is_long_press = 1;
}

/** 
* �����̰�������
* @param[in]   p_context��������������������ʹ�õĲ��������ﴫ�������Ǿ�����ĸ�����
* @retval      null
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/26, ��ʼ���汾\n 
*/

static void user_short_press_handler(void *p_context)
{
  gs_m_user_multi_click.user_multi_click_handler(*((uint8_t*)(p_context)),&gs_m_user_multi_click.click_counts);
}

/** 
* ����32.768KHz��ʱ��,��sdk_config.h�п���ѡ����RC����XTAL
* @param[in]   null
* @retval      null
* @note        ���ʹ����SOFT_DEVICE����Ҫ���ô˺�������Ϊʹ��Э��ջʱ���ʼ��LFCLK����������û��ʹ��Э��ջ���û��Լ�����
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/19, ��ʼ���汾\n 
*/
ret_code_t lfclk_config(void)
{
  /* ��ʼ��nrf_drv_clockģ�� */
  ret_code_t err_code = nrf_drv_clock_init();
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("nrf_drv_clock_init is %d\n",err_code);
    return err_code;
  }
  
  /* ����LFCLK��������LFCLKʱ�� */
  nrf_drv_clock_lfclk_request(NULL);

  return err_code;
}

/** 
* ������ʱ���õ���ʱ�ӳ�ʼ����һ��Ҫuser_multi_click_init֮ǰ���øú��������򰴼�������������
* @param[in]   null
* @retval      NRF_SUCCESS����ʾ��ʼ���ɹ�������ֵ���ʼ��ʧ��
* @note        �޸���־ 
*               Ver0.0.1: 
                  Helon_Chan, 2018/08/26, ��ʼ���汾\n 
*               Ver0.0.2: 
                  Helon_Chan, 2018/12/26, ������app_timer��ʼ��\n                   
*/
ret_code_t user_button_timer_init(void)
{
  ret_code_t err_code = NRF_SUCCESS;

  err_code = app_timer_create(&g_long_press_timer_id,APP_TIMER_MODE_SINGLE_SHOT,user_long_press_handler);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("app_timer_create is %d\n",err_code);
    return err_code;
  } 
  err_code = app_timer_create(&g_short_press_timer_id,APP_TIMER_MODE_SINGLE_SHOT,user_short_press_handler);
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("app_timer_create is %d\n",err_code);
    return err_code;
  } 

  return err_code;
}


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
*               Ver0.0.2: 
                  Helon_Chan, 2018/12/23, ��ʼ��ʱ��ʹ�ܰ���\n   
*               Ver0.0.3: 
                  Helon_Chan, 2018/12/26, �����˿���32.768KHzʱ�ӵĲ���\n                                 
*/
ret_code_t user_multi_click_init(user_multi_click_handler_t multi_click_handler,user_long_pressed_handler_t long_pressed_handler,uint8_t button_counts)
{
  ret_code_t err_code = NRF_SUCCESS;

  if((!multi_click_handler)||(!button_counts))
  {
    return NRF_ERROR_INVALID_PARAM;
  }

  gs_m_user_multi_click.user_multi_click_handler  = multi_click_handler;
  gs_m_user_multi_click.user_long_pressed_handler = long_pressed_handler;   

  /* ��ʼ�����������ð�������ʱ��Ϊ10ms */
  err_code = app_button_init(gs_m_user_multi_click.app_button_cfg, button_counts, APP_TIMER_TICKS(10));
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("app_button_init is %d\n",err_code);
    return err_code;
  }  
  /* ���ܰ��� */
  err_code = app_button_disable();  
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("app_button_disable is %d\n",err_code);
    return err_code;
  }    
  return err_code;
}
