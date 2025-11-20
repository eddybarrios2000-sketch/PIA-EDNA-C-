#include<iostream>
#include<regex>
#include<cstring>
#include<iomanip>


using namespace std;

void registro_destinos(FILE*);
void registro_viajes(FILE*, FILE*);
void listado_destinos(FILE*);
void listado_vuelos(FILE*, FILE*);


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
				if((ptr_destinos = fopen("destinos.txt", "r+"))==NULL)
				{
					cout << "ERROR archivo de destinos no existe. Creando, favor de ingresar datos"<<endl;
					ptr_destinos = fopen("destinos.txt", "w+");
					registro_destinos(ptr_destinos);
					fclose(ptr_destinos);
					
					if(ptr_destinos == NULL)
						cout << "ERROR creacion del archivo ha fallado...." << endl;					
				}
				else 
				{
					if(fscanf(ptr_destinos, "%[^|]|%[^|]|%[^|]|", clave, descripcion, precio) == EOF)
					{
						cout << "Archivo de destinos vacio, favor de ingresar datos..."<<endl;
						registro_destinos(ptr_destinos);
						fclose(ptr_destinos);
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
				break;
			case 'b':
				ptr_destinos = fopen("destinos.txt", "r+");
				if(ptr_destinos == NULL)
					cout <<"ERROR archvio existente pero no se pudo acceder a el"<<endl;
				else
				{
					listado_destinos(ptr_destinos);
					fclose(ptr_destinos);
				}
				break;
			case 'c':
				ptr_viajes = fopen("viajes.txt", "r+");
				if(ptr_viajes == NULL)
					cout <<"ERROR archvio existente pero no se pudo acceder a el"<<endl;
				else
				{
					if((ptr_destinos = fopen("destinos.txt", "r+"))==NULL)
						cout << "Error al abrir arcivo"<<endl;
					else
					{
						listado_vuelos(ptr_viajes, ptr_destinos);
						fclose(ptr_viajes);
						fclose(ptr_destinos);
					}
				}
				break;
			case 'd':
				cout << "saliendo..... (PIA)" << endl;
				break;				
				
		}
	}while(opc != 'd' && opc != 'D');
	
	
}

