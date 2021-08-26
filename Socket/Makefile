all:Cpp_package_client Cpp_package_server Server Client _client _server multi_progress_server C_package_client C_package_server generate_makefile 

Cpp_package_client:Cpp_package_client.cpp
	g++ -o Cpp_package_client Cpp_package_client.cpp

Cpp_package_server:Cpp_package_server.cpp
	g++ -o Cpp_package_server Cpp_package_server.cpp

Server:Server.cpp
	g++ -o Server Server.cpp

Client:Client.cpp
	g++ -o Client Client.cpp

_client:_client.cpp
	g++ -o _client _client.cpp

_server:_server.cpp
	g++ -o _server _server.cpp

multi_progress_server:multi_progress_server.cpp
	g++ -o multi_progress_server multi_progress_server.cpp

C_package_client:C_package_client.c
	gcc -o C_package_client C_package_client.c

C_package_server:C_package_server.c
	gcc -o C_package_server C_package_server.c

generate_makefile:generate_makefile.c
	gcc -o generate_makefile generate_makefile.c

clean:
	rm -rf Cpp_package_client Cpp_package_server Server Client _client _server multi_progress_server C_package_client C_package_server generate_makefile 
