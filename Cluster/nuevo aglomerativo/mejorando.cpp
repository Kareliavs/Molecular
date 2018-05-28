
#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
/// compilar asi -->   g++ -std=c++11 clus.cpp -o a
int aglomdis;
map<string, map<string,float> > matriz;

ofstream fs("salida.txt"); 
string ini;
int ininum;

unsigned t0, t1;
double tiempo=0;

float minimo;
int coordminy,coordminx;
int iteraciones=1, tipo=1 , maxiteraciones=1; 
map<string, float > distancias;

map<string, vector<float> > mapaincial;
vector<string> cabeceras;
void imprimir2()
{	

	cout<<"k = "<<iteraciones<<"\t min: "<<cabeceras[coordminx]<<cabeceras[coordminy]<<"\t"<<minimo<<endl;
	fs<<"k = "<<iteraciones<<"\t min: "<<cabeceras[coordminx]<<cabeceras[coordminy]<<"\t"<<minimo<<endl;
	distancias[ cabeceras[coordminx]+cabeceras[coordminy] ]=minimo;
	iteraciones++;
}
void leer()
{
 
    ifstream fichero; //variable fichero para leer los datos
    fichero.open(("diauxic.txt"));
    string frase,token;


    if (fichero.fail()) {// si fichero no falla coge un letra dle fichero
        cout << "Error al abrir el diauxic.txt" << endl;

    } 
    else {
       int flag=0;
       while (!fichero.eof()) 
		{//mientras fichero no llegue al final
            getline(fichero,frase);
		    if(flag!=0 and frase.size()>0)        
		    {
			    istringstream iss(frase);
			    int cabecera=0;
			    string llave;
			    vector<float> auxiliar_mapa;
			    while(getline(iss,token,'\t'))
			    {	 
					if(cabecera==0)
					{
					  llave="'"+token+"'";
					}	
					else
					{
					  auxiliar_mapa.push_back(stod(token));
					}
					cabecera++;
			    }
			    mapaincial[llave]=auxiliar_mapa;
			    cabeceras.push_back(llave);
		   }
		   flag++;
	    
        }	
    }

    fichero.close();
}
void hacer_matriz()
{	//map<string, map<string,float> > soyelmapa;
	
	float suma=0;
	for(int i=0; i<cabeceras.size(); i++)
	{	
		matriz[ cabeceras[i] ][ cabeceras[i] ]=0;
	}

	for(int i=1; i< cabeceras.size(); i++)
	{
		for(int j=0; j<i; j++)
		{	
				suma=0;
				for(int k=0; k<mapaincial[cabeceras[i]].size();k++)
				{   
					suma=suma+(pow(mapaincial[cabeceras[i]][k]-mapaincial[cabeceras[j]][k],2)); 	
				}
				float ingreso=sqrt(suma);
				matriz[cabeceras[i]][cabeceras[j]]=ingreso;
				matriz[cabeceras[j]][cabeceras[i]]=ingreso;
				if(i==1 and j==0)
				{
					minimo = ingreso;
					coordminx =min(i,j);
					coordminy =max(i,j);
				}
				if(ingreso<minimo)
				{
					minimo = ingreso;
					coordminx =min(i,j);
					coordminy =max(i,j);
				}
			
		}	
	}
	if(aglomdis==1)imprimir2();

}

