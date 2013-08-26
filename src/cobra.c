#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/cobra.h"
#include "output.h"
#include "benchmark.h"

void add_test(struct testgroup *tg, const char *name, void (*pref)(void*), void (*f)(void*), void (*postf)(void*), void *arg){
	struct test *t,*ptr;

	t=malloc(sizeof(*t));

	if(t==NULL)
		return;

	t->name=name;
	t->next=NULL;
	t->pref=pref;
	t->f=f;
	t->postf=postf;
	t->arg=arg;

	if(tg->list==NULL)
		tg->list=t;
	else{
		ptr=tg->list;
		while(ptr->next)
			ptr=ptr->next;
		ptr->next=t;
	}
}

static struct testgroup* testgroup_create(const char *name){
	struct testgroup *tg;

	tg=malloc(sizeof(*tg));

	if(tg==NULL)
		return NULL;

	tg->name=name;
	tg->next=NULL;
	tg->list=NULL;

	return tg;
};

struct testgroup* add_testgroup(BenchSet *bs, const char *name){
	struct testgroup *tgp;

	tgp=bs->list;
	bs->list=testgroup_create(strdup(name));
	bs->list->next=tgp;
	
	return bs->list;
}

void benchset_init(BenchSet *bs){
	bs->list=NULL;
}

void bench_run(BenchSet *bs){
	struct testgroup *tgp;
	struct test *tp;

	for(tgp=bs->list;tgp;tgp=tgp->next){
		printf("Running group: %s\n",tgp->name);
		for(tp=tgp->list;tp;tp=tp->next){
			printf("\tRunning test: %s\n",tp->name);
			run_test(tp);
		}
	}

	printf("\n\n");

	print_table(bs);
}

void bench_free(BenchSet *bs){
}
