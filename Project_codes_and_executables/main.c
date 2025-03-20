#include "simulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int c,num;
	printf("\n Welcome to CPU scheduling simulator. Please give me required parameters");
	printf("\n Scheduling algorithm: 1)FCFS 2)RR 3)SJF 4)SRTN 5)HRRN 6)LOTTERY 7)EDF 8)PRIORITY 9)ALL");
	printf("\n Please enter corresponding number of your choice: ");
	scanf("%d", &c);
	printf("\n Please enter number of processes: ");
	scanf("%d", &num);
	printf("\n Wait......generating results\n");
	switch (c) {
    	case 1:
        	/*FCFS*/
        	fcfs(num);
        	break;
    	case 2:
        	/*RR*/
		rr(num);
        	break;
    	case 3:
        	/*sjf*/
		sjf(num);
        	break;
    	case 4:
        	/*srtn*/
		srtn(num);
        	break;
    	case 5:
        	/*hrrn*/
        	hrrn(num);
        	break;
    	case 6:
        	/*lottery*/
        	lottery(num);
        	break;
    	case 7:
        	/*edf*/
        	edf(num);
        	break;
    	case 8:
        	/*priority*/
        	priority(num);
        	break;
    	case 9:
        	/*all*/
        	every(num);
        	break;
        default: 
        	printf("\n please choose the correct option");
	}
   printf("\n Done . Please check output.tex for result and data.tex for the input data\n");
	return 0;
}

