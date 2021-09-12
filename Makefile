CC=gcc
CFLAGS=-I. -std=c17
OBJDIR := dist
SRC := lv.c winm.c glob.c tab.c input.c screen.c
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: %.c
	mkdir -p '$(@D)'
	$(CC) -c $< $(CFLAGS) -o $@

lv: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf dist lv
