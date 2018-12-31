/**
* @file         user_app.c
* @brief        Ӧ�ò���صĺ�������
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/12/02, ��ʼ���汾\n
*/

/* 
=============
ͷ�ļ�����
=============
*/
#include "user_app.h"
/* 
=============
ȫ�ֱ���
=============
*/

/* ����һ��1�ֽڵ�tx������ */
static uint8_t g_s_tx_buffer[HX_LOG_UART_TEMP_BUFFER_SIZE];

/* ����˵��ṹ����� */
modular_test_menu_t g_m_menu;
/* ���LED��ɫ��ȫ�־�̬������Ĭ���Ǻ�ɫ */
uint8_t led_color = COMMON_R_LED_NUMBER;

/* ���ADC��ֵ�Ļ��� */
static nrf_saadc_value_t m_buffer_pool[1]; 

/* 
=============
�ⲿ��������
=============
*/

/* 
=============
��������
=============
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
      if (*click_counts != 0)
        HX_PRINTF("click counts is %d\n", *click_counts);
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
      HX_PRINTF("gpio%d long pressed\n",button_no);      
      break;
    default:
      break;
  }
}

/**
 * ����ӳ�䴮��
 * @param[in]   format������ĸ�ʽ
 * @retval      ...���ɱ䳤�ȵĲ���
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/2, ��ʼ���汾\n
 */
void user_customer_printf(char *format, ...)
{
  volatile uint8_t iWriteNum = 0, i = 0;
  va_list ap;

  if (!format)
    return;

  va_start(ap, format);

  iWriteNum = vsprintf((char *)g_s_tx_buffer, format, ap);

  va_end(ap);

  if (iWriteNum > HX_LOG_UART_TEMP_BUFFER_SIZE)
    iWriteNum = HX_LOG_UART_TEMP_BUFFER_SIZE;

  for (i = 0; i < iWriteNum; i++)
  {
    app_uart_put(g_s_tx_buffer[i]);
  }
}

/**
 * ���˵���Ϣ��ʾ
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
void main_menu_display(void)
{
  HX_PRINTF("\n/******************************************************************************/\n");
  HX_PRINTF("                         Welcome to phase summary project                       \n");
  HX_PRINTF("                         website :bbs.wireless-tech.cn                          \n");
  HX_PRINTF("                         QQ Group:671139854                                     \n");
  HX_PRINTF("/******************************************************************************/\n");
  HX_PRINTF("--> This is the phase summary project to test what the basic tutorials said,\n");
  HX_PRINTF("--> and there are total 3 modular test projects,please input the corresponded\n");
  HX_PRINTF("--> number to come into the corresponded the test project.\n");
  HX_PRINTF("--> Such as \"1\" for testing the button. \n");
  HX_PRINTF("/******************************************************************************/\n");
  HX_PRINTF("1.BUTTON\n");
  HX_PRINTF("2.LED\n");
  HX_PRINTF("3.ADC\n");  
}



/**
 * �Ӳ˵�ʶ��
 * @param[in]   NULL
 * @retval      ���ص�ǰ���ĸ��˵�������Ͳο�em_submenuö��
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
static uint8_t user_submenu_identification(void)
{  
  return g_m_menu.current_menu;
}


/**
 * �����Ӳ˵�����
 * @param[in]   type��ENTER��ʾ�����Ӳ˵���EXIT��ʾ�˳��Ӳ˵�
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
static void user_button_submenu_handler(uint8_t type)
{
  switch (type)
  {
  /* �����Ӳ˵� */
  case PRIMARY_BUTTON:
    g_m_menu.current_menu = PRIMARY_BUTTON;
    HX_PRINTF("\n/****************************************************************************************/\n");
    HX_PRINTF("-->You can implement click��Double click��Multi click and Long Pressafter go to this submenu.\n");
    HX_PRINTF("/*******************************************************************************************/\n");
    HX_PRINTF(" 0. Back to the upper menu.\n");    
    /* ʹ�ܰ��� */
    app_button_enable();
    break;
  /* �˳��Ӳ˵� */
  case EXIT_PRIMARY_MENU:
    g_m_menu.current_menu = MAIN_MENU;
    main_menu_display();
    /* ���ܰ��� */
    app_button_disable();
    break;
  }
  
  
}

