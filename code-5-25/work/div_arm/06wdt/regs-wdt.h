/***************************
 * 看门狗硬件的寄存器头文件
 * 头文件中一般包含寄存器的偏移，以及控制寄存器的位定义
 * Author: zht
 * Date: 2015-09-08
 ****************************/
#ifndef __REGS_WDT_H
#define __REGS_WDT_H

//定义寄存器的偏移
#define WTCON		0x0
#define WTDAT		0x4
#define WTCNT		0x8
#define WTCLRINT	0xC

//WTCON寄存器的位定义
#define WTCON_RSTEN		(0x1<<0)
#define WTCON_INTEN		(0x1<<2)
#define WTCON_DIVMASK	(0x3<<3)
#define WTCON_DIV16		(0<<3)
#define WTCON_DIV32		(1<<3)
#define WTCON_DIV64		(2<<3)
#define WTCON_DIV128	(3<<3)
#define WTCON_ENABLE	(1<<5)
#define WTCON_PRESCMASK	(0xFF<<8)
#define WTCON_PRESC(x)	((x)<<8)

/* 如何将分频比设定为100
 * value = readl(vir_base+WTCON);
 * value &= ~(WTCON_PRESCMASK);
 * value |= WTCON_PRESC(99);
 * writel(value, vir_base+WTCON);
 */

//C代码中用到的私有结构体等，也可以写在头文件中

#endif //__REGS_WDT_H

