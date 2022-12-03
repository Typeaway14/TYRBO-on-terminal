CC := gcc
CFLAGS := -g
obj_files := type_structures.o type_content.o client.o tc.o art.o misc.o signal_handlers.o

tyrbo.exe: ${obj_files}
	${CC} ${CFLAGS} ${addprefix resources/bin/,${obj_files}} -o tyrbo
%.o: resources/src/%.c
	${CC} -c ${CFLAGS} ${<} -o resources/bin/${@}