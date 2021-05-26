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