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
static const char *ng0 = "E:/ZJU/CS/CA/Labs/Bonus/Cache/src/cpu/ALU.v";
static int ng1[] = {32, 0};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {1U, 0U};
static unsigned int ng4[] = {2U, 0U};
static unsigned int ng5[] = {3U, 0U};
static unsigned int ng6[] = {4U, 0U};
static unsigned int ng7[] = {5U, 0U};
static unsigned int ng8[] = {6U, 0U};
static unsigned int ng9[] = {7U, 0U};
static unsigned int ng10[] = {8U, 0U};
static unsigned int ng11[] = {9U, 0U};
static unsigned int ng12[] = {10U, 0U};
static unsigned int ng13[] = {11U, 0U};
static unsigned int ng14[] = {12U, 0U};
static unsigned int ng15[] = {13U, 0U};
static unsigned int ng16[] = {14U, 0U};
static unsigned int ng17[] = {15U, 0U};



static void Cont_28_0(char *t0)
{
    char t3[16];
    char t5[8];
    char t8[8];
    char t18[16];
    char *t1;
    char *t2;
    char *t4;
    char *t6;
    char *t7;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    char *t17;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;

LAB0:    t1 = (t0 + 3168U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(28, ng0);
    t2 = (t0 + 1208U);
    t4 = *((char **)t2);
    t2 = ((char*)((ng1)));
    t6 = (t0 + 1208U);
    t7 = *((char **)t6);
    memset(t8, 0, 8);
    t6 = (t8 + 4);
    t9 = (t7 + 4);
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 31);
    t12 = (t11 & 1);
    *((unsigned int *)t8) = t12;
    t13 = *((unsigned int *)t9);
    t14 = (t13 >> 31);
    t15 = (t14 & 1);
    *((unsigned int *)t6) = t15;
    xsi_vlog_mul_concat(t5, 32, 1, t2, 1U, t8, 1);
    xsi_vlogtype_concat(t3, 64, 64, 2U, t5, 32, t4, 32);
    t16 = (t0 + 1048U);
    t17 = *((char **)t16);
    xsi_vlog_unsigned_rshift(t18, 64, t3, 64, t17, 32);
    t16 = (t0 + 4096);
    t19 = (t16 + 56U);
    t20 = *((char **)t19);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    xsi_vlog_bit_copy(t22, 0, t18, 0, 64);
    xsi_driver_vfirst_trans(t16, 0, 63);
    t23 = (t0 + 3984);
    *((int *)t23) = 1;

LAB1:    return;
}

static void Always_30_1(char *t0)
{
    char t10[8];
    char t42[8];
    char t43[8];
    char t44[8];
    char t45[8];
    char t54[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    int t33;
    int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    char *t41;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    char *t51;
    char *t52;
    char *t53;
    char *t55;
    char *t56;

LAB0:    t1 = (t0 + 3416U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 4000);
    *((int *)t2) = 1;
    t3 = (t0 + 3448);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(30, ng0);

LAB5:    xsi_set_current_line(31, ng0);
    t4 = (t0 + 1368U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng2)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t4, 4);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng4)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng6)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng8)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng10)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng12)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng13)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng14)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng15)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng16)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng17)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 4, t2, 4);
    if (t6 == 1)
        goto LAB37;

LAB38:
LAB39:    goto LAB2;

LAB7:    xsi_set_current_line(32, ng0);
    t7 = (t0 + 1048U);
    t8 = *((char **)t7);
    t7 = (t0 + 1208U);
    t9 = *((char **)t7);
    t11 = *((unsigned int *)t8);
    t12 = *((unsigned int *)t9);
    t13 = (t11 & t12);
    *((unsigned int *)t10) = t13;
    t7 = (t8 + 4);
    t14 = (t9 + 4);
    t15 = (t10 + 4);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t14);
    t18 = (t16 | t17);
    *((unsigned int *)t15) = t18;
    t19 = *((unsigned int *)t15);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB40;

