all:
	gcc -o build/main src/main.c src/LOG_LLC_BIBLIO.c src/lists.c src/table.c src/interface.c src/file.c
clean:
	@del /f /build/main.exe
