#include <stdio.h>
#include "simulator.h"
#include <stdlib.h>
#include <time.h>
#define MAX_ARRIVAL 100
#define MIN_ARRIVAL 0
#define MAX_BURST 50
#define MIN_BURST 1
/*this is the deadline offset (will add arrival time to it)*/
#define MAX_DEADLINE 60
#define MIN_DEADLINE 20
#define MIN_QUANT 1
#define MAX_QUANT 50
//returns the index of the smallest deadline time in array
int highestresponse(struct process *arr, int cpuTime, int num) {
  double highRatio=1;
  int index =-1;
  int i =0;
  while (arr[i].arrival <= cpuTime && i < num) {
    double tmp=(arr[i].wait/arr[i].burst)+1;
    if (tmp>=highRatio && arr[i].rburst!= 0) {
      index=i;
      highRatio=tmp;
    }
    i++;
  }
  return index;
}

void hrrn(int num) {
	struct process tmp;
	/*seeding random number generator with time*/
	srand(time(0));
   /*random generation of arrival burst and deadline*/
	struct process arr[num];
	for (int i = 0; i < num; i++) {
   	 arr[i].pid=i;
    	arr[i].arrival = rand() % (MAX_ARRIVAL - MIN_ARRIVAL + 1) + MIN_ARRIVAL;
    	arr[i].burst = rand() % (MAX_BURST - MIN_BURST + 1) + MIN_BURST;
    arr[i].rburst=arr[i].burst;
    	arr[i].deadline = rand() % (MAX_DEADLINE - MIN_DEADLINE + 1)+ arr[i].burst;
    arr[i].wait=arr[i].response=0;
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
fptr1=fopen("output.tex","w");
fprintf(fptr1,"================RESULT FOR HRRN========================");
   /*assuming cpu was idle the moment the first program arrived*/
   
	int cpuTime=arr[0].arrival;
   	int completed=0;
   	int current=-1;
   	int tmp2;
   	while(completed!=num){
   		tmp2=highestresponse(arr,cpuTime,num);
   		//if no process left
   		if(tmp2==-1){
   			//if the next process cpuTime is very far away
   			if(completed!=num){
   				cpuTime=arr[current+1].arrival;
   			}
   			continue;
   		}
   		current=tmp2;
   		arr[current].response=(arr[current].rburst==arr[current].burst)?cpuTime:arr[current].response;
   		int i=0;
   		//incrementing the wait time with waiting processes's burst time 
   		while(arr[i].arrival<=cpuTime){
   			if(i==current || arr[i].rburst==0) {i++; continue;}
   			arr[i].wait=arr[i].wait+arr[current].burst;
   			i++;
   		}
   		cpuTime=cpuTime+arr[current].rburst;
   		arr[current].rburst=0;
   		arr[current].turn=cpuTime-arr[current].arrival;
   		arr[current].wait=arr[current].turn-arr[current].burst;
   		completed++;
}
   	
	
    	/*storing data in output.tex*/
    	int sumTurn=0,sumWait=0,sumBurst=0,sumResponse=0;
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


