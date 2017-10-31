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
bool solucion_Existe = false; // Se encontro una solucion ?
int Tiempo_solucion = 0 ; //Tiempo de la solucion
string Path_solucion = ""; // Camino de la solucion
//Posicion inicial de Luke
int pos_inicial_X;  
int pos_inicial_Y; 
//Struct que representa la posicion de un StormTrooper y si esta vivo o no
struct posTrooper{
	int pos_x;
	int pos_y;
	bool alive;
};

//lista auxiliar de iTroopers
//list<posTrooper> aux;

class  State{
	public:
		int pos_actual_X;
		int pos_actual_Y;
		int cant_Troopers;
		int Time_Left;
		string solucion;
		list<posTrooper> iTroopers;  
		int pos_estado_anterior_X;
		int pos_estado_anterior_Y;
		bool NoDN;
		bool NoDS;
		bool NoDE;
		bool NoDO;
		int **marcas;
		
	State(){
		this->pos_actual_X = 0;
		this->pos_actual_Y = 0;
		this->Time_Left = 0;
		this->solucion = "";
		this->cant_Troopers= 0;
		//this.->list<troopers>* iTroppers = new list<troopers>;
		this->pos_estado_anterior_X=0;
		this->pos_estado_anterior_Y=0;
		this->NoDN =false;
		this->NoDS =false;
		this->NoDE =false;
		this->NoDO =false;
		this->marcas = new int*[N];
	     	for(int x=0; x<N; x++){
		        this->marcas[x] = new int[M]; 
		    }
		 iniciar_marcas();
	}
	State( int pos_actual_X, int pos_actual_Y, int Time_Left, int nrotroopers, int pos_estado_anterior_X, int pos_estado_anterior_Y, list<posTrooper> troopers){
		this->pos_actual_X = pos_actual_X;
		this->pos_actual_Y = pos_actual_Y;
		this->Time_Left = Time_Left;
		this->solucion = "";
		this->cant_Troopers = nrotroopers;
		this->iTroopers = troopers;
		this->pos_estado_anterior_X=pos_estado_anterior_X;
		this->pos_estado_anterior_Y=pos_estado_anterior_Y;
		this->NoDN =false;
		this->NoDS =false;
		this->NoDE =false;
		this->NoDO =false;
	     this->marcas = new int*[N];
	    	for(int x=0; x<N; x++){
		         this->marcas[x] = new int[M]; 
		     }
		     iniciar_marcas();
	}
	
	 void iniciar_marcas(){
	 	for (int i =0; i<N; i++){
	 		for (int j=0; j<M;j++){
	 			this->marcas[i][j] = 0;
	 		}
	 	}
	 	this->marcas[this->pos_actual_X][this->pos_actual_Y] = 1;
	 }

	bool isAliveTrooper(list<posTrooper> troopers, int x, int y){
		// posTrooper tope;
		// while (!troopers.empty()){
		// 	tope = troopers.front(); //obtenemos el tope
		// 	if (tope.pos_x == x && tope.pos_y ==y && tope.alive == true){
		// 		return true;
		// 	}
		// 	troopers.pop_front();
		// }
		// return false;

		list<posTrooper>::iterator it;
    	for (it = troopers.begin(); it != troopers.end(); it++){
        	if (it->pos_x == x && it->pos_y == y && it->alive == true){
            	return true;
        	}
    	}
    	return false;
	}

	void modifyAlive(list<posTrooper> &troopers, int x, int y) {
    	list<posTrooper>::iterator it;
    	for (it = troopers.begin(); it != troopers.end(); it++){
        	if (it->pos_x == x && it->pos_y == y){
        		if (it->alive == true){
            		it->alive = false;
            		
            		break;
            	}
            /*	else
            	{
            		break;
            	}*/
        	}
    	}
	}

	bool allDeadStroopers(list<posTrooper> troopers){
		list<posTrooper>::iterator it;
    	for (it = troopers.begin(); it != troopers.end(); it++){
        	if (it->alive == true){
        		return false;
        	}
    	}
    	return true;
	}

