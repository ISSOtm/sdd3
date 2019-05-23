
BINDIR  = bin
OBJDIR  = obj
SRCDIR  = src

CFLAGS   = -Wall -Wextra -ansi -g -pedantic
LDFLAGS  =
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPSDIR)/$*.d.tmp
DEPSDIR = deps


SRCS = $(wildcard $(SRCDIR)/*.c)


all: $(BINDIR)/tp3
.PHONY: all


dist: tp3.zip
.PHONY: dist


tp3.zip: Makefile README.md rapport.pdf $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.h)
	-rm -f $@
	zip $@ $^


$(BINDIR)/tp3: $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	set -e; \
	$(CC) -c $(DEPFLAGS) $(CFLAGS) -o $@ $<; \
	sed 's,\($*\)\.o[ :]*,\1.o $(DEPSDIR)/\1.d: ,g' < $(DEPSDIR)/$*.d.tmp > $(DEPSDIR)/$*.d; \
	rm $(DEPSDIR)/$*.d.tmp


$(shell mkdir -p $(BINDIR) > /dev/null)
$(shell mkdir -p $(OBJDIR) > /dev/null)
$(shell mkdir -p $(SRCDIR) > /dev/null)
$(shell mkdir -p $(DEPSDIR) > /dev/null)

$(DEPSDIR)/%.d: ;
.PRECIOUS: $(DEPSDIR)/%.d


clean:
	-rm -rf $(BINDIR)
	-rm -rf $(OBJDIR)
	-rm -rf $(DEPSDIR)
.PHONY: clean


include $(patsubst $(SRCDIR)/%.c,$(DEPSDIR)/%.d,$(SRCS))

