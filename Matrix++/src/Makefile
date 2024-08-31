CC=gcc
FLAGS= -Wall -Werror -Wextra -std=c++17
LIBS=-lgtest -lstdc++

OS:=$(shell uname -s)
ifeq ($(OS), Darwin)
		OPEN=open
		LEAKS=leaks --atExit --
else
		LIBS+=-lm
		OPEN=xdg-open
		LEAKS=valgrind
endif

REPORT_DIR = report 

rebuild: clean all

all: test

s21_matrix_oop.a: s21_matrix_oop.cc
	$(CC) $(FLAGS) -c s21_matrix_oop.cc -o s21_matrix_oop.o
	ar rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

test: s21_test.cc s21_matrix_oop.a
	$(CC) $(FLAGS) -c s21_test.cc -o s21_test.o
	$(CC) $(FLAGS) s21_test.o s21_matrix_oop.a $(LIBS) -o test
	./test

gcov_report: $(REPORT_DIR)
	$(CC) $(FLAGS) -c s21_matrix_oop.cc --coverage -o s21_matrix_oop.o
	$(CC) $(FLAGS) -c s21_test.cc -o s21_test.o
	$(CC) $(FLAGS) s21_test.o s21_matrix_oop.o --coverage $(LIBS) -o test
	./test
	gcovr --exclude-unreachable-branches --exclude-throw-branches -r . --html --html-details -o $(REPORT_DIR)/report.html
	$(OPEN) $(REPORT_DIR)/report.html

$(REPORT_DIR):
	mkdir -p $(REPORT_DIR)

clean:
	rm -rf *.o *.a *.gcda *.gcno ./report test

clf:
	clang-format -n --style=Google *.cc *.h

cpk:
	cppcheck --language=c++ *.cc *.h

style: clf cpk

leaks: test
	$(LEAKS) ./test