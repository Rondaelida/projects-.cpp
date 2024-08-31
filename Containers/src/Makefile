CC := gcc
WWW = -std=c++17 -Wall -Werror -Wextra -lstdc++ -g
LIBS=-lgtest -lgmock -pthread

all: clean test

test: clean
	$(CC) $(WWW) $(LIBS) tests.cc -o test
	./test

style:
	clang-format -style=Google -n *.cc *.h

tostyle:
	clang-format -style=Google -i *.cc *.h

leaks: test
	leaks -atExit -- ./test

clean:
	rm -rf a.out test test.dSYM