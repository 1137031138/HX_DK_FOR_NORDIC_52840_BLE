/**
* @file         user_log.c
* @brief        log��صĺ�������
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
ȫ�ֱ���
=============
*/
static uint8_t s_formatBuffer[HX_LOG_UART_TEMP_BUFFER_SIZE];
/* 
=============
��������
=============
*/

/**
 * uart��ʼ������
 * @param[in]   nrf_drv_uart:����ʵ��
 * @param[in]   nrf_uart_event_handler:uart�¼��ص�������
  * @param[in]   rx_buffer:uart��rx������
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/06/09, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/11/28, ȫ�����ʹ�ùٷ���logģ�飬ֱ������
 */
void user_uart_init(nrf_drv_uart_t *nrf_drv_uart,
										nrf_uart_event_handler_t nrf_uart_event_handler,										
										uint8_t *rx_buffer)
{
	nrf_drv_uart_config_t m_config = NRF_DRV_UART_DEFAULT_CONFIG;
	m_config.pseltxd = HX_LOG_UART_TX_PIN;
	m_config.pselrxd = HX_LOG_UART_RX_PIN;
	m_config.pselcts = NRF_UART_PSEL_DISCONNECTED;
	m_config.pselrts = NRF_UART_PSEL_DISCONNECTED;
	m_config.baudrate = (nrf_uart_baudrate_t)HX_LOG_UART_BAUDRATE;
	ret_code_t err_code = nrf_drv_uart_init(nrf_drv_uart, &m_config, nrf_uart_event_handler);	
	APP_ERROR_CHECK(err_code);		
	err_code = nrf_drv_uart_rx(nrf_drv_uart,rx_buffer,1);
	APP_ERROR_CHECK(err_code);
	// err_code = nrf_drv_uart_tx(&g_m_uart_id,tx_buffer,sizeof(tx_buffer));
	// APP_ERROR_CHECK(err_code);
}


