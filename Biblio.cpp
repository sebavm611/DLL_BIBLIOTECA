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

nodo* esExistente(int id){
	nodo *aux = inicio;
	while(aux!=NULL || aux->dato->libro_id!=id){
		aux = aux->sig;
	}
	
	if(aux->dato->libro_id==id){
		return aux;
	}
	return NULL;
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

int main(){
	
	
}





