#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <cctype>
#include <limits>
#include <dirent.h>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

void menuPrincipal();
void menuEdicion();
void disenarMatriz(string **, int, int);
void createMatriz(int, int);
void list_dir(string);
void guardarMatriz(string** punteromatriz, int f, int c);
void abrirjson(string** punteromatriz, int f, int c);


void ingresarContenido(string **, int*, int*); 	//1 opcion
void saltarCelda(string **, int*, int*); 		//2 opcion
void copiarContenido(string **, int*, int*); 	//3 opcion
void cortarContenido(string **, int*, int*); 	//4 opcion
void pegarContenido(string **, int*, int*); 	//5 opcion
void moverIzquierda(string **, int*, int*); 	//6 opcion
void moverDerecha(string **, int*, int*); 		//7 opcion
void moverArriba(string **, int*, int*); 		//8 opcion
void moverAbajo(string **, int*, int*); 		//9 opcion

int main()
{
	
	menuPrincipal(); //Llama a la funcion que crea el menu principal
	
    return 0;
}

string **punteromatriz;
string aux = " ";
string copiar = " ";

void menuPrincipal(){
	
	bool band = true; //Crea una seï¿½al para deterner el do-while
	
	do{
		char answer;
		
		cout<<"\t\t+-------------------------------------------------------+"<<endl;
		cout<<"\t\t\t\tEXCEL IMPROVISADO"<<endl;
		cout<<"\t\t+-------------------------------------------------------+"<<endl;
		
		cout<<"\n\t1. Crear Nuevo Documento"<<"\n\t2. Abrir Nuevo Documento"<<"\n\t3. Salir"<<endl; // Escribe las opciones posibles en pantalla
		cout<<"\tR/";cin>>answer;
		
		system("cls"); //Limpia la consola
		
		try{
			switch(answer){ //Switch para decidir la respuesta del usuario
				case '1':
					aux = " ";
					createMatriz(16, 16);
					menuEdicion();
					break;
					
				case '2':
					createMatriz(16, 16);
					abrirjson(punteromatriz, 16, 16);
					break;
					
				case '3':
					
					cout<<"GRACIAS POR USAR NUESTRO PROGRAMA :)"<<endl;
					system("pause");
					band = false;
					break;
					
				default:
					throw (answer);
					break;
					
				}	
		}catch(char myAnswer){
			cout<<"caracter '" <<myAnswer<<"' Invalido :("<<endl;
			system("pause");
			system("cls");
		}
		
			
	}while(band);
	
	
	
}

void createMatriz(int f, int c){
	
	punteromatriz = new string*[f];
	
	for (int i = 0; i<f;i++){
		punteromatriz[i] = new string[c];
	}
	
	
}

void list_dir(string dir){
	DIR *directorio;
	struct dirent *elemento;
	string elem;
	
	if(directorio = opendir(dir.c_str())){
		while(elemento = readdir(directorio)){
			
			elem = elemento->d_name;
			if(elem.find(".json") != string::npos){
				cout<<"\t\t"<<elem<<endl;
			}
		}
		cout<<"\n";
	}
	
	closedir(directorio);
	
}

