#ifndef __RP_DDS_H__
#define __RP_DDS_H__

#include <stdint.h>
#include <sys/types.h>

#define PHASE_WIDTH 30
#define DEFAULT_ADDR 0x60000000
#define DEFAULT_SYSCLK_MHz 125

typedef struct 
{
  int mmapfd;
  volatile void *dds_cfg;
  int sys_clk_mhz;
  uint32_t pin0, pin1;
  uint16_t asf0, asf1;
} RP_DDS;

int rp_dds_open(RP_DDS * rp_dds, off_t hardware_addr, int sys_clk_mhz);
int rp_dds_set_freq(RP_DDS * rp_dds, double freq0, double freq1);
int rp_dds_set_freq_bin(RP_DDS * rp_dds, uint32_t pin0, uint32_t pin1);
int rp_dds_set_ampl(RP_DDS * rp_dds, double ampl0, double ampl1);
int rp_dds_set_ampl_bin(RP_DDS * rp_dds, uint16_t asf0, uint32_t asf1);
int rp_dds_close(RP_DDS * rp_dds);

#endif
