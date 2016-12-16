doit: doit.c doit.h process_data.c process_data.h
	gcc -w -o doit doit.c process_data.c

clean:
	rm -f *.o doit
