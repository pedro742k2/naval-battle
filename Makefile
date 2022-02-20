.PHONY : clean execute

COMPILER = gcc
OUTPUT = game.exe
ENTRY = main.c

$(OUTPUT) : $(ENTRY)
	$(COMPILER) -o $@ $< -Wall -std=c99

execute : $(OUTPUT)
	./$<

clean :
	rm *.o *.exe *.out *.txt
