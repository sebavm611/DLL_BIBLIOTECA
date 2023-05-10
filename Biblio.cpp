//BIBLIOTECA ACTUALIZADA
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef char texto[75];
#define tamanio 4000


//Definicion de la estructura a usar
struct libro{
	int libro_id;
	char ISBN[13];
	texto autor;
	texto nombre;
	texto genero;
};

//Validacion de un numero ingresado con un lim. inferior y uno superior
int validarNum(string s,int min,int max){
	int num;
	cout<<s;
	cin>>num;
	while((num<min)or(num>max)){
		cout<<"ERROR! Ingrese un numero entre "<<min<<" y "<<max<<": ";
		cin>>num;
	}
	return num;
}

//Impresion y lectura de la opcion de un menu
int fnMenuPrincipal(){
	cout<<"1. INSERTAR DATOS "<<endl;
	cout<<"2. MODIFICAR DATOS "<<endl;
	cout<<"3. ELIMINAR DATOS "<<endl;
	cout<<"4. CONSULTAR DATOS "<<endl;
	cout<<"5. REPORTE DE DATOS "<<endl;
	cout<<"6. SALIR DEL PROGRAMA "<<endl;
	return validarNum("Digite una opcion: ",1,7);
}

//Impresion y lectura de las opciones de insercion de datos
int fnMenuInsercion(){
	cout<<"1. INSERTAR DATOS MANUALMENTE"<<endl;
	cout<<"2. INSERTAR DATOS DE MANERA ALEATORIA"<<endl;
	return validarNum("Digite una opcion: ",1,2);
}

//Impresion y lectura de las opciones de consultar
int fnMenuConsultar(){
	cout<<"1. BUSQUEDA LINEAL"<<endl;
	cout<<"2. BUSQUEDA BINARIA"<<endl;
	return validarNum("Digite una opcion: ",1,2);
}

//Impresion y lectura de las opciones de reporte
int fnMenuReportar(){
	cout<<"1. ORDENAMIENTO BURBUJA"<<endl;
	cout<<"2. ORDENAMIENTO QUICKSORT"<<endl;
	return validarNum("Digite una opcion: ",1,2);
}

//Valida la existencia del libro con ese codigo e ISBNB
int esExistente(int id,char ISBN[],libro biblio[],int n){
	int i;
	for(i=0;i<n;i++){
		if((biblio[i].libro_id==id)||(strcmp(ISBN,biblio[i].ISBN)==0)){
			return i;
		}
	}
	return -1;
}


//Ingreso manual de los datos de la estructura
void crearLibro(libro *biblio,int *n){
	int id;
	char ISBN[13];
	texto autor;
	texto nombre;
	texto genero;
	
	
	cout<<"Ingrese el id del libro: ";
	cin>>id;
	while(esExistente(id,"0",biblio,*n)>=0){
		cout<<"ERROR! Id ya existente, ingrese nuevamente: ";
		cin>>id;
	}
	
	cin.ignore();
	cout<<"Ingrese el ISBN del libro: ";
	gets(ISBN);
	while(esExistente(id,ISBN,biblio,*n)>=0){
		cout<<"ERROR! ISBN ya existente, ingrese nuevamente: ";
		gets(ISBN);
	}
	
	cout<<"Ingrese el autor del libro: ";
	gets(autor);
	
	cout<<"Ingrese el nombre del libro: ";
	gets(nombre);
	
	cout<<"Ingrese el genero del libro: ";
	gets(genero);
	
	biblio[*n].libro_id = id;
	strcpy(biblio[*n].ISBN,ISBN);
	strcpy(biblio[*n].autor,autor);
	strcpy(biblio[*n].nombre,nombre);
	strcpy(biblio[*n].genero,genero);
	
	*n = *n+1;
}

//Ingreso aleatorio de los datos de la estructura
void crearLibroAleatorio(libro *biblio,int *n){
	srand(clock());
	int id;
	char ISBN[13];
	unsigned long semilla = rand();
	texto autor;
	texto nombre;
	texto genero;
	
	
	do{
		semilla = ((17 * semilla + 152)*(semilla+semilla+2)+((clock()+16)*124))%999999999;
		id = semilla % 20000 ; 
	}while(esExistente(id,"0",biblio,*n)>=0);
	
	do{
		semilla = ((17 * semilla + 152)*(semilla+semilla+2)+((clock()+16)*124))%999999999;
		strcpy(ISBN,to_string(semilla).c_str());
	}while(esExistente(id,ISBN,biblio,*n)>=0);
	
	
	semilla = ((17 * semilla + 152)*(semilla+semilla+2)+((clock()+16)*124))%999999999;
	strcpy(autor,to_string(semilla).c_str());
	
	
	semilla = ((17 * semilla + 152)*(semilla+semilla+2)+((clock()+16)*124))%999999999;
	strcpy(nombre,to_string(semilla).c_str());
	
	semilla = ((17 * semilla + 152)*(semilla+semilla+2)+((clock()+16)*124))%999999999;
	strcpy(genero,to_string(semilla).c_str());
	
	biblio[*n].libro_id = id;
	strcpy(biblio[*n].ISBN,ISBN);
	strcpy(biblio[*n].autor,autor);
	strcpy(biblio[*n].nombre,nombre);
	strcpy(biblio[*n].genero,genero);
	
	*n = *n+1;
}

