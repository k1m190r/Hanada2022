# C = cc -std=c2x
C = c++ -std=c++23
CFLAGS = -no-pie -fsanitize=address -Wall -Wextra -pedantic -lm -Werror

# get the top most directory
D = $(shell ls | sort | head -1)


main:
	mkdir -p $(D)/out
	$(C) $(CFLAGS) $(D)/main.c*  -o $(D)/out/main
	objdump -M intel -s -d $(D)/out/main > $(D)/out/main.objdump.asm
	$(D)/out/main
	
