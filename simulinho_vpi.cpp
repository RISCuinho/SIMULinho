#include <vpi_user.h>
#include "simulinho_global.h"
#include "simulinho.h"
#include "simulinho_vpi.h"

static PLI_INT32 simulinho_ui_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data){
    (void)user_data;
    return 0;
}

static PLI_INT32 simulinho_ui_calltf(ICARUS_VPI_CONST PLI_BYTE8 *user_data){
    (void)user_data;
    char *argv[] = {(char*)"SIMULINHO VPI"};

    vpi_printf("Executando com Argumentos: ");
    vpi_printf("%s",*argv);

    startMainWindow(1,argv);
    return 0;
}

static PLI_INT32 hello_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data)
{
    (void)user_data;
    return 0;
}

static PLI_INT32 hello_calltf(PLI_BYTE8 *user_data)
{
    (void)user_data;

    vpi_printf("Hello, World!\n");
    return 0;
}

void hello_register()
{
    vpi_printf("Hello Register!");

    PLI_BYTE8 *user_data = (PLI_BYTE8*)'0';

    s_vpi_systf_data tf_data;
    //t_vpi_systf_data tf_data;
    tf_data.type      = vpiSysTask;
    tf_data.tfname    = "$hello";
    tf_data.calltf    = hello_calltf;
    tf_data.compiletf = hello_compiletf;
    tf_data.sizetf    = 0;
    tf_data.user_data = user_data;
    vpi_register_systf(&tf_data);
}

void simulinho_ui_open_register()
{
    printf("Simulinho UI Open Register!");

    s_vpi_systf_data tf_data;
      //t_vpi_systf_data tf_data;
      tf_data.type      = vpiSysTask;
      tf_data.tfname    = "$openUI";
      tf_data.calltf    = simulinho_ui_calltf;
      tf_data.compiletf = simulinho_ui_compiletf;
      tf_data.sizetf    = 0;
      tf_data.user_data = SIMULINHO_UI_OPEN_WINDOW;
      vpi_register_systf(&tf_data);
}

void simulinho_ui_close_register()
{
    printf("Simulinho UI Close Register!");

    s_vpi_systf_data tf_data;
      //t_vpi_systf_data tf_data;
      tf_data.type      = vpiSysTask;
      tf_data.tfname    = "$closeUI";
      tf_data.calltf    = simulinho_ui_calltf;
      tf_data.compiletf = simulinho_ui_compiletf;
      tf_data.sizetf    = 0;
      tf_data.user_data = SIMULINHO_UI_CLOSE_WINDOW;
      vpi_register_systf(&tf_data);
}

void (*vlog_startup_routines[])() = {
    hello_register,
    simulinho_ui_open_register,
    simulinho_ui_close_register,
    0
};
