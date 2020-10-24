## generic gcc CFLAGS.  -DTIME must be included.
CFLAGS += -Wall -pedantic $(OPTON) -I $(SRCDIR) -DTIME
OPTON = -O0 -ffast-math

PROGDIR = ./bin
SRCDIR = ./src

# Program binaries.
BINS = $(PROGDIR)/arithoh  \
       $(PROGDIR)/register \
       $(PROGDIR)/short    \
       $(PROGDIR)/int      \
       $(PROGDIR)/long     \
       $(PROGDIR)/float    \
       $(PROGDIR)/double   \
       $(PROGDIR)/syscall  \
       $(PROGDIR)/pipe     \
       $(PROGDIR)/spawn    \
       $(PROGDIR)/fstime

.PHONY: all
all: $(BINS)

$(PROGDIR)/%:  | $(PROGDIR)
	$(CC) -o $@ $(CFLAGS) $< $(LDFLAGS)

$(PROGDIR)/arithoh:  $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/arithoh:  CFLAGS += -Darithoh
$(PROGDIR)/register: $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/register: CFLAGS += -Ddatum='register int'
$(PROGDIR)/short:    $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/short:    CFLAGS += -Ddatum=short
$(PROGDIR)/int:      $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/int:      CFLAGS += -Ddatum=int
$(PROGDIR)/long:     $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/long:     CFLAGS += -Ddatum=long
$(PROGDIR)/float:    $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/float:    CFLAGS += -Ddatum=float
$(PROGDIR)/double:   $(SRCDIR)/arith.c #$(SRCDIR)/timeit.c
$(PROGDIR)/double:   CFLAGS += -Ddatum=double
$(PROGDIR)/pipe: $(SRCDIR)/pipe.c #$(SRCDIR)/timeit.c
$(PROGDIR)/spawn: $(SRCDIR)/spawn.c #$(SRCDIR)/timeit.c
$(PROGDIR)/fstime: $(SRCDIR)/fstime.c
$(PROGDIR)/syscall: $(SRCDIR)/syscall.c #$(SRCDIR)/timeit.c

$(PROGDIR):
	mkdir bin


.PHONY: all check distr programs run clean spotless
clean:
	$(RM) $(BINS) core *~ */*~
	$(RM) -rf $(PROGDIR)

spotless:	clean
	$(RM) $(RESULTDIR)/* $(TMPDIR)/*