/**
 * LED�Ӳ˵�����
 * @param[in]   type��������ο�em_submenu_actionö��
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
static void user_led_submenu_handler(uint8_t type)
{
  switch (type)
  {
  /* ����һ���Ӳ˵� */
  case PRIMARY_LED:
    g_m_menu.current_menu = PRIMARY_LED;
    HX_PRINTF("\n/****************************************************************************************/\n");
    HX_PRINTF("--> You can implement the LED related functions in this submenu.\n");
    HX_PRINTF("/******************************************************************************************/\n");
    HX_PRINTF("0. Back to the upper menu.\n");
    HX_PRINTF("1. PPI\n");
    HX_PRINTF("2. PWM\n");
    HX_PRINTF("3. TIMER\n");
    break;
  case SECONDARY_PPI:
    g_m_menu.current_menu = SECONDARY_PPI;
    HX_PRINTF("\n/****************************************************************************************/\n");
    HX_PRINTF("--> The led is on or off via PPI by the 1000ms interval in this submenu.\n");    
    HX_PRINTF("--> Or select which led color your favorite.\n");
    HX_PRINTF("/******************************************************************************************/\n");
    HX_PRINTF("0. Back to the upper menu.\n");
    HX_PRINTF("1. Set the LED color to Red.\n");
    HX_PRINTF("2. Set the LED color to Green.\n");
    HX_PRINTF("3. Set the LED color to Blue.\n");

    led_color = COMMON_R_LED_NUMBER;
    user_gpiote_timer0_ppi_init(led_color,DEFAULT_BLINK_FREQUENCY);
    break;
  case SECONDARY_PWM:
    g_m_menu.current_menu = SECONDARY_PWM;
    HX_PRINTF("\n/******************************************************************************************/\n");
    HX_PRINTF("--> You can modify the PWM duty cycle in this submenu,the default PWM duty cyce is 5%c\n",'%');
    HX_PRINTF("--> Or select which led color your favorite.\n");
    HX_PRINTF("/********************************************************************************************/\n");
    HX_PRINTF("0. Back to the upper menu.\n");
    HX_PRINTF("1. 20%c \n",'%');
    HX_PRINTF("2. 40%c\n",'%');
    HX_PRINTF("3. 60%c\n",'%');
    HX_PRINTF("4. 80%c\n",'%');
    HX_PRINTF("5. Set the LED color to Red.\n");
    HX_PRINTF("6. Set the LED color to Green.\n");
    HX_PRINTF("7. Set the LED color to Blue.\n");

    user_pwm_init(COMMON_R_LED_NUMBER,5);
    break;
  case SECONDARY_TIMER:
    g_m_menu.current_menu = SECONDARY_TIMER;
    HX_PRINTF("\n/******************************************************************************************/\n");
    HX_PRINTF("--> You can modify the blink frequency in this submenu.The default blink frequency is 1000ms.\n");
    HX_PRINTF("--> Or select which led color your favorite.\n");
    HX_PRINTF("/********************************************************************************************/\n");
    HX_PRINTF("0. Back to the upper menu.\n");
    HX_PRINTF("1. 100ms \n");
    HX_PRINTF("2. 200ms \n");
    HX_PRINTF("3. 300ms \n");
    HX_PRINTF("4. 400ms \n");
    HX_PRINTF("5. Set the LED color to Red.\n");
    HX_PRINTF("6. Set the LED color to Green.\n");
    HX_PRINTF("7. Set the LED color to Blue.\n");
    
    user_gpiote_timer0_ppi_init(COMMON_R_LED_NUMBER,DEFAULT_BLINK_FREQUENCY);
    break;  
  case EXIT_PRIMARY_MENU:
    g_m_menu.current_menu = MAIN_MENU;
    main_menu_display();
    break;
  }
}