	int countTroopers(list<posTrooper> troopers){
		int cont = 0;
		list<posTrooper>::iterator it;
    	for (it = troopers.begin(); it != troopers.end(); it++){
        	if (it->alive == true){
        		cont++;
        	}
    	}
    	return cont;
	}


};  
	void copyTroopers(list<posTrooper> &nueva, list<posTrooper> actual){
		list<posTrooper>::iterator it;
    	for (it = actual.begin(); it != actual.end(); it++){
    		posTrooper x ;
    		x.alive = it->alive;
    		x.pos_x =it->pos_x;
    		x.pos_y = it->pos_y;
        	nueva.push_back(x);
    	}
	}

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
}
*/
//sobrecargar el operador > //operador que estamos usando VERSION TIEMPO + IMPORTANTE
bool operator> (const State& structState1, const State &structState2){

	//return 10000 - ((T - structState1.Time_Left) + structState1.cant_Troopers) > 10000 - ((T - structState2.Time_Left) + structState2.cant_Troopers);
		return structState1.Time_Left  > structState2.Time_Left;

}
//sobrecargar el operador > //operador que estamos usando VERSION CANTIDAD DE TROOPERS + IMPORTANTE
/*bool operator> (const State& structState1, const State &structState2){
	if( structState1.cant_Troopers == structState2.cant_Troopers ){
		return structState1.Time_Left < structState2.Time_Left;
	}
	return structState1.cant_Troopers > structState2.cant_Troopers;
}*/


int maxTroopersKill (int time){
	if( time%2 ==0){
		return maxTroopersKill (time-1) +1;
	}
	else{
		return ( ((time-1)/2)*3 ) +8;
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

void printTroopers (list<posTrooper> troopers){
	list<posTrooper>::iterator it;
	for (it = troopers.begin(); it != troopers.end(); it++){
    	cout << it->pos_x << " " << it->pos_y << "";
    	if (it->alive){
    		cout << "vivo" << endl;
    	}
    	else{
    		cout << "muerto" << endl;
    	}
	}
}


//Funcion que verifica si se puede disparar a un Stormtrooper dependiendo las direcciones cardinales
//recibe el hangar, un nuevo estado, la posición x,y de Luke, la direccion y 2 variables por referencias que tendrán la coordenada del strooper
bool canShoot(char **hangar, State estado_actual, int x, int y, string Dir, int &stormx, int &stormy){
	int i;
	if (Dir == "N" && x-1 >= 0){
		for (i=x-1; i>=0; i--){
			if (hangar[i][y] == '*'){
				return false;
			}
			else if (estado_actual.isAliveTrooper(estado_actual.iTroopers,i,y)){
				stormx = i;
				stormy = y;
				return true;
			}
		}
	}
	else if (Dir == "S" && x+1 < N){
		for (i=x+1; i<N; i++){
			if (hangar[i][y] == '*'){
				return false;
			}
			else if (estado_actual.isAliveTrooper(estado_actual.iTroopers,i,y)){
				stormx = i;
				stormy = y;
				return true;
			}
		}
	}
	else if (Dir == "E" && y+1 < M){
		for (i=y+1; i<M; i++){
			if (hangar[x][i] == '*'){
				return false;
			}
			else if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x,i)){
				stormx = x;
				stormy = i;
				return true;
			}
		}
	}
	else if (Dir == "O" && y-1 >= 0){
		for (i=y-1; i>=0; i--){
			if (hangar[x][i] == '*'){
				return false;
			}
			else if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x,i)){
				stormx = x;
				stormy = i;
				return true;
			}
		}
	}
	return false;
}

