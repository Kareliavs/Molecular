#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
map<string, map<string,float> > matriz;
ofstream fs("salida.txt"); 
string ini;
int ininum;
unsigned t0, t1;
float minimo; //string keya,keyb; 
int coordminy,coordminx;
int iteraciones=1, tipo=1; 
map<string, float > distancias;
double tiempo=0;
vector<string>cabeceras1;
vector<vector<float>> matriz1;
int imprimir(vector<string>cabeceras,vector<vector<float>> matriz)
{	
	cout<<endl;
	fs<<endl;

	cout<<"-\t";
	fs<<"-\t";
	for(int i=0; i< cabeceras.size(); i++)
	{
		cout<<cabeceras[i]<<"\t";
		fs<<cabeceras[i]<<"\t";
	}
	cout<<endl;
	fs<<endl;
	for(int i=0; i< matriz.size(); i++)
	{	cout<<cabeceras[i]<<"\t";
		fs<<cabeceras[i]<<"\t";
		for(int j=0; j<matriz[i].size();j++)
		{
			cout<<matriz[i][j]<<"\t";
			fs<<matriz[i][j]<<"\t";
		}
		cout<<endl;
		fs<<endl;
	}
	
	cout<<endl;
	fs<<endl;

	cout<<"k = "<<iteraciones<<"\t min: "<<cabeceras1[min(coordminx,coordminy)]<<cabeceras1[max(coordminx,coordminy)]<<"\t"<<minimo<<endl;
	fs<<"k = "<<iteraciones<<"\t min: "<<cabeceras1[min(coordminx,coordminy)]<<cabeceras1[max(coordminx,coordminy)]<<"\t"<<minimo<<endl;
	distancias[ cabeceras1[min(coordminx,coordminy)]+cabeceras1[max(coordminx,coordminy)] ]=minimo;
	iteraciones++;

	cout<<endl;
	fs<<endl;
}
void inicio()
{
	cout<<"Ingrese numero de clusters iniciales"<<endl;
	cin>>ininum;
	for(int i=0; i<ininum; i++)
	{
		cin>>ini;
		cabeceras1.push_back(ini);
	}

	for(int i=0; i<ininum; i++)
	{
		matriz[ cabeceras1[i] ][ cabeceras1[i] ]=0;
	}
	for(int i=1; i<ininum; i++)
	{
		for(int j=0; j<i; j++)
		{
			float ingreso;
			cin>>ingreso;
			matriz[ cabeceras1[i] ][ cabeceras1[j] ] = ingreso;
			matriz[ cabeceras1[j] ][ cabeceras1[i] ] = ingreso;
			if(i==1 and j==0)
			{
				minimo = ingreso;
				coordminx =i;
				coordminy =j;
				/*
				keya   = cabeceras1[i];
				keyb   = cabeceras1[j];
				*/
			}
			
			if(ingreso<minimo)
			{
				minimo = ingreso;
				coordminx =i;
				coordminy =j;
				/*
				keya   = cabeceras1[i];
				keyb   = cabeceras1[j];
				*/
			}
			//cout<<"coord "<<coordminx<<" "<<coordminy<<endl;

		}
	}
	///Conversion a matriz 
	for(int i=0; i<ininum; i++)
	{
		vector<float> aux;
		for(int j=0; j<ininum; j++)
		{
			aux.push_back(matriz[ cabeceras1[i] ][ cabeceras1[j] ] );
		}
		matriz1.push_back(aux);

	}
	imprimir(cabeceras1,matriz1);

}
map<string, map<string,float> > agrupando(map<string, map<string,float> > matriz)
{
	vector<string>cabecerasanterior=cabeceras1;
	vector<vector<float>> matrizsalida;
	int pos1 = min(coordminx,coordminy);
	int pos2 = max(coordminx,coordminy);

	cabeceras1[pos1]= cabecerasanterior[pos1]+cabecerasanterior[pos2];
	string cluster = cabeceras1[pos1];
	cabeceras1.erase (cabeceras1.begin()+pos2);
	
	map<string, map<string,float> > salida;
    t0=clock();

	for(int i=0; i<cabeceras1.size(); i++)
	{
		float valor;

		if(tipo==1)valor= min( matriz[ cabecerasanterior[coordminx] ][ cabeceras1[i] ], matriz[ cabecerasanterior[coordminy] ][ cabeceras1[i] ]);
		else if(tipo==2)valor= max( matriz[ cabecerasanterior[coordminx] ][ cabeceras1[i] ], matriz[ cabecerasanterior[coordminy] ][ cabeceras1[i] ]);
		else if(tipo==3)valor= ( matriz[ cabecerasanterior[coordminx] ][ cabeceras1[i] ] + matriz[ cabecerasanterior[coordminy] ][ cabeceras1[i] ])/2;
		salida[ cluster ][ cabeceras1[i] ] = valor;
		salida[ cabeceras1[i] ][ cluster ] = valor;
	}
	for(int i=0; i<cabeceras1.size(); i++)
	{
		for(int j=0; j<cabeceras1.size(); j++)
		{
			if(!(salida[ cabeceras1[i] ][ cabeceras1[j] ] ))
			{
				salida[ cabeceras1[i] ][ cabeceras1[j] ] = matriz [ cabeceras1[i] ][ cabeceras1[j] ];
				salida[ cabeceras1[j] ][ cabeceras1[i] ] = matriz [ cabeceras1[i] ][ cabeceras1[j] ];
			}
		}
	}
	///Conversion a matriz 
	for(int i=0; i<cabeceras1.size(); i++)
	{
		vector<float> aux;
		for(int j=0; j<cabeceras1.size(); j++)
		{
			aux.push_back(salida[ cabeceras1[i] ][ cabeceras1[j] ] );
			if(i!=j)
			{
				if(i==0 and j==j)
				{
					minimo = salida[ cabeceras1[i] ][ cabeceras1[j] ];
					coordminx =i;
					coordminy =j;
				}
				if(salida[ cabeceras1[i] ][ cabeceras1[j] ]<minimo)
				{
					minimo = salida[ cabeceras1[i] ][ cabeceras1[j] ];
					coordminx =i;
					coordminy =j;
				}
			}
		}
		matrizsalida.push_back(aux);

	}
	t1 = clock();
	double time0 = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	tiempo =tiempo+time0;
	imprimir(cabeceras1,matrizsalida);
	return (salida);
}
void repetir(map<string, map<string,float> > matriz)
{
	while(cabeceras1.size()>2)
	{
		matriz = agrupando(matriz);
	}
}

void arbol()
{
	cout<<endl<<"Arbol"<<endl<<endl;
	fs<<endl<<"Arbol"<<endl<<endl;
	string orden;
	for(int i=0; i<cabeceras1.size();i++)
	{
		orden+=cabeceras1[i];
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
	
	cout<<"Seleccione tipo de operacion"<<endl;
	cout<<"1	Minimo"<<endl;
	cout<<"2	Maximo"<<endl;
	cout<<"3	Promedio"<<endl;
	cin>>tipo;
	cout<<endl;
	
	inicio();
	repetir(matriz);
	arbol();

	cout<<endl << "Tiempo de ejecucion: " << tiempo <<"	milisegundos"<< endl;
	fs <<endl<< "Tiempo de ejecucion: " << tiempo <<"	milisegundos"<< endl;

	fs.close();
	return 0;
}