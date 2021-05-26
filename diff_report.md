# Code Modification Report
Bagian code dimodifikasi untuk project 2

## Makefile
Line 3 :
```C
CS333_PROJECT ?= 2
```
## syscall.c
Line 112 - 119:
```C
#ifdef CS333_P2
extern int sys_getuid(void);
extern int sys_getgid(void);
extern int sys_getppid(void);
extern int sys_setuid(void);
extern int sys_setgid(void);
extern int sys_getprocs(void);
#endif // CS333_P2
```
Line 149 - 156:
```C
#ifdef CS333_P2
[SYS_getuid]  sys_getuid,
[SYS_getgid]  sys_getgid,
[SYS_getppid] sys_getppid,
[SYS_setuid]  sys_setuid,
[SYS_setgid]  sys_setgid,
[SYS_getprocs]  sys_getprocs,
#endif
```
Line 188 - 195:
```C
#ifdef CS333_P2
  [SYS_getuid]  "getuid",
  [SYS_getgid]  "getgid",
  [SYS_getppid] "getppid",
  [SYS_setuid]  "setuid",
  [SYS_setgid]  "setgid",
  [SYS_getprocs]  "getprocs",
#endif
```

## usys.s
Line 34-39:
```C
SYSCALL(getuid)
SYSCALL(getgid)
SYSCALL(getppid)
SYSCALL(setuid)
SYSCALL(setgid)
SYSCALL(getprocs)
```

## syscall.h
Line 27-31:
```C
#define SYS_getgid  SYS_getuid+1
#define SYS_getppid SYS_getgid+1
#define SYS_setuid  SYS_getppid+1
#define SYS_setgid  SYS_setuid+1
#define SYS_getprocs  SYS_setgid+1
```

## user.h
Line 32 - 39:
```C
#ifdef CS333_P2
uint getuid(void);
uint getgid(void);
uint getppid(void);
int setuid(uint);
int setgid(uint);
int getprocs(uint max, struct uproc* table);
#endif
```

## sysproc.c
Line 114 - 172:
```C
#ifdef CS333_P2
uint
sys_getuid(void){
  return myproc()->uid;
}

uint
sys_getgid(void){
  return myproc()->gid;
}

uint
sys_getppid(void){
  if(!myproc()->parent){
    return myproc()->pid;
  }
  return myproc()->parent->pid;
}

int
sys_setuid(void){
  int uid;
  if(argint(0,&uid) < 0){
    return -1;
  }
  if(uid < 0 || uid > 32767){
    return -1;
  }
  myproc()->uid = uid;
  return 0;
}

int
sys_setgid(void){
  int gid;
  if(argint(0,&gid) < 0){
    return -1;
  }
  if(gid < 0 || gid > 32767){
    return -1;
  }
  myproc()->gid = gid;
  return 0;
}

int
sys_getprocs(void)
{
  uint max;
  struct uproc* table;
  if(argint(0, (void*)&max) < 0){
    return -1;
  }
  if(argptr(1, (void*)&table, sizeof(&table) * max) < 0){
    return -1;
  }
  return getprocs(max, table);
}
#endif
```

## proc.h
Line 56 - 61:
```C
  #ifdef CS333_P2
    uint uid;
    uint gid;
    uint cpu_ticks_total;
    uint cpu_ticks_in;
  #endif
```