//Usar la fuerza contra los Stormtroopers
bool canForceStormtrooper(State estado_actual, int x, int y){
	//printTroopers(estado_actual.iTroopers);
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x-1,y))
			return true;
	}
	if (x-1 >= 0 && (y-1) >= 0){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x-1,y-1))
			return true;
	}
	if (x-1 >= 0 && (y+1) <= M){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x-1,y+1))
			return true;
	}

	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x,y-1))
			return true;
	}
	if (y+1 < M){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x,y+1))
			return true;
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x+1,y))
			return true;
	}
	if (x+1 < N && (y-1) >= 0){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x+1,y+-1))
			return true;
	}
	if (x+1 < N && (y+1) <= M){
		if (estado_actual.isAliveTrooper(estado_actual.iTroopers,x+1,y+1))
			return true;
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
void forceStormtrooper3(State &nuevo_estado, int x, int y, bool & NoDN, bool & NoDS, bool & NoDE, bool & NoDO){
	// usar fuerza con los troopers N, NO, NE
	if (x-1 >= 0){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x-1, y);
		NoDO=false;
	}
	if (x-1 >= 0 && (y-1) >= 0){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x-1, y-1);
	}
	if (x-1 >= 0 && (y+1) <= M){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x-1, y+1);
	}

	// usar fuerza con los troopers O, E
	if (y-1 >= 0){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x, y-1);
		NoDS=false;
	}
	if (y+1 < M){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x, y+1);
		NoDN=false;
	}
	
	// usar fuerza con los troopers S, SO, SE
	if (x+1 <N){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x+1, y);
		NoDE=false;
	}
	if (x+1 < N && (y-1) >= 0){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x+1, y-1);
	}
	if (x+1 < N && (y+1) <= M){
		nuevo_estado.modifyAlive(nuevo_estado.iTroopers, x+1, y+1);
	}
/*	printTroopers(nuevo_estado.iTroopers);*/
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
	int i,j,contador=0;
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
				pos_inicial_X = i;
				pos_inicial_Y = j;
				break;
			}
		}
	}
}

void getTroopers(char **hangar, list<posTrooper> &aux){

		int i,j;
		posTrooper a;
		for (i=0; i<N; i++){
			for (j=0; j<M; j++){
				//Si encontramos un trooper, añadimos su posicion a nuestra lista auxiliar de posTrooper
				if (hangar[i][j] == 'S'){ 
					a.pos_x = i;
					a.pos_y = j;
					a.alive = true;
					aux.push_back(a);
				}
			}
		}

}


bool solucion(State estado_actual, int Tiempo_Nueva_Solucion, string Nueva_Solucion){
	if(Tiempo_Nueva_Solucion <= T){
		if (!estado_actual.allDeadStroopers(estado_actual.iTroopers)){
			return false;
		}
		if (solucion_Existe){
			if (Tiempo_Nueva_Solucion < Tiempo_solucion  ){
				Tiempo_solucion= Tiempo_Nueva_Solucion;
				Path_solucion = Nueva_Solucion;
				cout<<"si sol"<<endl;
			}
		}
		else{
			Tiempo_solucion= Tiempo_Nueva_Solucion;
			Path_solucion = Nueva_Solucion;
			solucion_Existe = true;
			cout<<"si sol"<<endl;
		}
		//cout<<"si sol"<<endl;
		return true;
	}
	return false;
}

/*void showQueue(priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
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
	
}*/