void inicio()
{
	cout<<"Ingrese numero de clusters iniciales"<<endl;
	cin>>ininum;
	for(int i=0; i<ininum; i++)
	{
		cin>>ini;
		cabeceras.push_back(ini);
	}

	for(int i=0; i<ininum; i++)
	{
		matriz[ cabeceras[i] ][ cabeceras[i] ]=0;
	}

	for(int i=1; i<ininum; i++)
	{
		for(int j=0; j<i; j++)
		{
			float ingreso;
			cin>>ingreso;
			matriz[ cabeceras[i] ][ cabeceras[j] ] = ingreso;
			matriz[ cabeceras[j] ][ cabeceras[i] ] = ingreso;
			if(i==1 and j==0)
			{
				minimo = ingreso;
				coordminx =min(i,j);
				coordminy =max(i,j);
			}
			
			if(ingreso<minimo)
			{
				minimo = ingreso;
				coordminx =min(i,j);
				coordminy =max(i,j);
			}

		}
	}

	if(aglomdis==1)imprimir2();

}
map<string, map<string,float> > agrupando(map<string, map<string,float> > matriz)
{
	vector<string>cabecerasanterior=cabeceras;
	vector<vector<float>> matrizsalida;
	int pos1 = coordminx;
	int pos2 = coordminy;

	cabeceras[pos1]= cabecerasanterior[pos1]+cabecerasanterior[pos2];
	string cluster = cabeceras[pos1];
	cabeceras.erase (cabeceras.begin()+pos2);
	
	map<string, map<string,float> > salida;

	salida=matriz;
	cout<<"DEBO BORRAR: "<<cabecerasanterior[pos1]<<" y "<<cabecerasanterior[pos2]<<endl;
	salida.erase(cabecerasanterior[pos1]);
	salida.erase(cabecerasanterior[pos2]);
	for (map<string, map<string,float> >::iterator  iteradorgrande=salida.begin(); iteradorgrande!=salida.end(); ++iteradorgrande)
	 {
	 	salida[iteradorgrande->first].erase(cabecerasanterior[pos1]);
	 	salida[iteradorgrande->first].erase(cabecerasanterior[pos2]);
	 }
	/*cout<<"*********************************************************************"<<endl;
	for (map<string, map<string,float> >::iterator iteradorgrande=salida.begin(); iteradorgrande!=salida.end(); ++iteradorgrande)
	 { 
	 	for(map<string,float>::iterator iteradorchico=iteradorgrande->second.begin(); iteradorchico!=iteradorgrande->second.end(); ++iteradorchico)
	 	{   //cout<<"esto es:"<<i<<" , "<<j<<endl;
	 		cout<<iteradorgrande->first<<iteradorchico->first<<"\t";//<<"("<<i<<","<<j<<")";
	 	}
	 	cout<<endl;	 	
	 }
	 cout<<"*********************************************************************"<<endl;*/
	int tope=cabeceras.size();
	float temp;
	t0=clock();
	//cout<<"HOLA 1"<<endl;
	for(int i=0; i<tope; i++)
	{
		float valor;

		if(tipo==1)valor= min( matriz[ cabecerasanterior[coordminx] ][ cabeceras[i] ], matriz[ cabecerasanterior[coordminy] ][ cabeceras[i] ]);
		else if(tipo==2)valor= max( matriz[ cabecerasanterior[coordminx] ][ cabeceras[i] ], matriz[ cabecerasanterior[coordminy] ][ cabeceras[i] ]);
		else if(tipo==3)valor= ( matriz[ cabecerasanterior[coordminx] ][ cabeceras[i] ] + matriz[ cabecerasanterior[coordminy] ][ cabeceras[i] ])/2;
		salida[ cluster ][ cabeceras[i] ] = valor;
		salida[ cabeceras[i] ][ cluster ] = valor;
	}
	//cout<<"HOLA 2"<<endl; 4.0458
	minimo = salida[ cabeceras[0] ][ cabeceras[1] ];
	coordminx =0;
	coordminy =1;
	//cout<<"HOLA 3"<<endl;
	/*for(int i=0; i<tope; i++)
	{   	//cout<<"HOLA 3.1"<<endl;
		for(int j=0; j<i; j++)
		{   	//cout<<"HOLA 3.2"<<endl;
			temp=salida[ cabeceras[i] ][ cabeceras[j] ];
			cout<<cabeceras[i]<<cabeceras[j]<<"\t";
			/*if(temp<minimo)
			{   //cout<<"ENTRE"<<endl;
				minimo = temp;
				coordminx =min(i,j);
				coordminy =max(i,j);
			}//cout<<"HOLA 3.3"<<endl;
		}
		cout<<endl;
	}
    cout<<"---------------------------------------------------------------------"<<endl;*/
	int i=0, j;
	 for (map<string, map<string,float> >::iterator iteradorgrande=salida.begin(); iteradorgrande!=salida.end(); ++iteradorgrande)
	 {  j=0;
	 	for(map<string,float>::iterator iteradorchico=iteradorgrande->second.begin(); iteradorchico!=next(iteradorgrande->second.begin(),i); ++iteradorchico)
	 	{   //cout<<"esto es:"<<i<<" , "<<j<<endl;
	 		//cout<<iteradorgrande->first<<iteradorchico->first<<"\t";//<<"("<<i<<","<<j<<")";
	 		if(iteradorchico->second<minimo)
	 		{   //cout<<iteradorchico->second<<" < "<<minimo<<"    "<<coordminx<<" >> "<< i<<" and "<<coordminy<<" >> "<<j<<endl;
	 			//cout<<"*"<<endl;
	 			minimo =iteradorchico->second;
	 			coordminx =min(i,j);
				coordminy =max(i,j);
	 		}
	 		//cout<<"\t";
	 		++j;
	 	}
	 //	cout<<endl;
	 	++i;
	 	
	 }	
	cout<<"HOLA 4: "<<coordminx<<" , "<<coordminy<<" : "<<minimo<<endl;
	t1 = clock();
	double time0 = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	tiempo =tiempo+time0;
	imprimir2();
	return (salida);
}
//////DISOCIATIVO
map<string, float> elegidos;
string mayor_inicial;
vector<string> apartados;
vector<string> inmediato_anterior;

