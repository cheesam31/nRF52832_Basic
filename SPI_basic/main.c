#include "nrf_drv_spi.h"
#include "boards.h"

#define SPI_BUFSIZE		1024
#define SPI_INSTANCE	0

uint8_t spi_tx_buf[SPI_BUFSIZE];
uint8_t spi_rx_buf[SPI_BUFSIZE];

static volatile bool spi_xfer_done;

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);

void spi_event_handler(nrf_drv_spi_evt_t const* p_event, void * p_conetext)
{
	spi_xfer_done = true;
}

void spi_init(void)
{
	nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
	spi_config.ss_pin	= DW_CS;
	spi_config.miso_pin	= SPI1_MISO;
	spi_config.mosi_pin	= SPI1_MOSI;
	spi_config.sck_pin	= SPI1_CLK;
	
	nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL);
}

int read_single_octet(int reg, int rx_size)
{
	reg = reg & 0x3F;

	spi_xfer_done = false;

	nrf_drv_spi_transfer(&spi, spi_tx_buf, 1, spi_rx_buf, rx_size + 1);

	while(spi_xfer_done == false)
	{
		;
	}

	return 0;
}

int main(void) 
{
	spi_init();

	read_single_octet(0x00, 4);

	while(true) 
	{
		;
	}
}