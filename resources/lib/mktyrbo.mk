tyrbo.exe: resources/lib/type_content.o resources/lib/client.o resources/lib/tc.o
	gcc -g resources/lib/type_content.o resources/lib/tc.o resources/lib/client.o -o tyrbo
type_content.o: resources/lib/type_content.c
	gcc -c -g resources/lib/type_content.c
client.o: resources/lib/client.c
	gcc -c -g resources/lib/client.c
tc.o: resources/lib/tc.c
	gcc -c -g resources/lib/tc.c

.PHONY: clean
clean:
	rm resources/lib/*.o tyrbo
