//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <list>
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
	    int **marcas;
	    char *possible_Solution;
	    list<string> path_Solution;

	    State(){
	    	this->pos_actual_X = 0;
	    	this->pos_actual_Y = 0;
	    	this->Time_Left = 0;
	    	this->hangarAux = new char*[N];
	    	 for(int x=0; x<N; x++){
		        this->hangarAux[x] = new char[M]; 
		       /* this->hangarAux[x] = '.';*/
		    }
	    	this->marcas = new int*[N];
	    	for(int x=0; x<N; x++){
		        this->marcas[x] = new int[M]; 
		    }
		    
	    	this->possible_Solution = new char[N];
	    }
	    State( int pos_actual_X, int pos_actual_Y, int Time_Left, char **hangarAux, int **marcas){
	    	this->pos_actual_X = pos_actual_X;
	    	this->pos_actual_Y = pos_actual_Y;
	    	this->Time_Left = Time_Left;
	    	this->hangarAux = hangarAux;
	    	this->marcas = marcas;
	    	this->possible_Solution = new char[N];
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
void toList(list<string> &list1, list<string> &list2){
	while ( !list1.empty() ) {
	        list2.push_back(list1.front());
	        list1.pop_front();
	}

}
void printMarcas(int**hangar){
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cout << hangar[i][j];
		}
		cout << endl;
	}
}

void copyHangar( char** hangar1, char** &hangar2 ){
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			hangar2[i][j]= hangar1[i][j];
		}

	}
}
void copyMarcas( int** marcas1, int** &marcas2 ){
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			marcas2[i][j]= marcas1[i][j];
		}

	}
}
//Funcion que verifica si se puede disparar a un Stormtrooper dependiendo las direcciones cardinales
//recibe el hangar, la posición x,y de Luke, la direccion, y 2 variables por refencia que serían la posible ubicación del Stormtrooper (en caso de que se pueda disparar)
bool canShoot(char **hangar, int x, int y, string Dir, int &stormX,int &stormY){
	int i;
	if (Dir == "N" && x-1 >= 0){
		for (i=x-1; i>=0; i--){
			if (hangar[i][y] == '*'){
				return false;
			}
			else if (hangar[i][y] == 'S'){
                stormX = i;
                stormY = y;
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
                stormX = i;
                stormY = y;
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
                stormX = x;
                stormY = i;
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
                stormX = x;
                stormY = i;
				return true;
			}
		}
		return false;
	}
	return false;
}

