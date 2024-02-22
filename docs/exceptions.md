# Exceptions

There are two types of exceptions, synchronous and asynchronous.

Instructions that intentionally cause an exception to be taken are called exception
producing instructions. For the purpose of this project, we only care about `SVC`,
i.e., supervisor call, that will cause an exception that will take the Exception level
from EL0 to EL1, which will be used to implement system calls.

Asynchronous exceptions taken to AArch64 state are also known as interrupts.

## Exception Levels

The ARMv8 defines four Exception levels: EL0, EL1, EL2, and EL3.

EL3 is the highest level and EL0 the lowest.

Unprivileged execution is any execution that occurs at EL0.

For the purpose of this project, the current Exception level changes ONLY 
when any of the following occurs:

* Taking an exception
* Returning from an exception
* Processor reset

An exception cannot be taken to EL0. An exception cannot cause entry to
a lower Exception level.

## Typical Exception level usage model

* EL0 - Applications
* EL1 - OS kernel and associated libraries
* EL2 - Hypervisor
* EL3 - Secure monitor

## Stack (registers)

If in AArch64 state, each implemented Exception level has a dedicated stack 
pointer register. For this project we only care about EL1 (kernel space) and
EL0 (user space). The stack pointer registers for these Exception levels
are: SP_EL1 and SP_EL0.

## Stack pointer register selection

The core uses the following stack pointer:

* If executing in user space (EL0), then the core uses the EL0 stack pointer, SP_EL0.
* If executing in kernel space (EL1), then the core uses the stack pointer determined
  by the PSTATE.SP bit:
    * If PSTATE.SP is 0, then the core uses the EL0 stack pointer, SP_EL0.
    * If PSTATE.SP is 1, then the core uses the stack pointer for the current Exception level.

When an exception is taken, the stack pointer for the target Exception level is selected.

## Exception vector table

When an exception occurs, the core must execute handler code that corresponds to the exception.
The location in memory where the handler is stored is called the exception vector. Each
Exception level has its own vector table. For this project, we only care about the table for
EL1.

The table contains instructions to be executed, rather than a set of addresses. These 
instructions normally be branch instructions that direct the core to the full exception handler.

## Exception Link Register

Exception Link Register hold preferred exception return address. In this project, we only need to
take care of exceptions taken to EL1 using the ELR_EL1 register.

The preferred exception return address is an address that software might return to after handling
an exception in order to resume execution.

## References

* ARM Architecture Reference Manual for A-profile Architecture - D1.3 Exceptions p.4632
* https://developer.arm.com/documentation/100933/0100/AArch64-exception-vector-table
