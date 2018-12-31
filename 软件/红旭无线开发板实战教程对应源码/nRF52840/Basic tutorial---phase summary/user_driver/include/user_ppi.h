/**
* @file         user_ppi.h
* @brief        ppi��غ����������Լ��궨��
* @author       Helon_Chan
* @website      http://bbs.wireless-tech.cn/
* @par Copyright (c):
*               �������߿����Ŷ�
* @par History:
*               Ver0.0.1:
                    Helon_Chan, 2018/12/26, ��ʼ���汾\n
*/
#ifndef USER_PPI_H
#define USER_PPI_H

/*
===========================
ͷ�ļ�����
=========================== 
*/

#include "nrfx_ppi.h"
#include "nrfx_gpiote.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_ppi.h"
#include "nrf_gpiote.h"
#include "user_log.h"
#include "nrf_drv_timer.h"
#include "nrf_gpio.h"
#include "nrfx_timer.h"
#include "user_common.h"
/*
===========================
�궨��
=========================== 
*/

#define KEY_NUMBER          13                        ///< ������Ӧ��GPIOΪP0.13
#define R_LED_NUMBER        26                        ///< LED��Ӧ��GPIOΪP0.26
#define G_LED_NUMBER        13+P0_PIN_NUM             ///< LED��Ӧ��GPIOΪP1.13
#define B_LED_NUMBER        15+P0_PIN_NUM             ///< LED��Ӧ��GPIOΪP1.15

#if HX_LOG_UART_ENABLED
#define NRF_LOG_INFO(...)
#endif

/*
===========================
�ⲿ��������
=========================== 
*/



/**
 * ��ʼ��gpiote+timer0+ppi,����LED�˵�֮�Ӳ˵�PPI
 * @param[in]   led_color         :ѡ��LED����ɫ,����ο�user_common.h��ͷ��
 * @param[in]   blink_interval_ms :ѡ��LED����˸��Ƶ�ʣ���λΪms
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/26, ��ʼ���汾\n
 *              Ver0.0.2:
                  Helon_Chan, 2018/12/31, ���ٽ������ܵĺ����ֿ������ˣ�ֱ�Ӽ����ڸú���\n              
 */

void user_gpiote_timer0_ppi_init(uint8_t color, uint32_t blink_interval_ms);


/**
 * ȡ����ʼ��gpiote+timer0+ppi
 * @param[in]   NULL
 * @retval      NULL
 * @par         �޸���־
 *              Ver0.0.1:
                  Helon_Chan, 2018/12/31, ��ʼ���汾\n          
 */

void user_gpiote_timer0_ppi_uninit(void);

#endif /* USER_PPI_H */