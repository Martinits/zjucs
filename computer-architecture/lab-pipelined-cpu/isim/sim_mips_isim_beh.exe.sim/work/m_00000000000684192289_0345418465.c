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
static const char *ng0 = "D:/ZJU/CS/CA/Labs/Lab2/Lab2_mixup_reg_fork_good_sw_for/src/cpu/IF_ID.v";
static int ng1[] = {0, 0, 0, 0, 0, 0};
static unsigned int ng2[] = {1U, 0U};



static void Always_28_0(char *t0)
{
    char t14[24];
    char t15[8];
    char t28[24];
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
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;

LAB0:    t1 = (t0 + 3328U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 3648);
    *((int *)t2) = 1;
    t3 = (t0 + 3360);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(28, ng0);

LAB5:    xsi_set_current_line(29, ng0);
    t4 = (t0 + 1528U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 1688U);
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

LAB6:    xsi_set_current_line(29, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 2408);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 33, 0LL);
    t13 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t13, t11, 33, 0, 32, 0LL);
    goto LAB8;

LAB9:    xsi_set_current_line(30, ng0);
    t4 = (t0 + 1848U);
    t5 = *((char **)t4);
    memset(t15, 0, 8);
    t4 = (t5 + 4);
    t16 = *((unsigned int *)t4);
    t17 = (~(t16));
    t18 = *((unsigned int *)t5);
    t19 = (t18 & t17);
    t20 = (t19 & 1U);
    if (t20 != 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) != 0)
        goto LAB14;

LAB15:    t12 = (t15 + 4);
    t21 = *((unsigned int *)t15);
    t22 = *((unsigned int *)t12);
    t23 = (t21 || t22);
    if (t23 > 0)
        goto LAB16;

LAB17:    t24 = *((unsigned int *)t15);
    t25 = (~(t24));
    t26 = *((unsigned int *)t12);
    t27 = (t25 || t26);
    if (t27 > 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t12) > 0)
        goto LAB20;

LAB21:    if (*((unsigned int *)t15) > 0)
        goto LAB22;

LAB23:    memcpy(t14, t28, 24);

LAB24:    t31 = (t0 + 2408);
    xsi_vlogvar_wait_assign_value(t31, t14, 0, 0, 33, 0LL);
    t33 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t33, t14, 33, 0, 32, 0LL);
    goto LAB11;

LAB12:    *((unsigned int *)t15) = 1;
    goto LAB15;

LAB14:    t11 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB15;

LAB16:    t13 = ((char*)((ng1)));
    goto LAB17;

LAB18:    t29 = (t0 + 1208U);
    t30 = *((char **)t29);
    t29 = ((char*)((ng2)));
    t31 = (t0 + 1048U);
    t32 = *((char **)t31);
    xsi_vlogtype_concat(t28, 65, 65, 3U, t32, 32, t29, 1, t30, 32);
    goto LAB19;

LAB20:    xsi_vlog_unsigned_bit_combine(t14, 65, t13, 65, t28, 65);
    goto LAB24;

LAB22:    memcpy(t14, t13, 24);
    goto LAB24;

}


extern void work_m_00000000000684192289_0345418465_init()
{
	static char *pe[] = {(void *)Always_28_0};
	xsi_register_didat("work_m_00000000000684192289_0345418465", "isim/sim_mips_isim_beh.exe.sim/work/m_00000000000684192289_0345418465.didat");
	xsi_register_executes(pe);
}
