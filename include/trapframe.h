#pragma once
#include <stdint.h>

// Exactly matches your kernel_entry save order:
//   regs[0] = x0, regs[1] = x1, … regs[28]=x28, regs[29]=x29, regs[30]=x30
typedef struct {
    uint64_t regs[31];
    // 8 bytes padding unused (because S_FRAME_SIZE = 256)
} trap_frame_t;
