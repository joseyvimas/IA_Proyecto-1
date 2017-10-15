//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
using namespace std;

int main(){
	int N; //Filas
	int M; //Columnas
	int T; //Tiempo
	
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	char hangar[N][M];  
	
	//Llenando el hangar
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cin >> hangar[i][j];
		}
	}
	return 0;
}
