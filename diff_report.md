# Code Modification Report
Kode yang di modifikasi

## Makefile
Line 3 :
```C
CS333_PROJECT ?= 1
```
Line 16 :
```C
CS333_UPROGS += _date
```
## syscall.c
Line 109 - 111:
```C
#ifdef CS333_P1
extern int sys_date(void);
#endif // CS333_P1
```
Line 138 - 140:
```C
#ifdef CS333_P1
[SYS_date]    sys_date,
#endif // CS333_P1
```
Line 181 - 186:
```C
    #ifdef CS333_P1
      #ifdef PRINT_SYSCALLS
        cprintf("%s -> %d\n",
              syscallnames[num], curproc->tf->eax);
      #endif
    #endif
```

## user.h
Line 28 - 30:
```C
#ifdef CS333_P1 
    int date(struct rtcdate*);
#endif // CS333_P1
```

## usys.s
Line 33:
```
SYSCALL(date)
```

## syscall.h
Line 24:
```C
#define SYS_date    SYS_halt+1
```

## sysproc.c
Line 101 - 112:
```C
#ifdef CS333_P1
int
sys_date(void)
{
  struct rtcdate *d;
  if(argptr(0, (void*)&d, sizeof (struct rtcdate)) < 0){
    return -1;
  }
  cmostime(d);
  return 0;
}
#endif
```

## proc.h
Line 52 - 54:
```C
  #ifdef CS333_P1
    uint start_ticks;
  #endif
```

## proc.c
Line 152 - 154:
```C
  #ifdef CS333_P1
    p->start_ticks = ticks;
  #endif
```
Line 569 - 578:
```C
  int duration_ms = ticks - p->start_ticks;
  int duration_s_satuan = duration_ms / 1000;
  int duration_s_komaan = duration_ms % 1000;
  if(duration_s_komaan<10){
    cprintf("%d\t%s\t\t%d.00%d\t%s\t%d\t", p->pid, p->name, duration_s_satuan, duration_s_komaan , state_string,p->sz);
  }else if (duration_s_komaan<100){
    cprintf("%d\t%s\t\t%d.0%d\t%s\t%d\t", p->pid, p->name, duration_s_satuan, duration_s_komaan , state_string,p->sz);
  }else{
    cprintf("%d\t%s\t\t%d.%d\t%s\t%d\t", p->pid, p->name, duration_s_satuan, duration_s_komaan , state_string,p->sz);
  }
```