bool puedo_visitar2(State estado_actual, int pos_x, int pos_y, char **hangar, string dir, int &LukeX , int &LukeY, int pos_estado_anterior_X, int pos_estado_anterior_Y){   
	//Norte
	if (dir == "N"){
		if(pos_x-1 >= 0){
			if( (pos_x-1 == pos_estado_anterior_X && pos_y == pos_estado_anterior_Y) || estado_actual.isAliveTrooper(estado_actual.iTroopers,pos_x-1,pos_y) ||  (hangar[pos_x-1][pos_y] == '*') /*|| (estado_actual.marcas[pos_x-1][pos_y]) */){
				return false;
			}	  
			LukeX = pos_x-1;
			LukeY = pos_y;
			return true;  
		}
	}
	 //Sur
	else if(dir == "S"){
		if(pos_x+1 < N){
			if( (pos_x+1 == pos_estado_anterior_X && pos_y == pos_estado_anterior_Y) || estado_actual.isAliveTrooper(estado_actual.iTroopers,pos_x+1,pos_y) ||  (hangar[pos_x+1][pos_y] == '*') /*|| (estado_actual.marcas[pos_x+1][pos_y])*/){
				return false;
			}
			LukeX = pos_x+1;
			LukeY = pos_y;
			return true;
		}
	 }
	//Este
	else if(dir == "E"){
		if(pos_y+1 < M){
			if( (pos_x == pos_estado_anterior_X && pos_y+1 == pos_estado_anterior_Y) || estado_actual.isAliveTrooper(estado_actual.iTroopers,pos_x,pos_y+1) ||  (hangar[pos_x][pos_y+1] == '*') /*|| (estado_actual.marcas[pos_x][pos_y+1])*/){
				return false;
			}
			LukeX = pos_x;
			LukeY = pos_y+1;
			return true;
		}
	}
	//Oeste
	else if(dir == "O"){
		if(pos_y-1 >= 0){
			if( (pos_x == pos_estado_anterior_X && pos_y-1 == pos_estado_anterior_Y) || estado_actual.isAliveTrooper(estado_actual.iTroopers,pos_x,pos_y-1) ||  (hangar[pos_x][pos_y-1] == '*') /*|| (estado_actual.marcas[pos_x][pos_y]-1)*/){
				return false;
			}
			LukeX = pos_x;
			LukeY = pos_y-1;
			return true;   
		}
	}
	return false;
}

/////////////////////////////


