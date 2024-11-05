.PHONY: gcc-compile build valgrind format

BUILD_DIR=build
INCLUDE_DIR=src
TARGET=compiler

CORE_DEPS=$(BUILD_DIR)/lex.o $(BUILD_DIR)/file.o $(BUILD_DIR)/characters.o
ALL_DEPS=$(BUILD_DIR)/main.o $(CORE_DEPS)

GCC_PROJ=gcc -I ${INCLUDE_DIR} -Wall -Wextra -pedantic

GCC_NO_OPTIMIZATION_FLAGS=-fverbose-asm -fno-asynchronous-unwind-tables -fno-pie -fno-stack-protector 
GCC_32=gcc -m32



gcc-compile: test/$(TARGET).c
	$(GCC_32) -S $(GCC_NO_OPTIMIZATION_FLAGS) test/$(TARGET).c -o gcc/$(TARGET).s

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./compiler test/simple.c

format:
	clang-format -i src/**/*

build: $(ALL_DEPS)
	$(GCC_PROJ) $^ -o $(TARGET)

# Project targets

${BUILD_DIR}/main.o: src/main.c $(CORE_DEPS)
	$(GCC_PROJ) -c $< -o $@

${BUILD_DIR}/lex.o: src/lexer/lex.c
	$(GCC_PROJ) -c $^ -o $@

${BUILD_DIR}/file.o: src/utils/file.c
	$(GCC_PROJ) -c $^ -o $@

${BUILD_DIR}/characters.o: src/utils/characters.c
	$(GCC_PROJ) -c $^ -o $@
