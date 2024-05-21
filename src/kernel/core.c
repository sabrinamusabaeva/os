
#include <SabrinaOS/fs/ffs.h>
#include <SabrinaOS/kernel/interrupts/interrupts.h>
#include <SabrinaOS/kernel/interrupts/timer.h>
#include <SabrinaOS/kernel/process/process.h>
#include <SabrinaOS/memmgr/stackguard/stackguard.h>

#include <conio.h>
#include <process.h>
#include <stddef.h>
#include <string.h>
#include <sys/syscall.h>

#include <drivers/disk/disk.h>
#include <drivers/display/text_mode.h>
#include <SabrinaOS/drivers/ps2/keyboard.h>
#include <SabrinaOS/drivers/ps2/ps2.h>

#include <SabrinaOS/kernel/panic.h>
#include <lib/utils/input.h>
#include <lib/utils/logging.h>
#include <lib/utils/output.h>
#include <lib/utils/time.h>

extern void kernel_enable_interrupts();
extern void kernel_core_entry_asm();

char command[30];
int need_to_clear_hack;
int run;
int lba_start, sector_count;
extern void enable_timer_interrupt();

void kernel_core_entry() {
    set_color_bg(C_BLUE);
    set_color_fg(C_WHITE);
    print_rectangle(0, 0, TEXT_WINDOW_WIDTH - 1, TEXT_WINDOW_HEIGHT - 1);
    move_xy(0, 0);
    print_log("Initializing Kernel");

    populate_and_load_idt_table();

    kernel_core_entry_asm();

    print_log("Kernel enabling interrupts");

    ps2_init();
    ps2_keyboard_init();

    process_scheduler_init();

    clrscr();

    VERIFY_STACKGUARD();
    int init_pid = spawnl(INIT_APPNAME, INIT_APPNAME, NULL);
    print_info("init process got created: %d", init_pid);

    kernel_enable_interrupts();
    interrupt_pit_enable();
    while (1)
        ;
}