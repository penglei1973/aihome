ROOTFS_DIR = /source/rootfs

all:
	gcc src/*/*.c src/*/*/*.c -Iinclude -lsqlite3 -lpthread -ljson -o bin/myapp

armapp:
	arm-none-linux-gnueabi-gcc src/*/*.c src/*/*/*.c -Iinclude -lsqlite3  -I/home/linux/sqlite3/sqlite3.13/include -L/home/linux/sqlite3/sqlite3.13/lib  -lpthread -ljson -I/home/linux/json/install/include -L/home/linux/json/install/lib -o bin/aihome

run:
	sudo bin/myapp

install:
	cp -rf bin/aihome $(ROOTFS_DIR)/aihome

clean:
	rm bin/*