//Disparar a un Stormtrooper indicao por la dirección cardinal
/*void shootStormtrooper(char **hangar, int x, int y, string dir){
	if (dir == "N"){
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
void ForceStormtrooper(char **hangar, int x, int y, int** marcas){
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		if (hangar[x-1][y] == 'S'){
			hangar[x-1][y] = '.';
			marcas[x-1][y] = 0;
		}
		
	}
	if (x-1 >= 0 && (y-1) >= 0){
		if (hangar[x-1][y-1] == 'S'){
			hangar[x-1][y-1] = '.';
			marcas[x-1][y-1] = 0;
		}
	}
	if (x-1 >= 0 && (y+1) <= M){
		if (hangar[x-1][y+1] == 'S'){
			hangar[x-1][y+1] = '.';
			marcas[x-1][y+1] = 0;
		}
	}
	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		if (hangar[x][y-1] == 'S'){
			hangar[x][y-1] = '.';
			marcas[x][y-1] = 0;
		}
	}
	
	if (y+1 < M){
		if (hangar[x][y+1] == 'S'){
			hangar[x][y+1] = '.';
			marcas[x][y+1] = 0;
		}
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		if (hangar[x+1][y] == 'S'){
			hangar[x+1][y] = '.';
			marcas[x+1][y] = 0;
		}
	}
	if (x+1 < N && (y-1) >= 0){
		if (hangar[x+1][y-1] == 'S'){
			hangar[x+1][y-1] = '.';
			marcas[x+1][y-1] = 0;
		}
	}
	if (x+1 < N && (y+1) <= M){
		if (hangar[x+1][y+1] == 'S'){
			hangar[x+1][y+1] = '.';
			marcas[x+1][y+1] = 0;
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
					
					cout<<"hay troopers"<<endl;
					return false;
				}
			}
		}
		cout<<"no hay troopers"<<endl;
		return true;
	}
	else{
		cout<<"no hay tiempo"<<endl;
		return false;
	}
}

bool puedo_visitar(int pos_x, int pos_y, int **marcas, string dir, int &LukeX , int &LukeY){   
/*	cout<< "x: "<< pos_x<<" Y: "<<pos_y<<" direccion: "<<dir<<endl;*/
	
     //Norte
     if (dir == "N"){
        if(pos_x-1 >= 0){
                   if(marcas[pos_x-1][pos_y] == 0){
                   	LukeX = pos_x-1;
                   	LukeY = pos_y;
                 /*  	cout<< "me movi al norte"<<endl;*/
                      return true;
                   }
                   return false;
                   
        }
        return false;
     }
     //Sur
     else if(dir == "S"){
        if(pos_x+1 < N){
                   if(marcas[pos_x+1][pos_y] == 0){
                   	 LukeX = pos_x+1;
                   	 LukeY = pos_y;
                  	/* cout<< "posX: "<< LukeX<<" posY: " << LukeY <<endl;*/
                      return true;
                   }
                   return false;
                   
        }
        return false;
     }
     //Este
     else if(dir == "E"){
        if(pos_y+1 < M){
                   if(marcas[pos_x][pos_y+1] == 0){
                   	LukeX = pos_x;
                   	LukeY = pos_y+1;
                  /* 	cout<< "me movi al este"<<endl;*/
                      return true;
                   }
                   return false;
        }
        return false;
     }
     //Oeste
     else if(dir == "O"){
        if(pos_y-1 >= 0){
                   if(marcas[pos_x][pos_y-1] == 0){
                   	LukeX = pos_x;
                   	LukeY = pos_y-1;
                   /*	cout<< "me movi al oeste"<<endl;*/
                      return true;
                   }
                   return false;
        }
        return false;
     }
}

