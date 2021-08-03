#include "nrf_drv_twi.h"
#include "boards.h"

#define TWI_INSTANCE_ID	0

uint8_t ret;

uint8_t who_am_i = 0x0F;

static volatile bool m_xfer_done = false;

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

void twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
	m_xfer_done = true;
}

void twi_init (void)
{
    ret_code_t err_code;

    nrf_drv_twi_config_t twi_config = {
       .scl                = I2C_SCL,
       .sda                = I2C_SDA,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

	nrf_drv_twi_init(&m_twi, &twi_config, twi_handler, NULL);
	nrf_drv_twi_enable(&m_twi);
}


static void read_who_am_i()
{
    m_xfer_done = false;
	
	nrf_drv_twi_tx(&m_twi, LIS2DH12_ADDR, &who_am_i, 1, true);
	
	while (!m_xfer_done) ;

	m_xfer_done = false;

    nrf_drv_twi_rx(&m_twi, LIS2DH12_ADDR, &ret, 1);
	
	while(!m_xfer_done) ;
}


int main(void)
{
    twi_init();
	read_who_am_i();
	
	while(true)
		;
}
