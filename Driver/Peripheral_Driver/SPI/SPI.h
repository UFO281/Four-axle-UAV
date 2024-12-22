/**
 * @file SPI.h
 * @author wls (ufo281@outlook.com)
 * @brief
 * @version 1.0
 * @date 2024-11-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef __MYSPI_H
#define __MYSPI_H

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif
