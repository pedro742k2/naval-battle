.PHONY : clean execute

COMPILER = gcc
OUTPUT = output.exe
ENTRY = BatalhaNaval.c

execute : $(OUTPUT)
	./$<

$(OUTPUT) : $(ENTRY)
	$(COMPILER) -o $@ $<

clean :
	rm *.o *.exe *.out
