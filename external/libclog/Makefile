SRC_DIR       := ./clog
OBJ_DIR       := ./build/obj
LIB_DIR       := ./lib

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

CC = gcc
CFLAGS := -std=c99 -pedantic

ifeq ($(BUILD),dev)
# "dev" build - no optimization, and debugging symbols
CFLAGS += -g -Wall -Werror -DDEBUG -O0 -DCLOGABORTFATAL
LIB = $(LIB_DIR)/libclog-dev.a
else
# "Release" build - optimization, and no debug symbols
CFLAGS += -O2 -s -DNDEBUG -DNCLOGDEBUG -DCLOGABORTFATAL
LIB = $(LIB_DIR)/libclog.a
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: cleanobjs $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(LIB_DIR)
	@$(AR) cr $@ $^
	@echo "    Archive    $(notdir $@)"

$(OBJS): $(SRCS)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $^ $(CFLAGS)
	@echo "    CC        $(OBJS)"

dev:
	make "BUILD=dev"

install:
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(LIB_DIR)/*.a $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/clog/
	install -m 644 $(SRC_DIR)/*.h $(DESTDIR)$(PREFIX)/include/clog/

clangformat:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h

.PHONY: clean cleanobjs
clean:
	@$(RM) -rf $(LIB_DIR) $(OBJ_DIR)
	@echo "    Remove Objects:   $(OBJS)"

cleanobjs:
	@$(RM) -rf $(OBJ_DIR)
	