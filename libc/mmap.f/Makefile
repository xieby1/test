CC = gcc
CFLAGS = -g -I../../include/ -I./ -m32

shared_writable_4x4k_page: shared_writable_4x4k_page.c
	${CC} -o $@ $< ${CFLAGS} -lrt

4x4k_pages_access_prot: 4x4k_pages_access_prot.c
	${CC} -o $@ $< ${CFLAGS} -lrt
