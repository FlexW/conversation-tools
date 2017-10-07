all: dtoh htod

install: all
	cp dtoh /usr/bin/
	cp htod /usr/bin

dtoh: common.o
	$(CC) -o dtoh common.o dec_to_hex.c -lgmp

htod: common.o
	$(CC) -o htod common.o hex_to_dec.c -lgmp

common.o:
	$(CC) -c common.c

clean:
	rm -rf common.o htod dtoh

uninstall:
	rm -Rf /usr/bin/dtoh
	rm -Rf /usr/bin/htod
