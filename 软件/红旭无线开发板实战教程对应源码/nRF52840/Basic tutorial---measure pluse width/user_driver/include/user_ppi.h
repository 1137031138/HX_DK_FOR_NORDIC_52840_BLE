/**
* @file         user_ppi.h
* @brief        PPI����غ�������
* @details      ʹ��PPI�����������ȵ���غ��������Լ���صĺ궨��
* @author       Helon_Chan
* @QQ Group     671139854
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                     Helon_Chan, 2018/10/27, ��ʼ���汾\n
*/

#ifndef USER_PPI_H
#define USER_PPI_H

/* 
=============
ͷ�ļ�����
=============
*/

#include "nrf_drv_ppi.h"

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
void user_ppi_init(uint32_t eep, uint32_t tep);

#endif