int indice;
void imprimirdisociativo()
{
	cout<<"k= "<<iteraciones<<": ";
	fs<<"k= "<<iteraciones<<": ";
	for(int i=0; i<apartados.size();i++)
	{	
		cout<<"\t(";
		fs<<"\t(";
		cout<<apartados[i];
		fs<<apartados[i];
		cout<<")";
		fs<<")";
	}
	cout<<"\t(";
	fs<<"\t(";
	for(int i=0; i<cabeceras.size();i++)
	{	
		cout<<cabeceras[i];
		fs<<cabeceras[i];
	}
	cout<<")\t"<<endl;
	fs<<")\t"<<endl;

	cout<<endl;
	fs<<endl;

}
void elegir()
{

	for(int i=0; i<cabeceras.size(); i++)
	{
		float referencia;
		float acumulado=0;
		int banderita=0;
		for(int j=0; j<cabeceras.size(); j++)
		{
			
			if(i!=j)
			{
				if(banderita==0)
				{
					referencia=matriz[ cabeceras[i] ][ cabeceras[j] ];
					banderita++;
				}
				else
				{
					if(tipo==1)referencia= min(referencia,matriz[ cabeceras[i] ][ cabeceras[j] ]);
					else if(tipo==2)referencia= max(referencia,matriz[ cabeceras[i] ][ cabeceras[j] ]);
					else if(tipo==3)acumulado=acumulado+matriz[ cabeceras[i] ][ cabeceras[j] ];
				}
			
				
			}			
		}
		if(tipo==3) 
		{
			referencia=acumulado/cabeceras.size();
		}

		elegidos[cabeceras[i]]=referencia;	
		//elegir mayor
		if(i==0)
		{
			mayor_inicial=cabeceras[i];
			indice=i;
		}
		else if(elegidos[cabeceras[i]]>elegidos[mayor_inicial])
		{
			mayor_inicial=cabeceras[i];
			indice=i;
		}


	}

	apartados.push_back(mayor_inicial);
	cabeceras.erase(cabeceras.begin()+indice);
	elegidos.erase(mayor_inicial);
	inmediato_anterior.push_back(mayor_inicial);
	imprimirdisociativo();
	
}
void disociativo()
{	int nonegativo=-1;
	t0=clock();
	for(int i=0; i<cabeceras.size();i++)
	{	
		float a,b,dif;
		if(inmediato_anterior.size()==1)
		{
			a=elegidos[cabeceras[i]];
			b=matriz[ cabeceras[i] ][inmediato_anterior[0]];
			dif=a-b;
			//cout<<endl<<cabeceras[i]<<"\t"<<a<<"\t"<<b<<"\t"<<dif;
		}
		else
		{
			a=elegidos[cabeceras[i]];
			if(tipo==1)b= min(matriz[ cabeceras[i] ][inmediato_anterior[0]],matriz[ cabeceras[i] ][inmediato_anterior[1]]);
			else if(tipo==2)b= max(matriz[ cabeceras[i] ][inmediato_anterior[0]],matriz[ cabeceras[i] ][inmediato_anterior[1]]);
			else if(tipo==3)b= ( matriz[ cabeceras[i] ][inmediato_anterior[0]] + matriz[ cabeceras[i] ][inmediato_anterior[1]])/2;
			dif=a-b;
			//cout<<endl<<cabeceras[i]<<"\t"<<a<<"\t"<<b<<"\t"<<dif;
		}
		if(dif>=0)
		{
			nonegativo=i;
		}
		
		if(i==0)
		{
			mayor_inicial=cabeceras[i];
			indice=i;
			//cout<<a<<" ? "<<mayor_inicial<<"-->"<<elegidos[mayor_inicial]<<endl;
		}
		else if(a>elegidos[mayor_inicial])
		{
			//cout<<a<<" > "<<elegidos[mayor_inicial]<<endl;
			mayor_inicial=cabeceras[i];
			indice=i;
		}

	}
	//cout<<endl;

	if(nonegativo>=0)
	{
		//cout<<"ENTRE AQUI"<<endl;
		apartados.erase(apartados.end()-1);
		string acum="";
		vector<string> auxi;
		for(int i=0;i<inmediato_anterior.size();i++)
		{
			acum+=inmediato_anterior[i];
			auxi.push_back(inmediato_anterior[i]);
		}	
		apartados.push_back(acum+cabeceras[nonegativo]);
		auxi.push_back(cabeceras[nonegativo]);
		cabeceras.erase(cabeceras.begin()+nonegativo);
		elegidos.erase(cabeceras[nonegativo]);
		inmediato_anterior.clear();
		inmediato_anterior=auxi;
	}
	else
	{
		apartados.push_back(mayor_inicial);
		cabeceras.erase(cabeceras.begin()+indice);
		elegidos.erase(mayor_inicial);
		inmediato_anterior.clear();
		inmediato_anterior.push_back(mayor_inicial);
		
	}


	t1 = clock();
	imprimirdisociativo();
	if(nonegativo<0)iteraciones++;

	double time0 = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	tiempo =tiempo+time0;

}
void repetirdis()
{
	elegir();
	//disociativo();
	while(cabeceras.size()>0 and iteraciones <= maxiteraciones)
	{   
		disociativo();
		if((iteraciones-1)%50 ==0)
		{
			cout<<endl << "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
			fs <<endl<< "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
		}
		
	}
}
void repetir(map<string, map<string,float> > matriz)
{
	while(cabeceras.size()>2 and iteraciones <= maxiteraciones)
	{   
		matriz = agrupando(matriz);
		if((iteraciones-1)%50 ==0)
		{
			cout<<endl << "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
			fs <<endl<< "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
		}
		
	}
}

