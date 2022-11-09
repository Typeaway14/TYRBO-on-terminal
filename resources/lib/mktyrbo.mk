tyrbo.exe: type_content.o client.o tc.o
	gcc -g resources/bin/type_content.o resources/bin/tc.o resources/bin/client.o -o tyrbo
type_content.o: resources/src/type_content.c
	gcc -c -g resources/src/type_content.c -o resources/bin/type_content.o
client.o: resources/src/client.c
	gcc -c -g resources/src/client.c -o resources/bin/client.o
tc.o: resources/src/tc.c
	gcc -c -g resources/src/tc.c -o resources/bin/tc.o