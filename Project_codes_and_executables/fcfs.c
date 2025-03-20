#include <stdio.h>
#include "simulator.h"
#include <stdlib.h>
#include <time.h>
#define MAX_ARRIVAL 100
#define MIN_ARRIVAL 0
#define MAX_BURST 50
#define MIN_BURST 1
/*this is the deadline offset (will add arrival time to it)*/
#define MAX_DEADLINE 120
#define MIN_DEADLINE 20

void fcfs(int num) {
	struct process tmp;
	/*seeding random number generator with time*/
	srand(time(0));
   /*random generation of arrival burst and deadline*/
	struct process arr[num];
	for (int i = 0; i < num; i++) {
   	 arr[i].pid=i;
    	arr[i].arrival = rand() % (MAX_ARRIVAL - MIN_ARRIVAL + 1) + MIN_ARRIVAL;
    	arr[i].burst = rand() % (MAX_BURST - MIN_BURST + 1) + MIN_BURST;
    	arr[i].deadline = rand() % (MAX_DEADLINE - MIN_DEADLINE + 1) + arr[i].burst;
	}
   FILE *fptr1=fopen("data.tex","w");
   /*storing data in data.tex*/
	fprintf(fptr1,"\n The random data generator output");
	fprintf(fptr1,"\n	The process table ");
	fprintf(fptr1,"\n%-8s %-18s %-12s %-12s", "pid", "arrival", "burst", "deadline");
	for (int i = 0; i < num; i++) {
    	fprintf(fptr1,"\n%-8d %-18d %-12d %-12d", arr[i].pid, arr[i].arrival, arr[i].burst, arr[i].deadline);
	}
    fprintf(fptr1,"\n");
    fclose(fptr1);
   /*sorting in ascending order of arrival time*/
	for (int i = 0; i < num ; i++) {
    	for (int j = 0; j < num-1; j++) {
        	if (arr[j].arrival > arr[j + 1].arrival) {
            	tmp = arr[j];
            	arr[j] = arr[j + 1];
            	arr[j + 1] = tmp;
        	}
    	}
	}
   /*assuming cpu was idle the moment the first program arrived*/
	fptr1=fopen("output.tex","w");
	int cpuTime=arr[0].arrival;
	for(int i=0;i<num;i++){
    if(arr[i].arrival>cpuTime)cpuTime=arr[i].arrival;
    arr[i].wait=cpuTime-arr[i].arrival;
    arr[i].response=cpuTime-arr[i].arrival;
    arr[i].turn=arr[i].burst+arr[i].wait;
    cpuTime=cpuTime+arr[i].burst;
	}
    /*storing data in output.tex*/
    int sumTurn=0;
    int sumWait=0;
    int sumResponse=0;
    int sumBurst=0;
	fprintf(fptr1,"\n================FIRST COME FIRST SERVE===================");
 	fprintf(fptr1,"\nThe processes in their working order and their data");
 	fprintf(fptr1,"\n%-8s %-18s %-12s %-12s %-12s %-12s %-12s", "pid", "arrival", "burst", "deadline","wait","response","turn");
	for (int i = 0; i < num; i++) {
   	fprintf(fptr1,"\n%-8d %-18d %-12d %-12d %-12d %-12d %-12d", arr[i].pid, arr[i].arrival, arr[i].burst, arr[i].deadline,arr[i].wait,arr[i].response,arr[i].turn);
    sumTurn=sumTurn+arr[i].turn;
    sumWait=sumWait+arr[i].wait;
    sumBurst=sumBurst+arr[i].burst;
    sumResponse=sumResponse+arr[i].response;    
}
    fprintf(fptr1,"\nAverage turnaround time = %f",(float)sumTurn/num);
    fprintf(fptr1,"\nAverage waiting time	= %f",(float)sumWait/num);
    fprintf(fptr1,"\nAverage response time   = %f",(float)sumResponse/num);
    fprintf(fptr1,"\nCpu utilisation     	= %f",((float)sumBurst/(float)sumTurn)*100);
    fprintf(fptr1,"\n");
    fclose(fptr1);
}


