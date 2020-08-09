Target: test
test: test.c project.c project.h
	gcc test.c project.c -lm -o test
	./test 