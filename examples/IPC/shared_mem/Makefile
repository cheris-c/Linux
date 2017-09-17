all: reader writer

writer: writer.c  share_mem.h
	gcc writer.c -o writer -g

reader: reader.c share_mem.h
	gcc reader.c -o reader -g

clean:
	rm reader; 
	rm writer; 
	rm core.*

