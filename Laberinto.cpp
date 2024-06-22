#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

int fila, columna;
char **matriz;
char **matriz_juego;
int *creador;
int *jugador;
char P = '#', C = '.';
// izquierda/abajo/arriba/derecha
int direcciones[4][2];


struct Nodo {
    int x;
    int y;
    Nodo(int _x, int _y) : x(_x), y(_y) {}
};

void crear_bordes();
void callejon(int lado);
void crear_laberinto();
void movimiento_futuro(int futuros[4][2]);
void imprimir_matriz();
bool mover_jugador(stack<Nodo>& camino);

int main() {
    int eleccion=0;
    cout<<endl;
    cout<<"\033[31m*************************** Bienvenido al laberinto ***************************\033[0m "<<endl;
    cout<<"\033[31mSi le gustaria saber mas sobre el codigo puede leer el README en el repositorio\033[0m "<<endl;
    cout<<"\033[31m********************************** Comencemos *********************************\033[0m "<<endl;
    cout<<endl;
    while(eleccion!=1 && eleccion!=2){
        cout<<"****************** Elija su manera de recorrer el laberinto *******************"<<endl;
        cout<<"1. Apollando la mano izquierda a la pared (DFS)"<<endl;
        cout<<"2. Recorrer el laberinto y probar cada callejon usando solo (Backtracking)"<<endl;
        cin>>eleccion;
    }

    if(eleccion==1){
        // izquierda/abajo/arriba/derecha
        //{{1,0}, {0,-1}, {-1,0}, {0,1}}
        direcciones[0][0]=1;
        direcciones[0][1]=0;
        direcciones[1][0]=0;
        direcciones[1][1]=-1;
        direcciones[2][0]=-1;
        direcciones[2][1]=0;
        direcciones[3][0]=0;
        direcciones[3][1]=1;
         
    }else{
        //arriba/abajo/derecha/izquierda
        //{{-1,0}, {1,0}, {0,1}, {0,-1}}
        direcciones[0][0]=-1;
        direcciones[0][1]=0;
        direcciones[1][0]=1;
        direcciones[1][1]=0;
        direcciones[2][0]=0;
        direcciones[2][1]=1;
        direcciones[3][0]=0;
        direcciones[3][1]=-1;
    }
    
    cout << "Ingrese el tamaño del laberinto (fila): ";
    cin >> fila;
    cout << "Ingrese el tamaño del laberinto (columna): ";
    cin >> columna;
    //Asigno la memoria a la matriz
    matriz = new char*[fila];
    matriz_juego = new char*[fila];
    for (int i = 0; i < fila; i++) {
        matriz[i] = new char[columna];
        matriz_juego[i] = new char[columna];
    }

    creador = new int[2]{fila-2, columna-1};
    jugador = new int[2]{fila-1, columna-1};

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
    cout<<"\033[32mFelicidades aventurero, haz salido del laberinto\033[0m"<<endl;
    //Libera memoria dinamicamente
    for (int i = 0; i < fila; i++) {
        delete[] matriz[i];
        delete[] matriz_juego[i];
    }
    delete[] matriz;
    delete[] matriz_juego;
    delete[] creador;
    delete[] jugador;

    return 0;
}
//Cargamos los futuros movimientos sumando la posicion del jugador mas las direcciones posibles
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

    //Si no se puede mover, retroceder
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
//Antes de crear los callejones, se genera el borde del mapa
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
            if (aux >= 0 && matriz[creador[0]][aux] != P) {
                matriz[creador[0]][aux] = C;
            }
        }

        for (int j = 0; j < 3; j++) {
            //Abajo
            if (creador[0] + j < fila && matriz[creador[0] + j][aux] != P) {
                matriz[creador[0] + j][aux] = C;
            }
            //Arriba
            if (creador[0] - j >= 0 && matriz[creador[0] - j][aux] != P) {
                matriz[creador[0] - j][aux] = C;
            }
        }
    }

    if (lado == 2) {
        int aux = creador[0];
        //Arriba
        for (int j = 0; j < 2; j++) {
            aux -= 1;
            if (aux >= 0 && matriz[aux][creador[1]] != P) {
                matriz[aux][creador[1]] = C;
            }
        }

        for (int j = 0; j < 3; j++) {
            //Derecha
            if (creador[1] + j < columna && matriz[aux][creador[1] + j] != P) {
                matriz[aux][creador[1] + j] = C;
            }
            //Izquierda
            if (creador[1] - j >= 0 && matriz[aux][creador[1] - j] != P) {
                matriz[aux][creador[1] - j] = C;
            }
        }
    }
}

void crear_laberinto() {
    srand(time(0));
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            matriz[i][j] = ' ';
        }
    }
    //Coloca el punto de entrada
    matriz[fila-2][columna-1] = C;

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
            if (creador[0] >= 0) {
                matriz[creador[0]][creador[1]] = C;
            }
            if (i == (num-1) && creador[0] >= 2) {
                callejon(2);
            }
        }
    }
    //Genera caminos o pared en los lugares aun libre, con una posibilidad variable de acuerdo al tamaño
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            int num = rand() % 10 + 1;

            if (matriz[i][j] != C && matriz[i][j] != P) {
                if(fila<25 || columna<25){                  //Si mi laberinto es chico tiene una probabilidad de 20% de ser camino y 80% pared
                    if (num <= 8) {
                        matriz[i][j] = '#';
                    } else {
                        matriz[i][j] = '.';
                    }
                }
                else if (fila<50 || columna<50){           //Si mi laberinto es mediano tiene una probabilidad de 40% de ser camino y 60% pared
                
                    if (num <= 6) {
                        matriz[i][j] = '#';
                    } else {
                        matriz[i][j] = '.';
                    }
                }
                else{
                    if (num <= 5) {                         //Si mi laberinto es grande tiene una probabilidad de 50% de ser camino y 50% pared
                        matriz[i][j] = '#';
                    } else {
                        matriz[i][j] = '.';
                    }
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
    cout << endl;
}

void imprimir_matriz() {
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            if (matriz_juego[i][j] == 'o') {
                cout << "\033[32mo\033[0m ";
            } else if (matriz_juego[i][j] == 'X') {
                cout << "\033[31mX\033[0m ";
            } else {
                cout << matriz_juego[i][j] << " ";
            }
        }
        cout << endl;
    }
}
