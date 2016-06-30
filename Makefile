# Compiler
CPP=g++

# The folder containing:
# source files *.cpp, header files *.h, objects *.o, executable
HEAD_DIR=Include
OBJ_DIR=Obj
BIN_DIR=Bin

# Compiler options
# -fopenmp (multithreading, linux only)
# -g (debug) / -O6 (optimized)
CFLAGS=-I Include -g -Wall -pedantic
# linked libraries
GLLIBS= -lstdc++


# List of header files
HEAD_FILES= $(wildcard $(HEAD_DIR)/*.h)

# the executable
all: MyExec

# create the executable
MyExec: $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	@echo "link $(BIN_DIR)/$@"
	@$(CPP) -o $(BIN_DIR)/$@ $^ $(CFLAGS) $(GLLIBS)

# create main.o
$(OBJ_DIR)/main.o: main.cpp $(HEAD_FILES)
	@mkdir -p $(OBJ_DIR)
	@echo "compile $@ ($(CPP))"
	@$(CPP) -o $@ -c $< $(CFLAGS)


# clean the objects (Everything will be compile from scratch!)
clean:
	@echo "clean objects"
	@rm -R -f $(OBJ_DIR)

# complete cleanning (clean + delete the executable)
Clean: clean
	@echo "clean binaries and temporary files"
	@rm -R -f $(BIN_DIR)
	@find . -name "*~" -exec rm {} \;

# Generate the documentation
doc: $(HEAD_FILES) main.cpp doc/Doxyfile doc/mainpage.dox
	@echo "generate documentation"
	@doxygen doc/Doxyfile