## proc.c
Line 9 - 11:
```C
#ifdef CS333_P2
#include "uproc.h"
#endif //CS333_P2
```
Line 160 - 167:
```C
  #ifdef CS333_P2
    p->start_ticks = ticks;
  #endif

  #ifdef CS333_P2
    p->cpu_ticks_total = 0;
    p->cpu_ticks_in = 0;
  #endif
```
Line 105 - 208:
```C
  #ifdef CS333_P2
    p->uid = DEFAULT_UID;
    p->gid = DEFAULT_GID;
  #endif
```
Line 275 - 278:
```C
  #ifdef CS333_P2
    np->uid = curproc->uid;
    np->gid = curproc->gid;
  #endif
```
Line 418 - 420:
```C
      #ifdef CS333_P2
        p->cpu_ticks_in = ticks;
      #endif
```
Line 462 - 464:
```C
  #ifdef CS333_P2
    p->cpu_ticks_total += (ticks - p->cpu_ticks_in);
  #endif //P2
```
Line 592 - 608:
```C
  int duration_ms = ticks - p->start_ticks;
  int duration_s_satuan = duration_ms / 1000;
  int duration_s_komaan = duration_ms % 1000;

  int total_ms = p->cpu_ticks_total;
  int total_s_satuan = total_ms / 1000;
  int total_s_komaan = total_ms % 1000;

  // int total = p->cpu_ticks_total;
  int ppid;

  if(p->parent){
    ppid = p->parent->pid;
  }else{
    ppid = p->pid;
  }
  cprintf("%d\t%s\t\t%d\t%d\t%d\t%d.%d\t%d.%d\t%s\t%d\t", p->pid, p->name, p->uid, p->gid, ppid, duration_s_satuan, duration_s_komaan, total_s_satuan, total_s_komaan, state_string, p->sz);
```
Line 976 - 1006:
```C
#ifdef CS333_P2
int
getprocs(uint max, struct uproc* table)
{
  int i = 0;
  struct proc* p;
  acquire(&ptable.lock);
  if(!table || max <= 0){
    release(&ptable.lock);
    return -1;
  }
  for(p = ptable.proc;p < &ptable.proc[NPROC];p++){
    if(i >= max)
      break;
    if(p->state != EMBRYO && p->state != UNUSED){
      table[i].pid = p->pid;
      table[i].uid = p->uid;
      table[i].gid = p->gid;
      table[i].ppid = (!p->parent) ? p->pid:p->parent->pid;
      table[i].elapsed_ticks = ticks - p->start_ticks;
      table[i].CPU_total_ticks = p->cpu_ticks_total;
      table[i].size = p->sz;
      safestrcpy(table[i].state, states[p->state], sizeof(table[i]).state);
      safestrcpy(table[i].name, p->name, sizeof(table[i]).name);
      i++;
    }
  }
  release(&ptable.lock);
  return i;
}
#endif // CS333_P2
```

## defs.h
Line 12 - 14:
```C
#ifdef CS333_P2
  struct uproc;
#endif // CS333_P2
```
Line 135 - 137:
```C
#ifdef CS333_P2
  int getprocs(uint max, struct uproc* table);
#endif // CS333_P2
```

## ps.c
Line 1 - 50:
```C
#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

int
main(void)
{
  struct uproc* table;
  uint max = 72;
  uint satuan;
  uint desimal;
  uint cpu_satuan;
  uint cpu_desimal;
  int catch = 0;
  int i;

  table = malloc(sizeof(struct uproc) * max);
  catch = getprocs(max, table);
  if(catch == -1){
    printf(1, "\nError: Invalid max or NULL uproc table\n");
  }else{
    printf(1, "\nPID\tName\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize");
    for(i = 0;i < catch;++i) {
      satuan = table[i].elapsed_ticks / 1000;
      desimal = table[i].elapsed_ticks % 1000;
      cpu_satuan = table[i].CPU_total_ticks / 1000;
      cpu_desimal = table[i].CPU_total_ticks % 1000;
      printf(1, "\n%d\t%s\t%d\t%d\t%d\t%d.", table[i].pid, table[i].name, table[i].uid, table[i].gid, table[i].ppid, satuan);

      if(desimal < 10){
        printf(1, "00");
      }else if(desimal < 100){
        printf(1, "0");
      }
      printf(1, "%d\t%d.", desimal, cpu_satuan);

      if(cpu_desimal < 10){
        printf(1, "00");
      }else if(cpu_desimal < 100){
        printf(1, "0");
      }
      printf(1, "%d\t%s\t%d", cpu_desimal, table[i].state, table[i].size);
    }
    printf(1, "\n");
  }
  free(table);
  exit();
}
#endif // CS333_P2
```

## time.c
Line 1 - 38:
```C
#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char* argv[])
{
    int t1 = 0; 
    int t2 = 0; 
    int satuan = 0; 
    int desimal = 0; 
    int pid = 0;

    ++argv;
    t1 = uptime();
    pid = fork();
    if(pid < 0) {
        printf(1, "Ran in 0.000 seconds\n");
        exit();
    }
    else if(pid == 0) {
        exec(argv[0], argv);
    }
    else {
        wait();
        t2 = uptime();
        satuan = (t2 - t1) / 1000;
        desimal = (t2 - t1) % 1000;
        printf(1, "%s ran in %d.", argv[0], satuan);
        if(desimal < 10)
          printf(1, "00");
        else if(desimal < 100)
          printf(1, "0");
        printf(1, "%d seconds\n", desimal);
    }
    exit();
}
#endif // CS333_P2
```

## testsetuid.c
Line 1 - 11:
```C
#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "***** In %s: my uid is %d\n\n", argv[0], getuid());
  exit();
}
#endif
```