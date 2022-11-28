all: 
	make bmi
bmi: 
	gcc -o client client.c
	gcc -o server server.c
	
