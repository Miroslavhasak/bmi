all: bmi
bmi: client server
	gcc -o client bmi_c.c
	gcc -o server bmi_s.c
	
