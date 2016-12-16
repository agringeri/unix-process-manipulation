// process_data.c
// Anthony Gringeri

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>

#include "process_data.h"

process_data* start() {
	// memory
	process_data* initial = (process_data*) (malloc (sizeof (struct process_data)));
	struct timeval t;
	// get current TOD
	gettimeofday(&t, 0);
	// calculate initial wall time
	initial -> wall_clock_time = ((t.tv_sec * 1000000) + t.tv_usec) / 1000;
	return initial;
}

process_data** process_information(struct rusage *usage, process_data *shell) {
	// memory
	process_data* exec = (process_data*) (malloc(sizeof(struct process_data)));
	struct timeval t;
	// get current TOD
	gettimeofday(&t, 0);
	// calculate elapsed time
	long real_time_elapsed = ((t.tv_sec * 1000000) + t.tv_usec) / 1000;

	exec -> cpu_time = 0 - shell -> cpu_time + usage -> ru_stime.tv_sec * 1000000 + usage -> ru_stime.tv_usec / 1000;
	exec -> wall_clock_time = real_time_elapsed - shell -> wall_clock_time;	
	exec -> num_voluntary = 0 - shell -> num_voluntary + usage -> ru_nivcsw;
	exec -> num_involuntary = 0 - shell -> num_involuntary + usage -> ru_nvcsw;
	exec -> num_major_faults = 0 - shell -> num_major_faults + usage -> ru_majflt;
	exec -> num_minor_faults = 0 - shell -> num_minor_faults + usage -> ru_minflt;
	exec -> max_set_size = 0 - shell -> max_set_size + usage -> ru_maxrss;
	
	shell -> cpu_time = usage -> ru_stime.tv_sec * 1000000 + usage -> ru_stime.tv_usec / 1000;
	shell -> wall_clock_time = real_time_elapsed;	
	shell -> num_voluntary = usage -> ru_nivcsw;
	shell -> num_involuntary = usage -> ru_nvcsw;
	shell -> num_major_faults = usage -> ru_majflt;
	shell -> num_minor_faults = usage -> ru_minflt;
	shell -> max_set_size = usage -> ru_maxrss;

	process_data** result = (process_data**)(malloc(2 * sizeof(process_data*)));
	*result = shell;
	*(result + 1) = exec;

	return result;
}

void print_data(process_data* info) {
	printf("\nProcess exited.\n");
	printf("--------------------------\n");
	printf("    Process Statistics\n");
	printf("--------------------------\n");
	printf("    CPU Clock Time:                       %i\n", info->cpu_time);
	printf("    Wall Clock Time (ms):                 %i\n", info->wall_clock_time);
	printf("    Involuntary Context Switches:         %i\n", info->num_involuntary);
	printf("    Voluntary Context Switches:           %i\n", info->num_voluntary);
	printf("    Major Page Faults:                    %i\n", info->num_major_faults);
	printf("    Minor Page Faults:                    %i\n", info->num_minor_faults);
	printf("    Maximum Resident Set Size Used (kB):  %i\n", info->max_set_size);
}