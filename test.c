#define DEBUG
#include "coroutine.h"

#include <stdio.h>

void run(Coroutine coro) {
	printf("message from run: %s\n", (char*)(coro->res));
	Coroutine_yield(coro);
	printf("message from run: %s\n", (char*)(coro->res));
}

void run_again(Coroutine coro) {
	printf("now inside run_again\n");
	/* close cannot be used inside main of coroutine */
	//Coroutine_close(coro);
}

void test() {
	Coroutine coro = Coroutine_new(1024);
	Coroutine_bind(coro, &run);
	coro->res = "hello";
	Coroutine_resume(coro);
	printf("message from test: between yield\n");
	coro->res = "world";
	Coroutine_resume(coro);
	/* you can resume an already ended coroutine, but it is useless */
	//Coroutine_resume(coro);
	Coroutine_reset(coro);
	Coroutine_bind(coro, run_again);
	Coroutine_resume(coro);
	Coroutine_close(coro);
}

int main() {
	test();
	return 0;
}
