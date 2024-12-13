#include <global.h>
#include <string.h>
#include <stdio.h>  // Để sử dụng sprintf

extern uint32_t ADC_value;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
uint8_t str[30];
//uint8_t pre[30];
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart2;
extern uint8_t cmd_str1[6];
extern uint8_t cmd_str2[5];
extern uint8_t buffer_flag;
void uart_communiation_fsm() {
    switch (state) {
        case UART_SEND:
            ADC_value = HAL_ADC_GetValue(&hadc1);
            sprintf(str, "!ADC=%d#\n", ADC_value);
        	HAL_UART_Transmit (& huart2 , ( void *) str , sprintf(str, "!ADC=%d#\n", ADC_value), 1000) ;
            setTimer(0, 3000);
            state = CMD_WAIT;
            break;

        case UART_RESEND:
            // Gửi lại chuỗi lưu trong `pre`
            HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%d#\n", ADC_value), 1000);

            setTimer(0, 3000);

            // Chuyển trạng thái
            state = CMD_WAIT;
            break;
        case CMD_WAIT:
        	if(buffer_flag == 1){
        		HAL_GPIO_TogglePin (LED_RED2_GPIO_Port , LED_RED2_Pin);
            if (isSubstring(buffer, cmd_str2) == 1) {
            	HAL_GPIO_TogglePin (LED_RED2_GPIO_Port , LED_RED2_Pin);
                memset(buffer, 0, MAX_BUFFER_SIZE);
                index_buffer = 0;
                HAL_GPIO_TogglePin (LED_RED2_GPIO_Port , LED_RED2_Pin);
                state = CMD_IDLE;
                break;
            }
        	}
            if (timers[0].flag == 1) {
                timers[0].flag = 0;
                state = UART_RESEND;
            }
            break;
        default: break;
    }
}
