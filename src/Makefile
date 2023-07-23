.PHONY : clean check tests leaks tests_linux leaks_linux gcov_report

CC = gcc
CPPFLAGS = -ggdb -std=c++17 -pedantic -Wall -Werror -Wextra -lstdc++
TEST_FLAGS = -lgtest --coverage
LINUX_FLAGS = -lrt -lpthread -lm -lsubunit
VG_FLAGS = CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
all: clean check test leaks gcov_report
else ifeq ($(OS), Linux)
all: clean check test_linux leaks_linux gcov_report
else
all:
	@echo "Unsupported operating system: $(OS)"
endif

check:
	cp ../materials/linters/.clang-format .
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -n --style="Google" {} \;
	rm -f .clang-format

test:
	for TEST_SRC in $(shell find . -type f -name "*test.cc"); do \
		base_name=$$(basename $${TEST_SRC%%.cc}); \
		$(CC) $(CPPFLAGS)  $$TEST_SRC -o $$base_name.o $(TEST_FLAGS); \
		./$$base_name.o; \
	done

test_linux:
	for TEST_SRC in $(shell find . -type f -name "*test.cc"); do \
		base_name=$$(basename $${TEST_SRC%%.cc}); \
		$(CC) $$TEST_SRC $(CPPFLAGS) $(TEST_FLAGS) -o $$base_name.o $(LINUX_FLAGS); \
		./$$base_name.o; \
	done

leaks:
	for file in $(shell find . -maxdepth 1 -type f -name "*.o"); do \
		base_name=$$(basename $$file); \
		file_name=$$(echo $${base_name%_test.o} | tr '[:lower:]' '[:upper:]'); \
		leaks -atExit -- $$file > ./RESULT_$$file_name.txt; \
	done

leaks_linux:
	for file in $(shell find . -maxdepth 1 -type f -name "*.o"); do \
    	base_name=$$(basename $$file); \
    	file_name=$$(echo $${base_name%_test.o} | tr '[:lower:]' '[:upper:]'); \
    	$(VG_FLAGS) --log-file=RESULT_$$file_name.txt $$file; \
    done

gcov_report:
	lcov -t "test" -o s21_test.info -c -d ./ --no-external
	#lcov -t "test" -o s21_test.info -c -d ./ --no-external --ignore-errors mismatch
	genhtml ./s21_test.info --output-directory ./report/
	open ./report/index.html

clean:
	@rm -rf report *.txt
	@rm -rf *.gcda *.gcno *.info *.gch *.dSYM
	@rm -rf ../*.idea ../.run ../*.dSYM
	@rm -rf *.a *.o
