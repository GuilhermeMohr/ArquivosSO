#include "filesystem.h"

extern void loop_comandos();

int main() {
    iniciar_sistema();
    loop_comandos();
    return 0;
}