LAB41:
LAB42:    t41 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t41, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB9:    xsi_set_current_line(33, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    t11 = *((unsigned int *)t4);
    t12 = *((unsigned int *)t7);
    t13 = (t11 | t12);
    *((unsigned int *)t10) = t13;
    t3 = (t4 + 4);
    t8 = (t7 + 4);
    t9 = (t10 + 4);
    t16 = *((unsigned int *)t3);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    *((unsigned int *)t9) = t18;
    t19 = *((unsigned int *)t9);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB43;

LAB44:
LAB45:    t23 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t23, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB11:    xsi_set_current_line(34, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t43, 0, 8);
    xsi_vlog_signed_add(t43, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t43, 0, 0, 32, 0LL);
    goto LAB39;

LAB13:    xsi_set_current_line(35, ng0);
    t3 = (t0 + 1848U);
    t4 = *((char **)t3);
    memset(t10, 0, 8);
    t3 = (t10 + 4);
    t7 = (t4 + 4);
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 0);
    *((unsigned int *)t10) = t12;
    t13 = *((unsigned int *)t7);
    t16 = (t13 >> 0);
    *((unsigned int *)t3) = t16;
    t17 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t17 & 4294967295U);
    t18 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t18 & 4294967295U);
    t8 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t8, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB15:    xsi_set_current_line(36, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 1048U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_lshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB17:    xsi_set_current_line(37, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 1048U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_rshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB19:    xsi_set_current_line(38, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t43, 0, 8);
    xsi_vlog_signed_minus(t43, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t43, 0, 0, 32, 0LL);
    goto LAB39;

LAB21:    xsi_set_current_line(39, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t45, 0, 8);
    xsi_vlog_signed_less(t45, 32, t4, 32, t7, 32);
    memset(t42, 0, 8);
    t3 = (t45 + 4);
    t11 = *((unsigned int *)t3);
    t12 = (~(t11));
    t13 = *((unsigned int *)t45);
    t16 = (t13 & t12);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB46;

LAB47:    if (*((unsigned int *)t3) != 0)
        goto LAB48;

LAB49:    t9 = (t42 + 4);
    t18 = *((unsigned int *)t42);
    t19 = *((unsigned int *)t9);
    t20 = (t18 || t19);
    if (t20 > 0)
        goto LAB50;

LAB51:    t21 = *((unsigned int *)t42);
    t22 = (~(t21));
    t25 = *((unsigned int *)t9);
    t26 = (t22 || t25);
    if (t26 > 0)
        goto LAB52;

LAB53:    if (*((unsigned int *)t9) > 0)
        goto LAB54;

LAB55:    if (*((unsigned int *)t42) > 0)
        goto LAB56;

LAB57:    memcpy(t10, t15, 8);

LAB58:    t23 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t23, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB23:    xsi_set_current_line(40, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t43, 0, 8);
    xsi_vlog_unsigned_add(t43, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t43, 0, 0, 32, 0LL);
    goto LAB39;

LAB25:    xsi_set_current_line(41, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t43, 0, 8);
    xsi_vlog_unsigned_minus(t43, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t43, 0, 0, 32, 0LL);
    goto LAB39;

LAB27:    xsi_set_current_line(42, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    memset(t45, 0, 8);
    t3 = (t4 + 4);
    if (*((unsigned int *)t3) != 0)
        goto LAB60;

LAB59:    t8 = (t7 + 4);
    if (*((unsigned int *)t8) != 0)
        goto LAB60;

LAB63:    if (*((unsigned int *)t4) < *((unsigned int *)t7))
        goto LAB61;

LAB62:    memset(t42, 0, 8);
    t14 = (t45 + 4);
    t11 = *((unsigned int *)t14);
    t12 = (~(t11));
    t13 = *((unsigned int *)t45);
    t16 = (t13 & t12);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB64;

LAB65:    if (*((unsigned int *)t14) != 0)
        goto LAB66;

LAB67:    t23 = (t42 + 4);
    t18 = *((unsigned int *)t42);
    t19 = *((unsigned int *)t23);
    t20 = (t18 || t19);
    if (t20 > 0)
        goto LAB68;

LAB69:    t21 = *((unsigned int *)t42);
    t22 = (~(t21));
    t25 = *((unsigned int *)t23);
    t26 = (t22 || t25);
    if (t26 > 0)
        goto LAB70;

LAB71:    if (*((unsigned int *)t23) > 0)
        goto LAB72;

LAB73:    if (*((unsigned int *)t42) > 0)
        goto LAB74;

LAB75:    memcpy(t10, t41, 8);

LAB76:    t46 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t46, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB29:    xsi_set_current_line(43, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    t11 = *((unsigned int *)t4);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    *((unsigned int *)t10) = t13;
    t3 = (t4 + 4);
    t8 = (t7 + 4);
    t9 = (t10 + 4);
    t16 = *((unsigned int *)t3);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    *((unsigned int *)t9) = t18;
    t19 = *((unsigned int *)t9);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB77;

LAB78:
LAB79:    t14 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t14, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB31:    xsi_set_current_line(44, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = (t0 + 1208U);
    t7 = *((char **)t3);
    t11 = *((unsigned int *)t4);
    t12 = *((unsigned int *)t7);
    t13 = (t11 | t12);
    *((unsigned int *)t42) = t13;
    t3 = (t4 + 4);
    t8 = (t7 + 4);
    t9 = (t42 + 4);
    t16 = *((unsigned int *)t3);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    *((unsigned int *)t9) = t18;
    t19 = *((unsigned int *)t9);
    t20 = (t19 != 0);
    if (t20 == 1)
        goto LAB80;

LAB81:
LAB82:    memset(t10, 0, 8);
    t23 = (t10 + 4);
    t24 = (t42 + 4);
    t37 = *((unsigned int *)t42);
    t38 = (~(t37));
    *((unsigned int *)t10) = t38;
    *((unsigned int *)t23) = 0;
    if (*((unsigned int *)t24) != 0)
        goto LAB84;

LAB83:    t49 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t49 & 4294967295U);
    t50 = *((unsigned int *)t23);
    *((unsigned int *)t23) = (t50 & 4294967295U);
    t41 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t41, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB33:    xsi_set_current_line(45, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng1)));
    memset(t43, 0, 8);
    t7 = (t4 + 4);
    if (*((unsigned int *)t7) != 0)
        goto LAB86;

LAB85:    t8 = (t3 + 4);
    if (*((unsigned int *)t8) != 0)
        goto LAB86;

LAB89:    if (*((unsigned int *)t4) < *((unsigned int *)t3))
        goto LAB87;

LAB88:    memset(t42, 0, 8);
    t14 = (t43 + 4);
    t11 = *((unsigned int *)t14);
    t12 = (~(t11));
    t13 = *((unsigned int *)t43);
    t16 = (t13 & t12);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB90;

LAB91:    if (*((unsigned int *)t14) != 0)
        goto LAB92;

LAB93:    t23 = (t42 + 4);
    t18 = *((unsigned int *)t42);
    t19 = *((unsigned int *)t23);
    t20 = (t18 || t19);
    if (t20 > 0)
        goto LAB94;

LAB95:    t29 = *((unsigned int *)t42);
    t30 = (~(t29));
    t31 = *((unsigned int *)t23);
    t32 = (t30 || t31);
    if (t32 > 0)
        goto LAB96;

LAB97:    if (*((unsigned int *)t23) > 0)
        goto LAB98;

LAB99:    if (*((unsigned int *)t42) > 0)
        goto LAB100;

LAB101:    memcpy(t10, t45, 8);

LAB102:    t56 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t56, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB35:    xsi_set_current_line(46, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 1048U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_lshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB37:    xsi_set_current_line(47, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 1048U);
    t7 = *((char **)t3);
    memset(t10, 0, 8);
    xsi_vlog_unsigned_rshift(t10, 32, t4, 32, t7, 32);
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t10, 0, 0, 32, 0LL);
    goto LAB39;

LAB40:    t21 = *((unsigned int *)t10);
    t22 = *((unsigned int *)t15);
    *((unsigned int *)t10) = (t21 | t22);
    t23 = (t8 + 4);
    t24 = (t9 + 4);
    t25 = *((unsigned int *)t8);
    t26 = (~(t25));
    t27 = *((unsigned int *)t23);
    t28 = (~(t27));
    t29 = *((unsigned int *)t9);
    t30 = (~(t29));
    t31 = *((unsigned int *)t24);
    t32 = (~(t31));
    t33 = (t26 & t28);
    t34 = (t30 & t32);
    t35 = (~(t33));
    t36 = (~(t34));
    t37 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t37 & t35);
    t38 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t38 & t36);
    t39 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t39 & t35);
    t40 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t40 & t36);
    goto LAB42;

