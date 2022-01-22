.PHONY : clean execute

COMPILER = gcc
OUTPUT = output.exe
ENTRY = a48277_a48389.c

execute : $(OUTPUT)
	./$<

$(OUTPUT) : $(ENTRY)
	$(COMPILER) -o $@ $< -Wall -std=c99

clean :
	rm *.o *.exe *.out *.txt
