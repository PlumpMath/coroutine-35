#define DEBUG
#include "coroutine.h"

#include <stdio.h>

void* run(Coroutine coro, void* args) {
	printf(">> now inside RUN <<\n");
	printf("message from run: %s\n", (char*)(args));
	args = Coroutine_yield(coro, "OK");
	printf("message from run: %s\n", (char*)(args));
	return "done";
}

void* run_again(Coroutine coro, void* args) {
	printf(">> now inside RUN_AGAIN <<\n");
	printf("message from run_again: %s\n", (char*)(args));
	args = Coroutine_yield(coro, "OK");
	printf("message from run_again: %s\n", (char*)(args));
	return "done";
}

void test() {
	char* res;
	Coroutine coro = Coroutine_new(run, 1024);
	assert(Coroutine_isInit(coro));
	res = (char*)Coroutine_resume(coro, "hello");
	assert(Coroutine_isPend(coro));
	printf("message from run: %s\n", res);
	res = (char*)Coroutine_resume(coro, "world");
	assert(Coroutine_isEnd(coro));
	printf("message from run: %s\n", res);
	/* you can resume an already ended coroutine, but it is useless */
	assert(Coroutine_isEnd(coro));
	Coroutine_reset(coro, run_again);
	assert(Coroutine_isInit(coro));
	res = (char*)Coroutine_resume(coro, "hello");
	assert(Coroutine_isPend(coro));
	printf("message from run_again: %s\n", res);
	res = (char*)Coroutine_resume(coro, "world");
	assert(Coroutine_isEnd(coro));
	printf("message from run_again: %s\n", res);
	Coroutine_close(coro);
}

int main() {
	test();
	return 0;
}
