//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
using namespace std;

int N; //Filas del hangar
int M; //Columna del hangar
int T; //Tiempo en el centro de operaciones explotara


//Funcion que verifica si se puede disparar a un Stormtrooper dependiendo las direcciones cardinales, 
//Si se puede disparar, se elimina el Stormtrooper del hangar
void canShoot(char **hangar, int x, int y, string Dir){
	int i;
	if (Dir == "N"){
		for (i=x-1; i>=0; i--){
			if (hangar[i][y] == '*'){
				break;
			}
			else if (hangar[i][y] == 'S'){
				hangar[i][y] = '.';
				break;
			}
		}
		return;
	}
	else if (Dir == "S"){
		for (i=x+1; i<N; i++){
			if (hangar[i][y] == '*'){
				break;
			}
			else if (hangar[i][y] == 'S'){
				hangar[i][y] = '.';
				break;
			}
		}
		return;
	}
	else if (Dir == "E"){
		for (i=y+1; i<M; i++){
			if (hangar[x][i] == '*'){
				break;
			}
			else if (hangar[x][i] == 'S'){
				hangar[x][i] = '.';
				break;
			}
		}
		return;
	}
	else if (Dir == "O"){
		for (i=y-1; i>=0; i--){
			if (hangar[x][i] == '*'){
				break;
			}
			else if (hangar[x][i] == 'S'){
				hangar[x][i] = '.';
				break;
			}
		}
		return;
	}
}


//Disparar a los Stormtrooper
void shootStormtrooper(char **hangar, int x, int y){
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

int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar
	char **hangar;
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

	cout << endl;
	//shootStormtrooper(hangar,1,1);
	/*
			3 10 10 
			SSS......S 
			SL...S...S 
			SSS......S
	 */
	printHangar(hangar);
	
	return 0;
}
