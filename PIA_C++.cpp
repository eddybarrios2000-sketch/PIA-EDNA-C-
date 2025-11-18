#include<iostream>
#include<regex>
#include <cstring>


using namespace std;

void registro_destinos(FILE*);
void registro_viajes(FILE*, FILE*);


main()
{
	char opc, descripcion[200], precio[20];
	bool flag=false;
	FILE*ptr_viajes,*ptr_destinos;
	char clave[50];
	
	do
	{
		do
		{
			cout << "----MENU----\n"
			<< "a) REGISTRO DE VUELOS\n"
			<< "b) LISTADO DE DESTINOS\n"
			<< "c) LISTADO DE VUELOS \n"
			<< "d) SALIR" << endl;
			
			cin >> ws;
			cin >> opc;	
			
		}while(false);
		
		switch(opc)
		{
			case 'a':
				cout << "----Registros de vuelo----" << endl;
				if((ptr_destinos = fopen("destinos.txt", "r+"))==NULL)
				{
					cout << "ERROR archivo de destinos no existe. Creando, favor de ingresar datos"<<endl;
					ptr_destinos = fopen("destinos.txt", "w+");
					registro_destinos(ptr_destinos);
					
					if(ptr_destinos == NULL)
						cout << "ERROR creacion del archivo ha fallado...." << endl;					
				}
				else 
				{
					if(fscanf(ptr_destinos, "%[^|]|%[^|]|%[^|]|", clave, descripcion, precio) == EOF)
					{
						cout << "Archivo vacio, favor de ingresar datos..."<<endl;
						registro_destinos(ptr_destinos);
					}	
				}
				ptr_viajes = fopen("viajes.txt", "a+");
				if(ptr_viajes == NULL)
					cout <<"ERROR archvio existente pero no se pudo acceder a el"<<endl;
				else
				{
					registro_viajes(ptr_viajes, ptr_destinos);
					fclose(ptr_viajes);
					fclose(ptr_destinos);
				}
				
				
				
				
		}
	}while(opc != 'd' || opc != 'D');
	
	
}

void registro_destinos(FILE*destinostxt)
{
	char clave[50], descripcion[200], precio[20], ans;
	
	regex validacion_clave("^[A-Z]\\_\\d{4}$");
	regex validacion_descripcion("^[A-Z]{1}[A-Za-z\\s]+$");
	regex validacion_precio("^\\d{3,5}\\.\\d{2}$");
	
	do
	{
		do
		{
			cout << "Ingrese la clave del destino:"<< endl;
			cin >> ws;
			cin.getline(clave, 50);
			
			if(regex_match(clave, validacion_clave))
				cout << "Registrado con exito"<<endl;
			else 
				cout << "Formato equivocado, ingrese nuevamente" << endl;
				
		}while(!regex_match(clave, validacion_clave));
		
		do
		{
			cout << "Ingrese la descripcion del destino:"<< endl;
			cin >> ws;
			cin.getline(descripcion, 200);
			
			if(regex_match(descripcion, validacion_descripcion))
				cout << "Registrado con exito"<<endl;
			else 
				cout << "Formato equivocado, ingrese nuevamente" << endl;
				
		}while(!regex_match(descripcion, validacion_descripcion));
		
		do
		{
			cout << "Ingrese el precio del destino:"<< endl;
			cin >> ws;
			cin.getline(precio, 20);
			
			if(regex_match(precio, validacion_precio))
				cout << "Registrado con exito"<<endl;
			else 
				cout << "Formato equivocado, ingrese nuevamente" << endl;
				
		}while(!regex_match(precio, validacion_precio));
		
		fprintf(destinostxt,"%s|%s|%s|", clave, descripcion, precio);
		
		cout << "desea agregar otro destino? (s/n) "<<endl;
		cin >> ans;
	
	}while(ans != 'n');
	
	cout << "saliendo..." << endl;	
}

