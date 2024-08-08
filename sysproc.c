#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

// Implement the sys_gettime system call
uint
sys_gettime(void)
{
  struct rtcdate r;
  cmostime(&r);
  return (r.year << 16) | (r.month << 12) | (r.day << 8) | (r.hour << 4) | r.minute;
}

// Implement other system calls with uint return type
uint
sys_fork(void)
{
  return fork();
}

uint
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

uint
sys_wait(void)
{
  return wait();
}

uint
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

uint
sys_getpid(void)
{
  return myproc()->pid;
}

uint
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
