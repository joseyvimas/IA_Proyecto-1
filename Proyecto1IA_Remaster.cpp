//Josue Gabriel Sanchez - CI 24.757.111
//Jose Gregorio Yvimas - CI 23.712.348

#include <iostream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <list>
#include <utility> 
using namespace std;

int n; //Filas del hangar
int m; //Columna del hangar
int T; //Tiempo en el centro de operaciones explotara
char **Hangar;
list<pair <int,int> > Enemigos;  
class State{
	public:
		pair<int,int> pos;
		int Cant_Move;
		pair<int,int> estado_anterior;
		list< pair <int,int> > Troopers_Muertos;
		string path;
	State(){}
	State(pair<int,int> pos){
		this->pos.first = pos.first; this->pos.second = pos.second;
		this->estado_anterior.first = pos.first; this->estado_anterior.second = pos.second;
		this->path = "";
		Cant_Move = 0;
	}
	State(const State& p){
		this->pos.first = p.pos.first; this->pos.second = p.pos.second;
		this->estado_anterior.first = p.estado_anterior.first; this->estado_anterior.second = p.estado_anterior.second; 
		this->Cant_Move = p.Cant_Move;
		this->path = p.path;
		for( pair<int,int> enemy : p.Troopers_Muertos )
			this->Troopers_Muertos.push_back( enemy );
	}

	bool isKilled(int x, int y){
		for( pair<int,int> enemy : Troopers_Muertos )
  			if( enemy.first == x && enemy.second == y){
  				return true;
  			}
  		return false;
	}

	void move(char dir){
		this->estado_anterior.first = this->pos.first;
		this->estado_anterior.second = this->pos.second; 
		//cout << "Adentro de moverme" << endl;
		//cout << this->pos.first << " - " << this->pos.second << endl;
		switch(dir){
			case 'N':
				this->pos.first -= 1;	
				this->path += "N,";
				break;
			case 'S':
				this->pos.first += 1;
				this->path += "S,";	
				break;
			case 'O':
				this->pos.second -= 1;
				this->path += "O,";	
				break;
			case 'E':
				this->pos.second += 1;
				this->path += "E,";
				break;	
			case 'A':
				for (int i = this->pos.first - 1; i >= 0; i--)
				{
					if( Hangar[i][this->pos.second] == 'S' && !isKilled(i,this->pos.second)){
						this->Troopers_Muertos.push_back( make_pair(i,this->pos.second));
						this->path += "DN,";
						break;
					}					
				}
				break;
			case 'B':
				for (int i = this->pos.first + 1; i < n; i++)
				{
					if( Hangar[i][this->pos.second] == 'S' && !isKilled(i,this->pos.second)){
						this->Troopers_Muertos.push_back( make_pair(i,this->pos.second));
						this->path += "DS,";
						break;
					}					
				}
				break;
			case 'C':
				for (int i = this->pos.second - 1; i >= 0; i--)
				{
					if( Hangar[this->pos.first][i] == 'S' && !isKilled(this->pos.first,i)){
						this->Troopers_Muertos.push_back( make_pair(this->pos.first,i));
						this->path += "DO,";
						break;
					}					
				}
				break;
			case 'D':
				for (int i = this->pos.first + 1; i < m; i++)
				{
					if( Hangar[this->pos.first][i] == 'S' && !isKilled(this->pos.first,i)){
						this->Troopers_Muertos.push_back( make_pair(this->pos.first,i));
						this->path += "DE,";
						break;
					}					
				}
				break;
			case 'F':
				for (int i = this->pos.first-1; i <= this->pos.first+1; i++) {
                    for (int j = this->pos.second-1; j <= this->pos.second+1; j++) {
                        if(this->pos.first == i && this->pos.second == j) continue;
                        if( i < 0 || j < 0 || j >= m || i >= n) continue;
                        if(Hangar[i][j] == '*') continue;
                        if(Hangar[i][j] == 'S' && !isKilled(i, j)) this->Troopers_Muertos.push_back( make_pair(i,j));;
                    }
                }
                this->path += "F,";
				break;
		}
		this->Cant_Move++;				
	}
	
};

class Compare{
public:
	bool operator()(State t1, State t2){
		return t1.Troopers_Muertos.size() < t2.Troopers_Muertos.size();
	}
};