void registro_destinos(FILE*destinostxt)
{
	char clave[50], descripcion[200], precio[20], ans;
	
	regex validacion_clave("^[A-Z]\\_\\d{4}$");
	regex validacion_descripcion("^[A-Z]{1}[A-Za-z\\s]+$");
	regex validacion_precio("^\\d{3,5}\\.\\d{2}$");
	
	cout << "\n--Apartado de registro de destinos--"<<endl;
	
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
		
		fprintf(destinostxt,"%s|%s|%s|\n", clave, descripcion, precio);
		
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
	int opc;
	bool flag=true, booleano_viaje=false;
	
	regex validacion_nombre("^[A-Z]{1}[A-Za-z\\s]+$");
	regex validacion_sino("^(si|no|SI|NO|Si|No)$");
	regex validacion_fecha("(0[1-9]|[1-2]\\d|3[0-1])-(0[1-9]|1[0-2])-(000[1-9]|00[1-9]\\d|0[1-9]\\d{2}|[1-9]\\d{3})");
	
	
	do
	{
		do
		{
			cout << "----Registro de vuelos----\n" 
			<< "1- Registrar vuelos\n"
			<< "2- Registrar destinos\n" 
			<< "3- Salir"<<endl;
			
			cin >> opc;
			if(opc < 1 || opc > 3)
				cout << "ingrese solo opciones del 1 al 3" <<endl;
			
		}while(opc < 1 || opc > 3);
		
		switch(opc)
		{
			case 1:
				cout <<"--- REGISTRO DE VUELOS ---" << endl;
				do
				{	do
					{
						flag=true;
						booleano_viaje=false;
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
							fscanf(destinostxt,"%[^|]|%[^|]|%[^|]|\n", clave, descripcion, preciotxt);
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
						fprintf(viajestxt, "%s|%s|%s|\n",nombre_destino, fecha,fecha_regreso);
					else 
						fprintf(viajestxt, "%s|%s|\n",nombre_destino, fecha);
					
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
				break;
				
			case 2: 
				if((destinostxt = fopen("destinos.txt","a+"))==NULL)
					cout<<"error al abrir aechivo"<<endl;
				else
					registro_destinos(destinostxt);
				break;
			case 3:
				cout << "saliendo..."<< endl;
				break;				
				
		}
		
	}while(opc != 3);
	
}

void listado_destinos(FILE*destinostxt)
{
	char clave[20], descripcion[200], precio[20];
	    cout << left
         << setw(10) << "Clave"
         << setw(20) << "Descripcion"
         << setw(10) << "Precio"
         << endl;

    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
    
    while(!feof(destinostxt))
    {
    	if(!feof(destinostxt))
    	{
	    	fscanf(destinostxt,"%[^|]|%[^|]|%[^|]|\n", clave, descripcion, precio);
	    	
			cout << left
	         << setw(10) << clave
	         << setw(20) << descripcion
	         << setw(10) << precio
	         << endl;
		}
	}
}

void listado_vuelos(FILE*vuelostxt, FILE*destinostxt)
{
    char linea[300];
    char descripcion[200], fecha1[20], fecha2[20], fecha[20];
    char clave[20], nombre_destino[200], precio[20];
    float precio_doble;
    bool encontrado = false;
    regex validacion_fecha("(0[1-9]|[1-2]\\d|3[0-1])-(0[1-9]|1[0-2])-(000[1-9]|00[1-9]\\d|0[1-9]\\d{2}|[1-9]\\d{3})");
    
    do
    {
        cout << "ingresa la fecha del viaje a buscar" << endl;
        cin >> ws;
        cin.getline(fecha, 20);
                
        if(!regex_match(fecha,validacion_fecha))
            cout << "ingrese nuevamente la fecha con el formato establecido" << endl;
                        
    }while(!regex_match(fecha,validacion_fecha));

    cout << left
    << setw(20) << "Clave"
    << setw(20) << "Destino"
    << setw(30) << "Precio"
    << endl;

    cout << setfill('*') << setw(70) << "" << setfill(' ') << endl;

    rewind(vuelostxt);

    // Leer línea por línea
    while(fgets(linea, sizeof(linea), vuelostxt) != NULL)
    {
        // Limpiar las variables
        strcpy(fecha2, "");
        
        // Intentar leer con 3 campos (viaje redondo)
        int campos = sscanf(linea, "%[^|]|%[^|]|%[^|]|", descripcion, fecha1, fecha2);
        
        // Si no leyó 3 campos, intentar con 2 campos (solo ida)
        if(campos < 2)
        {
            campos = sscanf(linea, "%[^|]|%[^|]|", descripcion, fecha1);
        }

        // Verificar si tenemos al menos los 2 campos mínimos y coincide la fecha
        if(campos >= 2 && strcmp(fecha, fecha1) == 0)
        {
            encontrado = true;
            rewind(destinostxt);
            
            // Buscar el destino en el archivo de destinos
            while(fscanf(destinostxt,"%[^|]|%[^|]|%[^|]|\n", clave, nombre_destino, precio) == 3)
            {
                if(strcmp(nombre_destino, descripcion) == 0)
                {
                    // Determinar si es viaje redondo (tiene fecha2)
                    if(strlen(fecha2) > 0 && fecha2[0] != '\n' && fecha2[0] != '\0')
                    {
                        precio_doble = atof(precio) * 2;
                        cout << left
                        << setw(20) << clave
                        << setw(20) << nombre_destino
                        << setw(30) << fixed << setprecision(2) << precio_doble
                        << " (Redondo)"
                        << endl;
                    }
                    else
                    {
                        cout << left
                        << setw(20) << clave
                        << setw(20) << nombre_destino
                        << setw(30) << fixed << setprecision(2) << atof(precio)
                        << " (Solo ida)"
                        << endl;
                    }
                    break;
                }
            }
        }
    }
    
    if(!encontrado)
    {
        cout << "No se encontraron vuelos para la fecha: " << fecha << endl;
    }
}