/**
 * ADC�Ӳ˵�����
 * @param[in]   type��ENTER��ʾ�����Ӳ˵���EXIT��ʾ�˳��Ӳ˵�
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
static void user_adc_submenu_handler(uint8_t type)
{  
  switch (type)
  {
  /* �����Ӳ˵� */
  case PRIMARY_ADC:
    g_m_menu.current_menu = PRIMARY_ADC;
    HX_PRINTF("\n/******************************************************************************************/\n");
    HX_PRINTF("--> You can implement the ADC Measure in this submenu.\n");
    HX_PRINTF("/********************************************************************************************/\n");
    HX_PRINTF("0. Back to the upper menu.\n");
    user_adc_sample_start();
    break;
  /* �˳��Ӳ˵� */
  case EXIT_PRIMARY_MENU:
    g_m_menu.current_menu = MAIN_MENU;
    main_menu_display();
    break;
  }
}

/**
 * ���ڽ��մ�����
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/5, ��ʼ���汾\n
 */
static void user_uart_recevice_process(uint8_t rx_buffer)
{
  switch(g_m_menu.current_menu)
  {
    /* ���˵� */
    case MAIN_MENU:
      switch (rx_buffer)
      {
      /* BUTTON */
      case 1:
        user_button_submenu_handler(PRIMARY_BUTTON);
        break;
      /* LED */
      case 2:
        user_led_submenu_handler(PRIMARY_LED);
        break;
      /* ADC */
      case 3:
        user_adc_submenu_handler(PRIMARY_ADC);
        break;      
      /* ��������������Ч */
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 1~3 !!!\r\n", rx_buffer);
        break;
      }
      break;
    /* ����һ���Ӳ˵� */
    case PRIMARY_BUTTON:
      switch (rx_buffer)
      {
      /* ������һ���˵� */
      case 0:
        user_button_submenu_handler(EXIT_PRIMARY_MENU);
        break;      
      /* ��������������Ч */
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    /* LEDһ���Ӳ˵� */
    case PRIMARY_LED:
      switch(rx_buffer)
      {
        /* ������һ���˵� */
        case 0:
          user_led_submenu_handler(EXIT_PRIMARY_MENU);
          break;
        /* ����PPI�����˵� */
        case 1:
          user_led_submenu_handler(SECONDARY_PPI);
          break;
        /* ����PWM�����˵� */
        case 2:
          user_led_submenu_handler(SECONDARY_PWM);
          break;
        /* ����TIMER�����˵� */
        case 3:
          user_led_submenu_handler(SECONDARY_TIMER);
          break;
        /* ����RGB�����˵� */
        case 4:
          user_led_submenu_handler(SECONDARY_RGB);
          break;
        default:
          HX_PRINTF("Invalid Command is %d.Please input the numeric 0~4 in this submenu!!!\r\n", rx_buffer);
          break;
      }
    break;
    /* LED�����Ӳ˵�PPI */
    case SECONDARY_PPI:
      switch (rx_buffer)
      {
      case 0:
        user_led_submenu_handler(PRIMARY_LED);
        user_gpiote_timer0_ppi_uninit();
        break;
      /* Red */
      case 1:
        if (led_color != COMMON_R_LED_NUMBER)
        {
          led_color = COMMON_R_LED_NUMBER;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, DEFAULT_BLINK_FREQUENCY);
          HX_PRINTF("The current led color is Red!!!\r\n");
        }
        break;
      /* Green */
      case 2:
        if (led_color != (COMMON_G_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_G_LED_NUMBER + P0_PIN_NUM;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, DEFAULT_BLINK_FREQUENCY);
          HX_PRINTF("The current led color is Green!!!\r\n");
        }
        break;
      /* Blue */
      case 3:
        if (led_color != (COMMON_B_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_B_LED_NUMBER + P0_PIN_NUM;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, DEFAULT_BLINK_FREQUENCY);
          HX_PRINTF("The current led color is Blue!!!\r\n");
        }
        break;
      /* ��������������Ч */
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    case SECONDARY_PWM:
      switch (rx_buffer)
      {
      case 0:
        user_led_submenu_handler(PRIMARY_LED);
        user_pwm_uninit();
        break;
      /* ���20%��ռ�ձ� */
      case 1:
        user_set_pwm_duty_cycle(20);
        HX_PRINTF("The current PMW duty cycle is 20%c!!!\r\n", '%');
        break;
      /* ���40%��ռ�ձ� */
      case 2:
        user_set_pwm_duty_cycle(40);
        HX_PRINTF("The current PMW duty cycle is 40%c!!!\r\n", '%');
        break;
      /* ���60%��ռ�ձ� */
      case 3:
        user_set_pwm_duty_cycle(60);
        HX_PRINTF("The current PMW duty cycle is 60%c!!!\r\n", '%');
        break;
      /* ���80%��ռ�ձ� */
      case 4:
        user_set_pwm_duty_cycle(80);
        HX_PRINTF("The current PMW duty cycle is 80%c!!!\r\n", '%');
        break;
      /* ��ɫ */
      case 5:
        if (led_color != COMMON_R_LED_NUMBER)
        {
          led_color = COMMON_R_LED_NUMBER;
          user_pwm_uninit();
          user_pwm_init(led_color, pwm_duty_cycle);
          HX_PRINTF("The current led color is Red!!!\r\n");
        }
        break;
      /* ��ɫ */
      case 6:
        if (led_color != (COMMON_G_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_G_LED_NUMBER + P0_PIN_NUM;
          user_pwm_uninit();
          user_pwm_init(led_color, pwm_duty_cycle);
          HX_PRINTF("The current led color is Green!!!\r\n");
        }
        break;
      /* ��ɫ */
      case 7:
        if (led_color != (COMMON_B_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_B_LED_NUMBER + P0_PIN_NUM;
          user_pwm_uninit();
          user_pwm_init(led_color, pwm_duty_cycle);
          HX_PRINTF("The current led color is Blue!!!\r\n");
        }
        break;
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0~4 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    case SECONDARY_TIMER:
      switch (rx_buffer)
      {
      case 0:
        user_led_submenu_handler(PRIMARY_LED);
        user_gpiote_timer0_ppi_uninit();
        break;
      /* LED��100ms��˸ */
      case 1:
        if (blink_frequency != 100)
        {
          blink_frequency = 100;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current blink frequency is %dms!!!\r\n", blink_frequency);
        }
        break;
      /* LED��200ms��˸ */
      case 2:
        if (blink_frequency != 200)
        {
          blink_frequency = 200;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current blink frequency is %dms!!!\r\n", blink_frequency);
        }
        break;
      /* LED��300ms��˸ */
      case 3:
        if (blink_frequency != 300)
        {
          blink_frequency = 300;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current blink frequency is %dms!!!\r\n", blink_frequency);
        }
        break;
      /* LED��400ms��˸ */
      case 4:
        if (blink_frequency != 400)
        {
          blink_frequency = 400;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current blink frequency is %dms!!!\r\n", blink_frequency);
        }
        break;
      /* ��ɫ */
      case 5:
        if (led_color != COMMON_R_LED_NUMBER)
        {
          led_color = COMMON_R_LED_NUMBER;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current led color is Red!!!\r\n");
        }
        break;
      /* ��ɫ */
      case 6:
        if (led_color != (COMMON_G_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_G_LED_NUMBER + P0_PIN_NUM;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current led color is Green!!!\r\n");
        }
        break;
      /* ��ɫ */
      case 7:
        if (led_color != (COMMON_B_LED_NUMBER + P0_PIN_NUM))
        {
          led_color = COMMON_B_LED_NUMBER + P0_PIN_NUM;
          user_gpiote_timer0_ppi_uninit();
          user_gpiote_timer0_ppi_init(led_color, blink_frequency);
          HX_PRINTF("The current led color is Blue!!!\r\n");
        }
        break;
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0~4 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    case PRIMARY_ADC:    
      switch (rx_buffer)
      {
      case 0:
        user_adc_submenu_handler(EXIT_PRIMARY_MENU);
        break;
      /* ��������������Ч */
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    }
}

/**
 * �����¼�������
 * @param[in]   p_app_uart_event��������������¼��Լ������� 
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/28, ��ʼ������
 */
static void user_uart_evt_handler(app_uart_evt_t *p_app_uart_event)
{
  /* ��Ž��յ��Ĵ������ݵ���ʱ���� */
  uint8_t rx_buffer_temp = 0;
  switch (p_app_uart_event->evt_type)
  {
  case APP_UART_DATA_READY:
    app_uart_get(&rx_buffer_temp);
    user_uart_recevice_process(rx_buffer_temp);
    break;
  default:
    break;
  }
}

/**
 * adc�¼��ص�������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/11, ��ʼ���汾\n
 */
static void user_saadc_event_handler(nrfx_saadc_evt_t const *p_event)
{
  ret_code_t err_code;
  char float_str[80] = {0};
  float adc_value;

  switch (p_event->type)
  {
  /* ת����ɣ�����ж�·ADC�ɼ������ʱ��ʾ��·�ɼ���ɣ�
        ��ADCֵ���ж���·��Ҫ�����ٴΣ�����ֻ��һ·����ֻ��һ·��ֵ */
  case NRF_DRV_SAADC_EVT_DONE:
    /* ֻ��ת��һ��ͨ�������������4��ͨ���������4���Դ����� */
    err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, 1);
    NRF_LOG_INFO("nrf_drv_saadc_buffer_convert is %d\n", err_code);

    adc_value = p_event->data.done.p_buffer[0] * 3.6 / 16384;

    /* ������Nordic�Դ��Ĵ�ӡ������������ֻ����С�������λ��
         ���ﲻʹ�ã�����������ʹ�û����˽� */
    // NRF_LOG_INFO("adc_value is " NRF_LOG_FLOAT_MARKER " voltage \n",
    //                   NRF_LOG_FLOAT(adc_value));

    /* ����С�����4λ,���ﻹ��Ҫ�ڹ�����Ŀ��ʹ��float,�������sprintf�����ò��� */
    sprintf(float_str, "VDD is %.4f voltage\n", adc_value);
    /* �����õ�VDD��ѹֵ */
    HX_PRINTF("%s\n", float_str);
    break;
  default:
    break;
  }
}

/**
 * Ӧ�ò��ʼ��
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/2, ��ʼ���汾\n
 */
void user_app_init(void)
{  
  ret_code_t err_code = NRF_SUCCESS;
  /* log������ʼ��  */
  user_log_init(user_uart_evt_handler);
  /* Ĭ���������˵� */
  g_m_menu.current_menu = MAIN_MENU;

  /* ��ʼ��app_timerģ�� */
  err_code = app_timer_init();
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("app_timer_init is %d\n",err_code);
  }  

  /* ����32.768KHz��ʱ�� */
  err_code = lfclk_config();
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("lfclk_config is %d\n",err_code);
  }

  /* �������ڰ����Ķ�ʱ�� */
  user_button_timer_init();
  /* �û�������ʼ�� */
  user_multi_click_init(user_multi_click_handler, user_long_pressed_handler, BUTTON_COUNTS);

  /* ADC��ʼ�� */
  user_adc_init(user_saadc_event_handler,m_buffer_pool);  
}