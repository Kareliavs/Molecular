#include <bits/stdc++.h>
#include "memcount/memcount.cpp"
#include "memcount/memcount.hpp"
using namespace std;
///compila asi ---> g++ MSA.cpp -o a
/*
5
ATTGCCATT
ATGGCCATT
ATCCAATTTT
ATCTTCTT
ACTGACC
*/
#define MAXN 10001
int mat[MAXN][MAXN];
char route[MAXN][MAXN];
unsigned t0,t1,t2,t3;
string s,t;
double time1=0;
double time2=0;
int m, n,a,b,c,maxi,minpen;
vector<char> aux;
vector<vector<char> > ruta;	
vector<pair< pair<string,string>,int> > resultTemp;
vector<string> cadenas_finales;
//int numero=0;
ofstream fs("MSA-normal.txt"); 
int p=2;
int q=1;
string cadena_fin;
void cadenas(unsigned char coord,int m,int n, string acum)
{
	
	if(coord!='0')
	{
		if(coord=='1')//100 diagonal
		{
			string acumh=t[n-1]+acum;
			cadenas(ruta[m-1][n-1],m-1,n-1,acumh);
		}
	    if(coord=='2')//010 vertical
		{
			string acumi="-"+acum;
			cadenas(ruta[m-1][n],m-1,n,acumi);
		}
		if(coord=='3')//001 horizontal
		{   
			string acumj=t[n-1]+acum;
			cadenas(ruta[m][n-1],m,n-1,acumj);
		}

	}
	else
	{
		cadena_fin = acum;
	}
}

pair<string,int> global(string a1,string b1)
{
	///Horizontal s, m
	///Vertical   t, n
	s=a1;
	t=b1;
	m=s.length();//tenia que ser la cadena mayor ahora la estatica 
	n=t.length();	

	/*int mat[m+1][n+1];
	cout<<"Hasta aqui vivo 1.0"<<endl;
	char route[m+1][n+1];*/
	t0=clock();
	///inicializacion
	mat[0][0]=0;	
	route[0][0]='0';
	/*
	000 -> 0
	010 -> 3 horizontal
	001 -> 2 vertical
	100 -> 1 diagonal
	*/					
	for(int i=1;i<=m;i++)
	{
		mat[i][0]=mat[i-1][0]-2;
		route[i][0]='2';///vertical 
	}	
	for(int i=1;i<=n;i++)
	{
		mat[0][i]=mat[0][i-1]-2;
		route[0][i]='3';///horizontal
	}	
	///llenado
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			{
				if(s[i-1]==t[j-1]) ///si son iguales
					a=mat[i-1][j-1]+1; /// sumo
				else			
					a=mat[i-1][j-1]-1; /// resto
				b=mat[i-1][j]-2;
				c=mat[i][j-1]-2;
				maxi=max(a,max(b,c));
				route[i][j]='0';
				if(a==maxi) route[i][j]='1';///diagonal
				else if(b==maxi) route[i][j]='2';///vertical
				else if(c==maxi) route[i][j]='3';///horizontal
				mat[i][j]=maxi;
			}
	for(int i=0;i<=m;i++)
	{	
		for(int j=0;j<=n;j++)
		{
			aux.push_back(route[i][j]);
		}	
		ruta.push_back(aux);
		aux.clear();
	}	
	t1 = clock();
	
	t2=clock();
	cadenas(route[m][n],m,n,"");
	pair<string, int> rpta = make_pair(cadena_fin,mat[m][n]);
	t3=clock();
	time1 += (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	time2 += (double(t3-t2)/1000/*CLOCKS_PER_SEC*/);
	aux.clear();
	ruta.clear();
	resultTemp.clear();
	return rpta;
}

void completar_cadenas(int n)
{	//cout<<"CADENAS COMPLETADAS"<<endl;
 	for(int i=0; i<cadenas_finales.size();i++)
 	{
 		for(int j=cadenas_finales[i].size();j<n;j++)
 		{
 			cadenas_finales[i]+='-';
 		}
 		//cout<<cadenas_finales[i]<<endl;
 	}
}
int sc(char a, char b)
{
	if((a=='-' or b=='-') and (a!=b)) return -2;//-2
	if(a=='-' and b=='-') return 0;
	else if(a==b) return 1;
	else if(a!=b) return -1;
}
int main()
{
	int num_cad;
	string cad;
	vector<string> cadenas;


	cout<<"Ingrese numero de cadenas"<<endl;
	cin>>num_cad;
	for(int i=0;i<num_cad;i++)
	{
		cin>>cad;
		cadenas.push_back(cad);
	}
	//char  //memoria
    /*MSA*/
	int scores[num_cad][num_cad];
	string alineamientos_mem[num_cad][num_cad];
	for(int i=0;i<num_cad;i++)
	{	scores[i][i]=0;
		for(int j=i+1;j<num_cad;j++)
		{
			pair<string,int> aux =global(cadenas[i],cadenas[j]);
			int resultado=aux.second;
			scores[i][j]= resultado;
			scores[j][i]= resultado;
			alineamientos_mem[i][j]= aux.first;
			alineamientos_mem[j][i]= aux.first;
		}
	}
	// Suma por fila
	vector<int> sumas;
	for(int i=0;i<num_cad;i++)
	{
		int aux=0;
		for(int j=0;j<num_cad;j++)
		{
			aux+=scores[i][j];
			//cout<<scores[i][j]<<"\t";
			//fs<<scores[i][j]<<"\t";
		}
		sumas.push_back(aux);
		//cout<<" = "<<aux<<endl;
		//fs<<" = "<<aux<<endl;
	}
	///Encontrar suma maxima
	int max=sumas[0];
	int pos=0;
	for(int i=1;i<num_cad;i++)
	{
		if(sumas[i]>max)
		{
			max=sumas[i];
			pos = i;
		}
	}

	cadenas_finales.push_back(cadenas[pos]);///poner la cadena escogida primero
	int long_maxima=cadenas[pos].size();
	for(int i=0;i<num_cad;i++)
	{
		if(i!=pos)
		{	
			string tmp = alineamientos_mem[pos][i];
			if(long_maxima < tmp.size()) long_maxima=tmp.size();
			cadenas_finales.push_back(tmp);
			completar_cadenas(long_maxima);
			
		}
	}
	/*ALINEANMIENTOS*/
	cout<<endl<<"Alineamiento final"<<endl;
	fs<<endl<<"Alineamiento final"<<endl;
	for(int i=0;i<num_cad;i++)
	{
		cout<<cadenas_finales[i]<<endl;
		fs<<cadenas_finales[i]<<endl;
	}	
	/*SCORE FINAL - SUMA DE PARES*/
	int score_final=0;
	for(int k=0;k<long_maxima;k++)
	{
		for(int i=0;i<num_cad;i++)
		{
			for(int j=i+1;j<num_cad;j++)
			{
					score_final+=sc(cadenas_finales[i][k],cadenas_finales[j][k]);
			}
		}	
	}
    fs <<endl<<"Score: " << score_final << endl;
    cout<<endl<<"Score: " << score_final << endl; 
	
	cout << "Tiempo de ejecucion: " << time1/1000 + time2/1000 <<" segundos"<< endl;
	fs << "Tiempo de ejecucion: " << time1/1000 + time2/1000 <<" segundos"<< endl;
	cout << "Memoria usada: " <<   mem_total () <<" kilobytes"<< endl;
	fs << "Memoria usada: " <<   mem_total () <<" kilobytes"<< endl;
	fs.close();
	return 0;
}
