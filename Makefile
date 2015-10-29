NAME		=	game
CC			=	gcc
CXX			=	g++
LD			=	ld
LIBS		=	-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CFLAGS		=	-O3 -Wall
CXXFLAGS	=	$(CFLAGS) -std=c++11 -Weffc++ -I/usr/include/SDL2 -D_REENTRANT
DEBUGFLAGS	=	-g -O0
LDFLAGS		=	$(LIBS)

EXE			=	$(NAME).out
DEBUGEXE	=	$(NAME).debug
CFILES		=	$(wildcard src/*.c) $(wildcard src/engine/*.c)
CXXFILES	=	$(wildcard src/*.cpp) $(wildcard src/engine/*.cpp)
OBJECTS		=	$(CFILES:.c=.o) $(CXXFILES:.cpp=.o)

help:
	@echo "Usage:"
	@echo -e "  make all"
	@echo -e "    Build the executable."

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) -o $(EXE) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

#debug : $(OBJECTS)
#	$(CXX) $(OBJECTS) $(DEBUGFLAGS) $(LFLAGS) -o $(EXECUTABLE).debug

.PHONY: clean

clean:
	rm -rf $(EXE) $(OBJECTS)

# vim: set expandtab!

