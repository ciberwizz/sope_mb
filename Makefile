all: util server admin user testUser testServer

util.o: util.c util.h
	gcc -c util.h util.c
	
server: server.o util.o
	gcc server.o util.o -o server
	
server.o: server.c 
	gcc -c server.c
	
user: user.o util.o
	gcc user.o util.o -o user
	
user.o: user.c
	gcc -c user.c
	
admin: admin.o util.o
	gcc admin.o util.o -o admin
	
admin.o: admin.c
	gcc -c admin.c
	
testUser: testUser.o util.o
	gcc testUser.o util.o -pthread -o testUser
	
testUser.o: testUser.c
	gcc -c testUser.c -pthread

testServer: testServer.o util.o
	gcc testServer.o util.o -pthread -o testServer 
	
testServer.o: testServer.c
	gcc -c testServer.c -pthread
	
clean:
	rm -rf *.o *.gch util server admin user testUser testServer
