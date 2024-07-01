
#to compile server: make
#to compile memtest: make memtest

CC = gcc
CFLAGS = -Wall --ansi --pedantic -std=gnu99
SRCDIR = .
OBJDIR = ./compile

SOURCES = $(SRCDIR)/server.c $(SRCDIR)/DList.c $(SRCDIR)/memory_manager.c
MEMTEST_SOURCES = $(SRCDIR)/memtest.c $(SRCDIR)/memory_manager.c $(SRCDIR)/DList.c

# Header files
HEADERS = $(SRCDIR)/DList.h $(SRCDIR)/memory_manager.h
MEMTEST_HEADERS= $(SRCDIR)/DList.h $(SRCDIR)/memory_manager.h

# Object files
OBJECTS = $(OBJDIR)/server.o $(OBJDIR)/memory_manager.o $(OBJDIR)/DList.o
MEMTEST_OBJECTS = $(OBJDIR)/memtest.o $(OBJDIR)/memory_manager.o $(OBJDIR)/DList.o

# Target executable
SERVER_TARGET = $(OBJDIR)/server
MEMTEST_TARGET = $(OBJDIR)/memtest

# Default target
all: $(SERVER_TARGET)

# Rule to compile source files to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the final executable
$(SERVER_TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(SERVER_TARGET) $(OBJECTS)

memtest: $(MEMTEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(MEMTEST_TARGET) $(MEMTEST_OBJECTS)

# Clean up build files
clean:
	rm -f $(OBJDIR)/*.o $(SERVER_TARGET) $(MEMTEST_TARGET)

# Phony targets
.PHONY: all clean
