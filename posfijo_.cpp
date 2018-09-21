
/*SI TRATAS DE LEER ESTE CODIGO LO MAS PROBABLE ES QUE MUERAS
PERO SI AUN ASI QUEIERES INTENTARLO SOLO TE PUEDO DECIR
"QUE LA FUERZA TE ESTE CONTIGO */
//PD: EL PROGRAMA FUNCIONA A MEDIAS :( 

    
//LIBRERIAS A INCLUIR
#include<iostream>
using namespace std;

//DEFINICIONES
struct Elemento{
    char c;
    Elemento* puntero;
};


//prototipos
void push(Elemento** ,char );
Elemento* pop(Elemento** );
Elemento* crear(char );
int jerarquia(char );
void conversor(Elemento*,Elemento**,char*);
bool es_numero(char );
char* pedir_expresion();
int operacion(char ,char,char);
//funcion principal main
int main(){
    Elemento* top=NULL;
    Elemento* posfija=NULL;
    conversor(top,&posfija,pedir_expresion());
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

int jerarquia(char operador){
    
    switch(operador){
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
        	return 0;
    }
}
char* pedir_expresion(){
	char* infija=new char[64];
	cout<<"INGRESA UNA EXPRESION EN NOTACION INFIJA: "<<endl;
	cin>>infija;
	return infija;
}

void conversor(Elemento* top,Elemento** posfija,char* infija){
	int i=0;
    Elemento* aux;
    while(infija[i]!='\0'){
    	
        if(es_numero(*(infija+i))==true){
            push(posfija,infija[i]);
        }
        else{
            if(top==NULL || top->c== '('){
                push(&top,infija[i]);
            }
            else{
                if( infija[i]=='('){
                    push(&top,infija[i]);
                }
                else{
                    if( infija[i]==')' ){
                        while( top->c=='(' ){
                            aux=pop(&top);
                            push(posfija,aux->c);
                        }
                        aux=pop(&top);
                        push(posfija,aux->c);
                    }
                    else{
                        if(top!=NULL && jerarquia(top->c)>jerarquia(infija[i])){
                            while(jerarquia(top->c)>jerarquia(infija[i])){
                                aux=pop(&top);
                                push(posfija,aux->c);
                            }
                            push(&top,infija[i]);
                        }
                        else{
                            push(&top,infija[i]);
                        }
                    }
                }
            }
        } 
        i++;
    }

    while(top!=NULL){
    	aux=pop(&top);
    	push(posfija,aux->c);
	}
    char expresion[64];
    i=0;
    
    while(*posfija!=NULL){
    	aux=pop(posfija);
    	push(&top,aux->c);	
	}
	
    while(top->puntero!=NULL){
    	aux=pop(&top);
    	if(aux->c!='('){
    		if(aux->c!=')')
    		{
    			expresion[i]=aux->c;	
			}	
		} 		
    	i++;
	}
	cout<<expresion<<endl;
	Elemento* aux2;
	while(expresion[i]!='\0'){
		if(es_numero(expresion[i])==true){
			push(&top,expresion[i]);
		}else{
			aux=pop(&top);
			aux2=pop(&top);
			push(&top,(operacion(expresion[i],aux->c,aux2->c)-'0'));
		}
		i++;
	}
	aux=pop(&top);
	//cout<<aux->c<<endl;
	
}

bool es_numero(char caracter){
	if(caracter=='0' || caracter=='1' || caracter=='2' || caracter=='3' || caracter=='4' || caracter=='5' || caracter=='6' || caracter=='7' || caracter=='8' || caracter=='9' )
    	return true;
    return false;
}

int operacion(char operador,char operando1,char operando2){
	
	switch(operador){
		case '+':
			return (operando1-'0')+(operando2-'0');
		case '-':
			return (operando1-'0')-(operando2-'0');
		case '*':
			return (operando1-'0')*(operando2-'0');
		case '/':
			return (operando1-'0')/(operando2-'0');
		default:
			return 0;	
	}
}
