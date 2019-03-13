CC := g++
CXXFLAGS=-Wall -pedantic -std=c++11

ifdef opt
	CXXFLAGS += -O3
	LDFLAGS += -O3
else
	CXXFLAGS += -g
	LDFLAGS += -g
endif

SRCDIR := src
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj


all: init part3 interactive

part3: init $(addprefix $(OBJDIR)/,mma.o Graph.o)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/$@ $(filter-out init,$^)

interactive: init $(addprefix $(OBJDIR)/,interactive.o Graph.o)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/$@ $(filter-out init,$^)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c -o $@ $<


.PHONY: init
init:
	@mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)