void arbol()
{
	cout<<endl<<"Arbol"<<endl<<endl;
	fs<<endl<<"Arbol"<<endl<<endl;
	string orden;
	for(int i=0; i<cabeceras.size();i++)
	{
		orden+=cabeceras[i];
	}	
	cout<<orden<<endl;
	fs<<orden<<endl;

	typedef std::function<bool( pair<std::string, float>, pair<std::string, float>)> Comparator;
	Comparator compFunctor =
			[]( pair<std::string, float> elem1 , pair<std::string, float> elem2)
			{
				return elem1.second < elem2.second;
			};
    set<pair<std::string, float>, Comparator> setOfWords(distancias.begin(), distancias.end(), compFunctor);
 	for (pair<std::string, float> element : setOfWords)
	{
		size_t found = orden.find(element.first );
		if (found!=std::string::npos)
		{	for(int i=0; i<found;i++)
			{
				cout<<"-";
				fs<<"-";
			} 	
			cout<<element.first;
			fs<<element.first;
			for(int i=found+element.first.size();i<orden.size();i++)
			{
				cout<<"-";
				fs<<"-";
			}	
			cout<<"\t"<<element.second<<endl;
			fs<<"\t"<<element.second<<endl;

		}
	}	

}
int main()
{
	cout<<"Seleccione metodo"<<endl;
	cout<<"1	Aglomerativo"<<endl;
	cout<<"2	Disociativo"<<endl;

	cin>>aglomdis;
	cout<<endl;
	cout<<"Seleccione tipo de entrada"<<endl;
	cout<<"1	Texto plano sin procesar"<<endl;
	cout<<"2	Matriz de distancias"<<endl;
	int entrada;
	cin>>entrada;
	cout<<endl;
	cout<<"Seleccione tipo de operacion"<<endl;
	cout<<"1	Minimo"<<endl;
	cout<<"2	Maximo"<<endl;
	cout<<"3	Promedio"<<endl;
	cin>>tipo;
	cout<<endl;
	cout<<"Ingrese el maximo de iteraciones"<<endl;
	cin>>maxiteraciones;
	cout<<endl;
	if(entrada==1)
	{
		leer();
		hacer_matriz();
		if(aglomdis==1)
			repetir(matriz);
		else
			repetirdis();
	}
	else
	{	
		inicio(); 
		if(aglomdis==1)
		{
			repetir(matriz);
			arbol();
		}	
		else
			repetirdis();
		
	}
	

	cout<<endl << "Tiempo de ejecucion total: " << tiempo/1000 <<"	segundos"<< endl;
	fs <<endl<< "Tiempo de ejecucion total: " << tiempo/1000 <<"	segundos"<< endl;

	fs.close();
	return 0;
}
