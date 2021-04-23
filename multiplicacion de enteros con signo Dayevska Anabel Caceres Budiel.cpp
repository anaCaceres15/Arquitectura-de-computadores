#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <math.h>

using namespace std;
//Dayevska AnabelCaceres Budiel
//CCOMP 3-1

int  const n= 8;

void print_lis(int lis[n]){
	for(int i=0; i<n; i++){
		cout <<lis[i];
	}
}
void suma(int A[n], int M[n]){ // A= A+M
	int rpta, acarreo=0;
	for (int i=n-1; i>=0; i--){
		rpta = A[i]+M[i]+acarreo;
		if (rpta==0) {acarreo =0; rpta = 0;}
		if (rpta==1) {acarreo =0; rpta = 1;}
		if (rpta==2) {acarreo =1; rpta = 0;}
		if (rpta==3) {acarreo =1; rpta = 1;}
		A[i]= rpta;		
	}
}
void cambio_signo(int M[n], int auxM[n] ){//uso auxM para no modificar a M ya que lo usare en el multiplicando
	//invierto M 
	for (int j=0; j<n; j++){
		if (M[j]==0) { auxM[j]=1;}
		else {auxM[j]=0;}
	}
	int  uno[n]={0,0,0,0,0,0,0,1};
	suma(auxM,uno); //M = M+1  
}
void resta(int A[n], int M[n]){ // A= A-M
    int auxM[n];
    cambio_signo(M,auxM);
	suma(A,auxM);
}

void multiplicar(int A[n], int M[n], int Q1, int  Q[n]){
	int copy_n= n;
	while (copy_n>0){
	//solo hay 4 posibles casos
		if ( Q[n-1]== 1 and Q1== 0){ //10
			resta(A,M); //A = A-M
		}	
		else if ( Q[n-1]== 0 and Q1== 1){//01
	    	suma(A,M); //A = A+M
		}	
	//si no es ningun de los 2 anteriores significa que 11 o 00, entonces se hace el , corrimiento aritmetico a la derecha (SRA).
		Q1= Q[n-1];
	//recorro Q
		for (int i=n-1; i>0; i--){
	    	Q[i]=Q[i-1];
		}
		Q[0]=A[n-1];
	//recorro A "aritmetic shift"
		for (int i=n-1; i>0; i--){
		    A[i]=A[i-1];
		}
		A[0]=A[1];
		copy_n--;
	}
	//la respuesta queda en A y en Q
}

int bit_num(int bit[n]){//convierte de bit a num
    int  rpta, index=0;
	for (int i=n-1; i>0; i--){
		rpta += (bit[i] * pow(2,index));
		index++;
	}
	if (bit[0]==1) {rpta -= (bit[0] * pow(2,n-1)); }
	return rpta;
}
void num_bit_posi(int num, int bit[n]){//la rpta esta en bit
	int index= n-1;
    while (num != 0){
    	if (num%2 == 0){ bit[index]=0;	}
    	else{ bit[index]= 1;  }
        num /= 2;
        index--; 
    }
    if (index != 0){ 
        for (int i=0; i<=index;i++){
        	bit[i]=0;
		}
	}
}
void num_bit_nega(int num, int bit[n] ){//la rpta esta en bit
	int aux = -num;
	num_bit_posi(aux,bit);
	cambio_signo(bit,bit);
}

void recibir_bit(int M[n], string palabra){
	string str,aux ;
	int num;
	cout<<"ingrese un bit "<<palabra<<": "; cin >> str;
	for (int i=0; i<n; i++){
		aux= str[i];
	    istringstream entrada(aux);
	    entrada >> num;
	    M[i]=num;
	}
}
void recibir_num(int bit[n], string palabra){
	int num, auxN1[n];
	cout<<"ingrese un numero "<<palabra<<": "; cin >> num;
	if (num<0){ num_bit_nega(num,bit); }
	else{ num_bit_posi(num,bit); }
}

int main(){
		
	int  Q1=0; //Q multiplicador , M multiplicando y A empieza llena de 0
	int A[n], Q[n]={1,1,1,1,1,1,0,1},  M[n]={0,0,0,0,0,1,0,1};  
	char opcion;
	
	for (int i=0; i<n; i++){ A[i]= 0; } 
	
	
	cout << "Desea ingresar numeros(a) si desea ingresar bits(b): ";cin >>opcion;
	if (opcion=='a'){
		recibir_num(Q, "multiplicador");
		recibir_num(M, "multiplicando");
	}
	else{//por defecto ingresara en bits si es que la entrad es dif a 'a'
		recibir_bit(Q, "multiplicador");  // 11111101
	    recibir_bit(M, "multiplicando");  // 00000101	
	}
	
    cout<<"num Q: "<< bit_num(Q)  <<" bit Q: ";  print_lis(Q);cout <<endl;
    cout<<"num M: "<<  bit_num(M) <<" bit M: ";  print_lis(M);cout <<endl;
    cout<<"num A: "<<  bit_num(A) <<" bit A: ";  print_lis(A);cout <<endl;
	
    multiplicar (A,M,Q1,Q);
	cout <<"M * Q = "; print_lis(A); print_lis(Q); cout <<endl;
    return 0;
}
