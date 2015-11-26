# coroutine

A simple coroutine implementation for C.

### Acknowledge

This coroutine implementation is not stable enough for products.

### Compatibility

* Linux - both 32bit and 64bit

* FreeBSD - 64bit, have not been tested on the 32bit platform

* Mac OS X - have not been tested

* Windows - not compatible currently

### Status

* CORO_INIT - coroutine is initialized but hasn't bind to a main function

* CORO_RUN - coroutine is running inside the main function

* CORO_PEND - the main function is pended

* CORO_END - the main function is end

### API

* Coroutine Coroutine_new(coro_cb_t main, size_t stksize)

	- create an instance of coroutine with the target main function
	- return: the pointer to the new instance of `Coroutine`
	- main: the target main function of Coroutine
	- stksize: the recommended size of coroutine, which should be larger the PAGE size of system

* void Coroutine_close(Coroutine coro)

	- close an instance of coroutine
	- coro: the pointer to the instance of `Coroutine`

* void Coroutine_reset(Coroutine coro, coro_cb_t main)

	- reset the main function of coroutine, and transfer the state from END to INIT
	- coro: the pointer to the instance of `Coroutine`
	- main: new function for coroutine, it will still use the latest one if it is `NULL`

* void* Coroutine_yield(Coroutine coro, void* para)

	- yield from the main function of coroutine
	- return: the data delivered by `Coroutine_resume`
	- para: can be used to deliver the data

* void* Coroutine_resume(Coroutine coro, void* para)

	- resume the main function of coroutine
	- return: the data delivered by `Coroutine_yield` or the return operation of main function
	- para: can be used to deliver the data

### MACRO

* Coroutine_status(Coroutine coro)

	- get the current status of coroutine

* Coroutine_isInit(Coroutine coro)

	- check if the status of coroutine is `CORO_INIT`

* Coroutine_isPend(Coroutine coro)

	- check if the status of coroutine is `CORO_PEND`

* Coroutine_isRun(Coroutine coro)

	- check if the status of coroutine is `CORO_RUN`

* Coroutine_isEnd(Coroutine coro)

	- check if the status of coroutine is `CORO_END`

### Dependency

* cmocka: for unittest
