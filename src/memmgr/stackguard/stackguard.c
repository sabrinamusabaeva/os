#include <SabrinaOS/kernel/panic.h>
#include <SabrinaOS/memmgr/stackguard/stackguard.h>

extern int check_stack_guard();

void verify_stack_guard(char err_message[]) {
    int err = check_stack_guard();
    if (err != 0) {
        PANIC(0, err_message);
    }
}
