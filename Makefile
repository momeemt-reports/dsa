CC := gcc

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

$(TEST_BIN_DIR)/%_out: $(TEST_DIR)/%.c $(OBJS)
	$(CC) $(TEST_CFLAGS) $< $(OBJS) $(TEST_LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

generate_documentation:
	doxygen Doxyfile

clean:
	rm -f $(OBJS)
	rm -f $(TEST_EXES)
	rm -rf result
	rm -rf html

.DEFAULT_GOAL := test
