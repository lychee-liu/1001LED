#include "main.h"
#include "tim.h"
#include "math.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY_Pin)
    {
        uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1)+1; //配置的是1000
        uint32_t brightness = (__HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_2)+100)%arr_value;
        __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,brightness);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim == &htim1)
    {
        uint32_t arr_value = __HAL_TIM_GET_AUTORELOAD(&htim1)+1; //配置的是1000
        uint32_t brightness = (__HAL_TIM_GetCompare(&htim1, TIM_CHANNEL_2)+1)%arr_value;
        __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,brightness);
    }
}