void menuEdicion(){
	
	int f = 16; // Aqui se ponen la longitud // Una celda mas para definir filas y columnas
	int c = 16; // de casillas que se desean
	
	bool band1 = true; //Crea una seï¿½al para deterner el do-while
	
	//createMatriz(f, c); //Inicializa la matriz
	
	int filaActual = 1;
	int columnaActual = 1;
	
	do{
		
		try{
			
			char answer1;
			*(*(punteromatriz+filaActual)+columnaActual) = "***";
			
			disenarMatriz(punteromatriz, f, c); //Llamado a la funcion para crear la matriz
			
			cout<<"\t\t+-------------------------------------------------------+"<<endl;
			cout<<"\t\t\t\tNUEVO DOCUMENTO"<<endl;
			cout<<"\t\t+-------------------------------------------------------+"<<endl;
			
			cout<<"\n\t1. Ingresar Contenido";
			cout<<"\t2. Saltar a celda";
			cout<<"\t3. Copiar";
			cout<<"\n\t4. Cortar";
			cout<<"\t\t5. Pegar";
			cout<<"\t\t6. Mover a la Izquierda";
			cout<<"\n\t7. Mover a la derecha";
			cout<<"\t8. Moverse arriba";
			cout<<"\t9. Moverse abajo";
			cout<<"\n\tg. Guardar";
			cout<<"\t\te. Salir"; // Escribe las opciones posibles en pantalla del menu de nuevo documento
			cout<<"\n\tR/";cin>>answer1;
			
			
			switch(answer1){ //Switch para decidir la respuesta del usuario
				case '1':
						ingresarContenido(punteromatriz, &filaActual, &columnaActual);
					break;
				case '2':
						saltarCelda(punteromatriz, &filaActual, &columnaActual);
					break;
				case '3':
						copiarContenido(punteromatriz, &filaActual, &columnaActual);
					break;
					
				case '4':
						cortarContenido(punteromatriz, &filaActual, &columnaActual);
					break;
				case '5':
						pegarContenido(punteromatriz, &filaActual, &columnaActual);
					break;
				case '6':
						moverIzquierda(punteromatriz, &filaActual, &columnaActual);
					break;
				case '7':
						moverDerecha(punteromatriz, &filaActual, &columnaActual);
					break;	
				case '8':
						moverArriba(punteromatriz, &filaActual, &columnaActual);
					break;
				case '9':
						moverAbajo(punteromatriz, &filaActual, &columnaActual);
					break;
				case 'g':
						guardarMatriz(punteromatriz, f, c);
					break;
					
				case 'e':
						system("cls");
						band1 = false;
					break;
					
				default:
						throw(answer1);
					
					break;
				
			}	
		}catch(char myAnswer2){
			cout<<"Opcion Invalida, por favor, intente de nuevo"<<endl; 
			system("pause");
		}
	}while(band1);
}

void abrirjson(string** punteromatriz, int f, int c){
	string nombreArchivo;
		cout<<"\t\t+-------------------------------------------------------+"<<endl;
		cout<<"\t\t\t    Ingrese el nombre del archivo JSON: "<<endl;
		cout<<"\t\t+-------------------------------------------------------+"<<endl;
		
		list_dir("./"); //Llama a la funcion para abrir el directorio
		
		cout<<"\t\tNombre: " ;
		cin.ignore();
		getline(cin, nombreArchivo);
		nombreArchivo += ".json";
        ifstream jsonFile(nombreArchivo); //Se habre el archivo.json
        if (!jsonFile.is_open()) {	//se valida si el archivo se pudo habrir
        	
            cout << "\t\tEl archivo "<< nombreArchivo <<" no existe."<< endl;
            system("pause");
            system("cls");
        } 
		else {
        	ifstream jsonFile(nombreArchivo); //habre el archivo.json
			json root;	// se declara archivo json almazenar y manipular el .json
  			jsonFile >> root; //para leer el flujo del .json

  			if (root["matriz"].is_array()) { // verifica que el "matriz" sea un arreglo
  		  int x=0;	//contador columna
  		  for (const auto& fila : root["matriz"]) { // recorre cada columna 
     		 int y=0;	//contador de filas
     		 if (fila.is_array()) { //verifica que la fila sea un arreglo
      		  for (const auto& elemento : fila) { //Reccore cada la fila
      		    *(*(punteromatriz+x)+y) = elemento; //Se añade el elemento a la matris en la cordernadas
        		  y+=1;
					}
						}
					x+=1;
				}
			}
			aux = *(*(punteromatriz+1)+1);
			menuEdicion();
			}
        
    }

