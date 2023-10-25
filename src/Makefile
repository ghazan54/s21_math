CC=gcc
FLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lm
FUNC = s21_math.c
FUNC_LIB = s21_math.o

OS := $(shell uname -s)

ifeq ($(OS),Darwin) # Mac OS X
    LDFLAGS += 
endif
ifeq ($(OS),Linux)
    LDFLAGS += -lsubunit
endif

.PHONY: all clean rebuild

all: test gcov_report

s21_math.o:
	gcc $(FLAGS) -c $(FUNC) s21_math.h

s21_math.a: s21_math.o
	ar rc s21_math.a $(FUNC_LIB)
	ranlib s21_math.a

test: s21_math.a 
	$(CC) $(FLAGS) --coverage s21_math.c tests/*.c -lcheck -o math_test.out $(LDFLAGS)
	./math_test.out

test_run:
	./math_test.out

gcov_report: test
	# rm test.gcda test.gcno s21_math.h.gch
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info
	open ./report/index.html

check:
	# cp ../materials/linters/.clang-format .clang-format
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	# rm .clang-format

clean:
	rm -rf *.o out *.info *.gcda *.gcno *.gcov *.gch *.out *.a string_test
	rm -rf report

rebuild: clean all
