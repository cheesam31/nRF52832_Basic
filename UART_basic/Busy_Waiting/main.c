#include "nrfx_uart.h"
#include "boards.h"

nrfx_uart_t uart_inst = {NRF_UART0, 0};
char ch ;

int main(void) {

    nrfx_uart_config_t uart_config = {UART_TX, UART_RX, 0, 0, 
                                      NULL, NRF_UART_HWFC_DISABLED, 
                                      NRF_UART_PARITY_EXCLUDED, 
                                      NRF_UART_BAUDRATE_115200, 7};

    nrfx_uart_init(&uart_inst, &uart_config, NULL);

    while(true) {
        while(nrfx_uart_rx(&uart_inst, &ch, 1) != NRFX_SUCCESS);
        while(nrfx_uart_tx(&uart_inst, &ch, 1) != NRFX_SUCCESS);
    }
}