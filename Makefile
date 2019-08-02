BIN=../gbdk-n/bin
OBJ=./obj



build:
	mkdir -p $(OBJ)
	$(BIN)/gbdk-n-compile.sh print.c -o $(OBJ)/print.rel
	$(BIN)/gbdk-n-link.sh $(OBJ)/print.rel -o $(OBJ)/print.ihx
	$(BIN)/gbdk-n-make-rom.sh $(OBJ)/print.ihx print.gb

clean:
	rm -rf $(OBJ)
	rm -f print.gb