LAB43:    t21 = *((unsigned int *)t10);
    t22 = *((unsigned int *)t9);
    *((unsigned int *)t10) = (t21 | t22);
    t14 = (t4 + 4);
    t15 = (t7 + 4);
    t25 = *((unsigned int *)t14);
    t26 = (~(t25));
    t27 = *((unsigned int *)t4);
    t33 = (t27 & t26);
    t28 = *((unsigned int *)t15);
    t29 = (~(t28));
    t30 = *((unsigned int *)t7);
    t34 = (t30 & t29);
    t31 = (~(t33));
    t32 = (~(t34));
    t35 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t35 & t31);
    t36 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t36 & t32);
    goto LAB45;

LAB46:    *((unsigned int *)t42) = 1;
    goto LAB49;

LAB48:    t8 = (t42 + 4);
    *((unsigned int *)t42) = 1;
    *((unsigned int *)t8) = 1;
    goto LAB49;

LAB50:    t14 = ((char*)((ng3)));
    goto LAB51;

LAB52:    t15 = ((char*)((ng2)));
    goto LAB53;

LAB54:    xsi_vlog_unsigned_bit_combine(t10, 32, t14, 32, t15, 32);
    goto LAB58;

LAB56:    memcpy(t10, t14, 8);
    goto LAB58;

LAB60:    t9 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB62;

LAB61:    *((unsigned int *)t45) = 1;
    goto LAB62;

LAB64:    *((unsigned int *)t42) = 1;
    goto LAB67;

LAB66:    t15 = (t42 + 4);
    *((unsigned int *)t42) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB67;

