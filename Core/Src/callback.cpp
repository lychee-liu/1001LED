#include "main.h"
#include "tim.h"
#include "math.h"
#include "usart.h"
#include "can.h"
#include "motor.h"

// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//     if(GPIO_Pin == KEY_Pin)
//     {
//         uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1)+1; //配置的是1000
//         uint32_t brightness = (__HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_2)+100)%arr_value;
//         __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,brightness);
//     }
// }
//
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
// {
//     if (htim == &htim1)
//     {
//         uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1)+1; //配置的是1000
//         uint32_t brightness = (__HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_2)+1)%arr_value;
//         __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,brightness);
//     }
// }

extern uint8_t rx_msg[32];
extern uint8_t tx_msg[32];

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if (huart == &huart7)
//     {
//         for (int i=0;i<32;++i)
//         {
//             tx_msg[i] = rx_msg[i];
//         }
//         HAL_UART_Transmit(&huart7, tx_msg, 32, 1000);
//     }
//     HAL_UART_Receive_IT(&huart7,rx_msg,32);
// }

// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
//     if (huart == &huart7)
//     {
//         memcpy(tx_msg, rx_msg, Size);
//         HAL_UART_Transmit_DMA(&huart7, tx_msg, Size);
//         HAL_UARTEx_ReceiveToIdle_DMA(&huart7, rx_msg, 32);
//     }
// }
extern uint8_t rx_data[8];
extern CAN_RxHeaderTypeDef rx_header;
extern uint8_t tx_data[8];
extern CAN_TxHeaderTypeDef tx_header;
extern M3508_Motor Motor;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hcan->Instance==CAN1)
    {
        HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0, &rx_header, rx_data);
        if (rx_header.StdId == 0x201)
        {
            Motor.canRxMsgCallback(rx_data);
        }
    }
}

uint32_t can_tx_mail_box_;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
        HAL_CAN_AddTxMessage(&hcan1, &tx_header, tx_data, &can_tx_mail_box_);
    }
}