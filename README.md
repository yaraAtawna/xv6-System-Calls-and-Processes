# xv6 — System Calls & Processes

Implementation of operating-system functionality in **xv6-riscv**, focusing on system calls, process management, memory usage, process termination, and distributing work among multiple processes.

This project was developed as part of the **Operating Systems** course at Ben-Gurion University of the Negev. The assignment uses xv6, a small UNIX-like teaching operating system designed to provide hands-on experience with operating-system concepts and kernel development.

## Overview

The project extends xv6 with new userspace programs and kernel functionality through four main tasks:

* **Hello World** — creating and integrating a userspace program.
* **Memory Size System Call** — implementing the `memsize` system call.
* **Exit Messages** — extending process termination and `wait` to support exit messages.
* **Process Distribution** — implementing `forkn` and `waitall` to create and synchronize multiple child processes.

## Key Implementations

### `memsize` System Call

Implemented a new system call:

```c
int memsize(void);
```

The system call returns the memory size of the currently running process.

The implementation required changes to the system-call interface and kernel, including:

* `syscall.h`
* `syscall.c`
* `sysproc.c`
* `usys.pl`
* `user.h`

A userspace test program, `memsize_test.c`, was implemented to measure memory usage before allocation, after allocating 20 KB, and after freeing the allocated memory.

### Process Exit Messages

Extended the process termination mechanism to store and retrieve an exit message.

The implementation includes:

* Adding `exit_msg` to the Process Control Block (PCB).
* Extending `exit` to receive an exit message.
* Extending `wait` to return the child's exit message.
* Using `argstr` to transfer the message from userspace to kernelspace.
* Using `copyout` to transfer the message back to userspace.
* Creating the `goodbye.c` userspace program.
* Updating the shell to display the exit message when a child process terminates.

### Multiple-Process Creation with `forkn`

Implemented:

```c
int forkn(int n, int* pids);
```

The system call creates multiple child processes and returns their PIDs to the parent.

The implementation also handles partial failures: if creating one of the requested processes fails, already-created child processes must be cleaned up and the operation returns `-1`.

### Waiting for Multiple Processes with `waitall`

Implemented:

```c
int waitall(int* n, int* statuses);
```

`waitall` waits for all child processes to finish and returns:

* The number of completed child processes.
* The exit status of each child process.
* An error indication when the operation fails.

The implementation uses userspace/kernelspace data transfer through `copyout` and ensures that the call does not return while child processes are still operating.

## Distributed Array Computation

The `bigarray.c` program demonstrates process-based parallelism.

It:

1. Initializes an array containing consecutive integers.
2. Creates four child processes using `forkn`.
3. Assigns each child a quarter of the array.
4. Calculates a partial sum in each child.
5. Communicates the results through child exit statuses.
6. Uses `waitall` to wait for all children.
7. Prints the final sum after all processes have completed.

The expected final result is:

```text
2147450880
```

The assignment also requires testing the implementation with different numbers of child processes.

## Operating-System Concepts

This project provides practical experience with:

* **System calls**
* **Kernelspace and userspace**
* **Process Control Blocks (PCB)**
* **Process creation and termination**
* **Parent-child process relationships**
* **Process synchronization**
* **Memory management**
* **Inter-process communication**
* **Process exit statuses**
* **Kernel locking**
* **Deadlock avoidance**
* **RISC-V operating-system development**

A key part of the process-management implementation is correctly acquiring and releasing process locks while avoiding holding multiple process locks simultaneously, which can lead to deadlocks.

## Technologies

* **C**
* **xv6-riscv**
* **RISC-V**
* **QEMU**
* **Docker**
* **WSL 2**
* **Visual Studio Code**
* **Dev Containers**
* **Git & GitHub**

The recommended environment uses Docker with WSL and VS Code Dev Containers to compile and run xv6 in a controlled environment.

## Running xv6

After configuring the development environment, build and run xv6 with:

```bash
make qemu
```

After xv6 boots, the implemented userspace programs can be executed from the xv6 shell.

Example:

```bash
helloworld
```

```bash
memsize_test
```

```bash
goodbye
```

```bash
bigarray
```

To exit QEMU:

```text
Ctrl-A
X
```

## Project Structure

A simplified structure of the relevant components:

```text
xv6-riscv/
├── kernel/
│   ├── proc.c
│   ├── syscall.c
│   ├── sysproc.c
│   └── ...
│
├── user/
│   ├── helloworld.c
│   ├── memsize_test.c
│   ├── goodbye.c
│   ├── bigarray.c
│   └── ...
│
├── Makefile
└── ...
```

## Course

**Operating Systems**
Ben-Gurion University of the Negev
**Assignment 1 — Processes and Scheduling**

Based on **xv6-riscv**.
