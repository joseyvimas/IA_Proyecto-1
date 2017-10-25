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
bool solucion_Existe = false; // Se encontro una solucion ?
int Tiempo_solucion = 0 ; //Tiempo de la solucion
string Path_solucion = ""; // Camino de la solucion

class  State{
	public:
		int pos_actual_X;
	    int pos_actual_Y;
	    int Time_Left;
	    char possible_Mov;
	    char **hangarAux;
	    int **marcas;
		string solucion;
	    int cant_Troopers;
		int pos_estado_anterior_X;
	    int pos_estado_anterior_Y;
	    State(){
	    	this->pos_actual_X = 0;
	    	this->pos_actual_Y = 0;
	    	this->Time_Left = 0;
	    	this->hangarAux = new char*[N];
	    	this->solucion = "";
	    	 for(int x=0; x<N; x++){
		        this->hangarAux[x] = new char[M]; 
		    }
	    	this->marcas = new int*[N];
	    	for(int x=0; x<N; x++){
		        this->marcas[x] = new int[M]; 
		    }
		    
	    	this->cant_Troopers=0;
	    	this->pos_estado_anterior_X=0;
	    	this->pos_estado_anterior_Y=0;
	    }
	    State( int pos_actual_X, int pos_actual_Y, int Time_Left, char **hangarAux, int **marcas, int troopers, int pos_estado_anterior_X, int pos_estado_anterior_Y){
	    	this->pos_actual_X = pos_actual_X;
	    	this->pos_actual_Y = pos_actual_Y;
	    	this->Time_Left = Time_Left;
	    	this->hangarAux = hangarAux;
	    	this->marcas = marcas;
	    	this->solucion = "";
	    	this->cant_Troopers = troopers;
	    	this->pos_estado_anterior_X=pos_estado_anterior_X;
	    	this->pos_estado_anterior_Y=pos_estado_anterior_Y;
	    }
};   
//sobrecargar el operador <
/*bool operator< (const State& structState1, const State &structState2)
{
	if( structState1.Time_Left == structState2.Time_Left ){
		return structState1.cant_Troopers < structState2.cant_Troopers;
	}
return structState1.Time_Left > structState2.Time_Left;
}*/

//sobrecargar el operador > //operador que estamos usando VERSION TIEMPO + IMPORTANTE
/*bool operator> (const State& structState1, const State &structState2){
	if( structState1.Time_Left == structState2.Time_Left ){
		return structState1.cant_Troopers > structState2.cant_Troopers;
	}
	return structState1.Time_Left < structState2.Time_Left;
}*/
//sobrecargar el operador > //operador que estamos usando VERSION CANTIDAD DE TROOPERS + IMPORTANTE
bool operator> (const State& structState1, const State &structState2){
	if( structState1.cant_Troopers == structState2.cant_Troopers ){
		return structState1.Time_Left < structState2.Time_Left;
	}
	return structState1.cant_Troopers > structState2.cant_Troopers;
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
int cantTrooper(char **hangar){
	int i,j,contador;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			if(hangar[i][j]== 'S'){
				contador++;
			}
		}
	}
	return contador;
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
		
