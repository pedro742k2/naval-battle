.PHONY : clean execute

COMPILER = gcc
OUTPUT = game.exe
OUTPUT_DIR = "../dist"
ENTRY = main.c

$(OUTPUT_DIR)/$(OUTPUT) : $(ENTRY)
	mkdir -p $(OUTPUT_DIR)
	$(COMPILER) -o $(OUTPUT_DIR)/$@ $< -Wall -std=c99

execute : $(OUTPUT_DIR)/$(OUTPUT)
	$(OUTPUT_DIR)/$<

clean :
	rm *.o $(OUTPUT_DIR)/*.exe *.out; rm -r ../dist/
