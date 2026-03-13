
bin/student: obj/student.o obj/main.o
	gcc obj/student.o obj/main.o -o bin/student

obj/main.o: src/main.c include/student.h include/structure.h
	gcc -c src/main.c -o obj/main.o

obj/student.o: src/student.c include/student.h include/structure.h
	gcc -c src/student.c -o obj/student.o

clean:
	rm obj/* bin/*
	