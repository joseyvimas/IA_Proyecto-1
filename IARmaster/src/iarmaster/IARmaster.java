package iarmaster;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

/**
 * @authors
 * Josue Sanchez CI:. 24757111
 * José Yvimas CI:. 23712348
 */
public class IARmaster {
    public static int n; //Filas del hangar
    public static int m; //Columna del hangar
    public static int T; //Tiempo en el centro de operaciones explotara
    public static char Hangar [][];  //Matriz que representa el Hangar
    public static List<Pair<Integer,Integer>> Enemigos = new ArrayList<Pair<Integer,Integer>>();  
    
    //Funcion que verifica si se puede realizar determinado movimiento que se envia en un string
    public static boolean canVisit(String dir, State p){
	switch(dir){
            case "N":
                if( p.pos.first - 1 >= 0 ){
                    if( p.pos.first - 1 == p.estado_anterior.first && p.pos.second == p.estado_anterior.second){
			return false;
                    }
                    else{
                        if(Hangar[p.pos.first - 1][p.pos.second] != '*'){
                            if(Hangar[p.pos.first - 1][p.pos.second] == 'S'){							
                                if(p.isKilled(p.pos.first - 1, p.pos.second)) return true; 							
                            }
                            else return true;
                        }			
                    }
		}
                break;
            case "S":
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
            case "O":
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
            case "E":
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
            case "DN": // DN
		for (int i = p.pos.first-1; i >= 0; i--){
                    if(Hangar[i][p.pos.second] == '*') return false;				
                    if(Hangar[i][p.pos.second] == 'S' && !p.isKilled(i,p.pos.second)) return true;
		}
		break;
            case "DS": // DS
		for (int i = p.pos.first+1; i < n; i++){
                    if(Hangar[i][p.pos.second] == '*') return false;				
                    if(Hangar[i][p.pos.second] == 'S' && !p.isKilled(i,p.pos.second)) return true;
		}
		break;
            case "DO": // DO
		for (int i = p.pos.second - 1; i >= 0; i--){
                    if(Hangar[p.pos.first][i] == '*') return false;				
                    if(Hangar[p.pos.first][i] == 'S' && !p.isKilled(p.pos.first, i)) return true;
		}
		break;
            case "DE": // DE
		for (int i = p.pos.second + 1; i < m; i++){
                    if(Hangar[p.pos.first][i] == '*') return false;				
                    if(Hangar[p.pos.first][i] == 'S' && !p.isKilled(p.pos.first, i)) return true;
		}
                break;
            case "F": // F
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
    
    //Funcion que calcula cual es la cantidad maxima de StormTroopers que se pueden matar con un determinado tiempo restante
    public static int maxTroopersKill (int time) {
	if (time % 2 == 0){
            return maxTroopersKill(time - 1) + 1;
        }
        else{
            return (((time - 1) / 2) * 3) + 8;
        }
    }
    
    //Funcion que aplica la busqueda con un determinado T
    public static String search(State player){
	String solution = "";
	Stack<State> pila = new Stack<>();
	pila.add(player);
	int Cant_Move_Max = T;
	while(!pila.empty()){  //Mientras tengamos estados en la pila
		State p = pila.pop();  //Desapilamos
                
		if(p.Cant_Move == Cant_Move_Max) continue; //Si llevamos mas pasos que el maximo obviamos ese estado
		if(p.Cant_Move >= n*m) continue;  //Si llevamos más pasos que la suma de n*m obviamos ese estado
                if (p.Cant_Move + (Enemigos.size()-p.Troopers_Muertos.size()) > (T+9)) continue;
                if ((Enemigos.size()-p.Troopers_Muertos.size()) > maxTroopersKill(T-p.Cant_Move)) continue;
                
                if(p.Troopers_Muertos.size() == Enemigos.size()){ //Encontramos solucion
                    solution = p.path.substring(0,p.path.length()-1);
                    return solution;  //Retornamos el string de la solucion
		}
               
                //MOVERSE
		if( IARmaster.canVisit("N", p)){
                    State actual = new State(p);
                    actual.movimiento("N");
                    pila.add(actual);
		}
		if( IARmaster.canVisit("S", p)){
                    State actual = new State(p);
                    actual.movimiento("S");
                    pila.add(actual);
		}
                if( IARmaster.canVisit("E", p)){
                    State actual = new State(p);
                    actual.movimiento("E");
                    pila.add(actual);
		}
		if( IARmaster.canVisit("O", p)){
                    State actual = new State(p);
                    actual.movimiento("O");
                    pila.add(actual);
		}
                //DISPARAR
		if( IARmaster.canVisit("DN", p)){
                    State actual = new State(p);
                    actual.movimiento("DN");
                    pila.add(actual);
		}
		if( IARmaster.canVisit("DS", p)){
                    State actual = new State(p);
                    actual.movimiento("DS");
                    pila.add(actual);
		}
                if( IARmaster.canVisit("DE", p)){
                    State actual = new State(p);
                    actual.movimiento("DE");
                    pila.add(actual);
		}
		if( IARmaster.canVisit("DO", p)){
                    State actual = new State(p);
                    actual.movimiento("DO");
                    pila.add(actual);
		}
                //FUERZA
		if( IARmaster.canVisit("F", p)){
                    State actual = new State(p);
                    actual.movimiento("F");
                    pila.add(actual);
		}
	}
	return "";
    }
    
    //Funcion que itera el tiempo en busca de la mejor solucion
    public static String busqueda(State player){ 
	String posibleSolucion, solucion;
	posibleSolucion = solucion = "";
	int i;
	int limit = T;
	for (i=1; i<=limit; i++){
            T=i;  //iteramos el tiempo
            posibleSolucion = search(player);
            if (posibleSolucion.equals("")) continue;
            else{
                solucion = posibleSolucion; //Mejor solucion
                return solucion;
            }	
	}
        return solucion;
    }
   
    public static void main(String[] args) throws IOException {
        boolean lukExist = false;
        
        //Leyendo la entrada
        Scanner consola = new Scanner(System.in);
        n = consola.nextInt(); //Filas
        m = consola.nextInt(); //Columnas
        T = consola.nextInt(); //Tiempo (pasos)
        
        Hangar = new char[n][m]; //Le damos dimensiones al hangar
	State player = new State(); //Estado inicial
        
        //Llenando el hangar
        String linea; 
	for (int i = 0; i < n; i++){
            linea = consola.next();
            for (int j = 0; j < m; j++){
		char casilla = ' ';
                casilla = linea.charAt(j);
           
		if (casilla != 'L' && casilla != '*' && casilla != 'S' && casilla != '.'){ //Validamos los caracteres permitidos en el hangar
                    System.out.print("Hangar incorrecto\n");
                    return;
		}
		Hangar[i][j] = casilla;
		if(casilla == 'S'){
                    Enemigos.add( Pair.make_pair(i,j) ); //Añadimos los StormTroopers iniciales
		}
                else if( casilla == 'L'){
                    if (!lukExist){  //Se verifica que no hay mas de un Luke
			lukExist = true;
                        Pair<Integer,Integer> par = Pair.make_pair(i,j);
			player = new State(par);
                    }
                    else{
			System.out.print("Hangar incorrecto\n");
			return;
                    }
		}
            }
	}
        if(!lukExist){ //Verificamos que Luke exista
            System.out.print("Hangar incorrecto\n");
            return;
        }
        
	String solution = busqueda(player);  //aplicamos el algoritmo de busqueda
	if(solution.equals("")) System.out.print("A great loss for the rebels\n");
	else System.out.print("The Force is Strong in Luke!\n"+solution+"\n");
	return;
    }    
}

class Pair<L,R> {
    public L first;
    public R second;
    
    Pair(){
    }
    public Pair(L l, R r){
        this.first = l;
        this.second = r;
    }
    public static Pair<Integer,Integer> make_pair (Integer i ,Integer j){
        Pair<Integer,Integer> nodo = new Pair(i,j);
        return nodo;
    }
}

//Clase que representa cada estado posible de Luke en el hangar
class State{
    public Pair<Integer,Integer> pos;
    public int Cant_Move;
    public Pair<Integer,Integer> estado_anterior;
    public List< Pair <Integer,Integer> > Troopers_Muertos;
    public String path;
    public int evaluacion;
    
    State(){
        this.Troopers_Muertos = new ArrayList<Pair<Integer,Integer>>();
        this.pos = new Pair(0,0);
	this.estado_anterior = new Pair(0,0);
    }
    
    State(Pair<Integer,Integer> pos){
	this.pos = new Pair(pos.first,pos.second);
	this.estado_anterior = new Pair(pos.first,pos.second);
	this.path = "";
	this.Cant_Move = 0;
	this.evaluacion = 0;
        this.Troopers_Muertos = new ArrayList<Pair<Integer,Integer>>();
    }
    State( State p){
	this.pos = new Pair(p.pos.first,p.pos.second);
	this.estado_anterior = new Pair(p.pos.first,p.pos.second);
	this.Cant_Move = p.Cant_Move;
	this.path = p.path;
        this.Troopers_Muertos = new ArrayList<Pair<Integer,Integer>>();
	for( Pair<Integer,Integer>enemy : p.Troopers_Muertos )
            this.Troopers_Muertos.add( enemy );
    }
    
    //Funcion que verifica si un determinado StormTrooper esta muerto
    public boolean isKilled(int x, int y){
	for( Pair<Integer,Integer> enemy : Troopers_Muertos ){
            if( enemy.first == x && enemy.second == y){
  		return true;
            }
        }    
        return false;
    }

    public void movimiento(String dir){
	switch(dir){
            case "N":
		this.pos.first -= 1;	
		this.path += "N,";
		break;
            case "S":
		this.pos.first += 1;
		this.path += "S,";	
		break;
            case "O":
		this.pos.second -= 1;
		this.path += "O,";	
		break;
            case "E":
		this.pos.second += 1;
		this.path += "E,";
		break;	
            case "DN":
		for (int i = this.pos.first - 1; i >= 0; i--){
                    if(IARmaster.Hangar[i][this.pos.second] == 'S' && !isKilled(i,this.pos.second)){
			this.Troopers_Muertos.add( Pair.make_pair(i,this.pos.second));
			this.path += "DN,";
			break;
                    }					
		}
		break;
            case "DS":
		for (int i = this.pos.first + 1; i < IARmaster.n; i++){
                    if(IARmaster.Hangar[i][this.pos.second] == 'S' && !isKilled(i,this.pos.second)){
			this.Troopers_Muertos.add( Pair.make_pair(i,this.pos.second));
			this.path += "DS,";
			break;
                    }					
		}
		break;
            case "DO":
		for (int i = this.pos.second - 1; i >= 0; i--){
                    if(IARmaster.Hangar[this.pos.first][i] == 'S' && !isKilled(this.pos.first,i)){
			this.Troopers_Muertos.add( Pair.make_pair(this.pos.first,i));
                        this.path += "DO,";
                        break;
                    }					
                }
                break;
            case "DE":
		for (int i = this.pos.second + 1; i < IARmaster.m; i++){
                    if(IARmaster.Hangar[this.pos.first][i] == 'S' && !isKilled(this.pos.first,i)){
			this.Troopers_Muertos.add( Pair.make_pair(this.pos.first,i));
			this.path += "DE,";
			break;
                    }					
		}
                break;
            case "F":
		for (int i = this.pos.first-1; i <= this.pos.first+1; i++) {
                    for (int j = this.pos.second-1; j <= this.pos.second+1; j++) {
                        if(this.pos.first == i && this.pos.second == j) continue;
                        if( i < 0 || j < 0 || j >= IARmaster.m || i >= IARmaster.n) continue;
                        if(IARmaster.Hangar[i][j] == '*') continue;
                        if(IARmaster.Hangar[i][j] == 'S' && !isKilled(i, j)) this.Troopers_Muertos.add( Pair.make_pair(i,j));
                    }
                }
                this.path += "F,";
		break;
	}
	this.Cant_Move++;				
    }
};