bool solucion(char **hangar, int Tiempo_Nueva_Solucion, string Nueva_Solucion){
	if(Tiempo_Nueva_Solucion <= T){
		for (int i=0; i<N; i++){
			for (int j=0; j<M; j++){
				if(hangar[i][j] == 'S'){
					return false;
				}
			}
		}
		if (solucion_Existe){
			if (Tiempo_solucion < Tiempo_Nueva_Solucion){
				Tiempo_solucion= Tiempo_Nueva_Solucion;
				Path_solucion = Nueva_Solucion;
			}
		}
		else{
			Tiempo_solucion= Tiempo_Nueva_Solucion;
			Path_solucion = Nueva_Solucion;
			solucion_Existe=true;
		}
		return true;
	}
	else{
		return false;
	}
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
bool puedo_visitar2(int pos_x, int pos_y, char **hangar, string dir, int &LukeX , int &LukeY, int pos_estado_anterior_X, int pos_estado_anterior_Y){   

     //Norte
	if (dir == "N"){
		if(pos_x-1 >= 0){
                   if( (pos_x-1 == pos_estado_anterior_X && pos_y == pos_estado_anterior_Y) || (hangar[pos_x-1][pos_y] !='.') ){
                   	return false;
                   }      
                   LukeX = pos_x-1;
                   LukeY = pos_y;
                return true;
                   
        }
        return false;
     }
     //Sur
     else if(dir == "S"){
        if(pos_x+1 < N){
                   if( (pos_x+1 == pos_estado_anterior_X && pos_y == pos_estado_anterior_Y) || (hangar[pos_x+1][pos_y] !='.') ){
                   	 return false;
                   }
                   LukeX = pos_x+1;
                   	 LukeY = pos_y;
     
                      return true;
                   
                   
        }
        return false;
     }
     //Este
     else if(dir == "E"){
        if(pos_y+1 < M){
                   if( (pos_estado_anterior_X && pos_y+1 == pos_estado_anterior_Y) || (hangar[pos_x][pos_y+1] !='.') ){
                   	return false;
                   }
                   LukeX = pos_x;
                   	LukeY = pos_y+1;
     
                      return true;
                   
        }
        return false;
     }
     //Oeste
     else if(dir == "O"){
        if(pos_y-1 >= 0){
                   if( (pos_x == pos_estado_anterior_X && pos_y-1 == pos_estado_anterior_Y) || (hangar[pos_x][pos_y-1] !='.') ){
                   	return false;
                   }
                   LukeX = pos_x;
                   	LukeY = pos_y-1;
  
                      return true;
                   
        }
        return false;
     }
     return false;
}
void encolarVecinosV2(State estado_actual, priority_queue<State, vector<State>,greater<vector<State>::value_type> > &cola){
	int stormX, stormY, Luke_nuevo_X , Luke_nuevo_Y; //Posible posición del stormstrooper y Luke, a la hora de disparar
	cout<<"encolando vecinos"<<endl;	
	printHangar(estado_actual.hangarAux);
	cout<<endl;
	
	if(CanForceStormtrooper(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y ) ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );		
	    copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
	    
		ForceStormtrooper(nuevo_estado.hangarAux, estado_actual.pos_actual_X,  estado_actual.pos_actual_Y , nuevo_estado.marcas);

		
		
		nuevo_estado.solucion = estado_actual.solucion + ",F";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		
		nuevo_estado.cant_Troopers = cantTrooper(nuevo_estado.hangarAux);
		
		nuevo_estado.pos_estado_anterior_X = nuevo_estado.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = nuevo_estado.pos_actual_Y;
		 
		//encolar
		cola.push(nuevo_estado);

		
	}
	


	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N", stormX, stormY)){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 

		
		nuevo_estado.solucion = estado_actual.solucion + ",DN";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = cantTrooper(nuevo_estado.hangarAux);
		
		nuevo_estado.pos_estado_anterior_X = nuevo_estado.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = nuevo_estado.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
	if(canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S", stormX, stormY)){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 

		
		nuevo_estado.solucion = estado_actual.solucion + ",DS";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = cantTrooper(nuevo_estado.hangarAux);
		
		nuevo_estado.pos_estado_anterior_X = nuevo_estado.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = nuevo_estado.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
	if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E", stormX, stormY) ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
	    copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 

		
		nuevo_estado.solucion = estado_actual.solucion + ",DE";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = cantTrooper(nuevo_estado.hangarAux);
		
		nuevo_estado.pos_estado_anterior_X = nuevo_estado.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = nuevo_estado.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
    if( canShoot(estado_actual.hangarAux, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O", stormX, stormY) ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		nuevo_estado.pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_actual_Y = estado_actual.pos_actual_Y;
		
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		nuevo_estado.hangarAux[stormX][stormY] = '.'; //Eliminamos el stormstrooper del estado actual
		
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.marcas[stormX][stormY] = 0; //marcamos como no visitada donde estaba el trooper 

		
		nuevo_estado.solucion = estado_actual.solucion + ",DO";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = cantTrooper(nuevo_estado.hangarAux);
		
		nuevo_estado.pos_estado_anterior_X = nuevo_estado.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = nuevo_estado.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}

	if( puedo_visitar2(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.hangarAux, "N", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y) ){
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;

		
		nuevo_estado.solucion = estado_actual.solucion + ",N";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = estado_actual.cant_Troopers;
		
		nuevo_estado.pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar2(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.hangarAux, "S", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y) ){
		/*cout<<"moverme S "<<endl;*/
		//crear estado
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);

		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;

		
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.marcas[Luke_nuevo_X][Luke_nuevo_Y] = 1; //Marcamos como visitada la posicion anterior 
		
		

		
		nuevo_estado.solucion = estado_actual.solucion + ",S";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = estado_actual.cant_Troopers;
		
		nuevo_estado.pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar2(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.hangarAux, "E", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y) ){
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

		
		
		nuevo_estado.solucion = estado_actual.solucion + ",E";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = estado_actual.cant_Troopers;
		
		nuevo_estado.pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}
	if( puedo_visitar2(estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.hangarAux, "O", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y) ){

		//crear estadopos_estado_anterior_X
		State nuevo_estado =  State() ;
		//aplicar cambios
		copyHangar( estado_actual.hangarAux, nuevo_estado.hangarAux );
		copyMarcas( estado_actual.marcas, nuevo_estado.marcas);
		nuevo_estado.hangarAux[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = '.'; //quitamos la vieja posicion de Luke 
		nuevo_estado.marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y] = 1; //Marcamos como visitada la posicion anterior 
		nuevo_estado.hangarAux[Luke_nuevo_X][Luke_nuevo_Y] = 'L'; //movemos a Luke a su nueva posicion 
		
		nuevo_estado.pos_actual_X = Luke_nuevo_X;
		nuevo_estado.pos_actual_Y = Luke_nuevo_Y;

	
		
		nuevo_estado.solucion = estado_actual.solucion + ",O";
		
		nuevo_estado.Time_Left = estado_actual.Time_Left-1;
		nuevo_estado.cant_Troopers = estado_actual.cant_Troopers;
		
		nuevo_estado.pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado.pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		//encolar
		cola.push(nuevo_estado);
	}

}

void showTimeQueue(priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	State tope;
	int i=0;
	while(!cola.empty()){
		tope = cola.top();
		cout <<"cantidad troopers: " << tope.cant_Troopers <<"Tiempo: "<<tope.Time_Left<<" S"<<tope.pos_actual_X<<endl;
		i++;
		cola.pop();
	}
	cout<<endl;
	
}

void busqueda (priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
	
	if ( cola.empty() ){
		if ( solucion_Existe ){
			cout << "The Force is Strong in Luke!" << endl;
			for (int x=1; (unsigned)x<Path_solucion.length(); x++){
				cout << Path_solucion[x];
			}
		}
		else{
			cout<< "A great loss for the rebels" << endl;
		}	
		return;
	}
	
	State estado_actual =  State() ;
	estado_actual = cola.top();
	cola.pop();
	if( estado_actual.Time_Left<0 || ( solucion_Existe && estado_actual.Time_Left<= Tiempo_solucion ) ){
		busqueda(cola, i);
		return;
	}

	solucion(estado_actual.hangarAux, estado_actual.Time_Left, estado_actual.solucion);
		
	encolarVecinosV2( estado_actual, cola);
	i++;
	busqueda(cola, i);
}
void busquedaVIEJA (priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
	
	/*showQueue(cola);*/
	cout<<endl;
	if (cola.empty() ){
		cout<<"no hay solucion"<<endl;
		return;
	}
	State estado_actual =  State() ;
	estado_actual = cola.top();
	cola.pop();
	if(estado_actual.Time_Left<0){
		cola.pop();
		busqueda(cola, i);
		return;
	}
	cout<<"Iteracion "<<i <<endl;
	if( solucion (estado_actual.hangarAux, estado_actual.Time_Left ) ){
		 
		cout<<"SI HAY solucion"<<endl;

		string tope;
		
		while( !estado_actual.path_Solution.empty() ){
			tope = estado_actual.path_Solution.front();
			cout << tope <<", ";
			estado_actual.path_Solution.pop_front();
		}
		cout<<endl;
		return;
	}

	encolarVecinosV2( estado_actual, cola);
	/*freeMemory(estado_actual.hangarAux,estado_actual.marcas);*/
	/*showTimeQueue(cola);*/
	i++;
	
	busqueda(cola, i);
}
int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar y marcador de visitados
	char **hangar;
	int **marcas;

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
	cola.push( State(posX , posY , T, hangar, marcas, cantTrooper(hangar),posX,posY  ) );
	busqueda(cola,0);
	/*State S1,S2,S3,S4,S5;
	S1= State();
	S2= State();
	S3= State();
	S4= State();
	S5= State();
	S1.Time_Left = 2;
	S1.cant_Troopers= 2;
	
	S2.Time_Left = 1;
	S2.cant_Troopers= 3;
	
	S3.Time_Left = 2;
	S3.cant_Troopers= 3;
	
	S4.Time_Left = 2;
	S4.cant_Troopers= 4;
	
	
	S1.pos_actual_X = 1;
	S2.pos_actual_X = 2;
	S3.pos_actual_X = 3;
	S4.pos_actual_X = 4;
	
	cola.push(S1);
	cola.push(S2);
	cola.push(S3);
	cola.push(S4);

	showTimeQueue(cola);
	S5.Time_Left = 10;
	S5.cant_Troopers= 3;
	cola.push(S5);
	showTimeQueue(cola);*/
	/*system("pause");*/
	
	return 0;
}

