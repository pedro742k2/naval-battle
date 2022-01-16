.PHONY : clean execute

COMPILER = gcc
OUTPUT = output.exe
ENTRY = BatalhaNaval.c

execute : $(OUTPUT)
	./$<

$(OUTPUT) : $(ENTRY)
	$(COMPILER) -o $@ $< -Wall -std=c99

clean :
	rm *.o *.exe *.out *.txt
