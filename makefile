resultado.png : Ejercicio30.py resultado.dat
	python Ejercicio30.py

resultado.dat : Ejercicio30.x
	./Ejercicio30.x 

Ejercicio30.x : Ejercicio30.cpp
	c++ Ejercicio30.cpp -o Ejercicio30.x
	
clean : 
	rm Ejercicio29.x resultado.dat resultado.png 
