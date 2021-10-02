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
static const char *ng0 = "E:/ZJU/CS/CA/Labs/Bonus/Cache/src/cpu/ID_EX.v";
static int ng1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



static void Always_31_0(char *t0)
{
    char t18[56];
    char t19[8];
    char t32[56];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    char *t39;
    char *t40;

LAB0:    t1 = (t0 + 4608U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(31, ng0);
    t2 = (t0 + 4928);
    *((int *)t2) = 1;
    t3 = (t0 + 4640);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(31, ng0);

LAB5:    xsi_set_current_line(32, ng0);
    t4 = (t0 + 2168U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(33, ng0);
    t2 = (t0 + 2328U);
    t3 = *((char **)t2);
    t2 = (t3 + 4);
    t6 = *((unsigned int *)t2);
    t7 = (~(t6));
    t8 = *((unsigned int *)t3);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB9;

LAB10:
LAB11:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(32, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 3368);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 32, 0LL);
    t13 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t13, t11, 32, 0, 32, 0LL);
    t14 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t14, t11, 64, 0, 32, 0LL);
    t15 = (t0 + 3688);
    xsi_vlogvar_wait_assign_value(t15, t11, 96, 0, 36, 0LL);
    t16 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t16, t11, 132, 0, 33, 0LL);
    t17 = (t0 + 2888);
    xsi_vlogvar_wait_assign_value(t17, t11, 165, 0, 32, 0LL);
    goto LAB8;

LAB9:    xsi_set_current_line(33, ng0);
    t4 = (t0 + 2488U);
    t5 = *((char **)t4);
    memset(t19, 0, 8);
    t4 = (t5 + 4);
    t20 = *((unsigned int *)t4);
    t21 = (~(t20));
    t22 = *((unsigned int *)t5);
    t23 = (t22 & t21);
    t24 = (t23 & 1U);
    if (t24 != 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) != 0)
        goto LAB14;

LAB15:    t12 = (t19 + 4);
    t25 = *((unsigned int *)t19);
    t26 = *((unsigned int *)t12);
    t27 = (t25 || t26);
    if (t27 > 0)
        goto LAB16;

LAB17:    t28 = *((unsigned int *)t19);
    t29 = (~(t28));
    t30 = *((unsigned int *)t12);
    t31 = (t29 || t30);
    if (t31 > 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t12) > 0)
        goto LAB20;

LAB21:    if (*((unsigned int *)t19) > 0)
        goto LAB22;

LAB23:    memcpy(t18, t32, 56);

LAB24:    t14 = (t0 + 3368);
    xsi_vlogvar_wait_assign_value(t14, t18, 0, 0, 32, 0LL);
    t36 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t36, t18, 32, 0, 32, 0LL);
    t37 = (t0 + 3048);
    xsi_vlogvar_wait_assign_value(t37, t18, 64, 0, 32, 0LL);
    t38 = (t0 + 3688);
    xsi_vlogvar_wait_assign_value(t38, t18, 96, 0, 36, 0LL);
    t39 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t39, t18, 132, 0, 33, 0LL);
    t40 = (t0 + 2888);
    xsi_vlogvar_wait_assign_value(t40, t18, 165, 0, 32, 0LL);
    goto LAB11;

LAB12:    *((unsigned int *)t19) = 1;
    goto LAB15;

LAB14:    t11 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB15;

LAB16:    t13 = ((char*)((ng1)));
    goto LAB17;

LAB18:    t14 = (t0 + 1528U);
    t15 = *((char **)t14);
    t14 = (t0 + 1368U);
    t16 = *((char **)t14);
    t14 = (t0 + 1208U);
    t17 = *((char **)t14);
    t14 = (t0 + 1848U);
    t33 = *((char **)t14);
    t14 = (t0 + 1688U);
    t34 = *((char **)t14);
    t14 = (t0 + 1048U);
    t35 = *((char **)t14);
    xsi_vlogtype_concat(t32, 197, 197, 6U, t35, 32, t34, 33, t33, 36, t17, 32, t16, 32, t15, 32);
    goto LAB19;

LAB20:    xsi_vlog_unsigned_bit_combine(t18, 197, t13, 197, t32, 197);
    goto LAB24;

LAB22:    memcpy(t18, t13, 56);
    goto LAB24;

}


extern void work_m_00000000003514620691_0103510313_init()
{
	static char *pe[] = {(void *)Always_31_0};
	xsi_register_didat("work_m_00000000003514620691_0103510313", "isim/sim_mips_isim_beh.exe.sim/work/m_00000000003514620691_0103510313.didat");
	xsi_register_executes(pe);
}
