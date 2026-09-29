#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std; 
int main(){
	ofstream archivo_salida; 
	ifstream archivo_entrada; 
	double suma; 
	double promedio; 
	int num; 
	int cantidad; 
	
	archivo_salida.open("C:\\Users\\MSI-GAMER\\Downloads\\ARCHIVO EN BLANCO.txt");
	if (archivo_salida.fail()){
		cout << "Error al arbir el archivo"; 
		cout << endl << "Verfique que el archivo exista"; 
		exit(1);
	}
	else {
		archivo_salida << "5\t 96\t 87\t 78\t 93\t 21\t 4\t 92\t 82\t 85\t 87\t 6\t 72\t 69\t 85\t 75\t 81\t 73\t" << endl; 
		cout << "La informacion fue guardada"; 
		archivo_salida.close();
	}
	
	archivo_entrada.open("C:\\Users\\MSI-GAMER\\Downloads\\ARCHIVO EN BLANCO.txt"); 
	if (archivo_entrada.fail()){
		cout << "Error al arbir el archivo"; 
		cout << endl << "Verfique que el archivo exista"; 
		exit(1);
	}
	else{
	
		while(archivo_entrada >> cantidad){ // automaticamente se guarda en la varibale cantidad el cursor se pasa al siguiente elemento
			suma = 0;
			for(int i=1; i<=cantidad; i++){
				archivo_entrada >> num; 
				suma = suma + num; 
			}
			promedio = suma/cantidad;
			cout << endl <<  "Promedio es igual: " << promedio << endl; 
		}
		archivo_entrada.close(); 
	}
	
	return 0;
}







