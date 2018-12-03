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

//  nrf_drv_uart_tx(&g_m_uart_id, g_s_tx_buffer, iWriteNum);
//  while (nrf_drv_uart_tx_in_progress(&g_m_uart_id))
//    ;
  for (i = 0; i < iWriteNum; i++)
  {
    while (nrf_drv_uart_tx_in_progress(&g_m_uart_id))
      ;
    nrf_drv_uart_tx(&g_m_uart_id, g_s_tx_buffer + i, 1);
    /* �ȴ�tx����ʱ���������ݷ��ͳ�ȥ */
    //  		while(nrf_drv_uart_tx_in_progress(&g_m_uart_id));
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