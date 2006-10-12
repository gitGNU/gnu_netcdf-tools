CC = gcc
CFLAGS = -Wall
CPPFLAGS = -I/home/anton/include -I/var/home/anton/modis/include
LDFLAGS = -L/var/home/anton/modis/lib -lmfhdf -ldf -ljpeg -lz -lm

hdfdump: hdfdump.o hdfindex.o hdf_memory_alloc.o hdf_dump_array.o hdf_print_info.o
	$(CC) $^ $(LDFLAGS) $(CFLAGS) -o $@

.o: .c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

dist-clean: clean
	rm -f hdfdump

clean:
	rm -f *.o