void encolarVecinosV3(char **hangar, State estado_actual, priority_queue<State, vector<State>,greater<vector<State>::value_type> > &cola){
	int stormX, stormY, Luke_nuevo_X , Luke_nuevo_Y; //Posible posición del stormstrooper y Luke, a la hora de disparar
	//cout<<"encolando vecinos V3"<<endl;
	int costo = ((T - estado_actual.Time_Left) + estado_actual.cant_Troopers);
	cout<<" Tengo el costo: "<< costo<<endl;	
	cout<<" Tengo el tiempo: "<< estado_actual.Time_Left<<endl;		
	cout << "posible solucion: " << estado_actual.solucion << endl;
	cout << "pos ANT X: " << estado_actual.pos_estado_anterior_X << endl;
	cout << "pos ANT Y: " << estado_actual.pos_estado_anterior_Y << endl;
	printTroopers(estado_actual.iTroopers);
	//cout<<" Tengo la solucion: "<< estado_actual.solucion<<endl;
	cout<<endl;
	
	
	//FUERZA
	if(canForceStormtrooper(estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y)){
		cout<<"fuerza"<<endl;
	//	printTroopers(estado_actual.iTroopers);
	
		//crear estado
		State *nuevo_estado =  new State() ;
		
		//aplicar cambios
		nuevo_estado->pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_actual_Y = estado_actual.pos_actual_Y;

	/*	nuevo_estado->iTroopers = estado_actual.iTroopers;*/   //lista de las posiciones de los troopers
		
		copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);
		
		forceStormtrooper3(*nuevo_estado, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, estado_actual.NoDN,estado_actual.NoDS,estado_actual.NoDE,estado_actual.NoDO);   //Aplicamos fuerza

		nuevo_estado->solucion = estado_actual.solucion + ",F";  //Copiamos F en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1;  //Disminuimos el tiempo 

		nuevo_estado->cant_Troopers = nuevo_estado->countTroopers(nuevo_estado->iTroopers);  //Contamos la cantidad de troopers que quedan en el hangar
		/*cout << "troopers: " << nuevo_estado->cant_Troopers << endl;*/
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Asignamos nuestra posicion actual como posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = nuevo_estado->pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = nuevo_estado->pos_actual_Y;
		 
		 
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = estado_actual.NoDN;
		nuevo_estado->NoDS = estado_actual.NoDS;
		nuevo_estado->NoDE = estado_actual.NoDE;
		nuevo_estado->NoDO = estado_actual.NoDO;
		//encolar
		
		cola.push(*nuevo_estado);
	}
	
	
	
	//DISPARAR NORTE
	if(canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N", stormX, stormY) && !estado_actual.NoDN){
		cout<<"DN"<<endl;
//		printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();

		//aplicar cambios
		nuevo_estado->pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_actual_Y = estado_actual.pos_actual_Y;

	/*	nuevo_estado->iTroopers = estado_actual.iTroopers; */  //lista de las posiciones de los troopers
	
	  copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);
	
	
		nuevo_estado->modifyAlive(nuevo_estado->iTroopers,stormX,stormY);
		
		nuevo_estado->solucion = estado_actual.solucion + ",DN";  //Copiamos DN en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers-1;  //Contamos la cantidad de troopers que quedan en el hangar
		
		if (nuevo_estado->cant_Troopers ==0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}

		//Asignamos nuestra posicion actual como posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = nuevo_estado->pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = nuevo_estado->pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = estado_actual.NoDN;
		nuevo_estado->NoDS = estado_actual.NoDS;
		nuevo_estado->NoDE = estado_actual.NoDE;
		nuevo_estado->NoDO = estado_actual.NoDO;
		
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//DISPARAR SUR
	if(canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S", stormX, stormY) && !estado_actual.NoDS){
		cout<<"DS"<<endl;
	//	printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		nuevo_estado->pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_actual_Y = estado_actual.pos_actual_Y;

		/*nuevo_estado->iTroopers = estado_actual.iTroopers;*/   //lista de las posiciones de los troopers

        copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);
 
		nuevo_estado->modifyAlive(nuevo_estado->iTroopers,stormX,stormY);

		nuevo_estado->solucion = estado_actual.solucion + ",DS";  //Copiamos DS en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers-1;  //Contamos la cantidad de troopers que quedan en el hangar
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}

		//Asignamos nuestra posicion actual como posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = nuevo_estado->pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = nuevo_estado->pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = estado_actual.NoDN;
		nuevo_estado->NoDS = estado_actual.NoDS;
		nuevo_estado->NoDE = estado_actual.NoDE;
		nuevo_estado->NoDO = estado_actual.NoDO;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//DISPARAR ESTE
	if(canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E", stormX, stormY) && !estado_actual.NoDE){
	cout<<"DE"<<endl;
	//printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		nuevo_estado->pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_actual_Y = estado_actual.pos_actual_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers

         copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);

		nuevo_estado->modifyAlive(nuevo_estado->iTroopers,stormX,stormY);
		
		nuevo_estado->solucion = estado_actual.solucion + ",DE";  //Copiamos DE en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers-1;  //Contamos la cantidad de troopers que quedan en el hangar
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Asignamos nuestra posicion actual como posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = nuevo_estado->pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = nuevo_estado->pos_actual_Y;
		
		
		//mantener reglas disparos de otros estados
		nuevo_estado->NoDN = estado_actual.NoDN;
		nuevo_estado->NoDS = estado_actual.NoDS;
		nuevo_estado->NoDE = estado_actual.NoDE;
		nuevo_estado->NoDO = estado_actual.NoDO;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//DISPARAR OESTE
	if(canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O", stormX, stormY) && !estado_actual.NoDO){
		cout<<"DO"<<endl;
	//	printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		

		//aplicar cambios
		nuevo_estado->pos_actual_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_actual_Y = estado_actual.pos_actual_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers

      copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);


		nuevo_estado->modifyAlive(nuevo_estado->iTroopers,stormX,stormY);
		
		nuevo_estado->solucion = estado_actual.solucion + ",DO";  //Copiamos DO en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers-1;  //Contamos la cantidad de troopers que quedan en el hangar
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Asignamos nuestra posicion actual como posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = nuevo_estado->pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = nuevo_estado->pos_actual_Y;
		
		//mantener reglas disparos de otros estados
		nuevo_estado->NoDN = estado_actual.NoDN;
		nuevo_estado->NoDS = estado_actual.NoDS;
		nuevo_estado->NoDE = estado_actual.NoDE;
		nuevo_estado->NoDO = estado_actual.NoDO;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//MOVERME NORTE
	if( puedo_visitar2(estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, hangar, "N", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y)  ){
		cout<<"N"<<endl;
		//printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		copyMarcas(estado_actual.marcas,nuevo_estado->marcas);
		nuevo_estado->marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y];
		
		//bloquear disparar en proximos estados semejantes
		if(canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "N", stormX, stormY) ){
			nuevo_estado->NoDN = true;
		}
		//Actualizamos la posicion actual de Luke
		nuevo_estado->pos_actual_X = Luke_nuevo_X;
		nuevo_estado->pos_actual_Y = Luke_nuevo_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers
		
	copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);	
		
		nuevo_estado->solucion = estado_actual.solucion + ",N";  //Copiamos N en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers;  //Asignamos la misma cantidad de troopers
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Actualizamos la posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDS = false;
		nuevo_estado->NoDE = false;
		nuevo_estado->NoDO = false;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//MOVERME SUR
	if( puedo_visitar2(estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, hangar, "S", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y)){	
		cout<<"S"<<endl;
		//printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		copyMarcas(estado_actual.marcas,nuevo_estado->marcas);
		nuevo_estado->marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y];
		//bloquear disparar en proximos estados semejantes
		if( canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "S", stormX, stormY) ){
			nuevo_estado->NoDS = true;
		}
		//Actualizamos la posicion actual de Luke
		nuevo_estado->pos_actual_X = Luke_nuevo_X;
		nuevo_estado->pos_actual_Y = Luke_nuevo_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers
		
	copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);	
		
		nuevo_estado->solucion = estado_actual.solucion + ",S";  //Copiamos S en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers;  //Asignamos la misma cantidad de troopers
		
		if (nuevo_estado->cant_Troopers ==0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Actualizamos la posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = false;
		nuevo_estado->NoDE = false;
		nuevo_estado->NoDO = false;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//MOVERME ESTE
	if(puedo_visitar2(estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, hangar, "E", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y) ){
		cout<<"E"<<endl;
		//printTroopers(estado_actual.iTroopers);
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		copyMarcas(estado_actual.marcas,nuevo_estado->marcas);
		nuevo_estado->marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y];
		//bloquear disparar en proximos estados semejantes
		if( canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "E", stormX, stormY) ){
			nuevo_estado->NoDE = true;
		}
		//Actualizamos la posicion actual de Luke
		nuevo_estado->pos_actual_X = Luke_nuevo_X;
		nuevo_estado->pos_actual_Y = Luke_nuevo_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers
		
	copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);	
		
		nuevo_estado->solucion = estado_actual.solucion + ",E";  //Copiamos E en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers;  //Asignamos la misma cantidad de troopers
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Actualizamos la posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = false;
		nuevo_estado->NoDS = false;
		nuevo_estado->NoDO = false;
		//encolar
		cola.push(*nuevo_estado);
	}
	
	//MOVERME OESTE
	if(puedo_visitar2(estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, hangar, "O", Luke_nuevo_X, Luke_nuevo_Y, estado_actual.pos_estado_anterior_X, estado_actual.pos_estado_anterior_Y)){
		cout<<"O"<<endl;
	//	printTroopers(estado_actual.iTroopers);	
		//crear estado
		State *nuevo_estado =  new State();
		
		//aplicar cambios
		copyMarcas(estado_actual.marcas,nuevo_estado->marcas);
		nuevo_estado->marcas[estado_actual.pos_actual_X][estado_actual.pos_actual_Y];
		//bloquear disparar en proximos estados semejantes
		if( canShoot(hangar, estado_actual, estado_actual.pos_actual_X, estado_actual.pos_actual_Y, "O", stormX, stormY) ){
			nuevo_estado->NoDO = true;
		}
		
		//Actualizamos la posicion actual de Luke
		nuevo_estado->pos_actual_X = Luke_nuevo_X;
		nuevo_estado->pos_actual_Y = Luke_nuevo_Y;

	//	nuevo_estado->iTroopers = estado_actual.iTroopers;   //lista de las posiciones de los troopers
		
	copyTroopers(nuevo_estado->iTroopers,estado_actual.iTroopers);	
		
		nuevo_estado->solucion = estado_actual.solucion + ",O";  //Copiamos O en la posible solucion
		
		nuevo_estado->Time_Left = estado_actual.Time_Left-1; //Disminuimos el tiempo
		
		nuevo_estado->cant_Troopers = estado_actual.cant_Troopers;  //Asignamos la misma cantidad de troopers
		
		if (nuevo_estado->cant_Troopers == 0){
			solucion_Existe = true;
			Path_solucion = nuevo_estado->solucion;
			return;
		}
		
		//Actualizamos la posicion de estado anterior
		nuevo_estado->pos_estado_anterior_X = estado_actual.pos_actual_X;
		nuevo_estado->pos_estado_anterior_Y = estado_actual.pos_actual_Y;
		
		//desbloquear disparos de otros estados
		nuevo_estado->NoDN = false;
		nuevo_estado->NoDS = false;
		nuevo_estado->NoDE = false;
		//encolar
		cola.push(*nuevo_estado);
	}

}

