/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "D:/ZJU/CS/CA/Labs/Lab2/Lab2_mixup_reg_fork_good_sw_for/src/cpu/add4beqbne.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {14, 0};



static void Cont_25_0(char *t0)
{
    char t4[8];
    char t7[8];
    char t10[8];
    char t18[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;

LAB0:    t1 = (t0 + 2528U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(25, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    t5 = (t0 + 1208U);
    t6 = *((char **)t5);
    t5 = ((char*)((ng2)));
    t8 = (t0 + 1208U);
    t9 = *((char **)t8);
    memset(t10, 0, 8);
    t8 = (t10 + 4);
    t11 = (t9 + 4);
    t12 = *((unsigned int *)t9);
    t13 = (t12 >> 15);
    t14 = (t13 & 1);
    *((unsigned int *)t10) = t14;
    t15 = *((unsigned int *)t11);
    t16 = (t15 >> 15);
    t17 = (t16 & 1);
    *((unsigned int *)t8) = t17;
    xsi_vlog_mul_concat(t7, 14, 1, t5, 1U, t10, 1);
    xsi_vlogtype_concat(t4, 32, 32, 3U, t7, 14, t6, 16, t2, 2);
    memset(t18, 0, 8);
    xsi_vlog_unsigned_add(t18, 32, t3, 32, t4, 32);
    t19 = (t0 + 2928);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    memcpy(t23, t18, 8);
    xsi_driver_vfirst_trans(t19, 0, 31);
    t24 = (t0 + 2848);
    *((int *)t24) = 1;

LAB1:    return;
}


extern void work_m_00000000001934643685_1788697866_init()
{
	static char *pe[] = {(void *)Cont_25_0};
	xsi_register_didat("work_m_00000000001934643685_1788697866", "isim/sim_mips_isim_beh.exe.sim/work/m_00000000001934643685_1788697866.didat");
	xsi_register_executes(pe);
}
