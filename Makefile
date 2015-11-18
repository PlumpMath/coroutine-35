test: test.c coroutine.c coroutine.S
	gcc -o $@ $^
