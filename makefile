difusion.png : Ejercicio29.py difusion.dat
	python Ejercicio29.py

difusion.dat : Ejercicio29.x
	./Ejercicio29.x 

Ejercicio29.x : Ejercicio29.cpp
	c++ Ejercicio29.cpp -o Ejercicio29.x
	
clean : 
	rm Ejercicio29.x difusion.dat difusion.png 
