#include <global.h>
#include <string.h>  // Để sử dụng strstr

extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
uint8_t cmd_str1[6] = "!RST#";
uint8_t cmd_str2[5] = "!OK#";

#include <stdint.h>

int isSubstring(uint8_t *buffer, uint8_t *input) {
    if (input == NULL || buffer == NULL) {
        return 0; // Chuỗi không hợp lệ
    }

    // Tính độ dài của buffer và input
    int buffer_len = 0;
    int input_len = 0;

    while (buffer[buffer_len] != '\0') {
        buffer_len++;
    }

    while (input[input_len] != '\0') {
        input_len++;
    }

    // Nếu chuỗi cần tìm dài hơn chuỗi gốc, chắc chắn không phải chuỗi con
    if (input_len > buffer_len) {
        return 0;
    }

    // Tạo chuỗi "xoay vòng" bằng cách nối buffer với chính nó
    uint8_t extended_buffer[2 * buffer_len + 1];
    for (int i = 0; i < buffer_len; i++) {
        extended_buffer[i] = buffer[i];
        extended_buffer[i + buffer_len] = buffer[i];
    }
    extended_buffer[2 * buffer_len] = '\0'; // Kết thúc chuỗi

    // Kiểm tra input có phải chuỗi con của extended_buffer hay không
    for (int i = 0; extended_buffer[i] != '\0'; i++) {
        int j = 0;
        while (input[j] != '\0' && extended_buffer[i + j] == input[j]) {
            j++;
        }

        if (input[j] == '\0') {
            return 1; // Tìm thấy
        }
    }

    return 0; // Không tìm thấy
}



void command_parser_fsm() {
    switch (state) {
        case CMD_IDLE:
        	if(1){
        		state = CMD_CHECK;
        	}
        	break;
        case CMD_CHECK:
            if (isSubstring(buffer, cmd_str1) == 1) {
                memset(buffer, 0, MAX_BUFFER_SIZE);
                index_buffer = 0;
                state = UART_SEND;
            }
            else {
            	HAL_GPIO_TogglePin (LED_RED1_GPIO_Port , LED_RED1_Pin);
            }
            break;
        default: break;
    }
}