void encolarVecinos(State estado_actual, priority_queue<State, vector<State>,greater<vector<State>::value_type> > &cola){
	cout<<"encolando vecinos"<<endl;	
	printHangar(estado_actual.hangarAux);
	cout<<endl;
	if(CanForceStormtrooper(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y ) ){
		cout<<"fuerza "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		/*nuevo_estado.hangarAux = estado_actual.hangarAux;*/
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		/*nuevo_estado.marcas = estado_actual.marcas;*/
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		ForceStormtrooper(nuevo_estado.hangarAux, estado_actual.pos_actual_X,  estado_actual.pos_actual_Y , nuevo_estado.marcas);
		
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("F");*/
		/*toList( estado_actual.path_Solution.push_back("F")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
		
	}
	
	int stormX, stormY, Luke_nuevo_X , Luke_nuevo_Y; //Posible posición del stormstrooper, a la hora de disparar
	/*cout<<"verificando disparos "<<endl;*/
	/*printHangar(estado_actual.hangarAux);*/
/*	cout<<endl;*/
	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N", stormX, stormY)){
		cout<<"dispara N "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("DN");*/
	/*	toList(estado_actual.path_Solution.push_back("DN")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S", stormX, stormY)){
		cout<<"dispara S "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("DS");*/
	/*	toList(estado_actual.path_Solution.push_back("DS")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E", stormX, stormY) ){
		cout<<"dispara E "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
	    copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 
	/*	nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("DE");*/
	/*toList(estado_actual.path_Solution.push_back("DE")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
    if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O", stormX, stormY) ){
    	cout<<"dispara O "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("DO");*/
	/*	toList(estado_actual.path_Solution.push_back("DO")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	/*cout<<"verificando movimientos"<<endl;*/
/*	printHangar(estado_actual.hangarAux);*/
	if( puedo_visitar(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "N", Luke_nuevo_X, Luke_nuevo_Y) ){
		cout<<"moverme N "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("N");*/
		/*toList(estado_actual.path_Solution.push_back("N")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "S", Luke_nuevo_X, Luke_nuevo_Y) ){
		cout<<"moverme S "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
	/*	cout<<"copie el hangar y las marcas "<<endl;
		cout<<estado_actual.pos_actual_X <<" "<<estado_actual.pos_actual_Y<<endl;
		cout<<"valores nuevos_ "<<Luke_nuevo_X <<" "<<Luke_nuevo_Y<<endl;*/
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;
		/*cout<<"modifique el hangars "<<endl;*/
		
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.marcas[Luke_nuevo_X][Luke_nuevo_Y] = 1; //Marcamos como visitada la posicion anterior 
		
		
	/*	printHangar(nuevo_estado.hangarAux);
		printMarcas(nuevo_estado.marcas);*/
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("S");*/
		/*toList(estado_actual.path_Solution.push_back("S")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "E", Luke_nuevo_X, Luke_nuevo_Y) ){
		cout<<"moverme E "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("E");*/
	/*	toList(estado_actual.path_Solution.push_back("E")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.marcas, "O", Luke_nuevo_X, Luke_nuevo_Y) ){
		cout<<"moverme O "<<endl;
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;
		/*nuevo_estado.path_Solution = estado_actual.path_Solution.push_back("O");*/
	/*	toList(estado_actual.path_Solution.push_back("O")  , nuevo_estado.path_Solution );*/
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		//encolar
		cola.push(nuevo_estado);
	}
	cout<<"termine de encolar vecinos"<<endl;
}

void showQueue(priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	State tope;
	int i=0;
	while(!cola.empty()){
		tope = cola.top();
		cout<<"Estado numero: "<<i<<endl;
		printHangar(tope.hangarAux);
		i++;
		cola.pop();
	}
	cout<<endl;
	
}
void busqueda (priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
	
	/*showQueue(cola);*/
	cout<<endl;
	if (cola.empty() ){
		cout<<"no hay solucion"<<endl;
		return;
	}
	State estado_actual =  State() ;
	estado_actual = cola.top();
	cout<<"Iteracion "<<i <<endl;
	if( solucion (estado_actual.hangarAux, estado_actual.Time_Left ) ){
		/*return estado_actual.possible_Solution;*/
		cout<<"SI HAY solucion"<<endl;
		return;
	}
	encolarVecinos( estado_actual, cola);
	cola.pop();
	i++;
	busqueda(cola, i);
}
void showTimeQueue(priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	State tope;
	int i=0;
	while(!cola.empty()){
		tope = cola.top();
		cout<<"Estado numero: "<<i<<endl;
		cout<<"Tiempo: "<<tope.Time_Left<<" S"<<tope.pos_actual_X<<endl;
		i++;
		cola.pop();
	}
	cout<<endl;
	
}
int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar y marcador de visitados
	char **hangar;
	int **marcas;
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
	
	marcas = new int*[N];
    for(int x=0; x<N; x++){
    	marcas[x] = new int[M]; 
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
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			if( hangar[i][j] == 'S' || hangar[i][j] == '*' || hangar[i][j] == 'L'){
				marcas[i][j]=1;		
			}
			else{
				marcas[i][j]=0;
			}
			
		}
	}  
	cout<<endl;
	getLuke(hangar,posX,posY);
	// Encolando el estado inicial
	cola.push( State(posX , posY , T, hangar, marcas  ) );
	busqueda(cola,0);
/*	State S1,S2,S3,S4,S5;
	S1= State();
	S2= State();
	S3= State();
	S4= State();
	S1.Time_Left = 1;
	S2.Time_Left = 25;
	S3.Time_Left = 3;
	S4.Time_Left = 4;
	S5.Time_Left = 25;
	S1.pos_actual_X = 1;
	S2.pos_actual_X = 2;
	S3.pos_actual_X = 3;
	S4.pos_actual_X = 4;
	S5.pos_actual_X = 5;
	cola.push(S1);
	cola.push(S2);
	cola.push(S3);
	cola.push(S4);
	cola.push(S5);
	showTimeQueue(cola);*/
	system("pause");
	return 0;
}