void showTimeQueue(priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola){
	State tope;
	int i=0;
	while(!cola.empty()){
		tope = cola.top();
		cout <<"cantidad troopers: " << tope.cant_Troopers <<"Tiempo: "<< T-tope.Time_Left<<" S"<<tope.pos_actual_X<<endl;
		i++;
		cola.pop();
	}
	cout<<endl;
	
}

void busqueda (char **hangar, priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
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
		busqueda(hangar, cola, i);
		return;
	}
	
	solucion(estado_actual, estado_actual.Time_Left, estado_actual.solucion);
	//encolarVecinosV2( estado_actual, cola);
	i++;
	busqueda(hangar, cola, i);
}

void busqueda_por_Tiempo (char **hangar, priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
	if ( cola.empty() ){
		cout<< "A great loss for the rebels" << endl;
		return;	
	}
	if ( solucion_Existe ){
			cout << "The Force is Strong in Luke!" << endl;
			for (int x=1; (unsigned)x<Path_solucion.length(); x++){
				cout << Path_solucion[x];
			}
			return;
	}
	
	State *estado_actual = new State() ;
	*estado_actual = cola.top();
	cola.pop();
	if( estado_actual->Time_Left <=0 || estado_actual->cant_Troopers > maxTroopersKill(estado_actual->Time_Left) ){
		/*cout<<"mi tiempo se agoto :("<<endl;*/
		busqueda_por_Tiempo(hangar, cola, i);
		return;
	}

	solucion(*estado_actual, estado_actual->Time_Left, estado_actual->solucion);
	encolarVecinosV3(hangar, *estado_actual, cola);
	delete estado_actual;
	
	estado_actual = NULL;
	i++;
	busqueda_por_Tiempo(hangar, cola, i);
}