void registro_viajes(FILE*viajestxt, FILE*destinostxt)
{
	char nombre_destino[200], viajeRedondo[5], fecha[20], fecha_regreso[20], ans[2];
	char clave[50], descripcion[200], precio[20], preciotxt[20];
	float precio_doble;
	bool flag=true, booleano_viaje=false;
	
	regex validacion_nombre("^[A-Z]{1}[A-Za-z\\s]+$");
	regex validacion_sino("^(si|no|SI|NO|Si|No)$");
	regex validacion_fecha("(0[1-9]|[1-2]\\d|3[0-1])-(0[1-9]|1[0-2])-(000[1-9]|00[1-9]\\d|0[1-9]\\d{2}|[1-9]\\d{3})");
	
	do
	{	do
		{
			do
			{
				cout << "Ingrese el nombre del destino:"<< endl;
				cin >> ws;
				cin.getline(nombre_destino, 200);
				
				if(!regex_match(nombre_destino, validacion_nombre))
					cout << "formato equivocado, ingrese de nuevo"<<endl;
				
			}while(!regex_match(nombre_destino, validacion_nombre));
			
			rewind(destinostxt);
			while(!feof(destinostxt))
			{
				fscanf(destinostxt,"%[^|]|%[^|]|%[^|]|", clave, descripcion, preciotxt);
				if(strcmp(descripcion, nombre_destino) == 0)
				{
					strcpy(precio, preciotxt);
					flag = false;
				}
			}
				
			if(flag)
				cout << "ERROR, no existen destinos a esa zona ingrese otra"<<endl;
			else
			{
				cout << "Destino existente\n" << "tiene un precio de: " << precio <<endl;
			}
				
		}while(flag);
		
		do
		{
			cout << "El viaje sera redondo? (si/no)" << endl;
			cin >> ws;
			cin.getline(viajeRedondo, 5);
			
			if(!regex_match(viajeRedondo, validacion_sino))
				cout << "ingrese si o no, sea mayusculas o minusculas" << endl;
			 
		}while(!regex_match(viajeRedondo, validacion_sino));
		
		if(strcmp(viajeRedondo, "si") == 0 || strcmp(viajeRedondo, "SI") == 0)
		{
			booleano_viaje = true;
			precio_doble = atof(precio); 
			precio_doble = precio_doble*2;
			cout << "el precio en total de ida y vuelta seria de: " << precio_doble << endl;
		}
		
		do
		{
			cout << "ingresa la fecha del viaje" << endl;
			cin >> ws;
			cin.getline(fecha, 20);
			
			if(!regex_match(fecha,validacion_fecha))
				cout << "ingrese nuevamente la fecha con el formato establecido" << endl;
			
		}while(!regex_match(fecha,validacion_fecha));
		
		if(booleano_viaje)
		{
			do
			{
				cout << "--viaje redondo--" << endl;
				cout << "ingresa la fecha de regreso: " << endl;
				cin >> ws;
				cin.getline(fecha_regreso, 20);
				
				if(!regex_match(fecha_regreso,validacion_fecha))
					cout << "ingrese nuevamente la fecha con el formato establecido" << endl;
						
			}while(!regex_match(fecha_regreso,validacion_fecha));
		}
		
		if(booleano_viaje)
			fprintf(viajestxt, "%s|%s|%s|",nombre_destino, fecha,fecha_regreso);
		else 
			fprintf(viajestxt, "%s|%s|",nombre_destino, fecha);
		
		do
		{
			cout << "desea agregar otro registro? (si/no) "<<endl;
			cin >> ws;
			cin >> ans;
			if(!regex_match(ans, validacion_sino))
				cout << "ingrese solo si o no, mayusculas o minusculas"<<endl;
			
		}while(!regex_match(ans, validacion_sino));
	
	}while(strcmp(ans, "no") != 0 && strcmp(ans, "No") != 0);

	cout << "saliendo..." << endl;	
	
}






