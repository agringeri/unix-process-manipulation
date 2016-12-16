// process_data.h
// Anthony Gringeri

/* struct containing statistics that show some of the system 
 * resources some particular process uses 
 */
typedef struct process_data {
	int cpu_time;         // CPU time used
	int wall_clock_time;  // wall clock time used
	int num_involuntary;  // number of times the process was preempted involuntarily 
	int num_voluntary;    // number of times the process gave up CPU voluntarily
	int num_major_faults; // number of major page faults 
	int num_minor_faults; // number of minor page faults
	int max_set_size;     // maximum resident set size used (given in kilobytes)
} process_data;

process_data*  start();
process_data** process_information(struct rusage *usage, process_data *shell);
void print_data(process_data* info);


