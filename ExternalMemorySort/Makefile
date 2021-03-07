# ------------------------------------------------
# Generic Makefile
#
# Changelog :
# edited from: http://stackoverflow.com/users/128940/beta
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = p4

CC       = g++
# compiling flags here
CFLAGS   = -std=c++11 -Wall -I.

LINKER   = g++
# linking flags here
LFLAGS   = -Wall -I. -lm

# change these to proper directories where each file should be
SRCDIR    = src
OBJDIR    = build
BINDIR    = bin
SORTEDDIR = .sorted_data

TESTS    := $(wildcard $(TESTDIR)/*.cpp)
SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -rf

$(BINDIR)/$(TARGET): $(OBJECTS)
		@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
		@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
		@mkdir -p $(OBJDIR)
		@mkdir -p $(SORTEDDIR)
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
		@$(rm) $(OBJECTS)
		@$(rm) $(SORTEDDIR)
		@echo "Cleanup complete!"

.PHONY: remove
remove: clean
		@$(rm) $(BINDIR)/$(TARGET)
		@echo "Executable removed!"
