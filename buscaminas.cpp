#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//#include <Windows.h>

const int tam = 6;
const int max_bombas = 4;

int contar_bombas_alrededor(int tablero_bombas[tam][tam], int fila, int col){
    int contador = 0;
    for(int i = fila - 1; i <= fila + 1; i++){
        for(int j = col - 1; j <= col + 1; j++){
            if(i >= 0 && i < tam && j >= 0 && j < tam){
                if(tablero_bombas[i][j] == 1){
                    contador++;
                }
            }
        }
    }
    return contador;
}

void renderizar(bool tablero_visible[tam][tam], int tablero_bombas[tam][tam]){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(tablero_visible[i][j]){
                if(tablero_bombas[i][j] == 1){
                    cout << " X ";
                }else{
                    int bombas_cerca = contar_bombas_alrededor(tablero_bombas, i, j);
                    if(bombas_cerca == 0){
                        cout << "   ";
                    }else{
                        cout << " " << bombas_cerca << " ";
                    }
                }
            }else{
                cout << " # ";
            }
            if(j < (tam - 1)){
                cout << "|";
            }
        }
        if(i < (tam -1)){
            cout << "\n-----------------------\n";
        }
    }
    cout << "\n";
}

void descubrir_celda(int tablero_bombas[tam][tam], bool tablero_visible[tam][tam], int fila, int col){
    if(fila < 0 || fila >= tam || col < 0 || col >= tam) return;
    if(tablero_visible[fila][col]) return;
    if(tablero_bombas[fila][col] == 1) return;

    tablero_visible[fila][col] = true;

    int bombas_cerca = contar_bombas_alrededor(tablero_bombas, fila, col);
    if(bombas_cerca == 0){
        for(int i = fila - 1; i <= fila + 1; i++){
            for(int j = col - 1; j <= col + 1; j++){
                if(i != fila || j != col){
                    descubrir_celda(tablero_bombas, tablero_visible, i, j);
                }
            }
        }
    }
}

bool verificar_victoria(bool tablero_visible[tam][tam], int tablero_bombas[tam][tam]){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            if(tablero_bombas[i][j] != 1 && !tablero_visible[i][j]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    srand(time(NULL)); 

    // Set output code page to UTF-8
    //SetConsoleOutputCP(CP_UTF8);

    // Define the Unicode string
    //std::string unicodeString = "\U0001F600";

    // Output the Unicode string
    //std::cout << unicodeString << std::endl;

    //std::cout << "\U0001F922" << "\n";



    // # => Casilla no descubierta
    // 1 => Bomba
    // ' ' => Casilla descubierta sin nada

    bool tablero_visible[tam][tam] = {false};
    int tablero_bombas[tam][tam] = {0};

    int bombas_colocadas = 0;

    while(bombas_colocadas < max_bombas){
        int fila = rand() % tam;
        int columna = rand() % tam;

        if(tablero_bombas[fila][columna] != 1){
            tablero_bombas[fila][columna] = 1;
            bombas_colocadas++;
        }
    }

    bool gameover = false;
    bool victoria = false;

    while(!gameover){
        renderizar(tablero_visible, tablero_bombas);

        // Solicitar posicion de tiro
        int fila, columna;
        cout << "\nIngrese la fila: ";
        cin >> fila;
        cout << "Ingrese la columna: ";
        cin >> columna;

        if(fila < 0 || fila >= tam || columna < 0 || columna >= tam){
            cout << "La casilla seleccionada no se encuentra en el tablero. Intente de nuevo.\n";
            continue;
        }

        if(tablero_visible[fila][columna]){
            cout << "Casilla ya descubierta. Intenta otra.\n";
            continue;
        }

        if(tablero_bombas[fila][columna] == 1){
            tablero_visible[fila][columna] = true;
            gameover = true;
        }else{
            descubrir_celda(tablero_bombas, tablero_visible, fila, columna);
            if (verificar_victoria(tablero_visible, tablero_bombas)){
                victoria = true;
                gameover = true;
            }
        }
    }

    renderizar(tablero_visible, tablero_bombas);

    if(victoria){
        cout << "!Felicidades, descubriste todo el tablero sin pisar ninguna bomba!\n";
    }else{
        cout << "!Boom! Pisaste una bomba. PERDISTE >:).\n";
    }
    
    return 0;
}