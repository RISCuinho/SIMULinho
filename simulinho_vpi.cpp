#include "simulinho_base_app.h"
#include "simulinho_vpi.h"

#include <vpi_user.h>

#include <stdio.h>
#include <string.h>

static unsigned no_ui = 0;

static PLI_INT32 simulinho_ui_compiletf(ICARUS_VPI_CONST PLI_BYTE8 *user_data){
    (void)user_data;
    return 0;
}

static void check_command_line_args(void)
{
    vpi_printf("Verificando argumentos de linha de comando!\n");

    struct t_vpi_vlog_info vlog_info;

    vpi_get_vlog_info(&vlog_info);

    for (int idx = 0 ;  idx < vlog_info.argc ;  idx += 1) {
        if (strcmp(vlog_info.argv[idx],"--noui") == 0) {
            vpi_printf("Não usar UI!\n");
            no_ui = 1;
        }
    }
}

static PLI_INT32 simulinho_ui_calltf(ICARUS_VPI_CONST PLI_BYTE8 *user_data){
    (void)user_data;
    char *argv[] = {(char*)"SIMULINHO_VPI",user_data};

    vpi_printf("Executando com Argumentos: %s\n", *argv);

    vpi_printf("User Data: %s --- %i\n", user_data,strcmp(user_data,SIMULINHO_UI_OPEN_WINDOW));
    if(strcmp(user_data,SIMULINHO_UI_OPEN_WINDOW) == 0 && !no_ui)
    {
        vpi_printf("Abrir Janela!\n");
        startMainWindow(0,argv);
    }
    else
    {
        vpi_printf("Fechar Janela!\n");
        closeMainWindow();
    }
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
    vpi_printf("Hello Register!\n");

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
    vpi_printf("Simulinho UI Open Register!\n");

    check_command_line_args();

    s_vpi_systf_data tf_data;

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
    vpi_printf("Simulinho UI Close Register!\n");

    s_vpi_systf_data tf_data;

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
