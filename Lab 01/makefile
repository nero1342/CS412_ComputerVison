# make all 			Build the package
# make run			Builds and runs the program
# make clean 		Cleans results of the building and process

# Build Info
EXE			= main
CDEBUG		= -O2
CXXFLAGS	=  $(shell pkg-config --cflags --libs opencv4) $(CDEBUG) $(CFLAGS_PLATFORM) -std=c++11 -O2
LDFLAGS		=  $(shell pkg-config --cflags --libs opencv4)

INCLUDEDIRS = -I"Sources/"
LIBSDIR		=

# Project source files
CFILES = $(shell find Sources -type f -name '*.c')
CXXFILES = $(shell find Sources -type f -name '*.cpp')
OBJECTS = $(CFILES:.c=.o) \
		  $(CXXFILES:.cpp=.o)

# Verbose mode check
ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

# Make targets
all: dirs $(EXE)
	# Build sucessful!

$(EXE): $(OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) -o Release/$(EXE) $(LIBSDIR) $(LDFLAGS)

Sources/%.o: Sources/%.cpp
	# Compiling $<
	$(MUTE)$(CXX) $(CXXFLAGS) $(CDEBUG) $< -c -o $@ $(INCLUDEDIRS)

run: all
	# Running...
	$(MUTE)./Release/$(EXE)

clean:
	# Cleaning object files...
	$(MUTE)rm $(VTAG) -f $(OBJECTS)	
	$(MUTE)rm $(VTAG) -f Release/$(EXE)

dirs:
	$(MUTE)mkdir -p Release
	$(MUTE)mkdir -p Data
	