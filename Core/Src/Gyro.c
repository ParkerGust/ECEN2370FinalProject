#include "Gyro.h"

static HAL_StatusTypeDef HAL_Status;

static SPI_HandleTypeDef hspi5;

void Gyro_Init(){
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_SPI5_CLK_ENABLE();

	GPIO_InitTypeDef PinConfig0;
	PinConfig0.Mode = GPIO_MODE_AF_PP;
	PinConfig0.Pull = GPIO_NOPULL;
	PinConfig0.Speed = GPIO_SPEED_FREQ_MEDIUM;
	PinConfig0.Alternate = GPIO_AF5_SPI5;
	PinConfig0.Pin = GPIO_PIN_7;
	HAL_GPIO_Init(GPIOF, &PinConfig0);

	GPIO_InitTypeDef PinConfig1;
	PinConfig1.Mode = GPIO_MODE_AF_PP;
	PinConfig1.Pull = GPIO_NOPULL;
	PinConfig1.Speed = GPIO_SPEED_FREQ_MEDIUM;
	PinConfig1.Alternate = GPIO_AF5_SPI5;
	PinConfig1.Pin = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOF, &PinConfig1);

	GPIO_InitTypeDef PinConfig2;
	PinConfig2.Mode = GPIO_MODE_AF_PP;
	PinConfig2.Pull = GPIO_NOPULL;
	PinConfig2.Speed = GPIO_SPEED_FREQ_MEDIUM;
	PinConfig2.Alternate = GPIO_AF5_SPI5;
	PinConfig2.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOF, &PinConfig2);

	GPIO_InitTypeDef PinConfig3;
	PinConfig3.Mode = GPIO_MODE_OUTPUT_PP;
	PinConfig3.Pull = GPIO_NOPULL;
	PinConfig3.Speed = GPIO_SPEED_FREQ_MEDIUM;
	PinConfig3.Pin = GPIO_PIN_1;
	HAL_GPIO_Init(GPIOC, &PinConfig3);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);

	hspi5.Instance = SPI5;
	hspi5.Init.Mode = SPI_MODE_MASTER;
	hspi5.Init.Direction = SPI_DIRECTION_2LINES;
	hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi5.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi5.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi5.Init.NSS = SPI_NSS_SOFT;
	hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
	HAL_Status = HAL_SPI_Init(&hspi5);

	Gyro_Power();
	uint8_t CR5_Config = 0;
	CR5_Config |= (GYRO_CR5_REBOOTMEMCONTENT);
	CR5_Config |= (GYRO_CR5_FIFO);
	Gyro_ConfigureReg(GYRO_CR5, CR5_Config);
	uint8_t CR1_Config = 0;
	CR1_Config |= GYRO_CR1_POWERDOWN_NORMAL_ENABLE;
	CR1_Config |= GYRO_CR1_BANDWIDTH_SET;
	CR1_Config |= GYRO_CR1_Y_ENABLE;
	Gyro_ConfigureReg(GYRO_CR1, CR1_Config);
}
int16_t Gyro_GetYLoc(){
	uint8_t yLow = Gyro_ReadReg(GYRO_OUT_Y_L);
	uint16_t yHigh = Gyro_ReadReg(GYRO_OUT_Y_H);
	yHigh = yHigh << 8;
	int16_t yLoc = (int16_t)(yLow | yHigh);
	return yLoc;
}

void Gyro_GetPrintID	(){
	uint8_t ID = Gyro_ReadReg(GYRO_WHO_AM_I);
	printf("Gyro ID: 0x%02X\n", ID);
}

void Gyro_Power(){
	uint8_t CR1_Config = 0;
	CR1_Config |= GYRO_CR1_POWERDOWN_NORMAL_ENABLE;
	Gyro_ConfigureReg(GYRO_CR1, CR1_Config);
	HAL_Delay(100);
}

void Gyro_GetPrintTemp(){
	uint8_t Temp = Gyro_ReadReg(GYRO_OUT_TEMP);
	printf("Temperature: %d\n", Temp);
}

void Gyro_ConfigureReg(uint16_t Reg, uint8_t data){
	uint16_t package = 0;
	package = SPI_WRITE | Reg ;
	package |= (data << SPI_DATA_OFFSET);
	Gyro_EnableSlaveConnection();

	HAL_SPI_Transmit(&hspi5, (uint8_t*) &package, 2, timeout);

	Gyro_DisableSlaveConnection();

}

uint16_t Gyro_ReadReg(uint16_t Reg){
	uint8_t package = 0;
	package = SPI_READ | Reg;
	uint16_t data = 0;
	Gyro_EnableSlaveConnection();

	while (HAL_GPIO_ReadPin(GYRO_CS_PORT, GYRO_CS_PIN) != GPIO_PIN_RESET);
	HAL_Status = HAL_SPI_TransmitReceive(&hspi5, &package,(uint8_t*) &data, 2, timeout);
	Gyro_VerifyHAL();
	uint16_t DataReturned = (0xFF00 & data) >> 8;
	Gyro_DisableSlaveConnection();
	return DataReturned;

}

void Gyro_VerifyHAL(){
	while(HAL_Status != HAL_OK);
}

void Gyro_EnableSlaveConnection(){
	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, 0);
}

void Gyro_DisableSlaveConnection(){
	HAL_GPIO_WritePin(GYRO_CS_PORT, GYRO_CS_PIN, 1);
}
