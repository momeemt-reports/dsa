CC := clang

SRC_DIR := ./src
OBJ_DIR := ./obj
HEADER_DIR := ./headers
TEST_DIR := ./test
TEST_BIN_DIR := ./test/bin
RESULT_BIN_DIR := ./result/bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))
HEADERS := $(wildcard $(HEADER_DIR)/**/*.h)
CFLAGS := -W -Wall -I$(HEADER_DIR)

TEST_CFLAGS := $(CFLAGS)
TEST_LIB := -lcunit
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_EXES := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%_out,$(TEST_FILES))
RESULT_EXES := $(patsubst $(TEST_DIR)/%.c,$(RESULT_BIN_DIR)/%_out,$(TEST_FILES))

test_run:
	$(foreach test,$(RESULT_EXES),$(test);)

test: $(TEST_EXES)

binarytree: ./test/bin/test_binarytree_out

binarysearchtree: ./test/bin/test_binarysearchtree_out

bst_advanced: ./test/bin/test_bst_advanced_out

$(TEST_BIN_DIR)/test_binarytree_out: $(TEST_DIR)/test_binarytree.c $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/queue.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_binarysearchtree_out: $(TEST_DIR)/test_binarysearchtree.c $(OBJ_DIR)/binarysearchtree.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_bst_advanced_out: $(TEST_DIR)/test_bst_advanced.c $(OBJ_DIR)/bst_advanced.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/%_out: $(TEST_DIR)/%.c $(filter-out $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/binarysearchtree.o $(OBJ_DIR)/bst_advanced.o, $(OBJS))
	$(CC) $(TEST_CFLAGS) $< $(filter-out $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/binarysearchtree.o $(OBJ_DIR)/bst_advanced.o, $(OBJS)) $(TEST_LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

generate_documentation:
	doxygen Doxyfile

tidy:
	INCLUDES=$$(clang -E -x c - -v < /dev/null 2>&1 | sed -n '/#include <...> search starts here:/,/End of search list./p' | grep -vE '#include|End of search list.'); \
	clang-tidy $(SRCS) --checks=* -- -I$(HEADER_DIR) $$(echo $$INCLUDES | sed 's/ / -I/g')

clean:
	rm -f $(OBJS)
	rm -f $(TEST_EXES)
	rm -f test/graph/*
	rm -rf result
	rm -rf html

.DEFAULT_GOAL := test