void disenarMatriz(string **punteromatriz, int f, int c){
	
	system("mode con: cols=175 lines=50"); //dimensiona la consola
	
	*(*(punteromatriz+10)+0) = "10";
	*(*(punteromatriz+11)+0) = "11";
	*(*(punteromatriz+12)+0) = "12"; //Rellenan las posiciones 
	*(*(punteromatriz+13)+0) = "13"; //de referencia para las filas
	*(*(punteromatriz+14)+0) = "14";
	*(*(punteromatriz+15)+0) = "15";
	
	
	puts("+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
	for (int i = 0; i < f; i++) {
		putchar('|');
		for (int j = 0; j < c; j++){
			
			if(j==0 && i>0 && i<10){
				*(*(punteromatriz+i)+j) = i + 48; //Codigo ASCII para numeros
			}
			
			if(i==0 && j>0 ){
				*(*(punteromatriz+i)+j) = j + 64; //Codigo ASCII para letras
			}
				
			if ( (*(*(punteromatriz+i)+j)).empty() ){ // Revisa si donde apunta el puntero (casilla) esta vacio
				printf("         |");
			}else{
				
				
				switch( (*(*(punteromatriz+i)+j)).length() ){ //    Rellena de espacion en blanco segun la longitud de los caracteres
					case 1:
						cout<< (*(*(punteromatriz+i)+j)) << "        |";
						break;
					case 2:
						cout<< (*(*(punteromatriz+i)+j)) << "       |";
						break;
					case 3:
						cout<< (*(*(punteromatriz+i)+j)) << "      |";
						break;
					case 4:
						cout<< (*(*(punteromatriz+i)+j)) << "     |";
						break;
					case 5:
						cout<< (*(*(punteromatriz+i)+j)) << "    |";
						break;
					case 6:
						cout<< (*(*(punteromatriz+i)+j)) << "   |";
						break;
					case 7:
						cout<< (*(*(punteromatriz+i)+j)) << "  |";
						break;
					case 8:
						cout<< (*(*(punteromatriz+i)+j)) << " |";
						break;	
					default:
						break;
				
				}
			}
			
			
		}
		puts("\n+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
	}
	putchar('\n');
	
}

void ingresarContenido(string **punteromatriz, int *filaActual, int *columnaActual){
	
	
	do{
		cout<<"Ingrese el contenido que desea en la celda ["<<*filaActual<<"]["<<*(*(punteromatriz)+*(columnaActual))<<"] : ";
		cin.ignore();
		getline(cin, *(*(punteromatriz+*filaActual)+*columnaActual));
		
		if((*(*(punteromatriz+*filaActual)+*columnaActual)).length() > 8){
			cout<<"La palabra excede los caracteres permitidos (8), por favor, intentelo de nuevo"<<endl;
		}
		
	}while( (*(*(punteromatriz+*filaActual)+*columnaActual)).length() > 8 );
	
	if(*filaActual+1 < 16){
		*filaActual += 1;
	}else{
		*filaActual = 1;
	}
	
	
	aux = *(*(punteromatriz+*filaActual)+*columnaActual);
	
}

void saltarCelda(string **punteromatriz, int *filaActual, int *columnaActual){
	

	
	*(*(punteromatriz+*filaActual)+*columnaActual) = aux;
	
	bool band = true;
	int number;
	
	do{
		bool valid = false;
		while (!valid) {
        cout<<"Ingrese la fila de la celda [1-15]: ";
        if (cin >> number) {
            if (cin.peek() == '\n') {
                valid = true;
            }
        }
        if (!valid) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Por favor, ingrese solo numeros enteros." << std::endl;
        }
    }
		*filaActual = number;
		if((*filaActual >= 1) && (*filaActual <=15) ){
			band = false;
		}else{
			cout<<"numero de fila Invalido, intente de nuevo :)"<<endl;
		}
		
	}while(band);
	
	band = true;
	char columna;
	int num;
	
	do{
		cout<<"Ingrese la columna en mayuscula de la celda [A-O]: ";
		cin>>columna;
		columna = toupper(columna);
		num = columna-64;
		
		if((num >= 1) && (num <= 15) ){
			band = false;
			*columnaActual = num;
		}else{
			cout<<"letra de columna Invalido, intente de nuevo :)"<<endl;
		}
		
	}while(band);
	
	
	aux = *(*(punteromatriz+*filaActual)+*columnaActual);
	
}

void copiarContenido(string **punteromatriz, int *filaActual, int *columnaActual){
	
	copiar = aux;
	cout<<"Usted ha copiado la palabra: "<<copiar<<endl;
	system("pause");
	
}

void cortarContenido(string **punteromatriz, int *filaActual, int *columnaActual){
	
	copiar = aux;
	
	*(*(punteromatriz+*filaActual)+*columnaActual) = " ";
	
	aux = *(*(punteromatriz+*filaActual)+*columnaActual);
	
	cout<<"Usted ha cortado la palabra: "<<copiar<<endl;
	system("pause");
	
}

void pegarContenido(string **punteromatriz, int *filaActual, int *columnaActual){
	
	aux = copiar;
	cout<<"Usted ha pegado la palabra '"<<copiar<<"' en ["<<*filaActual<<"]["<<*(*(punteromatriz)+*(columnaActual))<<"]"<<endl;
	system("pause");
	
}

void moverIzquierda(string **punteromatriz, int *filaActual, int *columnaActual){
	
	*(*(punteromatriz+*filaActual)+*columnaActual) = aux;
	
	if(*columnaActual-1 > 0){
		*columnaActual -= 1;
	}else{
		*columnaActual = 15;
	}
	
	aux = *(*(punteromatriz+*filaActual)+*(columnaActual));
	
}

void moverDerecha(string **punteromatriz, int *filaActual, int *columnaActual){
	
	
	*(*(punteromatriz+*filaActual)+*(columnaActual)) = aux;
	
	
	if(*columnaActual+1 < 16){
		*columnaActual += 1;
	}else{
		*columnaActual = 1;
	}
	
	aux = *(*(punteromatriz+*filaActual)+*(columnaActual));
	
}

void moverArriba(string **punteromatriz, int *filaActual, int *columnaActual){
	
	*(*(punteromatriz+*filaActual)+*columnaActual) = aux;
	
	if(*filaActual-1 > 0){
		*filaActual -= 1;
	}else{
		*filaActual = 15;
	}
	
	aux = *(*(punteromatriz+*filaActual)+*(columnaActual));
	
}

void moverAbajo(string **punteromatriz, int *filaActual, int *columnaActual){
	
	*(*(punteromatriz+*filaActual)+*columnaActual) = aux;
	
	if(*filaActual+1 < 16){
		*filaActual += 1;
	}else{
		*filaActual = 1;
	}
	
	aux = *(*(punteromatriz+*filaActual)+*(columnaActual));
	
}

void guardarMatriz(string **punteromatriz, int f, int c) {
    
	string nombreArchivo;
    string nombreJSON;
    
    bool archivoExiste = false;

	while (!archivoExiste) {
        cout << "Digite el nombre del archivo con el que quisiera guardarlo: ";
        cin.ignore();
        getline(cin, nombreArchivo);

        nombreJSON = nombreArchivo + ".json";

        ifstream archivo(nombreJSON.c_str());
    
        if (archivo) {
            archivo.close();
            cout << "El archivo '" << nombreArchivo << "' ya existe, ¿Desea reemplazarlo? (s/n): ";
            char opcion;
            cin >> opcion;
            if (opcion == 's' || opcion == 'S') {// Reemplazar el archivo con el mismo nombre
                remove(nombreJSON.c_str());
                archivoExiste = true;
            } else {
                continue; //solicitar otro nombre de archivo
            }
        } else {
            archivoExiste = true;
        }
    }

    ofstream archivo(nombreJSON.c_str()); // Escribir datos en un archivo en modo de escritura // c_str transforma el archivo al parametro que necsita la funcion oftream

    // Crea un objeto JSON, { es el inicio de un objeto
    archivo << "{\n";
    archivo << "\t\"matriz\": [\n";

    for (int i = 0; i < f; i++) {
        archivo << "\t\t["; // Inicio de una nueva fila

        // Recorre las columnas de la matriz
        for (int j = 0; j < c; j++) {
        	archivo << '"' ;
        	if( (*(*(punteromatriz+i)+j)) == "***"){
        		archivo<< aux;
			}else{
            archivo  <<(*(*(punteromatriz+i)+j));
			} // Escribe el valor del elemento 
			archivo << '"' ;
            // Verifica si no es el Ãºltimo elemento de la fila
            if (j != c - 1) {
                archivo << ", "; // escribe una coma y espacio para separar los elementos
            }
        }

        archivo << "]"; // Cierre de la fila

        // Verifica si no es la Ãºltima fila
        if (i != f - 1) {
            archivo << ","; // escribe una coma para separar las filas
        }

        archivo << "\n"; 
    }

    archivo << "\t]\n";
    archivo << "}"; // Cierre del objeto JSON

    archivo.close(); // Cierra el archivo
    cout << "La matriz se ha guardado como: " << nombreArchivo << ".json" << endl;
    
    
    
}
