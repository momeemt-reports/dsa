CC := clang

SRC_DIR := ./src
OBJ_DIR := ./obj
HEADER_DIR := ./headers
TEST_DIR := ./test
TEST_HEADER_DIR := ./test/headers
TEST_BIN_DIR := ./test/bin
RESULT_BIN_DIR := ./result/bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))
HEADERS := $(wildcard $(HEADER_DIR)/**/*.h)
CFLAGS := -W -Wall -I$(HEADER_DIR)

TEST_CFLAGS := $(CFLAGS) -I$(TEST_HEADER_DIR)
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

dijkstra: ./test/bin/test_dijkstra_out

floyd: ./test/bin/test_floyd_out

naive: ./test/bin/test_naive_out

compnext: ./test/bin/test_compnext_out

kmp: ./test/bin/test_kmp_out

$(TEST_BIN_DIR)/test_binarytree_out: $(TEST_DIR)/test_binarytree.c $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/queue.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_binarysearchtree_out: $(TEST_DIR)/test_binarysearchtree.c $(OBJ_DIR)/binarysearchtree.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_bst_advanced_out: $(TEST_DIR)/test_bst_advanced.c $(OBJ_DIR)/bst_advanced.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_sort_collection_out: $(TEST_DIR)/test_sort_collection.c $(OBJ_DIR)/sort_collection.o $(OBJ_DIR)/timer.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_dijkstra_out: $(TEST_DIR)/test_dijkstra.c $(OBJ_DIR)/dijkstra.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_floyd_out: $(TEST_DIR)/test_floyd.c $(OBJ_DIR)/floyd.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_naive_out: $(TEST_DIR)/test_naive.c $(OBJ_DIR)/naive.o $(OBJ_DIR)/cmp.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_compnext_out: $(TEST_DIR)/test_compnext.c $(OBJ_DIR)/compnext.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/test_kmp_out: $(TEST_DIR)/test_kmp.c $(OBJ_DIR)/kmp.o $(OBJ_DIR)/compnext.o
	$(CC) $(TEST_CFLAGS) $^ $(TEST_LIB) -o $@

$(TEST_BIN_DIR)/%_out: $(TEST_DIR)/%.c $(filter-out $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/binarysearchtree.o $(OBJ_DIR)/bst_advanced.o, $(OBJS))
	$(CC) $(TEST_CFLAGS) $< $(filter-out $(OBJ_DIR)/binarytree.o $(OBJ_DIR)/binarysearchtree.o $(OBJ_DIR)/bst_advanced.o, $(OBJS)) $(TEST_LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

generate_documentation:
	doxygen Doxyfile

.PHONY: tidy
tidy:
	clang-tidy $(SRCS) $(TEST_FILES) -- -W -Wall -Iheaders -Itest/headers -I$${CUNIT_INCLUDE_DIR} -isystem"$${CLANG_INCLUDE_DIR}" -isystem"$${LIBC_INCLUDE_DIR}" -isystem"$${CUNIT_INCLUDE_DIR}"

clean:
	rm -f $(OBJS)
	rm -f $(TEST_EXES)
	rm -f test/graph/*
	rm -rf result
	rm -rf html

.DEFAULT_GOAL := test
