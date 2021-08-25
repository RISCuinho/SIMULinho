#include "simulinhovpi.h"

#include <uuid/uuid.h>
#include <veriuser.h>
#include <acc_user.h>
#include <vpi_user.h>

static SIMULinhoVPI *simulinho;
static char *rtlName;
static uuid_t uuid;

static PLI_INT32 simulinho_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)user_data;
    simulinho = SIMULinhoVPI::getInstance();

    // get rtl project name

    return 0;
}

static PLI_INT32 simulinho_calltf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)user_data;
    vpi_printf("Starting SIMULinho!\n");
    if(user_data == SIMULINHO_INIT){
        simulinho->init(rtlName,uuid);

    }else if(user_data == SIMULINHO_STOP){
        simulinho->stop(uuid);

        vpi_control(vpiStop);
    }else if(user_data == SIMULINHO_FINISH){
        simulinho->finish(uuid);

        vpi_sim_control(vpiFinish);
    }

    return 0;
}


static PLI_INT32 clock_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)user_data;

    return 0;
}

static PLI_INT32 clock_calltf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)user_data;
    vpi_printf("Register principal clock!");

    return 0;
}

static void simulinho_init_register(void)
{
    s_vpi_systf_data tf_data;

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho";
    tf_data.calltf    = simulinho_calltf;
    tf_data.compiletf = simulinho_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = SIMULINHO_INIT;

    vpi_register_systf(&tf_data);

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho_init";
    tf_data.calltf    = simulinho_calltf;
    tf_data.compiletf = simulinho_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = SIMULINHO_INIT;

    vpi_register_systf(&tf_data);
}

static void simulinho_stop_register(void)
{
    s_vpi_systf_data tf_data;

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho_stop";
    tf_data.calltf    = simulinho_calltf;
    tf_data.compiletf = simulinho_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = SIMULINHO_STOP;

    vpi_register_systf(&tf_data);
}

static void simulinho_finish_register(void)
{
    s_vpi_systf_data tf_data;

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho_finish";
    tf_data.calltf    = simulinho_calltf;
    tf_data.compiletf = simulinho_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = SIMULINHO_FINISH;

    vpi_register_systf(&tf_data);
}

static void clock_register(void)
{
    s_vpi_systf_data tf_data;

    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$simulinho_clock";
    tf_data.calltf    = clock_calltf;
    tf_data.compiletf = clock_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = 0;

    vpi_register_systf(&tf_data);
}
void (*vlog_startup_routines[])(void) = {
    simulinho_init_register,
    simulinho_stop_register,
    simulinho_finish_register,
    clock_register,
    0
};
