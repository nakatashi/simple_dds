#ifndef __RP_DDS_H__
#define __RP_DDS_H__

#include <sys/types.h>

#define PHASE_WIDTH 30
#define DEFAULT_ADDR 0x60000000
#define DEFAULT_SYSCLK_MHz 125

typedef struct 
{
  int mmapfd;
  volatile void *dds_cfg;
  int sys_clk_mhz;
  double freq1_mhz, freq2_mhz;
  double ampl0, ampl1;
} RP_DDS;

int rp_dds_open(RP_DDS * rp_dds, off_t hardware_addr, int sys_clk_mhz);
int rp_dds_set_freq(RP_DDS * rp_dds, double freq0, double freq1);
int rp_dds_set_ampl(RP_DDS * rp_dds, double ampl0b, double ampl1);
int rp_dds_close(RP_DDS * rp_dds);

#endif