LIBDIR := lib
OBJDIR := obj
EXEDIR := bin
INCDIR := include

#$(addprefix $(EXEDIR)/, $(basename $(notdir $(wildcard src/*.c))))

EXE := $(filter-out bin/utils, $(addprefix $(EXEDIR)/, $(basename $(notdir $(wildcard src/*.c)))))
FILES := $(basename $(notdir $(wildcard src/*.c)))
SRCS := $(wildcard src/*.c)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst src/%.c, %.o, $(SRCS)))
LIBS := $(addprefix $(LIBDIR)/lib, $(patsubst src/%.c, %.a, $(SRCS)))
PLIB := $(addprefix $(LIBDIR)/lib, process_race.a)
TLIB := $(addprefix $(LIBDIR)/lib, thread_race.a)

LIBLINKS := $(addprefix -l, utils curses pthread)

all: build

.PHONY: test
test:
	$(info $(EXE))
	$(info $(FILES))
	$(info $(SRCS))
	$(info $(OBJS))
	$(info $(LIBS))
	$(info $(LIBLINKS))

build: $(EXE) | $(EXEDIR)
	@echo "Finished Compiling with static libraries"

.PRECIOUS: $(OBJS)
$(EXEDIR)/%: src/%.c liba | $(EXEDIR)
	gcc -o $@ -I $(INCDIR) $< -L $(LIBDIR) $(LIBLINKS)

liba: $(LIBS) | $(LIBDIR)
	@echo "Finished generating static libraries at lib/"

$(LIBDIR)/lib%.a: $(OBJDIR)/%.o | $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: src/%.c $(INCLUDES) | $(OBJDIR)
	gcc -o $@ -c -I $(INCDIR) $<

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(EXEDIR) $(LIBDIR) $(OBJDIR)