void busqueda_Troopers_Optimizada (char **hangar, priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola, int i){
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
	
	State *estado_actual = new State() ;
	*estado_actual = cola.top();
	cola.pop();
	if( estado_actual->Time_Left <=0 || estado_actual->cant_Troopers > maxTroopersKill(estado_actual->Time_Left) ){
		/*cout<<"mi tiempo se agoto :("<<endl;*/
		busqueda_Troopers_Optimizada(hangar, cola, i);
		return;
	}
	if(solucion_Existe){
		if (estado_actual->Time_Left < Tiempo_solucion){
			cout<<"no soy una buena solucion :("<<endl;
			busqueda_Troopers_Optimizada(hangar, cola, i);
			return;
		}
	}
	if(estado_actual->Time_Left <= 1){
			cout<<"no soy una buena solucion :()"<<endl;
			busqueda_Troopers_Optimizada(hangar, cola, i);
			return;
		
	}
	cout<< cola.size()<<endl;
	solucion(*estado_actual, estado_actual->Time_Left, estado_actual->solucion);
	encolarVecinosV3(hangar, *estado_actual, cola);
	delete estado_actual;
	free (estado_actual);
	estado_actual->marcas =NULL;
	estado_actual = NULL;	
	i++;
	busqueda_Troopers_Optimizada(hangar, cola, i);
	return;
}





