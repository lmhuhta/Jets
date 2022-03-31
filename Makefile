PROGRAM       = jetreco

version       = JTKT
CXX           = g++
#CXXFLAGS      = -O -Wall -g -Wno-deprecated -bind_at_load -D$(version)
#CXXFLAGS      =  -Wall -W
CXXFLAGS      = -O -Wall -g -Wno-deprecated -Wno-misleading-indentation -D$(version) #-ggdb
LD            = g++
LDFLAGS       = -O
SOFLAGS       = -shared
LDLIBS="root-config --glibs --libs"
#############################################
# -bind_at_load helps to remove linker error
############################################
CXXFLAGS += $(shell root-config --cflags)
LDFLAGS  = $(shell root-config --libs)
CXXFLAGS += $(shell $(FASTJET)/bin/fastjet-config --cxxflags )
#LDFLAGS  = $(shell $(FASTJET)/bin/fastjet-config --libs)

LDFLAGS += $(shell $(FASTJET)/bin/fastjet-config --libs --plugins )

#$(LINKCC) $(LDFLAGS) -o $(EXECUTABLE) $(OBJS) $(LDLIBS)

INCS    += -I$(PYTHIA8)/include
#LDFLAGS += -L$(PYTHIA8)/lib -lpythia8 
#Instead:
LDFLAGS += $(shell $(PYTHIA8)/bin/pythia8-config --cppflags --libs)

#####CHANGE THESE PATHS TO YOUR OWN ONES
LDFLAGS += -L/home/alidock/.sw/slc7_x86-64/cgal/latest-aliroot6-user-next-root6/lib/ -lCGAL
LDFLAGS += -L/home/alidock/.sw/slc7_x86-64/GMP/latest-aliroot6-user-next-root6/lib/ -lgmp
CXXFLAGS  += $(INCS)
LDFLAGS += $L -ldl

HDRSDICT = src/AliJBaseCard.h src/AliJCard.h src/JHistos.h src/AliJBaseTrack.h 

HDRS	+= $(HDRSDICT)  nanoDict.h

SRCS = $(HDRS:.h=.cxx)
OBJS = $(HDRS:.h=.o)

all:            $(PROGRAM)

$(PROGRAM):     $(OBJS) src/AliJConst.h $(PROGRAM).C
		@echo "Linking $(PROGRAM) ..."
		$(CXX)  -lPhysics   -L$(PWD) $(PROGRAM).C $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM) 
		@echo "finally done"

%.cxx:

%: %.cxx
#  commands to execute (built-in):
	$(LINK.cc) $^ $(CXXFLAGS) $(LOADLIBES) $(LDLIBS) -o $@

%.o: %.cxx %.h
#  commands to execute (built-in):
	$(COMPILE.cc) $(OUTPUT_OPTION) $<

clean:
		rm -f $(OBJS) core *Dict* $(PROGRAM).o *.d $(PROGRAM) $(PROGRAM).sl

cl:  clean $(PROGRAM)

nanoDict.cc: $(HDRSDICT)
		@echo "Generating dictionary ..."
		@rm -f nanoDict.cc nanoDict.hh nanoDict.h
		@rootcint nanoDict.cc -c -D$(version) $(HDRSDICT)
