all: rgb_rainbow_table

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

LDFLAGS = -lm

objects = rgb_rainbow_table.o

headers = rgb_hsi.h

$(objects): %.o: %.c $(headers)
	cc -c $(CFLAGS) $< -o $@

rgb_rainbow_table: $(objects)
	cc  -o $@ $(objects) $(LDFLAGS) 
