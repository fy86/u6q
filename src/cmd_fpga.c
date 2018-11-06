#include <common.h>
#include <net.h>
#include <command.h>
//#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <config_cmd_default.h>

#define D0 *p32data=v_dataLL; *p32data=v_dataHL;
#define D1 *p32data=v_dataLH; *p32data=v_dataHH;
#define CS00 case 0x000:  D0 D0 D0 D0 D0 D0 D0 D0 break;
#define CS01 case 0x001:  D1 D0 D0 D0 D0 D0 D0 D0 break;
#define CS02 case 0x002:  D0 D1 D0 D0 D0 D0 D0 D0 break;
#define CS03 case 0x003:  D1 D1 D0 D0 D0 D0 D0 D0 break;
#define CS04 case 0x004:  D0 D0 D1 D0 D0 D0 D0 D0 break;
#define CS05 case 0x005:  D1 D0 D1 D0 D0 D0 D0 D0 break;
#define CS06 case 0x006:  D0 D1 D1 D0 D0 D0 D0 D0 break;
#define CS07 case 0x007:  D1 D1 D1 D0 D0 D0 D0 D0 break;
#define CS08 case 0x008:  D0 D0 D0 D1 D0 D0 D0 D0 break;
#define CS09 case 0x009:  D1 D0 D0 D1 D0 D0 D0 D0 break;
#define CS0A case 0x00A:  D0 D1 D0 D1 D0 D0 D0 D0 break;
#define CS0B case 0x00B:  D1 D1 D0 D1 D0 D0 D0 D0 break;
#define CS0C case 0x00C:  D0 D0 D1 D1 D0 D0 D0 D0 break;
#define CS0D case 0x00D:  D1 D0 D1 D1 D0 D0 D0 D0 break;
#define CS0E case 0x00E:  D0 D1 D1 D1 D0 D0 D0 D0 break;
#define CS0F case 0x00F:  D1 D1 D1 D1 D0 D0 D0 D0 break;
#define CS10 case 0x010:  D0 D0 D0 D0 D1 D0 D0 D0 break;
#define CS11 case 0x011:  D1 D0 D0 D0 D1 D0 D0 D0 break;
#define CS12 case 0x012:  D0 D1 D0 D0 D1 D0 D0 D0 break;
#define CS13 case 0x013:  D1 D1 D0 D0 D1 D0 D0 D0 break;
#define CS14 case 0x014:  D0 D0 D1 D0 D1 D0 D0 D0 break;
#define CS15 case 0x015:  D1 D0 D1 D0 D1 D0 D0 D0 break;
#define CS16 case 0x016:  D0 D1 D1 D0 D1 D0 D0 D0 break;
#define CS17 case 0x017:  D1 D1 D1 D0 D1 D0 D0 D0 break;
#define CS18 case 0x018:  D0 D0 D0 D1 D1 D0 D0 D0 break;
#define CS19 case 0x019:  D1 D0 D0 D1 D1 D0 D0 D0 break;
#define CS1A case 0x01A:  D0 D1 D0 D1 D1 D0 D0 D0 break;
#define CS1B case 0x01B:  D1 D1 D0 D1 D1 D0 D0 D0 break;
#define CS1C case 0x01C:  D0 D0 D1 D1 D1 D0 D0 D0 break;
#define CS1D case 0x01D:  D1 D0 D1 D1 D1 D0 D0 D0 break;
#define CS1E case 0x01E:  D0 D1 D1 D1 D1 D0 D0 D0 break;
#define CS1F case 0x01F:  D1 D1 D1 D1 D1 D0 D0 D0 break;
#define CS20 case 0x020:  D0 D0 D0 D0 D0 D1 D0 D0 break;
#define CS21 case 0x021:  D1 D0 D0 D0 D0 D1 D0 D0 break;
#define CS22 case 0x022:  D0 D1 D0 D0 D0 D1 D0 D0 break;
#define CS23 case 0x023:  D1 D1 D0 D0 D0 D1 D0 D0 break;
#define CS24 case 0x024:  D0 D0 D1 D0 D0 D1 D0 D0 break;
#define CS25 case 0x025:  D1 D0 D1 D0 D0 D1 D0 D0 break;
#define CS26 case 0x026:  D0 D1 D1 D0 D0 D1 D0 D0 break;
#define CS27 case 0x027:  D1 D1 D1 D0 D0 D1 D0 D0 break;
#define CS28 case 0x028:  D0 D0 D0 D1 D0 D1 D0 D0 break;
#define CS29 case 0x029:  D1 D0 D0 D1 D0 D1 D0 D0 break;
#define CS2A case 0x02A:  D0 D1 D0 D1 D0 D1 D0 D0 break;
#define CS2B case 0x02B:  D1 D1 D0 D1 D0 D1 D0 D0 break;
#define CS2C case 0x02C:  D0 D0 D1 D1 D0 D1 D0 D0 break;
#define CS2D case 0x02D:  D1 D0 D1 D1 D0 D1 D0 D0 break;
#define CS2E case 0x02E:  D0 D1 D1 D1 D0 D1 D0 D0 break;
#define CS2F case 0x02F:  D1 D1 D1 D1 D0 D1 D0 D0 break;
#define CS30 case 0x030:  D0 D0 D0 D0 D1 D1 D0 D0 break;
#define CS31 case 0x031:  D1 D0 D0 D0 D1 D1 D0 D0 break;
#define CS32 case 0x032:  D0 D1 D0 D0 D1 D1 D0 D0 break;
#define CS33 case 0x033:  D1 D1 D0 D0 D1 D1 D0 D0 break;
#define CS34 case 0x034:  D0 D0 D1 D0 D1 D1 D0 D0 break;
#define CS35 case 0x035:  D1 D0 D1 D0 D1 D1 D0 D0 break;
#define CS36 case 0x036:  D0 D1 D1 D0 D1 D1 D0 D0 break;
#define CS37 case 0x037:  D1 D1 D1 D0 D1 D1 D0 D0 break;
#define CS38 case 0x038:  D0 D0 D0 D1 D1 D1 D0 D0 break;
#define CS39 case 0x039:  D1 D0 D0 D1 D1 D1 D0 D0 break;
#define CS3A case 0x03A:  D0 D1 D0 D1 D1 D1 D0 D0 break;
#define CS3B case 0x03B:  D1 D1 D0 D1 D1 D1 D0 D0 break;
#define CS3C case 0x03C:  D0 D0 D1 D1 D1 D1 D0 D0 break;
#define CS3D case 0x03D:  D1 D0 D1 D1 D1 D1 D0 D0 break;
#define CS3E case 0x03E:  D0 D1 D1 D1 D1 D1 D0 D0 break;
#define CS3F case 0x03F:  D1 D1 D1 D1 D1 D1 D0 D0 break;
#define CS40 case 0x040:  D0 D0 D0 D0 D0 D0 D1 D0 break;
#define CS41 case 0x041:  D1 D0 D0 D0 D0 D0 D1 D0 break;
#define CS42 case 0x042:  D0 D1 D0 D0 D0 D0 D1 D0 break;
#define CS43 case 0x043:  D1 D1 D0 D0 D0 D0 D1 D0 break;
#define CS44 case 0x044:  D0 D0 D1 D0 D0 D0 D1 D0 break;
#define CS45 case 0x045:  D1 D0 D1 D0 D0 D0 D1 D0 break;
#define CS46 case 0x046:  D0 D1 D1 D0 D0 D0 D1 D0 break;
#define CS47 case 0x047:  D1 D1 D1 D0 D0 D0 D1 D0 break;
#define CS48 case 0x048:  D0 D0 D0 D1 D0 D0 D1 D0 break;
#define CS49 case 0x049:  D1 D0 D0 D1 D0 D0 D1 D0 break;
#define CS4A case 0x04A:  D0 D1 D0 D1 D0 D0 D1 D0 break;
#define CS4B case 0x04B:  D1 D1 D0 D1 D0 D0 D1 D0 break;
#define CS4C case 0x04C:  D0 D0 D1 D1 D0 D0 D1 D0 break;
#define CS4D case 0x04D:  D1 D0 D1 D1 D0 D0 D1 D0 break;
#define CS4E case 0x04E:  D0 D1 D1 D1 D0 D0 D1 D0 break;
#define CS4F case 0x04F:  D1 D1 D1 D1 D0 D0 D1 D0 break;
#define CS50 case 0x050:  D0 D0 D0 D0 D1 D0 D1 D0 break;
#define CS51 case 0x051:  D1 D0 D0 D0 D1 D0 D1 D0 break;
#define CS52 case 0x052:  D0 D1 D0 D0 D1 D0 D1 D0 break;
#define CS53 case 0x053:  D1 D1 D0 D0 D1 D0 D1 D0 break;
#define CS54 case 0x054:  D0 D0 D1 D0 D1 D0 D1 D0 break;
#define CS55 case 0x055:  D1 D0 D1 D0 D1 D0 D1 D0 break;
#define CS56 case 0x056:  D0 D1 D1 D0 D1 D0 D1 D0 break;
#define CS57 case 0x057:  D1 D1 D1 D0 D1 D0 D1 D0 break;
#define CS58 case 0x058:  D0 D0 D0 D1 D1 D0 D1 D0 break;
#define CS59 case 0x059:  D1 D0 D0 D1 D1 D0 D1 D0 break;
#define CS5A case 0x05A:  D0 D1 D0 D1 D1 D0 D1 D0 break;
#define CS5B case 0x05B:  D1 D1 D0 D1 D1 D0 D1 D0 break;
#define CS5C case 0x05C:  D0 D0 D1 D1 D1 D0 D1 D0 break;
#define CS5D case 0x05D:  D1 D0 D1 D1 D1 D0 D1 D0 break;
#define CS5E case 0x05E:  D0 D1 D1 D1 D1 D0 D1 D0 break;
#define CS5F case 0x05F:  D1 D1 D1 D1 D1 D0 D1 D0 break;
#define CS60 case 0x060:  D0 D0 D0 D0 D0 D1 D1 D0 break;
#define CS61 case 0x061:  D1 D0 D0 D0 D0 D1 D1 D0 break;
#define CS62 case 0x062:  D0 D1 D0 D0 D0 D1 D1 D0 break;
#define CS63 case 0x063:  D1 D1 D0 D0 D0 D1 D1 D0 break;
#define CS64 case 0x064:  D0 D0 D1 D0 D0 D1 D1 D0 break;
#define CS65 case 0x065:  D1 D0 D1 D0 D0 D1 D1 D0 break;
#define CS66 case 0x066:  D0 D1 D1 D0 D0 D1 D1 D0 break;
#define CS67 case 0x067:  D1 D1 D1 D0 D0 D1 D1 D0 break;
#define CS68 case 0x068:  D0 D0 D0 D1 D0 D1 D1 D0 break;
#define CS69 case 0x069:  D1 D0 D0 D1 D0 D1 D1 D0 break;
#define CS6A case 0x06A:  D0 D1 D0 D1 D0 D1 D1 D0 break;
#define CS6B case 0x06B:  D1 D1 D0 D1 D0 D1 D1 D0 break;
#define CS6C case 0x06C:  D0 D0 D1 D1 D0 D1 D1 D0 break;
#define CS6D case 0x06D:  D1 D0 D1 D1 D0 D1 D1 D0 break;
#define CS6E case 0x06E:  D0 D1 D1 D1 D0 D1 D1 D0 break;
#define CS6F case 0x06F:  D1 D1 D1 D1 D0 D1 D1 D0 break;
#define CS70 case 0x070:  D0 D0 D0 D0 D1 D1 D1 D0 break;
#define CS71 case 0x071:  D1 D0 D0 D0 D1 D1 D1 D0 break;
#define CS72 case 0x072:  D0 D1 D0 D0 D1 D1 D1 D0 break;
#define CS73 case 0x073:  D1 D1 D0 D0 D1 D1 D1 D0 break;
#define CS74 case 0x074:  D0 D0 D1 D0 D1 D1 D1 D0 break;
#define CS75 case 0x075:  D1 D0 D1 D0 D1 D1 D1 D0 break;
#define CS76 case 0x076:  D0 D1 D1 D0 D1 D1 D1 D0 break;
#define CS77 case 0x077:  D1 D1 D1 D0 D1 D1 D1 D0 break;
#define CS78 case 0x078:  D0 D0 D0 D1 D1 D1 D1 D0 break;
#define CS79 case 0x079:  D1 D0 D0 D1 D1 D1 D1 D0 break;
#define CS7A case 0x07A:  D0 D1 D0 D1 D1 D1 D1 D0 break;
#define CS7B case 0x07B:  D1 D1 D0 D1 D1 D1 D1 D0 break;
#define CS7C case 0x07C:  D0 D0 D1 D1 D1 D1 D1 D0 break;
#define CS7D case 0x07D:  D1 D0 D1 D1 D1 D1 D1 D0 break;
#define CS7E case 0x07E:  D0 D1 D1 D1 D1 D1 D1 D0 break;
#define CS7F case 0x07F:  D1 D1 D1 D1 D1 D1 D1 D0 break;
#define CS80 case 0x080:  D0 D0 D0 D0 D0 D0 D0 D1 break;
#define CS81 case 0x081:  D1 D0 D0 D0 D0 D0 D0 D1 break;
#define CS82 case 0x082:  D0 D1 D0 D0 D0 D0 D0 D1 break;
#define CS83 case 0x083:  D1 D1 D0 D0 D0 D0 D0 D1 break;
#define CS84 case 0x084:  D0 D0 D1 D0 D0 D0 D0 D1 break;
#define CS85 case 0x085:  D1 D0 D1 D0 D0 D0 D0 D1 break;
#define CS86 case 0x086:  D0 D1 D1 D0 D0 D0 D0 D1 break;
#define CS87 case 0x087:  D1 D1 D1 D0 D0 D0 D0 D1 break;
#define CS88 case 0x088:  D0 D0 D0 D1 D0 D0 D0 D1 break;
#define CS89 case 0x089:  D1 D0 D0 D1 D0 D0 D0 D1 break;
#define CS8A case 0x08A:  D0 D1 D0 D1 D0 D0 D0 D1 break;
#define CS8B case 0x08B:  D1 D1 D0 D1 D0 D0 D0 D1 break;
#define CS8C case 0x08C:  D0 D0 D1 D1 D0 D0 D0 D1 break;
#define CS8D case 0x08D:  D1 D0 D1 D1 D0 D0 D0 D1 break;
#define CS8E case 0x08E:  D0 D1 D1 D1 D0 D0 D0 D1 break;
#define CS8F case 0x08F:  D1 D1 D1 D1 D0 D0 D0 D1 break;
#define CS90 case 0x090:  D0 D0 D0 D0 D1 D0 D0 D1 break;
#define CS91 case 0x091:  D1 D0 D0 D0 D1 D0 D0 D1 break;
#define CS92 case 0x092:  D0 D1 D0 D0 D1 D0 D0 D1 break;
#define CS93 case 0x093:  D1 D1 D0 D0 D1 D0 D0 D1 break;
#define CS94 case 0x094:  D0 D0 D1 D0 D1 D0 D0 D1 break;
#define CS95 case 0x095:  D1 D0 D1 D0 D1 D0 D0 D1 break;
#define CS96 case 0x096:  D0 D1 D1 D0 D1 D0 D0 D1 break;
#define CS97 case 0x097:  D1 D1 D1 D0 D1 D0 D0 D1 break;
#define CS98 case 0x098:  D0 D0 D0 D1 D1 D0 D0 D1 break;
#define CS99 case 0x099:  D1 D0 D0 D1 D1 D0 D0 D1 break;
#define CS9A case 0x09A:  D0 D1 D0 D1 D1 D0 D0 D1 break;
#define CS9B case 0x09B:  D1 D1 D0 D1 D1 D0 D0 D1 break;
#define CS9C case 0x09C:  D0 D0 D1 D1 D1 D0 D0 D1 break;
#define CS9D case 0x09D:  D1 D0 D1 D1 D1 D0 D0 D1 break;
#define CS9E case 0x09E:  D0 D1 D1 D1 D1 D0 D0 D1 break;
#define CS9F case 0x09F:  D1 D1 D1 D1 D1 D0 D0 D1 break;
#define CSA0 case 0x0A0:  D0 D0 D0 D0 D0 D1 D0 D1 break;
#define CSA1 case 0x0A1:  D1 D0 D0 D0 D0 D1 D0 D1 break;
#define CSA2 case 0x0A2:  D0 D1 D0 D0 D0 D1 D0 D1 break;
#define CSA3 case 0x0A3:  D1 D1 D0 D0 D0 D1 D0 D1 break;
#define CSA4 case 0x0A4:  D0 D0 D1 D0 D0 D1 D0 D1 break;
#define CSA5 case 0x0A5:  D1 D0 D1 D0 D0 D1 D0 D1 break;
#define CSA6 case 0x0A6:  D0 D1 D1 D0 D0 D1 D0 D1 break;
#define CSA7 case 0x0A7:  D1 D1 D1 D0 D0 D1 D0 D1 break;
#define CSA8 case 0x0A8:  D0 D0 D0 D1 D0 D1 D0 D1 break;
#define CSA9 case 0x0A9:  D1 D0 D0 D1 D0 D1 D0 D1 break;
#define CSAA case 0x0AA:  D0 D1 D0 D1 D0 D1 D0 D1 break;
#define CSAB case 0x0AB:  D1 D1 D0 D1 D0 D1 D0 D1 break;
#define CSAC case 0x0AC:  D0 D0 D1 D1 D0 D1 D0 D1 break;
#define CSAD case 0x0AD:  D1 D0 D1 D1 D0 D1 D0 D1 break;
#define CSAE case 0x0AE:  D0 D1 D1 D1 D0 D1 D0 D1 break;
#define CSAF case 0x0AF:  D1 D1 D1 D1 D0 D1 D0 D1 break;
#define CSB0 case 0x0B0:  D0 D0 D0 D0 D1 D1 D0 D1 break;
#define CSB1 case 0x0B1:  D1 D0 D0 D0 D1 D1 D0 D1 break;
#define CSB2 case 0x0B2:  D0 D1 D0 D0 D1 D1 D0 D1 break;
#define CSB3 case 0x0B3:  D1 D1 D0 D0 D1 D1 D0 D1 break;
#define CSB4 case 0x0B4:  D0 D0 D1 D0 D1 D1 D0 D1 break;
#define CSB5 case 0x0B5:  D1 D0 D1 D0 D1 D1 D0 D1 break;
#define CSB6 case 0x0B6:  D0 D1 D1 D0 D1 D1 D0 D1 break;
#define CSB7 case 0x0B7:  D1 D1 D1 D0 D1 D1 D0 D1 break;
#define CSB8 case 0x0B8:  D0 D0 D0 D1 D1 D1 D0 D1 break;
#define CSB9 case 0x0B9:  D1 D0 D0 D1 D1 D1 D0 D1 break;
#define CSBA case 0x0BA:  D0 D1 D0 D1 D1 D1 D0 D1 break;
#define CSBB case 0x0BB:  D1 D1 D0 D1 D1 D1 D0 D1 break;
#define CSBC case 0x0BC:  D0 D0 D1 D1 D1 D1 D0 D1 break;
#define CSBD case 0x0BD:  D1 D0 D1 D1 D1 D1 D0 D1 break;
#define CSBE case 0x0BE:  D0 D1 D1 D1 D1 D1 D0 D1 break;
#define CSBF case 0x0BF:  D1 D1 D1 D1 D1 D1 D0 D1 break;
#define CSC0 case 0x0C0:  D0 D0 D0 D0 D0 D0 D1 D1 break;
#define CSC1 case 0x0C1:  D1 D0 D0 D0 D0 D0 D1 D1 break;
#define CSC2 case 0x0C2:  D0 D1 D0 D0 D0 D0 D1 D1 break;
#define CSC3 case 0x0C3:  D1 D1 D0 D0 D0 D0 D1 D1 break;
#define CSC4 case 0x0C4:  D0 D0 D1 D0 D0 D0 D1 D1 break;
#define CSC5 case 0x0C5:  D1 D0 D1 D0 D0 D0 D1 D1 break;
#define CSC6 case 0x0C6:  D0 D1 D1 D0 D0 D0 D1 D1 break;
#define CSC7 case 0x0C7:  D1 D1 D1 D0 D0 D0 D1 D1 break;
#define CSC8 case 0x0C8:  D0 D0 D0 D1 D0 D0 D1 D1 break;
#define CSC9 case 0x0C9:  D1 D0 D0 D1 D0 D0 D1 D1 break;
#define CSCA case 0x0CA:  D0 D1 D0 D1 D0 D0 D1 D1 break;
#define CSCB case 0x0CB:  D1 D1 D0 D1 D0 D0 D1 D1 break;
#define CSCC case 0x0CC:  D0 D0 D1 D1 D0 D0 D1 D1 break;
#define CSCD case 0x0CD:  D1 D0 D1 D1 D0 D0 D1 D1 break;
#define CSCE case 0x0CE:  D0 D1 D1 D1 D0 D0 D1 D1 break;
#define CSCF case 0x0CF:  D1 D1 D1 D1 D0 D0 D1 D1 break;
#define CSD0 case 0x0D0:  D0 D0 D0 D0 D1 D0 D1 D1 break;
#define CSD1 case 0x0D1:  D1 D0 D0 D0 D1 D0 D1 D1 break;
#define CSD2 case 0x0D2:  D0 D1 D0 D0 D1 D0 D1 D1 break;
#define CSD3 case 0x0D3:  D1 D1 D0 D0 D1 D0 D1 D1 break;
#define CSD4 case 0x0D4:  D0 D0 D1 D0 D1 D0 D1 D1 break;
#define CSD5 case 0x0D5:  D1 D0 D1 D0 D1 D0 D1 D1 break;
#define CSD6 case 0x0D6:  D0 D1 D1 D0 D1 D0 D1 D1 break;
#define CSD7 case 0x0D7:  D1 D1 D1 D0 D1 D0 D1 D1 break;
#define CSD8 case 0x0D8:  D0 D0 D0 D1 D1 D0 D1 D1 break;
#define CSD9 case 0x0D9:  D1 D0 D0 D1 D1 D0 D1 D1 break;
#define CSDA case 0x0DA:  D0 D1 D0 D1 D1 D0 D1 D1 break;
#define CSDB case 0x0DB:  D1 D1 D0 D1 D1 D0 D1 D1 break;
#define CSDC case 0x0DC:  D0 D0 D1 D1 D1 D0 D1 D1 break;
#define CSDD case 0x0DD:  D1 D0 D1 D1 D1 D0 D1 D1 break;
#define CSDE case 0x0DE:  D0 D1 D1 D1 D1 D0 D1 D1 break;
#define CSDF case 0x0DF:  D1 D1 D1 D1 D1 D0 D1 D1 break;
#define CSE0 case 0x0E0:  D0 D0 D0 D0 D0 D1 D1 D1 break;
#define CSE1 case 0x0E1:  D1 D0 D0 D0 D0 D1 D1 D1 break;
#define CSE2 case 0x0E2:  D0 D1 D0 D0 D0 D1 D1 D1 break;
#define CSE3 case 0x0E3:  D1 D1 D0 D0 D0 D1 D1 D1 break;
#define CSE4 case 0x0E4:  D0 D0 D1 D0 D0 D1 D1 D1 break;
#define CSE5 case 0x0E5:  D1 D0 D1 D0 D0 D1 D1 D1 break;
#define CSE6 case 0x0E6:  D0 D1 D1 D0 D0 D1 D1 D1 break;
#define CSE7 case 0x0E7:  D1 D1 D1 D0 D0 D1 D1 D1 break;
#define CSE8 case 0x0E8:  D0 D0 D0 D1 D0 D1 D1 D1 break;
#define CSE9 case 0x0E9:  D1 D0 D0 D1 D0 D1 D1 D1 break;
#define CSEA case 0x0EA:  D0 D1 D0 D1 D0 D1 D1 D1 break;
#define CSEB case 0x0EB:  D1 D1 D0 D1 D0 D1 D1 D1 break;
#define CSEC case 0x0EC:  D0 D0 D1 D1 D0 D1 D1 D1 break;
#define CSED case 0x0ED:  D1 D0 D1 D1 D0 D1 D1 D1 break;
#define CSEE case 0x0EE:  D0 D1 D1 D1 D0 D1 D1 D1 break;
#define CSEF case 0x0EF:  D1 D1 D1 D1 D0 D1 D1 D1 break;
#define CSF0 case 0x0F0:  D0 D0 D0 D0 D1 D1 D1 D1 break;
#define CSF1 case 0x0F1:  D1 D0 D0 D0 D1 D1 D1 D1 break;
#define CSF2 case 0x0F2:  D0 D1 D0 D0 D1 D1 D1 D1 break;
#define CSF3 case 0x0F3:  D1 D1 D0 D0 D1 D1 D1 D1 break;
#define CSF4 case 0x0F4:  D0 D0 D1 D0 D1 D1 D1 D1 break;
#define CSF5 case 0x0F5:  D1 D0 D1 D0 D1 D1 D1 D1 break;
#define CSF6 case 0x0F6:  D0 D1 D1 D0 D1 D1 D1 D1 break;
#define CSF7 case 0x0F7:  D1 D1 D1 D0 D1 D1 D1 D1 break;
#define CSF8 case 0x0F8:  D0 D0 D0 D1 D1 D1 D1 D1 break;
#define CSF9 case 0x0F9:  D1 D0 D0 D1 D1 D1 D1 D1 break;
#define CSFA case 0x0FA:  D0 D1 D0 D1 D1 D1 D1 D1 break;
#define CSFB case 0x0FB:  D1 D1 D0 D1 D1 D1 D1 D1 break;
#define CSFC case 0x0FC:  D0 D0 D1 D1 D1 D1 D1 D1 break;
#define CSFD case 0x0FD:  D1 D0 D1 D1 D1 D1 D1 D1 break;
#define CSFE case 0x0FE:  D0 D1 D1 D1 D1 D1 D1 D1 break;
#define CSFF case 0x0FF:  D1 D1 D1 D1 D1 D1 D1 D1 break;
#define CASE256 \
  CS00 CS01 CS02 CS03 CS04 CS05 CS06 CS07 CS08 CS09 CS0A CS0B CS0C CS0D CS0E CS0F \
  CS10 CS11 CS12 CS13 CS14 CS15 CS16 CS17 CS18 CS19 CS1A CS1B CS1C CS1D CS1E CS1F \
  CS20 CS21 CS22 CS23 CS24 CS25 CS26 CS27 CS28 CS29 CS2A CS2B CS2C CS2D CS2E CS2F \
  CS30 CS31 CS32 CS33 CS34 CS35 CS36 CS37 CS38 CS39 CS3A CS3B CS3C CS3D CS3E CS3F \
  CS40 CS41 CS42 CS43 CS44 CS45 CS46 CS47 CS48 CS49 CS4A CS4B CS4C CS4D CS4E CS4F \
  CS50 CS51 CS52 CS53 CS54 CS55 CS56 CS57 CS58 CS59 CS5A CS5B CS5C CS5D CS5E CS5F \
  CS60 CS61 CS62 CS63 CS64 CS65 CS66 CS67 CS68 CS69 CS6A CS6B CS6C CS6D CS6E CS6F \
  CS70 CS71 CS72 CS73 CS74 CS75 CS76 CS77 CS78 CS79 CS7A CS7B CS7C CS7D CS7E CS7F \
  CS80 CS81 CS82 CS83 CS84 CS85 CS86 CS87 CS88 CS89 CS8A CS8B CS8C CS8D CS8E CS8F \
  CS90 CS91 CS92 CS93 CS94 CS95 CS96 CS97 CS98 CS99 CS9A CS9B CS9C CS9D CS9E CS9F \
  CSA0 CSA1 CSA2 CSA3 CSA4 CSA5 CSA6 CSA7 CSA8 CSA9 CSAA CSAB CSAC CSAD CSAE CSAF \
  CSB0 CSB1 CSB2 CSB3 CSB4 CSB5 CSB6 CSB7 CSB8 CSB9 CSBA CSBB CSBC CSBD CSBE CSBF \
  CSC0 CSC1 CSC2 CSC3 CSC4 CSC5 CSC6 CSC7 CSC8 CSC9 CSCA CSCB CSCC CSCD CSCE CSCF \
  CSD0 CSD1 CSD2 CSD3 CSD4 CSD5 CSD6 CSD7 CSD8 CSD9 CSDA CSDB CSDC CSDD CSDE CSDF \
  CSE0 CSE1 CSE2 CSE3 CSE4 CSE5 CSE6 CSE7 CSE8 CSE9 CSEA CSEB CSEC CSED CSEE CSEF \
  CSF0 CSF1 CSF2 CSF3 CSF4 CSF5 CSF6 CSF7 CSF8 CSF9 CSFA CSFB CSFC CSFD CSFE CSFF \
