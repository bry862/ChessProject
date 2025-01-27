CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= main

# Source directories
PIECES_DIR = pieces

# Chess piece objects
PIECE_OBJS = \
	$(PIECES_DIR)/Bishop.o \
	$(PIECES_DIR)/ChessPiece.o \
	$(PIECES_DIR)/King.o \
	$(PIECES_DIR)/Knight.o \
	$(PIECES_DIR)/Pawn.o \
	$(PIECES_DIR)/Queen.o \
	$(PIECES_DIR)/Rook.o

# Core game objects
CORE_OBJS = ChessBoard.o Move.o

# Main program objects
MAIN_OBJS = main.o

# Aggregate objects
OBJS = $(MAIN_OBJS) $(CORE_OBJS) $(PIECE_OBJS)

mainprog: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(PROG) *.o *.out \
		$(PIECES_DIR)/*.o \

rebuild: clean main