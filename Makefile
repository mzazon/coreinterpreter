SRC = main.cpp
OBJ = tokenizer.o parsetree.o parsetreeleaf.o symboltable.o parser.o printer.o executor.o scanner.o main.o

main: $(OBJ)
	g++ -o main $(OBJ) 
tokenizer.o: tokenizer.cpp
	g++ -c tokenizer.cpp
parsetree.o: parsetree.cpp
	g++ -c parsetree.cpp
parsetreeleaf.o: parsetreeleaf.cpp
	g++ -c parsetreeleaf.cpp
symboltable.o: symboltable.cpp
	g++ -c symboltable.cpp
parser.o: parser.cpp
	g++ -c parser.cpp
printer.o: printer.cpp
	g++ -c printer.cpp
executor.o: executor.cpp
	g++ -c executor.cpp
scanner.o: scanner.cpp
	g++ -c scanner.cpp
main.o: $(SRC)
	g++ -c $(SRC)
clean:
	rm main tokenizer.o parsetree.o parsetreeleaf.o symboltable.o parser.o printer.o executor.o scanner.o main.o