;

void __attribute__ ((noinline)) w32(unsigned int *pi,unsigned int v)
{
	*pi=v;
	return;
}
int do_fpga(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])  
{ 
	int i;
	int len;
	unsigned int *p32data,*p32dir;
	volatile unsigned int *p32status;
	unsigned int v_dir,v_data,v_status;
	unsigned int v_data0,v_data1,v_dataLH,v_dataHH,v_dataLL,v_dataHL;
	char *p,c;
	volatile unsigned int *pmux70,*pmux71,*pmux72,*pmux76,*pmux77;//gpio7_0,gpio7_1..............
#if 1
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

	*pmux70 = 0x1f0f9;//0x1b0b0;
	*pmux71 = 0x1f0f9;
	*pmux72 = 0x1f0f9;
	*pmux76 = 0x1f0f9;
	*pmux77 = 0x1f0f9;
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
		if(0==(0x0fffff & i))printf(" loop i : %x\n",i);
		c = *p++;
		switch(c&0x0ff){
			CASE256
			default:break;
		}
	}
    printf("\n wait.done \n");
    for(i=0;;i++){
      v_status = *p32status;
      printf("wait.status.high    status: %08x   bit.status %d\r",v_status,v_status & 1);
      if(0x81==(0x81&v_status))break;
      //if(0==(i&0x0fffff))printf(" %d status: 0x%08x\n",i,v_status);

      //output_d(0);
	  *p32data=v_dataLL;
	  *p32data=v_dataHL;
	  //w32(p32data,v_dataLL);
	  //w32(p32data,v_dataHL);
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
