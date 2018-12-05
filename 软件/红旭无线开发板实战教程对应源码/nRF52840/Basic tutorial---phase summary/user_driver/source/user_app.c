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
/* ����һ���ֽڵ�rx������ */
static uint8_t g_s_rx_buffer[1]={0};
/* ����uart0ʵ�� */
static nrf_drv_uart_t g_m_uart_id = NRF_DRV_UART_INSTANCE(0);

volatile uint8_t temp = 0; 
/* 
=============
��������
=============
*/

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
    /* �ȴ�tx����ʱ���������ݷ��ͳ�ȥ */
    while (nrf_drv_uart_tx_in_progress(&g_m_uart_id));
    nrf_drv_uart_tx(&g_m_uart_id, g_s_tx_buffer + i, 1);        
  }
}


/**
 * �����¼�������
 * @param[in]   p_event		�������ľ����¼���Э���ж�Ӧ������
 * @param[in]   p_context ���ⲿ������¼��ص��Ĳ�������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/11/28, ��ʼ������
 */
static void user_uart_evt_handler(nrf_drv_uart_event_t *p_event, void *p_context)
{  
  switch (p_event->type)
  {
  case NRF_DRV_UART_EVT_RX_DONE:
    nrf_drv_uart_rx(&g_m_uart_id,g_s_rx_buffer,1);   
	temp = g_s_rx_buffer[0];
    break;
  default:
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
void user_uart_recevice_process(void)
{
  switch(temp)
  {
    /* BUTTON */
    case 1:
      HX_PRINTF("/==============================================================================/\n");
      HX_PRINTF("--> You can achieve click��Double click��Multi click in this submenu.\n");
      HX_PRINTF("/==============================================================================/\n");
      break;
    /* LED */
    case 2:
      break;
    /* ADC */
    case 3:
      break;
    /* UART */  
    case 4:
      break;
    /* Pluse Width Measure */
    case 5:
      break;
    default:
      if (temp != 0x00)
        HX_PRINTF("Invalid Command is %d.Please input the numeric 1~5 !!!\r\n",temp);
      break;
  }
  if (temp != 0x00)
    temp = 0x00;
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
  /* log������ʼ��  */
  user_uart_init(&g_m_uart_id,user_uart_evt_handler,g_s_rx_buffer);
}