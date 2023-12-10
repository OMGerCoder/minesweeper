CXX=g++
CXXFLAGS_RELEASE=-O2 -Wall -Wno-missing-braces -I ./include/
CXXFLAGS_DEBUG=-Wall -Wno-missing-braces -g -DDEBUG -I ./include/
LDFLAGS=-L ./lib/ -mwindows -lraylib -lopengl32 -lgdi32 -lwinmm -static

SRCDIR=./src
BINDIR=./build

CXXFILES=$(wildcard $(SRCDIR)/*.cpp)
OBJFILES=$(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(CXXFILES))

all: release dist

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: $(BINDIR)/Game_debug.exe

release: CXXFLAGS = $(CXXFLAGS_RELEASE)
release: $(BINDIR)/Game.exe
dist: $(BINDIR)/Game.exe
	make -C $(BINDIR)

$(BINDIR)/Game.exe: $(OBJFILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BINDIR)/Game_debug.exe: $(OBJFILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

run:
	$(BINDIR)/Game.exe

run_debug:
	$(BINDIR)/Game_debug.exe

clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/Game.exe $(BINDIR)/Game_debug.exe $(BINDIR)/Minesweeper_setup.exe
	make -C $(BINDIR) clean

.PHONY: all debug release run run_debug clean
