#ifndef COBRA_H
#define COBRA_H

#define START_TEST(x,a) void x (void *a)
#define END_TEST

struct test{
	struct test *next;
	const char *name;
	void (*pref)(void*);
	void (*f)(void*);
	void (*postf)(void*);
	void *arg;
	unsigned int min;
	unsigned int max;
	unsigned int avg;
};

struct testgroup{
	struct testgroup *next;
	const char *name;
	struct test *list;
};

typedef struct BenchSet{
	struct testgroup *list;
}BenchSet;

void add_test(struct testgroup *tg, const char *name, void (*pref)(void*), void (*f)(void*), void (*postf)(void*), void *arg);
struct testgroup* add_testgroup(BenchSet *bs, const char *name);
void benchset_init(BenchSet *bs);
void bench_run(BenchSet *bs);
void bench_free(BenchSet *bs);

#endif
