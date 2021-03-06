LIBDIR := ./lib
OBJDIR := ./obj
EXEDIR := ./bin
INCDIR := ./include

EXE := bin/processes_main bin/threads_main
FILES := $(basename $(notdir $(wildcard src/*.c)))
SRCS := $(wildcard src/*.c)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst src/%.c, %.o, $(SRCS)))
LIBS := $(addprefix $(LIBDIR)/lib, $(patsubst src/%.c, %.a, $(SRCS)))
PLIB := $(addprefix $(LIBDIR)/lib, processes_main.a)
INCS := $(addprefix $(INCDIR)/, $(notdir $(wildcard include/*.h)))
LIBLINKS := $(addprefix -l, utils pthread god hare turtle reporter)

all: build $(INCS)

.PHONY: build
build: $(EXE) | $(EXEDIR)
	@echo "Finished Compiling with static libraries"

$(EXEDIR)/%: src/%.c liba | $(EXEDIR)
	gcc -o $@ -I $(INCDIR) $< -L $(LIBDIR) $(LIBLINKS)

liba: $(LIBS) | $(LIBDIR)
	@echo "Finished generating static libraries at lib/"

.PRECIOUS: $(OBJS)
$(LIBDIR)/lib%.a: $(OBJDIR)/%.o | $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: src/%.c $(INCS) | $(OBJDIR)
	gcc -o $@ -c -I $(INCDIR) $<

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(EXEDIR) $(LIBDIR) $(OBJDIR)
