all:
	gcc src/*/*.c src/*/*/*.c -Iinclude -lsqlite3 -lpthread -ljson -o bin/myapp

armapp:
	arm-none-linux-gnueabi-gcc src/*/*.c src/*/*/*.c -Iinclude -lsqlite3 -lpthread -ljson -o bin/myapp

run:
	bin/myapp

clean:
	rm bin/*