bool canVisit(char dir, State p){
	switch(dir){
		case 'N':
			if( p.pos.first - 1 >= 0 ){
				if( p.pos.first - 1 == p.estado_anterior.first && p.pos.second == p.estado_anterior.second){
				 return false;
				}else{
					if(Hangar[p.pos.first - 1][p.pos.second] != '*'){
						if(Hangar[p.pos.first - 1][p.pos.second] == 'S'){							
							if(p.isKilled(p.pos.first - 1, p.pos.second)) return true; 							
						}else return true;
					}
						
				}
			}
			break;
		case 'S':
			if( p.pos.first + 1 < n ){
				if( p.pos.first + 1 == p.estado_anterior.first && p.pos.second == p.estado_anterior.second) return false;
				else{
					if(Hangar[p.pos.first + 1][p.pos.second] != '*'){
						if(Hangar[p.pos.first + 1][p.pos.second] == 'S'){
							if(p.isKilled(p.pos.first + 1, p.pos.second)) return true; 
						}
						else return true;
					}
				}
			}
				
			break;
		case 'O':
			if( p.pos.second - 1 >= 0 ){
				if( p.pos.first == p.estado_anterior.first && p.pos.second - 1 == p.estado_anterior.second) return false;
				
				if(Hangar[p.pos.first][p.pos.second - 1] != '*'){
					if(Hangar[p.pos.first][p.pos.second - 1] == 'S'){
						if(p.isKilled(p.pos.first, p.pos.second - 1)) return true; 
					}
					else return true;
				}
				
			}
			break;
		case 'E':
			if( p.pos.second + 1 < m ){
				if( p.pos.first == p.estado_anterior.first && p.pos.second + 1 == p.estado_anterior.second) return false;
				if(Hangar[p.pos.first][p.pos.second + 1] != '*'){
					if(Hangar[p.pos.first][p.pos.second + 1] == 'S'){
						if(p.isKilled(p.pos.first, p.pos.second + 1)) return true; 
					}
					else return true;
				}
			
			}
			break;
		//Disparos A:DN B:DS C:DO D:DE F:Fuerza 
		case 'A': // DN
			for (int i = p.pos.first-1; i >= 0; i--)
			{
				if(Hangar[i][p.pos.second] == '*') return false;				
				if(Hangar[i][p.pos.second] == 'S' && !p.isKilled(i,p.pos.second)) return true;
			}
			break;
		case 'B': // DS
			for (int i = p.pos.first+1; i < n; i++)
			{
				if(Hangar[i][p.pos.second] == '*') return false;				
				if(Hangar[i][p.pos.second] == 'S' && !p.isKilled(i,p.pos.second)) return true;
			}
			break;
		case 'C': // DO
			for (int i = p.pos.second - 1; i >= 0; i--)
			{
				if(Hangar[p.pos.first][i] == '*') return false;				
				if(Hangar[p.pos.first][i] == 'S' && !p.isKilled(p.pos.first, i)) return true;
			}
			break;
		case 'D': // DE
			for (int i = p.pos.first + 1; i < m; i++)
			{
				if(Hangar[p.pos.first][i] == '*') return false;				
				if(Hangar[p.pos.first][i] == 'S' && !p.isKilled(p.pos.first, i)) return true;
			}
			break;
		case 'F': // F
			for (int i = p.pos.first-1; i <= p.pos.first+1; i++) {
                    for (int j = p.pos.second-1; j <= p.pos.second+1; j++) {
                        if(p.pos.first == i && p.pos.second == j) continue;
                        if( i < 0 || j < 0 || j >= m || i >= n) continue;
                        if(Hangar[i][j] == '*') continue;
                        if(Hangar[i][j] == 'S' && !p.isKilled(i, j)) return true;
                    }
                }
			break;
	}

	return false;
}

string search(State* player){
	string solution = "";
	priority_queue<State, vector<State>, Compare > cola;	
	cola.push(*player);
	int Cant_Move = T;
	while(!cola.empty()){
		State p = cola.top();
		cola.pop();
		if( p.Cant_Move >= Cant_Move) continue;
		if( p.Troopers_Muertos.size() == Enemigos.size()){
			cout << "Consegui una mejor solucion" << endl;
			solution = p.path.substr(0,p.path.length()-1);
			Cant_Move = p.Cant_Move;
			cout << p.Cant_Move << ": "<< solution << endl;
		}
		//Ahora agregamos adyacentes:
		if( canVisit('N', p)){
			State *actual = new State(p);
			actual->move('N');
			cola.push(*actual);
		}
		if( canVisit('S', p)){
			State *actual = new State(p);
			actual->move('S');
			cola.push(*actual);
		}
		if( canVisit('O', p)){
			State *actual = new State(p);
			actual->move('O');
			cola.push(*actual);
		}
		if( canVisit('E', p)){
			State *actual = new State(p);
			actual->move('E');
			cola.push(*actual);
		}
		//Disparos A:DN B:DS C:DO D:DE F:Fuerza 
		if( canVisit('A', p)){
			State *actual = new State(p);
			actual->move('A');
			cola.push(*actual);
		}
		if( canVisit('B', p)){
			State *actual = new State(p);
			actual->move('B');
			cola.push(*actual);
		}
		if( canVisit('C', p)){
			State *actual = new State(p);
			actual->move('C');
			cola.push(*actual);
		}
		if( canVisit('D', p)){
			State *actual = new State(p);
			actual->move('D');
			cola.push(*actual);
		}
		if( canVisit('F', p)){
			State *actual = new State(p);
			actual->move('F');
			cola.push(*actual);
		}

	}

	return solution;
}

int main(){
	cin >> n; cin >> m; cin >> T;	
	Hangar = new char*[n];	
	State *player = new State();
	for (int i = 0; i < n; i++)
	{
		Hangar[i] = new char[m];
		for (int j = 0; j < m; j++)
		{
			char casilla;
			cin >> casilla;
			Hangar[i][j] = casilla;
			if(aux == 'S'){
				Enemigos.push_back( make_pair(i,j) );
			}else if( casilla == 'L'){
				player = new State( make_pair(i,j) );
			}
		}
	}
	string solution = search(player);
	if(solution == "") cout << "A great loss for the rebels" << endl;
	else cout << "The Force is Strong in Luke!" << endl << solution << endl;
	return 0;
}

