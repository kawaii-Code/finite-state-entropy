SRC = src/main.c src/encoder.c src/decoder.c src/string_operations.c src/encoding_table.c src/fse.c src/symbol_counter.c

all: $(SRC)
	gcc $(SRC) -o fse

debug: $(SRC)
	gcc -g $(SRC) -o fse-debug
