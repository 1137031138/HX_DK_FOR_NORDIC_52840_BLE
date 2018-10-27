/**
* @file         user_ppi.c
* @brief        PPI����غ�������
* @details      ʹ��PPI�����������ȵ���غ�������
* @author       Helon_Chan
* @QQ Group     671139854
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/10/27, ��ʼ���汾\n
*/

/* 
=============
ȫ�ֱ�������
=============
*/

/* 
=============
ͷ�ļ�����
=============
*/
#include "user_ppi.h"
#include "user_log.h"
/* 
=============
��������
=============
*/
/**
 * ppi��ʼ������
 * @param[in]   eep:event�ĵ�ַ
 * @param[in]   tep:task�ĵ�ַ
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/10/27, ��ʼ���汾\n
 */
void user_ppi_init(uint32_t eep, uint32_t tep)
{
  ret_code_t error_code;
  /* ���ppiͨ�� */
  nrf_ppi_channel_t m_nrf_ppi_channel;
  /* ��ʼ��ppi */
  error_code = nrf_drv_ppi_init();
  NRF_LOG_INFO("nrf_drv_ppi_init is %d\n",error_code);
  /* ��δʹ�õ�ppiͨ���з���һ��ͨ�� */
  error_code = nrf_drv_ppi_channel_alloc(&m_nrf_ppi_channel);
  NRF_LOG_INFO("nrf_drv_ppi_channel_alloc is %d\n",error_code);

  /* ��ָ����event��ַ��task��ַ���������䵽��ppi channel */
  error_code = nrf_drv_ppi_channel_assign(m_nrf_ppi_channel,eep,tep);
  NRF_LOG_INFO("nrf_drv_ppi_channel_assign is %d\n",error_code);

  /* ʹ��ppi channel */
  error_code = nrf_drv_ppi_channel_enable(m_nrf_ppi_channel);
  NRF_LOG_INFO("nrf_drv_ppi_channel_enable is %d\n",error_code);
}