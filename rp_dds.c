#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "rp_dds.h"

int rp_dds_open(RP_DDS * rp_dds, off_t hardware_addr, int sys_clk_mhz)
{  
  int mmapfd;
  
  rp_dds->sys_clk_mhz = sys_clk_mhz;
  
  if((mmapfd = open("/dev/mem", O_RDWR)) < 0)
	{
	  perror("open");
	  return EXIT_FAILURE;
	}
  
  (rp_dds->mmapfd) = mmapfd;

  (rp_dds->dds_cfg) = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ|PROT_WRITE, MAP_SHARED, mmapfd, hardware_addr);
  if(!(rp_dds->dds_cfg))
	{
	  perror("failed to mmap dds_config register");
	  return EXIT_FAILURE;
	}

  // Initialize value.
  uint32_t* pin = ((uint32_t*) (rp_dds->dds_cfg + 0));
  rp_dds->pin0 = *(pin+0);
  rp_dds->pin1 = *(pin+1);

  uint32_t* asf = ((uint32_t*) (rp_dds->dds_cfg + 8));
  rp_dds->asf0 = (uint16_t) ((*asf) & 0b1111111111);
  rp_dds->asf1 = (uint16_t) (((*asf) >> 10) & 0b1111111111);

  return EXIT_SUCCESS;
}

int rp_dds_set_freq(RP_DDS * rp_dds, double freq0, double freq1)
{
  int sys_clk = rp_dds->sys_clk_mhz;
  int pWidth = 1 << PHASE_WIDTH;
  
  uint32_t pin0 = (uint32_t) (freq0 * (double) (pWidth / sys_clk));
  uint32_t pin1 = (uint32_t) (freq1 * (double) (pWidth / sys_clk));
  
  return rp_dds_set_freq_bin(rp_dds, pin0, pin1);
}

int rp_dds_set_freq_bin(RP_DDS * rp_dds, uint32_t pin0, uint32_t pin1)
{
  volatile uint32_t *pin = ((uint32_t*) ((rp_dds->dds_cfg) + 0));
  rp_dds->pin0 = pin0;
  rp_dds->pin1 = pin1;

  *(pin + 0) = pin0;
  *(pin + 1) = pin1;

  return EXIT_SUCCESS;
}

int rp_dds_set_ampl(RP_DDS * rp_dds, double ampl0, double ampl1)
{
  // convert to 10bit 2's complementary
  //uint16_t asf0 = ((~((uint16_t) (ampl0 * (1 << 9)) )) & 0x3FF) + 0b0000000001;
  //uint16_t asf1 = ((~((uint16_t) (ampl1 * (1 << 9)) )) & 0x3FF) + 0b0000000001;
  uint16_t asf0 = (uint16_t) (ampl0 * (1 << 9)) & 0x3FF;
  uint16_t asf1 = (uint16_t) (ampl1 * (1 << 9)) & 0x3FF;

  return rp_dds_set_ampl_bin(rp_dds, asf0, asf1);
}

int rp_dds_set_ampl_bin(RP_DDS * rp_dds, uint16_t asf0, uint32_t asf1)
{
  uint32_t * asf = ((uint32_t*) ((rp_dds->dds_cfg) + 8));
  *(asf) = (asf0 | (asf1 << 10)) & 0xFFFFFFFF;
  rp_dds->asf0 = asf0;
  rp_dds->asf1 = asf1;

  return EXIT_SUCCESS;
}

int rp_dds_close(RP_DDS * rp_dds)
{
  if(munmap((rp_dds->dds_cfg), sysconf(_SC_PAGESIZE)) < 0)
	{
	  perror("failed to munmap");
	  return EXIT_FAILURE;
	}

  close(rp_dds->mmapfd);
  return EXIT_SUCCESS;
}
