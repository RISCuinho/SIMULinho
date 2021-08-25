#include "simulinhovpi.h"

#include <uuid/uuid.h>
#include <veriuser.h>
#include <acc_user.h>
#include <vpi_user.h>

void SIMULinhoVPI::init(char *rtlName_p, uuid_t uuid_p){
    // Inicializa a comunicação
    printf("Init!");
    printf("Name: %s",rtlName_p);
    printf("Name: %s", uuid_p);
}


void SIMULinhoVPI::stop(uuid_t uuid_p){
    printf("Stop!");
    printf("Name: %s", uuid_p);
}

void SIMULinhoVPI::finish(uuid_t uuid_p){
    printf("Finish!");
    printf("Name: %s", uuid_p);

}
