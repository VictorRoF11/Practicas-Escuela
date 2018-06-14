#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

FILE *fd;
char Contenido[1000];
string cinta;
string cinAux;
char alfabeto[1000];
int tamarchivo;
int estadoInicial;
int estadoFinal;
int iniTrans;
char estados[50][50];
char movimientos[50][50];
char colocar[50][50];
int posTabla;

void imprimirCinta();
void actualizarCinta(int pos);
void ExtraerContenido(char *nomArch);
void pausa();
void ProbarCadena(string cad);
void ExtraerAlfabeto();
void extraerDescripcion();
void imprimirAlfabeto();
void extraerTransacciones();

int main()
{
	char tecla;
	bool bandera;
	bool ban;
	string cadena;
	char archivo[100];
	 do
    {
        system("clear");
        cout << "--------------------------"<<endl;
        cout << "|   Maquinas de Turing.  |" << endl;
        cout << "--------------------------" << endl << endl;
        cout<<"Alumno: Rodriguez Flores Victor Hugo"<<"\n";
        cout<<"Materia: Teoria Computacional"<<"\n";
        cout<<"Grupo: 2CV2"<<"\n";
        cout<<"Profesor: Luna Benoso Benjamin"<<"\n"<<"\n";
        cout<<"------ MENU ------"<<"\n";
        cout<<"Ingresar Archivo. (1)"<<endl;
        cout<<"Salir (2)"<<"\n";
        cout << "Elije una opcion: ";
        cin >> tecla;
 
		switch(tecla)
		{
			case '1':
					system("clear");
					char opc;
					cout<<"Ingresa el nombre del archivo: ";
					cin>>archivo;
					ExtraerContenido(archivo);
					ExtraerAlfabeto();
					extraerTransacciones();

					do{
						cout<<"\n"<<"Ingresa una cadena: ";
						cin>>cadena;
						ProbarCadena(cadena);
						cout<<"\n"<<"\n";
						
					cout<<"(1) para ingresar otra cadena, (2) para salir"<<"\n";
					cin>>opc;
						if(opc != '1'){
							ban = true;
						}
					}
					while(ban != true);
					
				pausa();
				break;
 			case '2':
 				bandera =true;
 				break;
			default:
				system("clear");
				cout << "Opcion no valida.\a\n";
				pausa();
				break;
		}
    }while(bandera!=true);
 return 0;
}
//Imprime en pantalla la cinta de la MT.
void imprimirCinta(int pos){
	usleep(70000);
	int posicion = pos;
	int i=0;
	system("clear");
	while(i < cinta.size()){
		if (i == posicion)
			cout<<char(118); //Muestra la posicion del puntero
		else
		cout<<"  ";
		i++;
	}
	cout<<"\n";
	int j=0;
	while(j < cinta.size()){ //Muestra el contenido de la cinta
		cout<<cinta[j]<<" ";
		j++;
	}
	cout<<"\n";
}

void actualizarCinta(){
	cinta= 'B' + cinAux + 'B';
}

void ExtraerContenido(char *nomArch){
	tamarchivo=0;
	char *nombreArchivo = nomArch;
	char c;
	//--------------Abrir Archivo----------
	fd = fopen(nombreArchivo, "r"); 
	
	if(fd == NULL){
		cout<<"Error al abrir el archivo"; 
		}
	//--------------- Leer contenido del archivo --------------------------
	int i=0;
	while((c=fgetc(fd))!=EOF ){
	Contenido[i]= c; //Guarda el contenido en un arreglo
		cout<<c;
		i++;
	}
	tamarchivo=i;
	fclose(fd);  	
	//--------------------------//Cerrar Archivo
}
void pausa()
{
	cout << "Pulsa una tecla para continuar...";
    getchar();
    getchar();
}

void ExtraerAlfabeto(){ //Guarda el alfabeto de la cinta en un arreglo
	int k=0,j=0;
			while(Contenido[k] != '\n'){
				if ( (Contenido[k] >= 48) && (Contenido[k] <= 122) )
				{
					alfabeto[j]= Contenido[k];
					j++;
				}
				k++;
			}
		iniTrans=j;	
}			

