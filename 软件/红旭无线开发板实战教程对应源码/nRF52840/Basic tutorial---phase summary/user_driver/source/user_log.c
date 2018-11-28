/**
* @file         user_log.c
* @brief        log��صĺ�������
* @details      �û�����ѡ��ʹ��ͨ��UART��ӡlog��Ϣ����RTT��ӡlog��Ϣ
* @author       Helon_Chan
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/06/09, ��ʼ���汾\n
*/
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
#if DBG_ENABLE
    #define DBG_PRINTF(format,...)              user_debug_printf(format,##__VA_ARGS__)
#else
    #define DBG_PRINTF(...)
#endif

/* 
=============
ȫ�ֱ���
=============
*/
/* ����uart0ʵ�� */
static nrf_drv_uart_t g_m_uart_id = NRF_DRV_UART_INSTANCE(0);
/* ����һ��255�ֽڵĻ����� */
static uint8_t s_formatBuffer[MAX_FORMAT_BUFFER_SIZE];
/* 
=============
��������
=============
*/
void user_debug_printf(char *format, ...)
{
	uint8_t iWriteNum = 0, i = 0;
	va_list ap;

	if (!format)
		return;

	va_start(ap, format);

	iWriteNum = vsprintf((char *)s_formatBuffer, format, ap);

	va_end(ap);

	if (iWriteNum > MAX_FORMAT_BUFFER_SIZE)
		iWriteNum = MAX_FORMAT_BUFFER_SIZE;

	for (i = 0; i < iWriteNum; i++)
	{
		nrf_drv_uart_tx(&g_m_uart_id,s_formatBuffer+i,1);
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

}

/**
 * log��ʼ������
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/11/28, ȫ�����ʹ�ùٷ���logģ�飬ֱ������
 */
void user_uart_init(nrf_uart_event_handler_t nrf_uart_event_handler)
{
	nrf_drv_uart_config_t m_config = NRF_DRV_UART_DEFAULT_CONFIG;
	m_config.pseltxd = NRF_LOG_BACKEND_UART_TX_PIN;
	m_config.pselrxd = NRF_LOG_BACKEND_UART_RX_PIN;
	m_config.pselcts = NRF_UART_PSEL_DISCONNECTED;
	m_config.pselrts = NRF_UART_PSEL_DISCONNECTED;
	m_config.baudrate = (nrf_uart_baudrate_t)NRF_LOG_BACKEND_UART_BAUDRATE;
	ret_code_t err_code = nrf_drv_uart_init(&g_m_uart_id, &m_config, nrf_uart_event_handler);
	APP_ERROR_CHECK(err_code);	
}


