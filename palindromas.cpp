//LIBRERIAS A INCLUIR
#include<iostream>
using namespace std;
//DEFINICIONES
struct Elemento{
    char c;
    Elemento* puntero;
};

//PROTOTIPOS
Elemento* crear(char caracter);
Elemento* pop(Elemento** top);
char* pedir_palabra();
void palindroma(Elemento* top);
void push(Elemento** top,char caracter);

int main(){
    Elemento* top=NULL;
    string opcion="";
    do{
        palindroma(top);
        cout<<"QUIERES VOLVER A VERIFICAR UNA PALABRA? (si-no) "<<endl;
        cin>>opcion;
    }while(opcion=="si");
    return 0;
}

//FUNCIONES
Elemento* crear(char caracter){
    Elemento* nuevo_elemento=new Elemento();
    nuevo_elemento->c=caracter;
    return nuevo_elemento;
} 

void push(Elemento** top,char caracter){

    Elemento* nuevo_elemento=crear(caracter);

    if(*top==NULL){
        *top=nuevo_elemento;
        nuevo_elemento->puntero=NULL;
    }
    else{
        nuevo_elemento->puntero=*top;
        *top=nuevo_elemento;
    }
}

Elemento* pop(Elemento** top){
    if(*top==NULL){
        cout<<"PILA VACIA"<<endl;
    }
    else{
        Elemento* aux=*top;
        *top=aux->puntero;
        return aux;
    }
}

void palindroma(Elemento* top){
    char* palabra=pedir_palabra();
    char* volteado=new char[64];
    int i=0,j=0;
    while(palabra[i]!='\0'){
        push(&top,palabra[i]);
        i++;
    }
    Elemento* aux;
    while(top!=NULL){
    	aux=pop(&top);
        volteado[j]=aux->c;
        j++;
    }

    if(*palabra==*volteado)
        cout<<"LA PALABRA ES PALINDROMA c: "<<endl;
    else
    	cout<<"LA PALABRA NO ES PALINDROMA :C "<<endl;  
}

char* pedir_palabra(){
    char* palabra=new char[64];
    cout<<"DIGITA UNA PALABRA: "<<endl;
    cin>>palabra;
    return palabra;
}
