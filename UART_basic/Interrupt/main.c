#include "nrfx_uart.h"
#include "boards.h"

nrfx_uart_t uart_inst = {NRF_UART0, 0};
char ch ;

void event_handler(nrfx_uart_event_t * p_event, void * p_context) {
   
    switch(p_event->type){
        case NRFX_UART_EVT_RX_DONE:
            nrfx_uart_rx(&uart_inst, &ch, 1);
            nrfx_uart_tx(&uart_inst, &ch, 1);
            break;
        case NRFX_UART_EVT_TX_DONE:
            break;
        case NRFX_UART_EVT_ERROR:
            break;
   }
}

int main(void) {

    nrfx_uart_config_t uart_config = {UART_TX, UART_RX, 0, 0, 
                                      NULL, NRF_UART_HWFC_DISABLED, 
                                      NRF_UART_PARITY_EXCLUDED, 
                                      NRF_UART_BAUDRATE_115200, 7};


    nrfx_uart_init(&uart_inst, &uart_config, event_handler);
    nrf_uart_int_enable(NRF_UART0, NRF_UART_INT_MASK_RXDRDY | NRF_UART_INT_MASK_ERROR);
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_ERROR);
    nrf_uart_event_clear(NRF_UART0, NRF_UART_EVENT_RXDRDY);
    nrf_uart_task_trigger(NRF_UART0, NRF_UART_TASK_STARTRX);

    while(true) {
        ;   // Do nothing...
    }
}