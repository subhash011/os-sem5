LIBDIR := lib
OBJDIR := obj
EXEDIR := bin
INCDIR := include
LIBDYN := libs

EXE := $(EXEDIR)/imageprocess
LIBS := $(addprefix $(LIBDIR)/, libmatrix.a libppm.a libtransform.a libmatrixmath.a)
DYNLIBS := $(addprefix $(LIBDYN)/, libmatrix.so libppm.so libtransform.so libmatrixmath.so)
SRCS := $(wildcard src/*.c)
INCLUDES := $(addprefix $(INCDIR)/, matrixmath.h transform.h ppm.h matrix.h)
OBJS := $(addprefix $(OBJDIR)/, $(patsubst src/%.c, %.o, $(SRCS)))
LIBLINKS := $(addprefix -l, matrix ppm transform matrixmath)

INPUT_DIR := inppm
OUT_DIR := outppm

INPUT_FILE := inppm/input.ppm
OUT_FILE := outppm/output.ppm

all: build

buildso: $(EXEDIR)/imageprocess_so | $(EXEDIR)
	@echo "Finished Compiling with dynamic libraries"
	@echo "Use './bin/imageprocess_so' to run the binary"
	@echo "The input is the path to input ppm file"

build: $(EXE) | $(EXEDIR)
	@echo "Finished Compiling with static libraries"
	@echo "Use './bin/imageprocess' to run the binary"
	@echo "The input is the path to input ppm file"

$(EXE): src/main.c liba $(OBJS) | $(EXEDIR)
	gcc -o $@ -I $(INCDIR) $< -L $(LIBDIR) $(LIBLINKS)

$(EXEDIR)/imageprocess_so: src/main.c libso | $(EXEDIR)
	gcc -o $@ -I $(INCDIR) $< -L $(LIBDYN) $(LIBLINKS)

liba: $(LIBS) | $(LIBDIR)
	@echo "Finished generating static libraries at lib/"

libso: $(DYNLIBS) | $(LIBDYN)
	@echo "Finished generating dynamic libraries at libso/"

$(OBJDIR)/%.o: src/%.c $(INCLUDES) | $(OBJDIR)
	gcc -o $@ -c -I $(INCDIR) $<

$(LIBDIR)/lib%.a: $(OBJDIR)/%.o | $(LIBDIR)
	ar rcs $@ $^

$(LIBDYN)/lib%.so: $(LIBDYN)/%.o | $(LIBDYN)
	gcc -shared -o $@ $<

$(LIBDYN)/%.o: src/%.c | $(LIBDYN)
	gcc -fPIC -c -I include $< -o $@

run: $(EXE) | outdir
	./$(EXE) $(INPUT_FILE) $(OUT_FILE)

prepare: $(EXE)
	@echo "Enter the input file path: "; \
	read inpath; echo "Enter the output file path: "; read outpath; ./$(EXE) $$inpath $$outpath	

T1: $(EXE) | outdir
	./$(EXE) $(INPUT_FILE) $(OUT_FILE) 1

T2: $(EXE) | outdir
	./$(EXE) $(INPUT_FILE) $(OUT_FILE) 2

tests: $(EXE) | outdir
	./testscript.sh

.PHONY: test
test: $(EXE) | outdir
	./testscript.sh

test%: $(EXE) | outdir
	./testscript.sh $@

outdir:
	mkdir -p outppm

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDYN):
	mkdir -p $(LIBDYN)

clean:
	rm -rf $(EXEDIR) $(LIBDIR) $(OBJDIR) $(LIBDYN) $(OUTDIR)
	rm -f *.ppm
