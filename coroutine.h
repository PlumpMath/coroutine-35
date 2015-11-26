/*
 * Linux and FreeBSD compatible Coroutine implementation.
 * Not ready for Windows currently.
 */
#ifndef _COROUTINE_H_
#define _COROUTINE_H_

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>

#define RED_ZONE 128
#define GREEN_ZONE 512
#define PAGE_SIZE 4096
#define STK_DEFAULT_SIZE (64 * 1024)

#if defined(__i386__)
	#define RLEN 6
#elif defined(__amd64__) || defined(__x86_64__)
	#define RLEN 8
#endif

#define CORO_PROMPT_RESET -1
#define CORO_PROMPT_INIT   1

struct coroutine;

typedef void* (*coro_cb_t)(struct coroutine*, void*);

typedef enum cstat {
	CORO_INIT,
	CORO_PEND,
	CORO_RUN,
	CORO_END
} cstat_t;

typedef void* regbuf_t[RLEN];

typedef struct coroutine {
	cstat_t state;
	regbuf_t env;
	void* stk;
	void* top;
	void* bot;
	void* sp;
	coro_cb_t main;
	void* res;
} coroutine_t, *Coroutine;

/* get or judge the status of coroutine */
#define Coroutine_status(coro) (coro)->state
#define Coroutine_isInit(coro) ((coro)->state == CORO_INIT)
#define Coroutine_isPend(coro) ((coro)->state == CORO_PEND)
#define Coroutine_isRun(coro)  ((coro)->state == CORO_RUN)
#define Coroutine_isEnd(coro)  ((coro)->state == CORO_END)

Coroutine Coroutine_new(coro_cb_t, size_t);

/* coroutine cannot be closed when it is running */
#define Coroutine_close(coro) \
	assert(!Coroutine_isRun(coro)); \
	free((coro))

void* Coroutine_yield(Coroutine, void*);
void* Coroutine_resume(Coroutine, void*);
void  Coroutine_reset(Coroutine, coro_cb_t);

/* functions for Debug */
#if defined(DEBUG)
void Coroutine_dumpRegs(Coroutine);
void Coroutine_dumpStack(Coroutine);
#endif // DEBUG

#endif // _COROUTINE_H_
