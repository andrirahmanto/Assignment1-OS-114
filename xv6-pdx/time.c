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