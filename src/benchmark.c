#include <limits.h>
#include <sys/time.h>
#include "../include/cobra.h"
#include "benchmark.h"

static unsigned int get_usec(struct timeval *tv){
	unsigned int ret;

	ret=tv->tv_usec;
	ret+=tv->tv_sec*1000000;

	return ret;
}

static unsigned int get_runtime(struct timeval *start, struct timeval *end){
	return get_usec(end)-get_usec(start);
}

void run_test(struct test *t){
	const int numruns=10;
	struct timeval start;
	struct timeval end; 
	int i;
	unsigned int runtime;
	t->min=UINT_MAX;
	t->max=0;
	t->avg=0;

	for(i=0;i<numruns;i++){
		if(t->pref)
			t->pref(t->arg);
		gettimeofday(&start,NULL);
		t->f(t->arg);
		gettimeofday(&end,NULL);
		if(t->postf)
			t->postf(t->arg);

		runtime=get_runtime(&start,&end);

		t->avg+=runtime;
		if(runtime>t->max)
			t->max=runtime;
		if(runtime<t->min)
			t->min=runtime;
	}
	t->avg/=numruns;
}
