# coroutine

A simple coroutine implementation for C.

### Acknowledge

This coroutine implementation is not stable enough for products.
It is ready for both Linux 32bit and 64bit, also FreeBSD is partly supported.

### Status

* CORO_INIT

	- coroutine is initialized but hasn't bind to a main function

* CORO_RUN

	- coroutine is running inside the main function

* CORO_PEND

	- the main function is pended

* CORO_END

	- the main function is end

### API

* Coroutine_new(size_t stksize)

	- create an instance of coroutine, you can specifiy the size of stack through `stksize`

* Coroutine_close(Coroutine coro)

	- close an instance of coroutine, it will coredump if you call it when coroutine is running

* Coroutine_bind(Coroutine coro)

	- bind or change the main function of coroutine

* Coroutine_resume(Coroutine coro)

	- resume the main function of coroutine

* Coroutine_yield(Coroutine coro)

	- yield from the main function of coroutine

* Coroutine_reset(Coroutine coro)

	- reset the coroutine when its status is `CORO_END`

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
