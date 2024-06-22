Deitel 7.25.
	Existe un algoritmo sencillo para recorrer los laberintos, que garantiza el poder encontrar la salida (asumiendo que existe una salida). Si no existe salida, usted llegará de nuevo a la ubicación inicial.Coloque su mano derecha en la pared y comience a caminar hacia delante. Nunca despegue su mano de la pared, seguirá la pared hacia la derecha. Mientras usted no mueva su mano de la pared, tarde o temprano llegará a la salida del laberinto.



El laberinto del minotauro.
	Teseo salió del laberinto del Minotauro gracias a la ayuda de Ariadna, hija de Minos y Pasífae. Ariadna se enamoró de Teseo y le enseñó un ardid para salir del laberinto: desenrollar un hilo a medida que avanzaba por el laberinto para poder salir más tarde.



Breve relato de mi código.
	En mi caso, utilicé la mano izquierda debido a que mi inicio se encuentra en la esquina inferior derecha. De esta forma, el personaje sigue una secuencia de prioridad en cada cruce, eligiendo en el orden de izquierda, abajo, arriba, y derecha para lograr un posible recorrido más corto hasta el final.

	Para comprender mejor esto, imagina que la "O" que se va moviendo dentro del tablero es una persona que constantemente tiene apoyada la mano en la pared. Al llegar a un camino sin salida, la persona "O" vuelve hasta el cruce anterior, donde tendrá prioridad el recorrido mencionado anteriormente, sin despegar la mano izquierda.
	
	Es posible cambiar esta logica del "recorrido de la mano izquierda" modificando el orden en el que se coloca las direcciones en arriba, abajo,derecha, izquierda haciendo que recorra mayor parte del laberinto. 

	Para poder realizar todo esto, utilicé una pila. Cada paso que da el personaje es guardado en dicha pila y en cada paso se analiza si existe una o más posibles jugadas. Al llegar a un camino sin jugadas posibles, los pasos son retirados de la pila, generando así la vuelta atrás y volviendo al cruce, donde tomará el siguiente camino disponible. Al mismo tiempo que se retira el camino sin salida de la pila, la matriz se llena con una "X" para saber por dónde ya ha pasado.

	Siguiendo el mito del laberinto del Minotauro, a medida que avanza el personaje va dejando un rastro de "O" para que podamos ver todo el camino recorrido por nuestro aventurero del laberinto.
