#ifndef RISCUINHO_VPI_H
#define RISCUINHO_VPI_H

#include "simulinho_global_vpi.h"

#include <vpi_user.h>

#include "simulinho_vpi.h"

static int hello_compiletf(char*user_data);

static int hello_calltf(char*user_data);

void hello_register();


#endif // RISCUINHO_VPI_H
