#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(int argc, const char* argv[]){

        float temps [10000];
        temps[0] = 298.15;

        float starttime = 0;
        float deltat;
        if(argc > 1)
                deltat = atof(argv[1]);
        else
                deltat = 0.001;
        float c2 = 0.991667;
        float c1 = 1.27575 * powf(10,-10);
        float tinf = 473.15;
        float tsur = powf(673.15,4);

        FILE* fp = fopen("data.txt","w+");

        int i = 0;
        for(i = 0; i < 10000 && temps[i] < 490.85; i++) {
                if(i % 10 == 0) {
                        fprintf(fp, "%f\n", temps[i]);
                }
                temps[i + 1] = (-1) * (deltat/c2) * (temps[i] - tinf + c1 * (pow(temps[i],4) - tsur)) + temps[i];
                starttime += deltat;
        }

        fclose(fp);

        int status;
        int pid = fork();
        if(pid == 0) {
                execl("/usr/local/bin/RScript", "/usr/local/bin/RScript",
                      "/Users/sjyn/Documents/LahTech/math_modeling/hw/chw/plot.R", (char *)NULL);
        } else if(pid > 0) {
                printf("The temperature at time %f is %f\n", starttime, temps[i]);
        } else {
                exit(2);
        }
        if(waitpid(pid, &status, 0) != pid)
                status = -1;

        return 0;
}
