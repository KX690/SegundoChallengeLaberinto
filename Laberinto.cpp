#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int fila = 15;
const int columna = 15;
char matriz[fila][columna];
int creador[] = {fila-2, columna-1};
int jugador[] = {fila-1, columna-1};
char P = '#', C = '.';
// izquierda/abajo/arriba/derecha
int direcciones[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
char matriz_juego[fila][columna];




struct Nodo {
    int x;
    int y;
    Nodo(int _x, int _y) : x(_x), y(_y) {}
};

void crear_bordes();
void callejon(int i, int num, int lado);
void crear_laberinto();
void movimiento_futuro();
void imprimir_matriz();
bool mover_jugador(stack<Nodo>& camino);

int main() {
    crear_laberinto();

    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz_juego[i][j] = matriz[i][j];
        }
    }

    stack<Nodo> camino;
    camino.push(Nodo(jugador[0], jugador[1]));

    while (jugador[0]!=0 && jugador[1]!=0) {
        if (mover_jugador(camino)) {
            sleep(1);
            imprimir_matriz();
            cout << endl;
        } else {
            break;
        }
    }

    return 0;
}
//Con la posicion actual de mi jugador mas las direcciones posibles creamos los posibles movimientos a futuros
void movimiento_futuro(int futuros[4][2]) {
    for (int i = 0; i < 4; i++) {
        futuros[i][0] = jugador[0] + direcciones[i][0];
        futuros[i][1] = jugador[1] + direcciones[i][1];
    }
}

bool mover_jugador(stack<Nodo>& camino) {
    int futuros[4][2];
    movimiento_futuro(futuros);

    for (int i = 0; i < 4; i++) {
        int x = futuros[i][0];
        int y = futuros[i][1];

        if (x >= 0 && x < fila && y >= 0 && y < columna && matriz_juego[x][y] == C) {
            jugador[0] = x;
            jugador[1] = y;
            camino.push(Nodo(x, y));
            matriz_juego[x][y] = 'o';
            return true;
        }
    }

    // Si no se puede mover, retroceder
    if (!camino.empty()) {
        Nodo anterior = camino.top();
        camino.pop();
        matriz_juego[anterior.x][anterior.y] = 'X';
        if (!camino.empty()) {
            Nodo nuevo_actual = camino.top();
            jugador[0] = nuevo_actual.x;
            jugador[1] = nuevo_actual.y;
            return true;
        }
    }
    return false;
}

void crear_bordes() {
    for (int i = 0; i < columna; i++) {
        if (matriz[0][i] != C) {
            matriz[0][i] = P;
        }
    }

    for (int i = 0; i < columna; i++) {
        if (matriz[fila-1][i] != C) {
            matriz[fila-1][i] = P;
        }
    }

    for (int i = 0; i < fila; i++) {
        if (matriz[i][0] != C) {
            matriz[i][0] = P;
        }
    }

    for (int i = 0; i < fila; i++) {
        if (matriz[i][columna-1] != C) {
            matriz[i][columna-1] = P;
        }
    }
}

void callejon(int lado) {
    if (lado == 1) {
        int aux = creador[1];
        //Izquierda
        for (int j = 0; j < 2; j++) {
            aux -= 1;
            if (matriz[creador[0]][aux] != P) {
                matriz[creador[0]][aux] = C;
            }
        }

        for (int j = 0; j < 3; j++) {
            //Abajo
            if (matriz[creador[0] + j][aux] != P) {
                matriz[creador[0] + j][aux] = C;
            }
            //Arriba
            if (matriz[creador[0] - j][aux] != P) {
                matriz[creador[0] - j][aux] = C;
            }
        }
    }

    if (lado == 2) {
        int aux = creador[0];
        //Arriba
        for (int j = 0; j < 2; j++) {
            aux -= 1;
            if (matriz[aux][creador[1]] != P) {
                matriz[aux][creador[1]] = C;
            }
        }

        for (int j = 0; j < 3; j++) {
            //Derecha
            if (matriz[aux][creador[1] + j] != P) {
                matriz[aux][creador[1] + j] = C;
            }
            //Izquierda
            if (matriz[aux][creador[1] - j] != P) {
                matriz[aux][creador[1] - j] = C;
            }
        }
    }
   
    
    

}

void crear_laberinto() {
    srand(time(0));
    bool b=true;
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz[i][j] = ' ';
        }
    }
    //Coloca el punto de entrada
    matriz[fila-2][columna-1] = C;
    srand(time(0));

    crear_bordes();
    //Genera la ruta correcta y a la vez algunos callejones sin salida, proximamente, en los espacios no ocupados se generarian paredes o mas caminos de manera aleatoria
    while (creador[0] > 0 && creador[1] > 0) {
        int num = rand() % 3 + 2;
        for (int i = 0; i < num; i++) {
            creador[1] -= 1;
            if (creador[1] >= 0) {
                matriz[creador[0]][creador[1]] = C;
            }
            if (i == (num-1) && creador[1] >= 2) {
                callejon(1);
            }
        }

        num = rand() % 3 + 2;
        for (int i = 0; i < num; i++) {
            creador[0] -= 1;
            if (creador[1] >= 0 && b == true) {
                matriz[creador[0]][creador[1]] = C;
            }
            if (i == (num-1) && creador[0] >= 2) {
                callejon(2);
            }
        }
    }
    //Genera caminos o pared en los lugares aun libre, con una posibilidad de 20% a que sea camino y 80% que sea pared de manera aleatoria
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            int num = rand() % 10 + 1;

            if (matriz[i][j] != C && matriz[i][j] != P) {
                switch (num) {
                    case 1:
                        matriz[i][j] = '#';
                        break;
                    case 2:
                        matriz[i][j] = '#';
                        break;
                    case 3:
                        matriz[i][j] = '.';
                        break;
                    case 4:
                        matriz[i][j] = '#';
                        break;
                    case 5:
                        matriz[i][j] = '#';
                        break;
                    case 6:
                        matriz[i][j] = '#';
                        break;
                    case 7:
                        matriz[i][j] = '.';
                        break;
                    case 8:
                        matriz[i][j] = '#';
                        break;
                    case 9:
                        matriz[i][j] = '#';
                        break;
                    case 10:
                        matriz[i][j] = '#';
                        break;
                }
            }
        }
    }
    //imprime la matriz creada por primera vez
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
}
//imprime la matriz 
void imprimir_matriz() {
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            if(matriz_juego[i][j]=='o'){
                cout <<"\033[32mo\033[0m "  ;
            }
            else if(matriz_juego[i][j]=='X'){
                cout << "\033[31mX\033[0m ";
            }else{
                cout << matriz_juego[i][j] << " ";
            }
            
        }
        cout << endl;
    }
}
