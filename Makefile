SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/ytsubsearcher.exe

SRC := $(wildcard $(SRC_DIR)/*.cpp)

OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS := -std=c++11 -lstdc++fs
CFLAGS   :=
LDFLAGS  :=
LDLIBS   := -std=c++11 -lstdc++fs

all: $(EXE)

.PHONY: all

$(EXE): $(OBJ)
		g++ $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		g++ $(CXXFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
		mkdir -p $@

clean:
		@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) # The @ disables the echoing of the command

-include $(OBJ:.o=.d) # The dash is used to silence errors if the files don't exist yet