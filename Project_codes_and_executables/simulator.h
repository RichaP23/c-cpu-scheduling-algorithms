#ifndef SIMULATOR_H
#define SIMULATOR_H

/*a process structure*/
struct process {
	int pid;
	double cputil;
	int wait, response, turn, arrival, burst, deadline,rburst,priority;
};
struct result{int current_arrival,cpuTicket;};


/* Function declarations */
void fcfs(int num);
void rr(int num);
void sjf(int num);
void srtn(int num);
void hrrn(int num);
void edf(int num);
void priority(int num);
void lottery(int num);
void every(int num);
int small(struct process *arr, int cpuTime, int num);
int highestresponse(struct process *arr, int cpuTime, int num);
int mostPrior(struct process *arr, int cpuTime, int num);
int smalld(struct process *arr, int cpuTime, int num) ;
struct result lotteryResult(struct process *arr, int cpuTime, int num);
#endif

