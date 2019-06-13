#include <stdio.h>
#include <stdlib.h>
#include "rp_dds.h"

int main(void)
{
  // malloc するのめんどくさいので
  // RP_DDS * rp_dds = (RP_DDS *) malloc(sizeof(RP_DDS));
  RP_DDS rp_dds;
  int result = rp_dds_open(&rp_dds, DEFAULT_ADDR, DEFAULT_SYSCLK_MHz);
  
  if(result == EXIT_FAILURE)
	{
	  printf("failed to load device.");
	  return EXIT_FAILURE;
	}
  rp_dds_set_ampl(&rp_dds, 0.4, 0.4);
  rp_dds_set_freq(&rp_dds, 25, 25);

  result |= rp_dds_close(&rp_dds);

  if(result == EXIT_FAILURE)
	{
	  printf("failed to unload device.");
	  return EXIT_FAILURE;
	}
  // free(rp_dds);
  
  return EXIT_SUCCESS;
}