void imprimirAlfabeto(){ //Muetra el alfabeto. No necesario
	cout<<"Alfabeto :";
	for (int i = 0; i < iniTrans; ++i)
	{
		cout<<alfabeto[i]<<" ";
	}
	cout<<"\n";
}

void extraerTransacciones(){ // Extrae las transacciones en 3 arreglos
	int i=iniTrans+1;
	int x=0,y;
	int aux=0;
	
	while(i< tamarchivo){
		
		if (Contenido[i] == '*'){
			y=0;
			aux = i;
			estadoInicial = Contenido[i+2];
			//cout<<"estadoInicial: "<<estadoInicial<<"\n";

			while(Contenido[aux] != '\n'){
				if (Contenido[aux] == '(')
				{
					estados[x][y] = Contenido[aux+2]; // Movimiento de estado
					movimientos[x][y] = Contenido[aux+6]; // Movimiento puntero de la cinta
					colocar[x][y] = Contenido[aux+4]; //Pintar un caracter en la cinta
					y++;
				}
				aux++;
			}
			x++;
			i= aux;
		}
		else{
			if (Contenido[i] == '+'){
			y=0;	
			aux = i;
			estadoFinal = Contenido[i+2];
			//cout<<"estadoFinal: "<<estadoFinal<<"\n";

				while(Contenido[aux] != '\n'){
					
					if (Contenido[aux] == '(')
					{
						estados[x][y] = Contenido[aux+2];
						movimientos[x][y] = Contenido[aux+6];
						colocar[x][y] = Contenido[aux+4];
						y++;
					}
					aux++;
				}
				x++;
				i=aux;
			}
			else{
				if (Contenido[i] == 'q'){
				aux = i;
				y=0;

				while(Contenido[aux] != '\n'){
					if (Contenido[aux] == '(')
					{
						estados[x][y] = Contenido[aux+2];
						movimientos[x][y] = Contenido[aux+6];
						colocar[x][y] = Contenido[aux+4];
						y++;
					}
					aux++;
				}
				x++;
				i=aux;
				}
			}
		}		
		i++;
	}
}

void ProbarCadena(string cad){
	
	string cadena = cad;
	cinAux = 'B'+ cadena + 'B'; //Concatena un espacio en blanco a los extremos de la cinta
	actualizarCinta();
	int cabeza= 2; //Posicion de inicio de la cinta
	int estadoActual=estadoInicial-48;
	int posEstado=0;
	int posAlfabeto=0;
	int posicion=0;
	bool bandera = true;

	int i=0;
	while(bandera == true){
	
			if(estadoActual == estadoFinal-48){ //si llega al estado de aceptacion
				cout<<"ACEPTADA.!!"<<"\n";
				bandera = false;
				break;
			}
			for (int i = 0; i < cinAux.size(); ++i) //si pinta un elemento que no esta en el alfabeto.
			{
				if (cinAux[i] == 'z')
				{
					cout<<"Cadena NO aceptada.!!"<<"\n";
					bandera = false;
					break;
				}
			}

			if (cinta[cabeza] == alfabeto[posAlfabeto])
			{
				imprimirCinta(cabeza);
				cinAux[cabeza-1]=colocar[estadoActual][posAlfabeto]; // cambia el caracter por el de la transaccion
				actualizarCinta();
				imprimirCinta(cabeza);

				if (movimientos[estadoActual][posAlfabeto] == 'D' ) //Desplaza el puntero hacia la derecha o izquierda
				{
					cabeza++;
				}
				else{
					if (movimientos[estadoActual][posAlfabeto] == 'I' ){
						cabeza--;
					}
				}

				estadoActual= estados[estadoActual][posAlfabeto]-48; //Actualiza el estado
				imprimirCinta(cabeza);
			posAlfabeto=0;	
			i++;	
			}
			else{
				posAlfabeto++;
			}		
	}
}