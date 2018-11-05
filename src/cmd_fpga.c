#include <common.h>
#include <net.h>
#include <command.h>
//#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <config_cmd_default.h>

int w32(unsigned int *pi,unsigned int v);

int w32(unsigned int *pi,unsigned int v)
{
	*pi = v;
	return 1;
}
int do_fpga(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])  
{ 
	int i;
	int len;
	volatile unsigned int *p32data,*p32dir;
	volatile unsigned int *p32status;
	unsigned int v_dir,v_data,v_status;
	unsigned int v_data0,v_data1,v_dataLH,v_dataHH,v_dataLL,v_dataHL;
	char *p,c;
	unsigned int *pmux70,*pmux71,*pmux72,*pmux76,*pmux77;//gpio7_0,gpio7_1..............
#if 0
	pmux70=0x20e02b0;
	pmux71=0x20e02b4;
	pmux72=0x20e02b8;
	pmux76=0x20e02c8;
	pmux77=0x20e02cc;

	*pmux70 = 5;
	*pmux71 = 5;
	*pmux72 = 5;
	*pmux76 = 5;
	*pmux77 = 5;

	pmux70=0x20e0698;
	pmux71=0x20e069c;
	pmux72=0x20e06a0;
	pmux76=0x20e06b0;
	pmux77=0x20e06b4;

	*pmux70 = 0x1b0b0;
	*pmux71 = 0x1b0b0;
	*pmux72 = 0x1b0b0;
	*pmux76 = 0x1b0b0;
	*pmux77 = 0x1b0b0;
#endif
	p32data   = 0x20b4000;
	p32dir    = 0x20b4004;
	p32status = 0x20b4008;

	v_dir = *p32dir;
	v_dir &= ~0x00c7;
	v_dir |= 0x46;
	*p32dir = v_dir;
	printf(" dir.reg: %08x\n",v_dir);

	v_data = *p32data;
	v_data0 = v_data & (~0x00c7);
	v_dataLH = v_data0 | 0x06;
	v_dataHH = v_data0 | 0x46;
	v_dataLL = v_data0 | 0x02;
	v_dataHL = v_data0 | 0x42;
	printf(" data.reg: %08x\n",v_data);

	v_data1 = v_data0 | 0x0002;
	*p32data = v_data1;
	printf("loop wait status high\n");
	for(;;){
		v_status=*p32status;
		printf(" status.reg: %08x\r",v_status);
		if(1 == (1&v_status)) break;
	}
	printf("\nnConfig.high ==> nStatus.high\n");

	v_data1 = v_data0 | 0x00;
	*p32data = v_data1;
	printf("loop wait status low\n");
	for(;;){
		v_status=*p32status;
		printf(" status.reg: %08x\r",v_status);
		if(0 == (1&v_status)) break;
	}
	printf("\nnConfig.low ==> nStatus.low\n");

	v_data1 = v_data0 | 0x0002;
	*p32data = v_data1;
	printf("loop wait status high\n");
	for(;;){
		v_status=*p32status;
		printf(" status.reg: %08x\r",v_status);
		if(1 == (1&v_status)) break;
	}
	printf("\nnConfig.high ==> nStatus.high\n");

	p = 0x10800000;
	len=7212234;//len cu
	for(i=0;i<len;i++){
		c = *p++;
		if(c&0x01){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x02){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x04){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x08){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x10){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x20){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x40){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
		if(c&0x80){
			//*p32data=v_dataLH;
			//*p32data=v_dataHH;
			w32(p32data,v_dataLH);
			w32(p32data,v_dataHH);
		}
		else{
			//*p32data=v_dataLL;
			//*p32data=v_dataHL;
			w32(p32data,v_dataLL);
			w32(p32data,v_dataHL);
		}
	}
    printf("\n wait.done \n");
    for(i=0;;i++){
      v_status = *p32status;
      printf("wait.status.high    status: %08x   bit.status %d\r",v_status,v_status & 1);
      if(0x81==(0x81&v_status))break;
      //if(0==(i&0x0fffff))printf(" %d status: 0x%08x\n",i,v_status);
      //output_d(0);
	  //*p32data=v_dataLL;
	  //*p32data=v_dataHL;
	  w32(p32data,v_dataLL);
	  w32(p32data,v_dataHL);
    }
    printf("\n   download done \n");
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
