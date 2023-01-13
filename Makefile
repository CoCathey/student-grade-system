a.out: main.o Student.o
	g++ main.o Student.o -o a.out

main.o: main.cpp
	g++ -c main.cpp

Student.o: Student.cpp
	g++ -c Student.cpp

clean:
	rm *.o a.out

reset:
	rm *.o a.out
