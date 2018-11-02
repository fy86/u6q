#include <common.h>
#include <net.h>
#include <command.h>
//#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <config_cmd_default.h>

int do_fpga(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])  
{ 
	int i;
	int len;
	volatile unsigned int *p32data,*p32dir,*p32status;
	unsigned int v_dir,v_data,v_status;
	unsigned int v_data0,v_data1,v_dataLH,v_dataHH,v_dataLL,v_dataHL;
	char *p,c;

	p32data   = 0x20b4000;
	p32dir    = 0x20b4004;
	p32status = 0x20b4008;

	v_dir = *p32dir;
	v_dir &= 0x00c7;
	v_dir |= 0x46;
	*p32dir = v_dir;

	v_data = *p32data;
	v_data0 = v_data & (~0x00c7);
	v_dataLH = v_data0 | 0x06;
	v_dataHH = v_data0 | 0x46;
	v_dataLL = v_data0 | 0x02;
	v_dataHL = v_data0 | 0x42;

	v_data1 = v_data0 | 0x0002;
	*p32data = v_data1;
	printf("loop wait status high\n");
	for(;;){
		v_status=*p32status;
		if(1 == (1&v_status)) break;
	}
	printf("nConfig.high ==> nStatus.high\n");

	v_data1 = v_data0 | 0x00;
	*p32data = v_data1;
	printf("loop wait status low\n");
	for(;;){
		v_status=*p32status;
		if(0 == (1&v_status)) break;
	}
	printf("nConfig.low ==> nStatus.low\n");

	v_data1 = v_data0 | 0x0002;
	*p32data = v_data1;
	printf("loop wait status high\n");
	for(;;){
		v_status=*p32status;
		if(1 == (1&v_status)) break;
	}
	printf("nConfig.high ==> nStatus.high\n");

	p = 0x10800000;
	len=7212234;//len cu
	for(i=0;i<len;i++){
		c = *p++;
		if(c&0x01){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x02){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x04){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x08){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x10){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x20){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x40){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
		if(c&0x80){
			*p32data=v_dataLH;
			*p32data=v_dataHH;
		}
		else{
			*p32data=v_dataLL;
			*p32data=v_dataHL;
		}
	}
	printf(" ** done\n");
#if 0
	int i;
	unsigned int *p32,*p32dir,u,u1;
	p32= 0x209c000;
	p32dir= 0x209c004;
	printf("(0x0209.c000) : 0x%08x\n",*p32);
	u=*p32dir;
	u=u|0x180;
	*p32dir = u;

	u=*p32;
	u1=u^0x180;
	for(i=0;i<4;i++){
		*p32 = u;
		udelay(1000000);
		*p32 = u1;
		udelay(1000000);
	}
#endif
	return 1;
}

U_BOOT_CMD(
        fpga ,      1,      1,      do_fpga,
        "fpga download\n",
        ""
);