//Modificacion de los datos del libro en base al id
bool actualizarLibro(libro *biblio,int n){
	int cod,i,j=0;
	bool existencia = false;
	char ISBN[13];
	texto autor;
	texto nombre;
	texto genero;
	int pos;
	
	cout<<"Ingrese el codigo del libro a actualizar: ";
	cin>>cod;
	
	pos = esExistente(cod,"0",biblio,n);
	if(pos<0){
		return false;
	}
	
	
	cin.ignore();
	cout<<"Ingrese el ISBN actualizado del libro: ";
	gets(ISBN);
	while((esExistente(0,ISBN,biblio,n)>=0)&&((esExistente(0,ISBN,biblio,n)!=pos))){
		cout<<"ERROR! ISBN ya existente, ingrese nuevamente: ";
		gets(ISBN);
	}
	
	cout<<"Ingrese el autor actualizado del libro: ";
	gets(autor);
	
	cout<<"Ingrese el nombre actualizado del libro: ";
	gets(nombre);
	
	cout<<"Ingrese el genero actualizado del libro: ";
	gets(genero);
	
	
	strcpy(biblio[pos].ISBN,ISBN);
	strcpy(biblio[pos].autor,autor);
	strcpy(biblio[pos].nombre,nombre);
	strcpy(biblio[pos].genero,genero);		
	
	return true;
}

//Impresion de todos los libros no ordenada
void imprimirLibro(libro biblio[],int n){
	libro l = biblio[n];
	
	cout<<"Id del libro: ";
	cout<<l.libro_id<<endl;
	
	cout<<"ISBN del libro: ";
	cout<<l.ISBN<<endl;
	
	cout<<"Autor del libro: ";
	cout<<l.autor<<endl;
	
	cout<<"Nombre del libro: ";
	cout<<l.nombre<<endl;
	
	cout<<"Genero del libro: ";
	cout<<l.genero<<endl;
	
}

void imprimirLibros(libro biblio[],int n){
	int i;
	for(i=0;i<n;i++){
		cout<<"---LIBRO #"<<i+1<<"---"<<endl;
		imprimirLibro(biblio,i);
	}
}

//Eliminacion de un libro en base al id
bool eliminarLibro(libro *biblio,int *n){
	int cod,i,j=0;
	int pos;
	
	cout<<"Ingrese el codigo del libro a eliminar: ";
	cin>>cod;
	
	pos = esExistente(cod,"0",biblio,*n);
	if(pos<0){
		return false;
	}
	
	for(i=pos;i<*n-1;i++){
		biblio[i] = biblio[i+1];
	}
	
	*n = *n - 1;
	return true;
}

//Busqueda lineal del libro
bool buscarLibro(libro *biblio,int n){
	int cod,pos;
	cout<<"Ingrese el codigo del libro a buscar: ";
	cin>>cod;
	
	pos = esExistente(cod,"0",biblio,n);
	if(pos<0){
		return false;
	}
	cout<<"LIBRO #"<<pos+1<<endl;
	imprimirLibro(biblio,pos);
	return true;
}


//Ordenamiento por burbuja
void prOrdenamientoBurbuja(libro *biblio2,int n){
	int aux;
    for (int i=0;i<n-1;i++) {
        for (int j=0; j<n-i-1;j++) {
            if (biblio2[j].libro_id>biblio2[j+1].libro_id) {
                aux = biblio2[j].libro_id;
                biblio2[j].libro_id = biblio2[j+1].libro_id;
                biblio2[j+1].libro_id = aux;
            }
        }
    }
}

//Busqueda binaria del libro
int busquedaBinaria(libro* biblio,int bajo,int alto,int cod){
	if (alto >= bajo) {
        int medio = bajo + (alto - bajo) / 2;
        if (biblio[medio].libro_id == cod) {
            return medio;
        } else if (biblio[medio].libro_id > cod) {
            return busquedaBinaria(biblio, bajo, medio - 1, cod);
        } else {
            return busquedaBinaria(biblio, medio + 1, alto, cod);
        }
    }
    return -1;
}

//Copiar arreglo
void copiarArreglo(libro *biblio,libro *biblio2,int n){
	int i;
  	for(i=0;i<n;i++){
		biblio2[i] = biblio[i];
	}
}

