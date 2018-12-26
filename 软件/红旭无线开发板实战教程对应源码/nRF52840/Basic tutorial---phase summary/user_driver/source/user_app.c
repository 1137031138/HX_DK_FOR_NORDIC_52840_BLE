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
// /* ����һ���ֽڵ�rx������ */
// static uint8_t g_s_rx_buffer[1]={0};
// /* ����uart0ʵ�� */
// static nrf_drv_uart_t g_m_uart_id = NRF_DRV_UART_INSTANCE(0);
/* ����˵��ṹ����� */
modular_test_menu_t g_m_menu;


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
  HX_PRINTF("/******************************************************************************/\n");
  HX_PRINTF("                         Welcome to phase summary project                       \n");
  HX_PRINTF("                         website :bbs.wireless-tech.cn                          \n");
  HX_PRINTF("                         QQ Group:671139854                                     \n");
  HX_PRINTF("/==============================================================================/\n");
  HX_PRINTF("--> This is the phase summary project to test what the basic tutorials said,\n");
  HX_PRINTF("--> and there are total 4 modular test projects,please input the corresponded\n");
  HX_PRINTF("--> number to come into the corresponded the test project.\n");
  HX_PRINTF("--> Such as \"1\" for testing the button. \n");
  HX_PRINTF("/==============================================================================/\n");
  HX_PRINTF("1.BUTTON\n");
  HX_PRINTF("2.LED\n");
  HX_PRINTF("3.ADC\n");  
  HX_PRINTF("4.Pulse Width Measure\n");
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
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can implement click��Double click��Multi click and Long Pressafter go to this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("/==============================================================================/\n");
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
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can implement the LED related functions in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("--> 1. PPI\n");
    HX_PRINTF("--> 2. PWM\n");
    HX_PRINTF("--> 3. TIMER\n");
    HX_PRINTF("--> 4. RGB\n");
    HX_PRINTF("/==============================================================================/\n");
    break;
  case SECONDARY_PPI:
    g_m_menu.current_menu = SECONDARY_PPI;
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> The led is on or off by 1000ms interval in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("/==============================================================================/\n");
    nrf_drv_timer_enable(&hardware_timer0);
    nrf_drv_gpiote_out_task_enable(LED_NUMBER);
    break;
  case SECONDARY_PWM:
    g_m_menu.current_menu = SECONDARY_PWM;
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can modify the PWM duty cycle in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("--> 1. 20%c \n",'%');
    HX_PRINTF("--> 2. 40%c\n",'%');
    HX_PRINTF("--> 3. 60%c\n",'%');
    HX_PRINTF("--> 4. 80%c\n",'%');
    HX_PRINTF("/==============================================================================/\n");
    break;
  case SECONDARY_TIMER:
    g_m_menu.current_menu = SECONDARY_TIMER;
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can modify the blink frequency in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("--> 1. 100ms \n");
    HX_PRINTF("--> 2. 200ms \n");
    HX_PRINTF("--> 3. 300ms \n");
    HX_PRINTF("--> 4. 400ms \n");
    HX_PRINTF("/==============================================================================/\n");
    break;
  case SECONDARY_RGB:
    g_m_menu.current_menu = SECONDARY_RGB;
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can select the led color in this submenu. The default color is Red.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("--> 1. Red \n");
    HX_PRINTF("--> 2. Green \n");
    HX_PRINTF("--> 3. Blue \n");    
    HX_PRINTF("/==============================================================================/\n");
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
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can implement the ADC Measure in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("/==============================================================================/\n");
    break;
  /* �˳��Ӳ˵� */
  case EXIT_PRIMARY_MENU:
    g_m_menu.current_menu = MAIN_MENU;
    main_menu_display();
    break;
  }
}

/**
 * �����Ȳ����Ӳ˵�����
 * @param[in]   type��ENTER��ʾ�����Ӳ˵���EXIT��ʾ�˳��Ӳ˵�
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/15, ��ʼ���汾\n
 */
static void user_pluse_width_measure_submenu_handler(uint8_t type)
{  
  switch (type)
  {
  /* �����Ӳ˵� */
  case PRIMARY_PWM_MEASURE:
    g_m_menu.current_menu = PRIMARY_PWM_MEASURE;
    HX_PRINTF("/==============================================================================/\n");
    HX_PRINTF("--> You can implement Pluse Width Measure function in this submenu.\n");
    HX_PRINTF("--> 0. Back to the upper menu.\n");
    HX_PRINTF("/==============================================================================/\n");
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
      /* Pluse Width Measure */
      case 4:
        user_pluse_width_measure_submenu_handler(PRIMARY_PWM_MEASURE);
        break;
      /* ��������������Ч */
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 1~4 !!!\r\n", rx_buffer);
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
        nrf_drv_timer_disable(&hardware_timer0);  
        nrf_drv_gpiote_out_task_disable(LED_NUMBER);
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
        break;
      /* ���20%��ռ�ձ� */
      case 1:
        break;
      /* ���40%��ռ�ձ� */
      case 2:
        break;
      /* ���60%��ռ�ձ� */
      case 3:
        break;
      /* ���80%��ռ�ձ� */
      case 4:
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
        break;
      /* LED��100ms��˸ */
      case 1:
        break;
      /* LED��200ms��˸ */
      case 2:
        break;
      /* LED��300ms��˸ */
      case 3:
        break;
      /* LED��400ms��˸ */
      case 4:
        break;
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0~4 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    case SECONDARY_RGB:
      switch (rx_buffer)
      {
      case 0:
        user_led_submenu_handler(PRIMARY_LED);
        break;
      /* ��ɫLED�� */
      case 1:
        break;
      /* ��ɫLED�� */
      case 2:
        break;
      /* ��ɫLED�� */
      case 3:
        break;
      default:
        HX_PRINTF("Invalid Command is %d.Please input the numeric 0~3 in this submenu!!!\r\n", rx_buffer);
        break;
      }
      break;
    case PRIMARY_ADC:
    case PRIMARY_PWM_MEASURE:
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
//    return err_code;
  }  

  /* ����32.768KHz��ʱ�� */
  err_code = lfclk_config();
  if(err_code != NRF_SUCCESS)
  {
    NRF_LOG_INFO("lfclk_config is %d\n",err_code);
//    return err_code;
  }

  /* �������ڰ����Ķ�ʱ�� */
  user_button_timer_init();
  /* �����Ѿ���ʼ�˵�Ƶʱ����,�����ط�����Ҫ�ٴε����� */
  user_multi_click_init(user_multi_click_handler, user_long_pressed_handler, BUTTON_COUNTS);
  /* ��ʼ��GPIOTE+PPI+TIMER0 */
  user_gpiote_timer0_init();
}