LAB68:    t24 = ((char*)((ng3)));
    goto LAB69;

LAB70:    t41 = ((char*)((ng2)));
    goto LAB71;

LAB72:    xsi_vlog_unsigned_bit_combine(t10, 32, t24, 32, t41, 32);
    goto LAB76;

LAB74:    memcpy(t10, t24, 8);
    goto LAB76;

LAB77:    t21 = *((unsigned int *)t10);
    t22 = *((unsigned int *)t9);
    *((unsigned int *)t10) = (t21 | t22);
    goto LAB79;

LAB80:    t21 = *((unsigned int *)t42);
    t22 = *((unsigned int *)t9);
    *((unsigned int *)t42) = (t21 | t22);
    t14 = (t4 + 4);
    t15 = (t7 + 4);
    t25 = *((unsigned int *)t14);
    t26 = (~(t25));
    t27 = *((unsigned int *)t4);
    t33 = (t27 & t26);
    t28 = *((unsigned int *)t15);
    t29 = (~(t28));
    t30 = *((unsigned int *)t7);
    t34 = (t30 & t29);
    t31 = (~(t33));
    t32 = (~(t34));
    t35 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t35 & t31);
    t36 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t36 & t32);
    goto LAB82;

LAB84:    t39 = *((unsigned int *)t10);
    t40 = *((unsigned int *)t24);
    *((unsigned int *)t10) = (t39 | t40);
    t47 = *((unsigned int *)t23);
    t48 = *((unsigned int *)t24);
    *((unsigned int *)t23) = (t47 | t48);
    goto LAB83;

LAB86:    t9 = (t43 + 4);
    *((unsigned int *)t43) = 1;
    *((unsigned int *)t9) = 1;
    goto LAB88;

LAB87:    *((unsigned int *)t43) = 1;
    goto LAB88;

LAB90:    *((unsigned int *)t42) = 1;
    goto LAB93;

LAB92:    t15 = (t42 + 4);
    *((unsigned int *)t42) = 1;
    *((unsigned int *)t15) = 1;
    goto LAB93;

LAB94:    t24 = (t0 + 1848U);
    t41 = *((char **)t24);
    memset(t44, 0, 8);
    t24 = (t44 + 4);
    t46 = (t41 + 4);
    t21 = *((unsigned int *)t41);
    t22 = (t21 >> 0);
    *((unsigned int *)t44) = t22;
    t25 = *((unsigned int *)t46);
    t26 = (t25 >> 0);
    *((unsigned int *)t24) = t26;
    t27 = *((unsigned int *)t44);
    *((unsigned int *)t44) = (t27 & 4294967295U);
    t28 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t28 & 4294967295U);
    goto LAB95;

LAB96:    t51 = ((char*)((ng1)));
    t52 = (t0 + 1208U);
    t53 = *((char **)t52);
    memset(t54, 0, 8);
    t52 = (t54 + 4);
    t55 = (t53 + 4);
    t35 = *((unsigned int *)t53);
    t36 = (t35 >> 31);
    t37 = (t36 & 1);
    *((unsigned int *)t54) = t37;
    t38 = *((unsigned int *)t55);
    t39 = (t38 >> 31);
    t40 = (t39 & 1);
    *((unsigned int *)t52) = t40;
    xsi_vlog_mul_concat(t45, 32, 1, t51, 1U, t54, 1);
    goto LAB97;

LAB98:    xsi_vlog_unsigned_bit_combine(t10, 32, t44, 32, t45, 32);
    goto LAB102;

LAB100:    memcpy(t10, t44, 8);
    goto LAB102;

}

static void Cont_51_2(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    unsigned int t27;
    unsigned int t28;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    char *t35;

LAB0:    t1 = (t0 + 3664U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(51, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng2)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB7;

LAB4:    if (t18 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t6) = 1;

LAB7:    t22 = (t0 + 4160);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memset(t26, 0, 8);
    t27 = 1U;
    t28 = t27;
    t29 = (t6 + 4);
    t30 = *((unsigned int *)t6);
    t27 = (t27 & t30);
    t31 = *((unsigned int *)t29);
    t28 = (t28 & t31);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t33 | t27);
    t34 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t34 | t28);
    xsi_driver_vfirst_trans(t22, 0, 0);
    t35 = (t0 + 4016);
    *((int *)t35) = 1;

LAB1:    return;
LAB6:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

}


extern void work_m_00000000000600019028_0886308060_init()
{
	static char *pe[] = {(void *)Cont_28_0,(void *)Always_30_1,(void *)Cont_51_2};
	xsi_register_didat("work_m_00000000000600019028_0886308060", "isim/sim_mips_isim_beh.exe.sim/work/m_00000000000600019028_0886308060.didat");
	xsi_register_executes(pe);
}
