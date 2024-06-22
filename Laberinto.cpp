#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
const int fila=15;
const int columna=15;
char matriz[fila][columna];
int creador[]={fila-2,columna-1};
int jugador[]={fila-2,columna-1};
bool b=true;
char P='#',C='.';
//abajo/arriba/derecha/izquierda
int direcciones[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int futuro[4][2];
char matriz_juego[fila][columna];

struct Nodo{
    int x;
    int y;
    Nodo *siguiente;
};
Nodo *pila=NULL;
void agregar_pila(Nodo *&pila,int x, int y){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->x =x;
    nuevo_nodo->y=y;
    pila = nuevo_nodo;

}

void sacar_pila(Nodo *&pila,int &x1,int &y1){
    Nodo *aux =pila;
    x1 = aux->x;
    y1 = aux->y;
    pila = aux->siguiente;
    delete aux;
}

void crear_borde();
void callejon(int i,int num,int lado);
void crear_laberinto();
void movimiento_futuros();
void movimiento_futuro();
void imprimir_matriz();

int main() {
    crear_laberinto();


    
    
    for (int i=0;i<fila;i++){
        for(int j=0;j<columna;j++){
            matriz_juego[i][j]=matriz[i][j];
        }
    }
    while(jugador[0]>0 && jugador[1]>0){
        movimiento_futuro();
        matriz[jugador[0]][jugador[1]]='x';


    }
    

}

void movimiento_futuro(){
    int cont=0;
    int x;
    int y;
    for(int i; i<4; i++){
        futuro[i][0]=jugador[0]+direcciones[i][0];
        futuro[i][1]=jugador[1]+direcciones[i][1];
    }
    for(int i=0;i<4;i++){
        if((futuro[i][0]>0 and futuro[i][0]<fila) && (futuro[i][1]<columna && futuro[i][1]>0)){
            if(matriz_juego[futuro[i][0]][futuro[i][1]]=='*'){
                x=futuro[i][0];
                y=futuro[i][1];

                cont++;
            }   
        }

    }
    if(cont==1){
        jugador[0]=x;
        jugador[1]=y;
    }else{
        agregar_pila(pila,jugador[0],jugador[1]);

        matriz_juego[jugador[0]][jugador[1]]='#';
        jugador[0]=x;
        jugador[1]=y;
    }
        
}


void crear_bordes(){

    
    for(int i=0;i<columna;i++){
        if(matriz[0][i]!=C){
            matriz[0][i]=P;
        }
    }

    for(int i=0;i<columna;i++){
        if(matriz[fila-1][i]!=C){
            matriz[fila-1][i]=P;
        }
    }


    for(int i=0;i<fila;i++){
        if(matriz[i][0]!=C){
            matriz[i][0]=P;
        }
    }

    for(int i=0;i<fila;i++){
        if(matriz[i][columna-1]!=C){
            matriz[i][columna-1]=P;
        }
    }

}

void callejon(int i,int num,int lado){
    
    if(lado==1){
        int aux = creador[1];
       
            //Izquierda
            for(int j=0;j<2;j++){

                aux-=1;
                if(matriz[creador[0]][aux]!=P){
                    matriz[creador[0]][aux]=C;
                }
                

            }
            
            for(int j=0;j<3;j++){
                //Abajo
                if(matriz[creador[0]+j][aux] != P){
                    matriz[creador[0]+j][aux]=C;
                }
                //Arriba
                if(matriz[creador[0]-j][aux] != P){
                    matriz[creador[0]-j][aux]=C;
                }

                
            }

    }
    
    if(lado==2){
        int aux = creador[0];
        
            //Arriba
            for(int j=0;j<2;j++){

                aux-=1;
                if(matriz[aux][creador[1]]!=P){
                    matriz[aux][creador[1]]=C;
                }
                
            }
            
            for(int j=0;j<3;j++){
                //Derecha
                if(matriz[aux][creador[1]+j] != P){
                    matriz[aux][creador[1]+j]=C;
                }

                //Izquierda
                if(matriz[aux][creador[1]-j] != P){
                    matriz[aux][creador[1]-j]=C;
                }
                
            }
            
        
    }
    //derecha
    if(lado==3){
        int aux = creador[1];
        if(i==(num-1) && creador[1]>=2){
            for(int j=0;j<2;j++){

                aux+=1;
                if(matriz[creador[0]][aux]!=P){
                    matriz[creador[0]][aux]=C;
                }
                
            }
        }
    }
    
}

void crear_laberinto(){
srand(time(0));

    for(int i=0;i<fila;i++){
        for(int j=0; j<columna;j++){
            matriz[i][j]=' ';
        }
    }

    matriz[fila-2][columna-1]=C;
    srand(time(0));

    crear_bordes();

    while (creador[0]>0 and creador[1]>0){

        int num = rand() % 3 + 2;
        // crea a la izquierda
        for(int i=0;i<num;i++){
            creador[1]-=1;
            if(creador[1]>=0){
                matriz[creador[0]][creador[1]]=C;

            }
            if(i==(num-1) && creador[1]>=2){
                callejon(i,num,1);
            }
        }

        // crea hacia arriba 
        num = rand() % 3 + 2;
        for(int i=0;i<num;i++){
            creador[0]-=1;
            if(creador[1]>=0 && b==true){
                matriz[creador[0]][creador[1]]=C;
            }
            if(i==(num-1) && creador[0]>=2){
                callejon(i,num,2);
            }
        }

    }

    
    

    

    for(int i=0;i<fila;i++){
        for(int j=0; j<columna;j++){
            int num =rand() % 10 + 1;

            if(matriz[i][j]!=C&& matriz[i][j]!=P){

                switch (num){
                    case 1:
                        matriz[i][j]='#';
                        break;
                    case 2:
                        matriz[i][j]='#';
                        break;
                    case 3:
                        matriz[i][j]='.';
                        break;
                    case 4:
                        matriz[i][j]='#';
                        break;
                    case 5:
                        matriz[i][j]='#';
                        break;
                    case 6:
                        matriz[i][j]='#';
                        break;
                    case 7:
                        matriz[i][j]='.';
                        break;
                    case 8:
                        matriz[i][j]='#';
                        break;
                    case 9:
                        matriz[i][j]='#';
                        break;
                    case 10:
                        matriz[i][j]='#';
                        break;
                }
            }

        }
    }



    for(int i=0;i<fila;i++){
        for(int j=0; j<columna;j++){
            cout<<matriz[i][j]<<" " ;
        }
    cout<<endl;
    }

}

void imprimir_laberinto(){

    for(int i=0;i<fila;i++){
        for(int j=0; j<columna;j++){
            cout<<matriz[i][j]<<" " ;
        }
    cout<<endl;
    }

}


