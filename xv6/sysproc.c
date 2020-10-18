#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
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

int
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

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// return how many times a syscall was called by
// a process.
int
sys_getcount(void)
{
    int syscall;
    if (argint(0, &syscall) < 0)
        return -1;
    return myproc() -> syscallcount [syscall - 1];
}

/*
 * return the physical address give a virtual address
 * returns -1 if the page is absent or in kernel space
 * If the page is present and can be accessed
 * in the user mode then it returns the corresponding
 * physical address.
 * */
int
sys_v2paddr(void)
{
    // input virtual address
    int vaddr;
    if (argint(0, &vaddr) < 0)
        return -2;
    pde_t *pde; // page directory.
    pte_t *pgtab; // page table by indexing the directory.
    pte_t *pte; // page table entry by indexing page table.
    pde_t *pgdir = myproc() -> pgdir;
    pde = &pgdir[PDX(vaddr)];
    if(!(*pde & PTE_P)) {
        return -1; // page dir is absent.
    }
    pgtab = (pte_t*)P2V(PTE_ADDR(*pde));
    pte = &pgtab[PTX(vaddr)];
    if(!(*pte & PTE_P)) {
        return -1; // page table entry is absent.
    }
    if(!(*pte & PTE_U)) {
        return -1; // this address cannot be accessed in user mode.
    }
    // final step i.e concatenate last 12 bits of vaddr
    // to the first 20 bits of pte
    return PTE_ADDR(*pte) | PTE_FLAGS(vaddr);
}
