CC := gcc

SRC_DIR := ./src
OBJ_DIR := ./obj
HEADER_DIR := ./headers
TEST_DIR := ./test
TEST_BIN_DIR := ./test/bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.c=.o))
HEADERS := $(wildcard $(HEADER_DIR)/**/*.h)
CFLAGS := -W -Wall -I$(HEADER_DIR)

TEST_CFLAGS := $(CFLAGS)
TEST_LIB := -lcunit
TEST_FILES := $(wildcard $(TEST_DIR)/*.c)
TEST_EXES := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%_out,$(TEST_FILES))

test: $(TEST_EXES)
	@for test in $(TEST_EXES); do \
		$$test; \
	done

$(TEST_BIN_DIR)/%_out: $(TEST_DIR)/%.c $(OBJS)
	$(CC) $(TEST_CFLAGS) $< $(OBJS) $(TEST_LIB) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(TEST_EXES)

.DEFAULT_GOAL := test
