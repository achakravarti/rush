LIB_INP = bld/log.o bld/mpool.o bld/string.o
LIB_OUT = bld/librush.so
LIB_OPT = -shared -g -O2


$(LIB_OUT): $(LIB_INP)
	gcc $(LIB_OPT) $(LIB_INP) -o $@


bld/%.o: src/%.c
	mkdir -p bld
	gcc -c -fPIC $(LIB_OPT) $< -o $@

clean:
	rm -rfv bld

