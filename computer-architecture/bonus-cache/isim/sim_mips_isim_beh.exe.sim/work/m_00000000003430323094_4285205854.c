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
static const char *ng0 = "E:/ZJU/CS/CA/Labs/Bonus/Cache/src/cpu/debug_datapath.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static int ng3[] = {2, 0};
static int ng4[] = {4, 0};
static int ng5[] = {3, 0};
static int ng6[] = {5, 0};
static int ng7[] = {6, 0};
static int ng8[] = {7, 0};
static int ng9[] = {8, 0};
static unsigned int ng10[] = {0U, 0U};
static int ng11[] = {9, 0};
static int ng12[] = {10, 0};
static int ng13[] = {11, 0};
static int ng14[] = {12, 0};
static int ng15[] = {13, 0};
static int ng16[] = {14, 0};
static int ng17[] = {15, 0};
static int ng18[] = {16, 0};
static int ng19[] = {17, 0};
static int ng20[] = {18, 0};
static int ng21[] = {19, 0};
static int ng22[] = {20, 0};
static int ng23[] = {21, 0};
static int ng24[] = {22, 0};
static int ng25[] = {23, 0};
static unsigned int ng26[] = {4294967295U, 0U};



static void Always_39_0(char *t0)
{
    char t4[8];
    char t18[8];
    char t19[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    int t15;
    char *t16;
    char *t17;

LAB0:    t1 = (t0 + 6848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(39, ng0);
    t2 = (t0 + 7416);
    *((int *)t2) = 1;
    t3 = (t0 + 6880);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(39, ng0);

LAB5:    xsi_set_current_line(40, ng0);
    t5 = (t0 + 1048U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t4 + 4);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t6);
    t9 = (t8 >> 0);
    *((unsigned int *)t4) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 0);
    *((unsigned int *)t5) = t11;
    t12 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t12 & 31U);
    t13 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t13 & 31U);

LAB6:    t14 = ((char*)((ng1)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t14, 32);
    if (t15 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng2)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng3)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng5)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng4)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng6)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng7)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng8)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng9)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng11)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng12)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng13)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng14)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng15)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng16)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng17)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng18)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng19)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng20)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB43;

