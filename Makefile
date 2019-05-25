CC = g++ -std=c++11

a.out: main.o Commands.o Network.o Admin.o User.o Publisher.o Film.o Comment.o Exceptions.o
	$(CC) main.o Commands.o Network.o Admin.o User.o Publisher.o Film.o Comment.o Exceptions.o

main.o: main.cpp Network.h Commands.h
	$(CC) -c main.cpp

Exceptions.o: Exceptions.cpp Exceptions.h
	$(CC) -c Exceptions.cpp

Commands.o: Commands.cpp Commands.h Exceptions.h
	$(CC) -c Commands.cpp

Network.o: Network.cpp Network.h User.h Publisher.h Film.h Admin.h
	$(CC) -c Network.cpp

Admin.o: Admin.cpp Admin.h
	$(CC) -c Admin.cpp

User.o: User.cpp User.h Publisher.h Film.h Comment.h
	$(CC) -c User.cpp

Publisher.o: Publisher.cpp Publisher.h Film.h
	$(CC) -c Publisher.cpp

Film.o: Film.cpp Film.h User.h Comment.h
	$(CC) -c Film.cpp

Comment.o: Comment.cpp Comment.h
	$(CC) -c Comment.cpp
	

.PHONY: clean
clean:
	rm *.o
	rm a.out