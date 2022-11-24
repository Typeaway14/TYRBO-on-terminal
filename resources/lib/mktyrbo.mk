tyrbo.exe: type_content.o client.o tc.o type_structures.o art.o
	gcc -g resources/bin/client.o resources/bin/type_content.o resources/bin/art.o resources/bin/type_structures.o resources/bin/tc.o -o tyrbo
type_content.o: resources/src/type_content.c
	gcc -c -g resources/src/type_content.c -o resources/bin/type_content.o
client.o: resources/src/client.c
	gcc -c -g resources/src/client.c -o resources/bin/client.o
tc.o: resources/src/tc.c
	gcc -c -g resources/src/tc.c -o resources/bin/tc.o
type_structures.o: resources/src/type_structures.c
	gcc -c -g resources/src/type_structures.c -o resources/bin/type_structures.o
art.o: resources/src/art.c
	gcc -g -c resources/src/art.c -o resources/bin/art.o