#include "simulinhovpi.h"

#include <vpi_user.h>

static PLI_INT32 simulinho_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)xx;
}

static PLI_INT32 simulinho_calltf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)xx;
    vpi_printf("Starting SIMULinho!\n");


}


static void simulinho_register(void)
{
    s_vpi_systf_data tf_data;

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho";
    tf_data.calltf    = simulinho_calltf;
    tf_data.compiletf = simulinho_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = SIMULINHO_UI_OPEN_WINDOW;

    vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])(void) = {
    simulinho_register,
    0
};
