#Output program name to make this Makefile more reusable between programming exercises
PNAME = OpenCV

#Project Tree Structure
LDIR = lib
SDIR = src
ODIR = obj
BDIR = bin
DDIR = dep

#Compiler flag variables
INC        = $(SDIR)
INC_PARAMS = $(foreach d, $(INC), -I$d)
DEPFLAGS   = -MT $@ -MMD -MP -MF $(DDIR)/$*.Td
CPPFLAGS   = -std=c++11 -g

include Makefile.link

#The full command for compilation
CPPC       = g++ $(CPPFLAGS) $(INC_PARAMS) $(DEPFLAGS)
CPPL       = g++ $(CPPFLAGS)
POSTCPPC   = @mv -f $(DDIR)/$*.Td $(DDIR)/$*.d && touch $@

#Default make target: setup the environment, build the program, build and run tests
.PHONY: all
all: | toolchain $(PNAME)

#List all sources to be included in the project (except main.cpp)
_SRCS = Transformer.cpp Color.cpp BlacknWhite.cpp Edge.cpp

#Derived variable SRCS used by dependency management
SRCS  = main.cpp  $(_SRCS)

#Derived variables POBJ/TOBJ lists dependencies for the output binaries
POBJ = $(ODIR)/main.o $(patsubst %.cpp, $(ODIR)/%.o, $(_SRCS))

#Program link step
$(BDIR)/$(PNAME): $(POBJ)
	$(CPPL) -o $@ $^ $(LINKFLAGS)

#Unit Test link step
$(BDIR)/test: $(TOBJ)
	$(CPPL) -o $@ $^ $(LINKFLAGS)

#All compilation units in the project
$(ODIR)/%.o: $(SDIR)/%.cpp $(DDIR)/%.d
	$(CPPC) -c -o $@ $<
	$(POSTCPPC)

#Standard build targets
.PHONY: clean
clean:
	rm -rf $(DDIR) $(ODIR) $(BDIR)

.PHONY: toolchain pmain $(PNAME)
toolchain: | $(BDIR) $(ODIR) $(DDIR)
pmain: $(BDIR)/$(PNAME)
#tmain: $(BDIR)/test
$(PNAME): | toolchain pmain
#test: | toolchain tmain
#	./$(BDIR)/test

$(DDIR):
	@mkdir $(DDIR)

$(ODIR):
	@mkdir $(ODIR)

$(BDIR):
	@mkdir $(BDIR)

#Dependency management
$(DDIR)/%.d: ;
.PRECIOUS: $(DDIR)/%.d

include $(wildcard $(patsubst %,$(DDIR)/%.d,$(basename $(SRCS))))