//Ordenamiento recursivo por QuickSort
void quickSort(libro *biblio2, int bajo, int alto) {
  	
  	if (bajo < alto) {
	    int pivote = biblio2[alto].libro_id;
	    
	    int i = bajo - 1;
	    for (int j = bajo; j <= alto - 1; j++) {
	      if (biblio2[j].libro_id < pivote) {
	        i++;
	        int temp = biblio2[i].libro_id;
	        biblio2[i].libro_id = biblio2[j].libro_id;
	        biblio2[j].libro_id = temp;
	      }
	    }
	    int temp = biblio2[i + 1].libro_id;
	    biblio2[i + 1].libro_id = biblio2[alto].libro_id;
	    biblio2[alto].libro_id = temp;
	
	    quickSort(biblio2, bajo, i);
	    quickSort(biblio2, i + 2, alto);
	}
  	
}

int main(){
	int opcion,opcion1,cantDatos,i;
	libro biblio[tamanio];
	libro biblio2[tamanio];
	int pos_actual = 0;
	
	do{
		opcion = fnMenuPrincipal();
		system("cls");
		
		switch(opcion){
			case 1:
				//cout<<"Ha seleccionado la opcion 1"<<endl;
				opcion1 = fnMenuInsercion();
				cantDatos = validarNum("Seleccione la cantidad de datos que desea crear: ",1,tamanio);
				if(opcion1==1){
					for(i=0;i<cantDatos;i++){
						cout<<"LIBRO #"<<pos_actual+1<<endl;
						crearLibro(biblio,&pos_actual);
						system("cls");
					}
				}
				else{
					for(i=0;i<cantDatos;i++){
						cout<<"LIBRO #"<<pos_actual+1<<" CREADO"<<endl;
						crearLibroAleatorio(biblio,&pos_actual);
						//system("cls");
					}
				}
				system("pause");
				system("cls");
				break;
			case 2:
				//cout<<"Ha seleccionado la opcion 2"<<endl;
				if(actualizarLibro(biblio,pos_actual)){
					cout<<"LIBRO ACTUALIZADO CORRECTAMENTE"<<endl;
				}else{
					cout<<"LIBRO NO ENCONTRADO, INTENTE DE NUEVO"<<endl;
				}
				system("pause");
				system("cls");
				break;
			case 3:
				//cout<<"Ha seleccionado la opcion 3"<<endl;
				if(eliminarLibro(biblio,&pos_actual)){
					cout<<"LIBRO ELIMINADO CORRECTAMENTE"<<endl;
				}else{
					cout<<"LIBRO NO ENCONTRADO, INTENTE DE NUEVO"<<endl;
				}
				system("pause");
				system("cls");
				break;
			case 4:
				//cout<<"Ha seleccionado la opcion 4"<<endl;
				opcion1 = fnMenuConsultar();
				if(opcion1==1){
					auto inicio = high_resolution_clock::now();
					if(!buscarLibro(biblio,pos_actual)){
						cout<<"LIBRO NO ENCONTRADO, INTENTE DE NUEVO"<<endl;
					}
					auto parada = high_resolution_clock::now();
					auto duracion = duration_cast<microseconds>(parada - inicio);
					cout << "Tiempo transcurrido: " << duracion.count() << " microsegundos" << endl;
				}
				else{
					int cod = validarNum("Ingrese el codigo a buscar: ",0,20000);
					copiarArreglo(biblio,biblio2,pos_actual);
					prOrdenamientoBurbuja(biblio2,pos_actual);
					auto inicio = high_resolution_clock::now();
					int n = busquedaBinaria(biblio2,0,pos_actual-1,cod);
					auto parada = high_resolution_clock::now();
					auto duracion = duration_cast<microseconds>(parada - inicio);
					if(n<0){
						cout<<"LIBRO NO ENCONTRADO, INTENTE DE NUEVO"<<endl;
					}else{
						cout<<"LIBRO #"<<n+1<<endl;
						imprimirLibro(biblio2,n);
					}
					cout << "Tiempo transcurrido: " << duracion.count() << " microsegundos" << endl;		
				}
				system("pause");
				system("cls");
				break;
			case 5: 	
				opcion1 = fnMenuReportar();
				if(opcion1==1){
					copiarArreglo(biblio,biblio2,pos_actual);
					auto inicio = high_resolution_clock::now();
					prOrdenamientoBurbuja(biblio2,pos_actual);
					auto parada = high_resolution_clock::now();
  					auto duracion = duration_cast<microseconds>(parada - inicio);
					imprimirLibros(biblio2,pos_actual);
					cout << "Tiempo transcurrido: " << duracion.count() << " microsegundos" << endl;
				}else{
					copiarArreglo(biblio,biblio2,pos_actual);
					auto inicio = high_resolution_clock::now();
					quickSort(biblio2,0,pos_actual-1);
					auto parada = high_resolution_clock::now();
  					auto duracion = duration_cast<microseconds>(parada - inicio);
  					imprimirLibros(biblio2,pos_actual);
  					cout << "Tiempo transcurrido: " << duracion.count() << " microsegundos" << endl;
				}
				
				system("pause");
				system("cls");
				break;
			default:
				cout<<"GRACIAS ;)"<<endl;
				break;
		}
		
	}while(opcion!=6);
	
}

