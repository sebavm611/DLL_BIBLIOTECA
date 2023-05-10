//CRUD DE UNA BIBLIOTECA UTILIZANDO UNA DLL
#include<iostream>
#include<cstdlib>
using namespace std;

struct libro{
	int libro_id;
	char autor[50];
	char nombre[50];
};

struct nodo{
	libro *dato;
	nodo *ant;
	nodo *sig;
};

nodo *inicio = NULL;
nodo *final = NULL;

bool esExistente(int id){
	if(inicio==NULL){
		return false;
	}
	
	nodo *aux = inicio;
	while((aux!=NULL) && (aux->dato->libro_id!=id)){
		aux = aux->sig;
	}
	
	if(aux==NULL){
		return false;
	}
	return true;
}

void crearLibro(libro *l){
	int id;
	char autor[50];
	char nombre[50];
	
	
	cout<<"Ingrese el id del libro: ";
	cin>>id;
	while(esExistente(id)){
		cout<<"ERROR! Id ya existente, ingrese nuevamente: ";
		cin>>id;
	}
	
	cin.ignore();
	
	cout<<"Ingrese el autor del libro: ";
	gets(autor);
	
	cout<<"Ingrese el nombre del libro: ";
	gets(nombre);
	
	l->libro_id = id;
	strcpy(l->autor,autor);
	strcpy(l->nombre,nombre);
}

void ingresarInicio(){
	nodo *nuevo = (nodo*) malloc(sizeof(nodo));
	nuevo->dato = (libro*) malloc(sizeof(libro));
	crearLibro(nuevo->dato);
	if(inicio==NULL){
		inicio = nuevo;
		inicio->ant = NULL;
		inicio->sig = NULL;
		final = inicio;
	}else{
		nuevo->ant = NULL;
		nuevo->sig = inicio;
		inicio->ant=nuevo;
		inicio=nuevo;
	}
	
}

void ingresarFinal(){
	nodo *nuevo = (nodo*) malloc(sizeof(nodo));
	nuevo->dato = (libro*) malloc(sizeof(libro));
	crearLibro(nuevo->dato);
	if(inicio==NULL){
		inicio = nuevo;
		inicio->ant = NULL;
		inicio->sig = NULL;
		final = inicio;
	}else{
		nuevo->ant = final;
		nuevo->sig = NULL;
		final->sig=nuevo;
		final=nuevo;
	}
}

void imprimirLibro(libro *l){
	cout<<"Id del libro: ";
	cout<<l->libro_id<<endl;
	
	cout<<"Autor del libro: ";
	cout<<l->autor<<endl;
	
	cout<<"Nombre del libro: ";
	cout<<l->nombre<<endl;
}

void imprimirInicio(){
	nodo *aux = inicio;
	while(aux!=NULL){
		imprimirLibro(aux->dato);
		aux = aux->sig;
	}
	cout<<"\n";
}

void imprimirFinal(){
	nodo *aux = final;
	while(aux!=NULL){
		imprimirLibro(aux->dato);
		aux = aux->ant;
	}
	cout<<"\n";
}

int main(){
	ingresarInicio();
	ingresarInicio();
	imprimirInicio();
	
}