LAB44:    t2 = ((char*)((ng21)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB45;

LAB46:    t2 = ((char*)((ng22)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB47;

LAB48:    t2 = ((char*)((ng23)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB49;

LAB50:    t2 = ((char*)((ng24)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB51;

LAB52:    t2 = ((char*)((ng25)));
    t15 = xsi_vlog_unsigned_case_compare(t4, 32, t2, 32);
    if (t15 == 1)
        goto LAB53;

LAB54:
LAB56:
LAB55:    xsi_set_current_line(65, ng0);
    t2 = ((char*)((ng26)));
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 32, 0LL);

LAB57:    goto LAB2;

LAB7:    xsi_set_current_line(41, ng0);
    t16 = (t0 + 1368U);
    t17 = *((char **)t16);
    t16 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t16, t17, 0, 0, 32, 0LL);
    goto LAB57;

LAB9:    xsi_set_current_line(42, ng0);
    t3 = (t0 + 1528U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB11:    xsi_set_current_line(43, ng0);
    t3 = (t0 + 1688U);
    t5 = *((char **)t3);
    t3 = ((char*)((ng4)));
    memset(t18, 0, 8);
    xsi_vlog_unsigned_minus(t18, 32, t5, 32, t3, 32);
    t6 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t6, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB13:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 2328U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB15:    xsi_set_current_line(45, ng0);
    t3 = (t0 + 1848U);
    t5 = *((char **)t3);
    t3 = ((char*)((ng4)));
    memset(t18, 0, 8);
    xsi_vlog_unsigned_minus(t18, 32, t5, 32, t3, 32);
    t6 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t6, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB17:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 2488U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB19:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 2008U);
    t5 = *((char **)t3);
    t3 = ((char*)((ng4)));
    memset(t18, 0, 8);
    xsi_vlog_unsigned_minus(t18, 32, t5, 32, t3, 32);
    t6 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t6, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB21:    xsi_set_current_line(48, ng0);
    t3 = (t0 + 2648U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB23:    xsi_set_current_line(49, ng0);
    t3 = (t0 + 2328U);
    t5 = *((char **)t3);
    memset(t19, 0, 8);
    t3 = (t19 + 4);
    t6 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 21);
    *((unsigned int *)t19) = t9;
    t10 = *((unsigned int *)t6);
    t11 = (t10 >> 21);
    *((unsigned int *)t3) = t11;
    t12 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t12 & 31U);
    t13 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t13 & 31U);
    t7 = ((char*)((ng10)));
    xsi_vlogtype_concat(t18, 32, 32, 2U, t7, 27, t19, 5);
    t14 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t14, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB25:    xsi_set_current_line(50, ng0);
    t3 = (t0 + 2968U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB27:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 2328U);
    t5 = *((char **)t3);
    memset(t19, 0, 8);
    t3 = (t19 + 4);
    t6 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 16);
    *((unsigned int *)t19) = t9;
    t10 = *((unsigned int *)t6);
    t11 = (t10 >> 16);
    *((unsigned int *)t3) = t11;
    t12 = *((unsigned int *)t19);
    *((unsigned int *)t19) = (t12 & 31U);
    t13 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t13 & 31U);
    t7 = ((char*)((ng10)));
    xsi_vlogtype_concat(t18, 32, 32, 2U, t7, 27, t19, 5);
    t14 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t14, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB29:    xsi_set_current_line(52, ng0);
    t3 = (t0 + 3128U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB31:    xsi_set_current_line(53, ng0);
    t3 = (t0 + 3288U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB33:    xsi_set_current_line(54, ng0);
    t3 = (t0 + 3448U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB35:    xsi_set_current_line(55, ng0);
    t3 = (t0 + 3608U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB37:    xsi_set_current_line(56, ng0);
    t3 = (t0 + 3768U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB39:    xsi_set_current_line(57, ng0);
    t3 = ((char*)((ng1)));
    t5 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t5, t3, 0, 0, 32, 0LL);
    goto LAB57;

LAB41:    xsi_set_current_line(58, ng0);
    t3 = ((char*)((ng1)));
    t5 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t5, t3, 0, 0, 32, 0LL);
    goto LAB57;

LAB43:    xsi_set_current_line(59, ng0);
    t3 = (t0 + 5368U);
    t5 = *((char **)t3);
    t3 = ((char*)((ng10)));
    t6 = (t0 + 5528U);
    t7 = *((char **)t6);
    t6 = ((char*)((ng10)));
    t14 = (t0 + 5208U);
    t16 = *((char **)t14);
    t14 = ((char*)((ng10)));
    xsi_vlogtype_concat(t18, 32, 32, 6U, t14, 19, t16, 1, t6, 7, t7, 1, t3, 3, t5, 1);
    t17 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t17, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB45:    xsi_set_current_line(60, ng0);
    t3 = (t0 + 4408U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB47:    xsi_set_current_line(61, ng0);
    t3 = (t0 + 4568U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB49:    xsi_set_current_line(62, ng0);
    t3 = (t0 + 4248U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

LAB51:    xsi_set_current_line(63, ng0);
    t3 = (t0 + 4728U);
    t5 = *((char **)t3);
    t3 = ((char*)((ng10)));
    xsi_vlogtype_concat(t18, 32, 32, 2U, t3, 27, t5, 5);
    t6 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t6, t18, 0, 0, 32, 0LL);
    goto LAB57;

LAB53:    xsi_set_current_line(64, ng0);
    t3 = (t0 + 4888U);
    t5 = *((char **)t3);
    t3 = (t0 + 5928);
    xsi_vlogvar_wait_assign_value(t3, t5, 0, 0, 32, 0LL);
    goto LAB57;

}

static void Cont_69_1(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;

LAB0:    t1 = (t0 + 7096U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(69, ng0);
    t2 = (t0 + 1048U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 5);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 5);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    memset(t4, 0, 8);
    t14 = (t6 + 4);
    t15 = *((unsigned int *)t14);
    t16 = (~(t15));
    t17 = *((unsigned int *)t6);
    t18 = (t17 & t16);
    t19 = (t18 & 1U);
    if (t19 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t14) != 0)
        goto LAB6;

LAB7:    t21 = (t4 + 4);
    t22 = *((unsigned int *)t4);
    t23 = *((unsigned int *)t21);
    t24 = (t22 || t23);
    if (t24 > 0)
        goto LAB8;

LAB9:    t28 = *((unsigned int *)t4);
    t29 = (~(t28));
    t30 = *((unsigned int *)t21);
    t31 = (t29 || t30);
    if (t31 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t21) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t33, 8);

LAB16:    t32 = (t0 + 7512);
    t34 = (t32 + 56U);
    t35 = *((char **)t34);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    memcpy(t37, t3, 8);
    xsi_driver_vfirst_trans(t32, 0, 31);
    t38 = (t0 + 7432);
    *((int *)t38) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t20 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB7;

LAB8:    t25 = (t0 + 5928);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    goto LAB9;

LAB10:    t32 = (t0 + 5048U);
    t33 = *((char **)t32);
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 32, t27, 32, t33, 32);
    goto LAB16;

LAB14:    memcpy(t3, t27, 8);
    goto LAB16;

}


extern void work_m_00000000003430323094_4285205854_init()
{
	static char *pe[] = {(void *)Always_39_0,(void *)Cont_69_1};
	xsi_register_didat("work_m_00000000003430323094_4285205854", "isim/sim_mips_isim_beh.exe.sim/work/m_00000000003430323094_4285205854.didat");
	xsi_register_executes(pe);
}
