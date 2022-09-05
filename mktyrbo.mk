Tyrbo.exe: type_content.o client.o tc.o
	gcc -g type_content.o tc.o client.o -o Tyrbo -lcurses
type_content.o: type_content.c
	gcc -c -g type_content.c
client.o: client.c
	gcc -c -g client.c
tc.o: tc.c
	gcc -c -g tc.c