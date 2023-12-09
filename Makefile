CXX=g++
CXXFLAGS=-O2 -Wall -Wno-missing-braces -I ./include/
LDFLAGS=-L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

SRCDIR=./src
BINDIR=./build

CXXFILES=$(wildcard $(SRCDIR)/*.cpp)
OBJFILES=$(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(CXXFILES))


all: $(BINDIR)/Game.exe

$(BINDIR)/Game.exe: $(OBJFILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
run:
	$(BINDIR)/Game.exe
clean:
	rm -f $(BINDIR)/*.o $(BINDIR)/Game.exe