#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/cobra.h"
#include "output.h"

#define COL_NAME 0
#define COL_MIN  1
#define COL_MAX  2
#define COL_AVG  3

#define NUM_COL  4

#define intstrlen(x) ((int)log10(x))

static void get_max_width(struct testgroup *tg, unsigned int *width){
	struct test *t=tg->list;
	int i;

	while(t){
		if((i=strlen(t->name))>width[COL_NAME])
			width[COL_NAME]=i;
		if((i=intstrlen(t->min))>width[COL_MIN])
			width[COL_MIN]=i;
		if((i=intstrlen(t->max))>width[COL_MAX])
			width[COL_MAX]=i;
		if((i=intstrlen(t->avg))>width[COL_AVG])
			width[COL_AVG]=i;
		t=t->next;
	}
}

void print_table(BenchSet *bs){
	struct testgroup *tgp;
	struct test *tp;
	unsigned int width[NUM_COL]={5,9,9,9};

	printf("Benchmark Summary:\n");
	for(tgp=bs->list;tgp;tgp=tgp->next){
		get_max_width(tgp,width);
		printf("%s:\n",tgp->name);
		printf("\tName%*c| min (us)%*c | max (us)%*c | avg (us)\n",width[COL_NAME]-4+1,' ',width[COL_MIN]-8+1,' ',width[COL_MAX]-8+1,' ');
		for(tp=tgp->list;tp;tp=tp->next){
			printf("\t%s%*c| ",tp->name,width[COL_NAME]-strlen(tp->name)+1,' ');
			printf("%d%*c| ",tp->min,width[COL_MIN]-intstrlen(tp->min)+1,' ');
			printf("%d%*c| ",tp->max,width[COL_MIN]-intstrlen(tp->min)+1,' ');
			printf("%d\n",tp->avg);
		}
		printf("\n");
	}
}
