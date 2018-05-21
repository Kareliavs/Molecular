#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
map<string, map<string,float> > matriz;
map<string, float > lista;
ofstream fs("salida.txt"); 
string ini,LetraElegida;
int ininum;
unsigned t0, t1;
float minimo; //string keya,keyb; 
int coordminy,coordminx;
int tipo=1; 
double tiempo=0;
vector<string>cabeceras1;
vector<string>cabeceras2;
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
			}
			
			if(ingreso<minimo)
			{
				minimo = ingreso;
				coordminx =i;
				coordminy =j;
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
void imprimircluster()
{
	
	for(int i=0; i<cabeceras2.size();i++)
	{	
		cout<<"\t(";
		fs<<"\t(";
		cout<<cabeceras2[i];
		fs<<cabeceras2[i];
		cout<<")";
		fs<<")";
	}


	cout<<"\t(";
	fs<<"\t(";
	for(int i=0; i<cabeceras1.size();i++)
	{	
		cout<<cabeceras1[i];
		fs<<cabeceras1[i];
	}
	cout<<")"<<endl;
	fs<<")"<<endl;
	cout<<endl;
	fs<<endl;
}
void separando()
{
	float mintemp;
	float maxitemp;
	int pos,flag;
	for(int i=0; i<matriz1.size(); i++)
	{	flag=0;
		for(int j=0; j<matriz1[i].size(); j++)
		{
			if(i!=j)
			{
				if(flag==0)
				{
					mintemp=matriz1[i][j];
					flag=1;
				}
				if(matriz1[i][j]<mintemp)
				{
					mintemp=matriz1[i][j];
				}
			}
		}
		cout<<cabeceras1[i]<<"\t"<<mintemp<<endl;
		fs<<cabeceras1[i]<<"\t"<<mintemp<<endl;
		lista[cabeceras1[i]]=mintemp;
		if(i==0) 
		{
			maxitemp=mintemp;
			LetraElegida=cabeceras1[i];
			pos=i;
		}
		if(mintemp>maxitemp)
		{
			maxitemp=mintemp;
			LetraElegida=cabeceras1[i];
			pos=i;
		}
	}
	cabeceras1.erase (cabeceras1.begin()+pos);
	cabeceras2.push_back(LetraElegida);
	cout<<maxitemp;
	fs<<maxitemp;
	imprimircluster();
	

}
void separando2()
{
	float mintemp;
	float maxitemp;
	int pos,flag=0;
	string LetraAnterior=LetraElegida;
	for(int i=0; i<cabeceras1.size();i++)
	{	
		float valor= lista[cabeceras1[i]];
		float valor_relacionado;
		if(LetraElegida.size()==1)
			valor_relacionado= matriz[LetraElegida][cabeceras1[i]];
		else
		{	//float temporal=matriz[LetraElegida[0]][cabeceras1[i]];
			float suma=0;
			for(int j=0; j<LetraElegida.size();j++)
			{  cout<<LetraElegida[j];
				/*string Let=LetraElegida[j];
				if(tipo==1) temporal=min(temporal, matriz[Let][cabeceras1[i]]);
				else if(tipo==2) temporal=max(temporal, matriz[Let][cabeceras1[i]]);
				else if(tipo ==3) suma=suma+matriz[Let][cabeceras1[i]];*/
			}
			//if(tipo ==3) valor_relacionado=temporal;
			//else  valor_relacionado= suma/LetraElegida.size();
		}
		float resta= valor-valor_relacionado;
		cout<<cabeceras1[i]<<"\t"<<valor<<"\t"<<valor_relacionado<<"\t"<<resta<<endl;
		if(i==0) 
		{
			maxitemp=valor;
			LetraElegida=cabeceras1[i];
			pos=i;
		}
		if(valor>maxitemp)
		{
			maxitemp=valor;
			LetraElegida=cabeceras1[i];
			pos=i;
		}
	}
	if(maxitemp>=0)
	{
		LetraElegida=LetraAnterior+LetraElegida;

	}
	 
	{
		cabeceras1.erase (cabeceras1.begin()+pos);
		cabeceras2.push_back(LetraElegida);
		cout<<maxitemp;
		fs<<maxitemp;
		imprimircluster();
	}

}
void repetir()
{
	while(cabeceras1.size()>0)
	{
		separando2();
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
	separando();
	//separando2();
	repetir();

	//cout<<endl << "Tiempo de ejecucion: " << tiempo <<"	milisegundos"<< endl;
	//fs <<endl<< "Tiempo de ejecucion: " << tiempo <<"	milisegundos"<< endl;

	fs.close();
	return 0;
}
