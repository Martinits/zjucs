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

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003484406445_1871713313_init();
    unisims_ver_m_00000000003927721830_1593237687_init();
    work_m_00000000003595122394_0707010114_init();
    work_m_00000000003841023203_3476153904_init();
    work_m_00000000002082166660_0426247469_init();
    work_m_00000000003112037452_2659630971_init();
    work_m_00000000000212879186_2570855430_init();
    work_m_00000000000197330456_3938928471_init();
    work_m_00000000003841023203_2931428527_init();
    work_m_00000000004237155407_1137345619_init();
    work_m_00000000002959910077_2869055374_init();
    work_m_00000000001469798461_0328104581_init();
    work_m_00000000001934643685_1788697866_init();
    work_m_00000000003102667137_4153506179_init();
    unisims_ver_m_00000000003266096158_0690727491_init();
    unisims_ver_m_00000000003510477262_2316096324_init();
    work_m_00000000003430323094_4285205854_init();
    work_m_00000000000684192289_0345418465_init();
    work_m_00000000003514620691_0103510313_init();
    work_m_00000000003749146237_4024466370_init();
    work_m_00000000001269958119_2520395732_init();
    work_m_00000000000600019028_0886308060_init();
    work_m_00000000001388373273_2544383568_init();
    work_m_00000000002671537370_4144471541_init();
    work_m_00000000001838955763_3448893584_init();
    work_m_00000000001848652094_1602209333_init();
    work_m_00000000002733248587_1397843898_init();
    work_m_00000000003387696891_0362415942_init();
    work_m_00000000001494838369_3877310806_init();
    work_m_00000000002138168198_2302953071_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000002138168198_2302953071");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
