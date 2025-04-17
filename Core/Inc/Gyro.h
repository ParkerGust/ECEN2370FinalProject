
#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"

#define GYRO_WHO_AM_I 0x0f
#define GYRO_CR1 0x20
#define GYRO_CR2 0x21
#define GYRO_CR3 0x22
#define GYRO_CR4 0x23
#define GYRO_CR5 0x24
#define GYRO_REFRENCEDATACAPTURE 0x25
#define GYRO_OUT_TEMP 0x26
#define GYRO_SR 0x27
#define GYRO_OUT_X_L 0x28
#define GYRO_OUT_X_H 0x29
#define GYRO_OUT_Y_L 0x2A
#define GYRO_OUT_Y_H 0x2B
#define GYRO_OUT_Z_L 0x2C
#define GYRO_OUT_Z_H 0x2D
#define GYRO_FIFO_CTRL_REG 0x2E
#define GYRO_FIFO_SRC_REG 0x2F
#define GYRO_INT1_CFG 0x30
#define GYRO_INT1_SRC 0x31
#define GYRO_INT1_THS_XH 0x32
#define GYRO_INT1_THS_XL 0x33
#define GYRO_INT1_THS_YH 0x34
#define GYRO_INT1_THS_YL 0x35
#define GYRO_INT1_THS_ZH 0x36
#define GYRO_INT1_THS_ZL 0x37
#define GYRO_INT1_DURATION 0x38

#define GYRO_CS_PORT GPIOC
#define GYRO_CS_PIN GPIO_PIN_1

#define GYRO_CR1_X_ENABLE (1 << 0)
#define GYRO_CR1_Y_ENABLE (1 << 1)
#define GYRO_CR1_Z_ENABLE (1 << 2)
#define GYRO_CR1_POWERDOWN_NORMAL_ENABLE (1 <<3)
#define GYRO_CR1_BANDWIDTH_SET (0b01 << 4)

#define GYRO_CR5_REBOOTMEMCONTENT (1 << 7)

#define SPI_WRITE (0 << 7)
#define SPI_READ (1 << 7)
#define SPI_REG_OFFSET 2
#define SPI_DATA_OFFSET 8

#define timeout 2600

void Gyro_Init();
void Gyro_GetPrintID();
void Gyro_Power();
void Gyro_GetPrintTemp();
void Gyro_ConfigureReg(uint16_t Reg, uint8_t data);
uint16_t Gyro_ReadReg(uint16_t Reg);
void Gyro_VerifyHAL();
void Gyro_EnableSlaveConnection();
void Gyro_DisableSlaveConnection();


#endif
