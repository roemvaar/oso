# Memory

A process has a program state defined by underlying machine registers
and the contents of the memory it can access.

The memory of a process can normally be classified into five categories:

* Code (the program being executed)
* Read-only static data
* Writable static data
* The heap
* The stack

A process MUST always have some code and a stack, but need not have any
of the other categories of memory.

## The Stack

The stack is a contiguous area of memory that may be used for storage for
local variables and for additional arguments to subroutines when there are
insufficient argument register availables.

The stack implementation is full-descending,


## Memory Layout

------------------- 1GB (RAM size)
                  |
                  |
Process n-1       |
                  |
                  |
------------------- 1GB - Frame Size
.                 |
.                 |
.                 |
------------------- 0x8000_0000 + KernelSize + 2*Frame Size (frame pointer?)
                  |
                  |
Process 1         |
                  |
------------------- 0x8000_0000 + Kernel Size + Frame Size
                  |
                  |
Process 0         | 
(init_task)       | 
                  |
                  |
------------------- 0x8000_0000 + Kernel Size
                  |
                  |
                  |
Kernel            |
                  |
                  |
                  |
------------------- 0x8000_0000
Reserved for RPi4 |
------------------- 0x0000_0000

The system will support n tasks:
    * From 0 to n - 1
    * Each task frame will be XXMB bigs
    * Some fixed tasks will be created at the beginning
        * init_task - parent to all tasks, first entry point to user space

Each process frame will contain:
    * TaskStruct
        * CPU context
            * general-purpose registers
            * stack pointer
            * frame pointer
    * Task


## Memory

OSo does not support dynamic memory allocation, it manages task
descriptors using static memory. This means, a fixed-size pool of
task descriptors is used, and `get_free_task_descriptor` function
finds an available slot from that pool when a new task is created.
