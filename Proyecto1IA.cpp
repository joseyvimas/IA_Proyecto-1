//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
using namespace std;

// Estructura para almacenar estados
struct state {
    int pos_actual_X;
    int pos_actual_Y;
    int Time_Left;
    char possible_Mov;
    char **hangarAux;
    bool **marcas;
    char *possible_Solution;
} estado;

int N; //Filas del hangar
int M; //Columna del hangar
int T; //Tiempo en el centro de operaciones explotara


//Funcion que verifica si se puede disparar a un Stormtrooper dependiendo las direcciones cardinales
//recibe el hangar, la posición x,y de Luke, y la direccion
bool canShoot(char **hangar, int x, int y, string Dir){
	int i;
	if (Dir == "N" && x-1 >= 0){
		for (i=x-1; i>=0; i--){
			if (hangar[i][y] == '*'){
				return false;
			}
			else if (hangar[i][y] == 'S'){
				return true;
			}
		}
		return false;
	}
	else if (Dir == "S" && x+1 < N){
		for (i=x+1; i<N; i++){
			if (hangar[i][y] == '*'){
				return false;
			}
			else if (hangar[i][y] == 'S'){
				return true;
			}
		}
		return false;
	}
	else if (Dir == "E" && y+1 < M){
		for (i=y+1; i<M; i++){
			if (hangar[x][i] == '*'){
				return false;
			}
			else if (hangar[x][i] == 'S'){
				return true;
			}
		}
		return false;
	}
	else if (Dir == "O" && y-1 >= 0){
		for (i=y-1; i>=0; i--){
			if (hangar[x][i] == '*'){
				return false;
			}
			else if (hangar[x][i] == 'S'){
				return true;
			}
		}
		return false;
	}
	return false;
}

//Disparar a los Stormtrooper
/*void shootStormtrooper(char **hangar, int x, int y){
	if (x-1 >= 0){
		canShoot(hangar,x,y,"N");
	}
	if (x+1 < N){
		canShoot(hangar,x,y,"S");
	}
	if (y+1 < M){
		canShoot(hangar,x,y,"E");
	}
	if (y-1 >= 0){
		canShoot(hangar,x,y,"O");
	}
}*/


//Usar la fuerza contra los Stormtroopers
bool ForceStormtrooper(char **hangar, int x, int y){
	bool killStormtrooper = false ; //Bandera que indica si se mato un trooper usando la fuerza
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		if (hangar[x-1][y] == 'S'){
			hangar[x-1][y] = '.';
			killStormtrooper = true;
		}
		
	}
	if (x-1 >= 0 && (y-1) >= 0){
		if (hangar[x-1][y-1] == 'S'){
			hangar[x-1][y-1] = '.';
			killStormtrooper = true;
		}
	}
	if (x-1 >= 0 && (y+1) <= M){
		if (hangar[x-1][y+1] == 'S'){
			hangar[x-1][y+1] = '.';
			killStormtrooper = true;
		}
	}
	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		if (hangar[x][y-1] == 'S'){
			hangar[x][y-1] = '.';
			killStormtrooper = true;
		}
	}
	
	if (y+1 < M){
		if (hangar[x][y+1] == 'S'){
			hangar[x][y+1] = '.';
			killStormtrooper = true;
		}
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		if (hangar[x+1][y] == 'S'){
			hangar[x+1][y] = '.';
			killStormtrooper = true;
		}
	}
	if (x+1 < N && (y-1) >= 0){
		if (hangar[x+1][y-1] == 'S'){
			hangar[x+1][y-1] = '.';
			killStormtrooper = true;
		}
	}
	if (x+1 < N && (y+1) <= M){
		if (hangar[x+1][y+1] == 'S'){
			hangar[x+1][y+1] = '.';
			killStormtrooper = true;
		}
	}
}
void printHangar(char **hangar){
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cout << hangar[i][j];
		}
		cout << endl;
	}
}
void getLuke(char **hangar,int &posX,int &posY){
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			if(hangar[i][j] == 'L'){
				posX = i;
				posY = j;
				break;
			}
		}
	}
}
bool solucion(char **hangar, int Tiempo){
	if(Tiempo <= T){
		for (i=0; i<N; i++){
			for (j=0; j<M; j++){
				if(hangar[i][j] == 'S'){
					return false;
				}
			}
		}
		return true;
	}
	else{
		return false;
	}
}

bool moverme(int pos_x, int pos_y, char **marcas, string dir){   
     //Norte
     if (dir == "N"){
        if(pos_x-1 >= 0){
                   if(marcas[pos_x-1][pos_y] == false){
                      return true;
                   }
                   return false;
                   
        }
     }
     //Sur
     else if(dir == "S"){
        if(pos_x+1 < N){
                   if(marcas[pos_x+1][pos_y] == false){
                      return true;
                   }
                   return false;
                   
        }
      
     }
     //Este
     else if(dir == "E"){
        if(pos_y+1 < M){
                   if(marcas[pos_x][pos_y+1] == false){
                      return true;
                   }
                   return false;
        }
     }
     //Oeste
     else if(dir == "O"){
        if(pos_y-1 >= 0){
                   if(marcas[pos_x][pos_y-1] == false){
                      return true;
                   }
                   return false;
        }
     }
}

void encolarVecinos(estado_actual, cola){
	if(fuerza en mi estado actual ){
		//crear estado
		//aplicar cambios
		//encolar
		
	}
	else if(disparar en mi estado actual ){
		if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N")){
			//crear estado
		//aplicar cambios
		//encolar
		}
		if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S"){
			//crear estado
		//aplicar cambios
		//encolar
		}
		if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E"){
			//crear estado
		//aplicar cambios
		//encolar
		}
        if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O"){
			//crear estado
		//aplicar cambios
		//encolar
		}
		
	}
	else{
		if(moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "N")){
			//crear estado
		//aplicar cambios
		//encolar
		}
		if(moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "S")){
			//crear estado
		//aplicar cambios
		//encolar
		}
		if(moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "E")){
			//crear estado
		//aplicar cambios
		//encolar
		}
		if(moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "O")){
			//crear estado
		//aplicar cambios
		//encolar
		}
	}
	
}
void busqueda (cola){
	state = estado_actual;
	estado_actual = cola.top();
	if( solucion(estado_actual.hangarAux,estado_actual.Time_Left) ){
		return estado_actual.possible_Solution;
	}
	encolarVecinos(estado_actual,cola);
	cola.pop();
	busqueda(cola);
}
int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar
	char **hangar;
	//Creamos a flag 
	bool IKill=false;
	//Posicion de Luke
	int posX,posY;
	
	//Dandole dimensiones al hangar
	//Array de punteros de char (A las filas solamente)
    hangar = new char*[N];
	//Ahora a las columnas
    for(int x=0; x<N; x++)
        hangar[x] = new char[M]; 
	
	//Llenando el hangar
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cin >> hangar[i][j];
		}
	} 
	
	//Se le da dimensiones a la matriz auxiliar del struct y se marca como no visitada
    estado.hangarAux = new bool*[N];
    
    for(int x=0; x<N; x++){
        estado.hangarAux[x] = new bool[M]; 
        estado.hangarAux[x] = false;
    }

	cout << endl;
	
	//shootStormtrooper(hangar,1,1);
	/*
			3 10 10 
			SSS......S 
			SL...S...S 
			SSS......S
	 */
	//IKill = ForceStormtrooper(hangar ,1,1);
	
	
	printHangar(hangar);
	cout<< endl;
		
    /* Crear cola para el BFS
    list<state> queue;*/
	

	system("pause");
	return 0;
}

