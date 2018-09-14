#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

struct producto{
	int id;
	char nombre[20];
	int cant;
	double costo;
};

void cascaron(char*);
void escribir(char*);
void inventario(char*);
void menor(char*);
void arch_sec(producto *, int);

int main()
{
	char file[20]={"almacen.dat"};
	
	//cascaron(file);
	//escribir(file);
	
	inventario(file);
	
	menor(file);
	
	
	
	return 1;
}

void inventario(char*archivo)
{
	producto registro;
	fstream file;
	double total=0;
	
	file.open(archivo , ios::binary | ios::in | ios::app);
	if(!file)
	  cout<<endl<<"ERROR al abrir el archivo";
	
		while(!file.eof())
		{
				if(registro.cant !=0)
				{
					total=total+(registro.cant*registro.costo);
				}
			file.read((char *)&registro, sizeof(producto));
			
		}
		
		
	file.close();
	
	cout<<endl<<"INVENTARIO TOTAL: "<<total;
}


void menor(char*archivo)
{
	producto aux[5];
	int i=0;
	producto registro;
	fstream file;
	
	file.open(archivo , ios::binary | ios::in | ios::app);
	file.read((char *)&registro, sizeof(producto));

	if(!file)
	  cout<<endl<<"ERROR al abrir el archivo";
	
	file.read((char *)&registro, sizeof(producto));

		while(!file.eof())
		{
				if(registro.id !=0 && registro.cant<5)
				{
						aux[i].id=registro.id;
						strcpy(aux[i].nombre, registro.nombre);
						aux[i].cant=registro.cant;
						aux[i].costo=registro.costo;
						i++;
					
				}   
			file.read((char *)&registro, sizeof(producto));

		}	
	file.close();
	
	arch_sec(aux, i);
	
}

void arch_sec(producto *v, int tam)
{
	fstream file;
	file.open("Menor_5.txt", ios::out| ios::app);
	
	if(!file)
	  cout<<endl<<"Error a abrir el archivo";
	
	else
	{
		for(int i=0; i<tam; i++)
		{
			file << v[i].id <<" "<< v[i].nombre <<" "<< v[i].cant <<" "<< v[i].costo<<endl;
		}
	}
	file.close();
	
	cout<<endl<<endl<<"Se genero archivo secuencial de productos cuya existencia es menor a 5"<<endl<<endl;
	cout<<"registro   nombre  cantidad  costo"<<endl;
	for(int i=0; i<tam; i++)
	{
		cout<< v[i].id <<"        "<< v[i].nombre <<"    "<< v[i].cant <<"       "<< v[i].costo<<endl;
	}
	
}
	

void cascaron(char*archivo)
{
	fstream file;
	
	file.open(archivo, ios::binary | ios::out |ios::app );
	if(!file)
	  cout<<"ERROR";
	else
	{
		producto registro={0, "", 0, 0};
		for(int i=0; i<15; i++)
		{
			file.write( reinterpret_cast<char *> (&registro),sizeof(producto));
		}
	}
	file.close();
}

void escribir(char* archivo)
{
	fstream file;
	producto registro;

	file.open(archivo, ios::binary| ios::out);
	
	if(!file)
	  cout<<"ERROR no se puede ingresar al archivo";
	
	  
	for(int i=0; i<4; i++)
	{
		    cout<<endl<<"Ingresa registro: ";
		    cin>>registro.id;
			cout<<endl<<"Ingresa nombre: ";
			fflush(stdin);
			cin.getline(registro.nombre, 20);
			cout<<endl<<"Cantidad: ";
			cin>>registro.cant;
			cout<<endl<<"Precio: ";
			cin>>registro.costo;
		
		file.seekp((registro.id -1) * sizeof(producto));
		file.write(reinterpret_cast<char*>(&registro),sizeof(producto));
	}
	
	file.close();
}