int main(){
	//Se leen las dimensiones del hangar y el tiempo
	cin >> N;
	cin >> M;
	cin >> T;
	
	//Creamos el hangar
	char **hangarOriginal;
	
	//Dandole dimensiones al hangar
	//Array de punteros de char (A las filas solamente)
	hangarOriginal = new char*[N];
	//Ahora a las columnas
	for(int x=0; x<N; x++)
		hangarOriginal[x] = new char[M]; 
	
	//Llenando el hangar
	int i,j;
	for (i=0; i<N; i++){
		for (j=0; j<M; j++){
			cin >> hangarOriginal[i][j];
		}
	}

	//declaramos una cola de prioridad y especificamos el orden del operador >
	//Se asigna la prioridad de la cola
	priority_queue<State, vector<State>,greater<vector<State>::value_type> > cola;
	
	
	//Posicion de Luke
	getLuke(hangarOriginal,pos_inicial_X,pos_inicial_Y);
	//Posicion de los StormTroopers

	list<posTrooper> posicion_troopers;
	getTroopers(hangarOriginal,posicion_troopers); 
	

	/*cout << cantTrooper(hangarOriginal) << endl;*/
	// Encolando el estado inicial
	cola.push(State(pos_inicial_X, pos_inicial_Y, T, cantTrooper(hangarOriginal),pos_inicial_X,pos_inicial_Y, posicion_troopers));
	//busqueda(cola,0);
	//busqueda_por_Tiempo(hangarOriginal,cola,0);
	busqueda_Troopers_Optimizada(hangarOriginal,cola,0);
	
	
/*
	State S1,S2,S3,S4,S5,S6;
	S1= State();
	S2= State();
	S3= State();
	S4= State();
	S5= State();
	S6= State();
	
	S1.Time_Left = 2;
	S1.cant_Troopers= 2;
	/*posTrooper a;*/
/*	a.pos_x = 1;
	a.pos_y = 2;
	a.alive = true;
	S1.iTroopers.push_back(a);
	aux = S1.iTroopers;
	aux.pop_front();
	
	posTrooper b;
	b.pos_x = 3;
	b.pos_y = 5;
	b.alive = true;
	aux.push_back(b);
	cout << aux.front().pos_x << " " << aux.front().pos_y <<endl;
	S1.modifyAlive(aux,3,5);
	
	if (S1.isAliveTrooper(aux,3,5)){
                               cout << "Lacreo" << endl;
                               }
                               else{
                                    cout << "No hay lacreo" << endl;
                                    }*/
/*	S2.Time_Left = 1;
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
	
/*	S5.Time_Left = 10;
	S5.cant_Troopers= 3;
	S5.pos_actual_X = 5;

	cola.push(S5);
	S6.Time_Left = 155;
	S6.cant_Troopers= 0;
	S6.pos_actual_X = 6;
	cola.push(S6);
	showTimeQueue(cola);*/
    system("pause");
	
/*	printHangar(hangarOriginal);*/
	return 0;
}

