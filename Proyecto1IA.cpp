//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>
using namespace std;

int N; //Filas del hangar
int M; //Columna del hangar
int T; //Tiempo en el centro de operaciones explotara

class  State{
	public:
		int pos_actual_X;
	    int pos_actual_Y;
	    int Time_Left;
	    char possible_Mov;
	    char **hangarAux;
	    bool **marcas;
	    char *possible_Solution;
	    
	    State(){
	    	this->pos_actual_X = 0;
	    	this->pos_actual_Y = 0;
	    	this->Time_Left = 0;
	    	this->hangarAux = new char*[N];
	    	 for(int x=0; x<N; x++){
		        this->hangarAux[x] = new char[M]; 
		        this->hangarAux[x] = false;
		    }
	    	this->marcas = new bool*[N];
	    	for(int x=0; x<N; x++){
		        this->marcas[x] = new bool[M]; 
		        this->marcas[x] = false;
		    }
	    	this->possible_Solution = new char[N];
	    }
	    State( int pos_actual_X, int pos_actual_Y, int Time_Left, char **hangarAux, bool **marcas){
	    	this->pos_actual_X = pos_actual_X;
	    	this->pos_actual_Y = pos_actual_Y;
	    	this->Time_Left = Time_Left;
	    	this->hangarAux = hangarAux;
	    	this->marcas = marcas;
	    	this->possible_Solution = new char[N];
	    }
	    void getLuke(){
			int i,j;
			for (i=0; i<N; i++){
				for (j=0; j<M; j++){
					if(this->hangarAux[i][j] == 'L'){
						this->pos_actual_X = i;
						this->pos_actual_Y = j;
						break;
					}
				}
			}
		}
	    bool solucion(int Tiempo){
			if(Tiempo <= T){
				for (int i=0; i<N; i++){
					for (int j=0; j<M; j++){
						if(this->hangarAux[i][j] == 'S'){
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
};   
//sobrecargar el operador <
bool operator< (const State& structState1, const State &structState2)
{
return structState1.Time_Left > structState2.Time_Left;
}
//sobrecargar el operador > 
bool operator> (const State& structState1, const State &structState2)
{
return structState1.Time_Left < structState2.Time_Left;
}

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
bool CanForceStormtrooper(char **hangar, int x, int y){
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		if (hangar[x-1][y] == 'S'){
			return true;
		}
		
	}
	if (x-1 >= 0 && (y-1) >= 0){
		if (hangar[x-1][y-1] == 'S'){
			return true;
		}
	}
	if (x-1 >= 0 && (y+1) <= M){
		if (hangar[x-1][y+1] == 'S'){
			return true;
		}
	}
	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		if (hangar[x][y-1] == 'S'){
			return true;
		}
	}
	
	if (y+1 < M){
		if (hangar[x][y+1] == 'S'){
			return true;
		}
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		if (hangar[x+1][y] == 'S'){
			return true;
		}
	}
	if (x+1 < N && (y-1) >= 0){
		if (hangar[x+1][y-1] == 'S'){
			return true;
		}
	}
	if (x+1 < N && (y+1) <= M){
		if (hangar[x+1][y+1] == 'S'){
			return true;
		}
	}
	return false;
}
void ForceStormtrooper(char **hangar, int x, int y){
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		if (hangar[x-1][y] == 'S'){
			hangar[x-1][y] = '.';
		}
		
	}
	if (x-1 >= 0 && (y-1) >= 0){
		if (hangar[x-1][y-1] == 'S'){
			hangar[x-1][y-1] = '.';
		}
	}
	if (x-1 >= 0 && (y+1) <= M){
		if (hangar[x-1][y+1] == 'S'){
			hangar[x-1][y+1] = '.';
		}
	}
	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		if (hangar[x][y-1] == 'S'){
			hangar[x][y-1] = '.';
		}
	}
	
	if (y+1 < M){
		if (hangar[x][y+1] == 'S'){
			hangar[x][y+1] = '.';
		}
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		if (hangar[x+1][y] == 'S'){
			hangar[x+1][y] = '.';
		}
	}
	if (x+1 < N && (y-1) >= 0){
		if (hangar[x+1][y-1] == 'S'){
			hangar[x+1][y-1] = '.';
		}
	}
	if (x+1 < N && (y+1) <= M){
		if (hangar[x+1][y+1] == 'S'){
			hangar[x+1][y+1] = '.';
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
		for (int i=0; i<N; i++){
			for (int j=0; j<M; j++){
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

bool moverme(int pos_x, int pos_y, bool **marcas, string dir){   
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

void encolarVecinos(State estado_actual, priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	if(CanForceStormtrooper(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y ) ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
		
	}
	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N")){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S")){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
    if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if( moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "N") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if( moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "S") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if( moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "E") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	if( moverme(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "O") ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		//encolar
		cola.push(nuevo_estado);
	}
	
}


void busqueda (priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	if (cola.empty() ){
		cout<<"no hay solucion";
		return;
	}
	State estado_actual =  State() ;
	estado_actual = cola.top();
	if( solucion (estado_actual.hangarAux, estado_actual.Time_Left ) ){
		/*return estado_actual.possible_Solution;*/
		cout<<"solucion";
	}
	encolarVecinos( estado_actual, cola);
	cola.pop();
	busqueda(cola);
}

int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar y marcador de visitados
	char **hangar;
	bool **marcas;
	//Creamos a flag 
	bool IKill=false;
	//Posicion de Luke
	int posX,posY;
	
	//declaramos una cola de prioridad y especificamos el orden del operador >
	//Se asigna la prioridad de la cola
	priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola;
	
	//Dandole dimensiones al hangar
	//Array de punteros de char (A las filas solamente)
    hangar = new char*[N];
	//Ahora a las columnas
    for(int x=0; x<N; x++)
        hangar[x] = new char[M]; 
	
	marcas = new bool*[N];
    for(int x=0; x<N; x++){
    	marcas[x] = new bool[M]; 
        marcas[x] = false;
    }
	//Llenando el hangar y matriz de marcas
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cin >> hangar[i][j];
		/*	if( hangar[i][j] == 'S' || hangar[i][j] == '*' || hangar[i][j] == 'L'){
				marcas[i][j]=true;
			}*/
		}
	} 
	getLuke(hangar,posX,posY);
	// Encolando el estado inicial
	cola.push( State(posX , posY , T, hangar, marcas  ) );

	    
	//Display container elements.
	/*while ( !cola.empty() ) {
	        cout << cola.top().pos_actual_X << endl;
	        cola.pop();
	}
	cout << endl;*/
	

	system("pause");
	return 0;
}

