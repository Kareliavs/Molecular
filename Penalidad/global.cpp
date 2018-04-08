#include <bits/stdc++.h>
using namespace std;
///compila asi ---> g++ Alinemiento.cpp -o a
unsigned t0, t1,t2,t3;
string s, t; 
int m, n,a,b,c,maxi,minpen;
vector<string> aux;
vector<vector<string> > ruta;	
vector<pair< pair<string,string>,int> > resultTemp;
int numero=0;
ofstream fs("nombre.txt"); 
int p=2;
int q=1;
int penalidad(string cadena)
{
	int pena=0;
	int prim=0;
	int sig=0;

	for(int i=0;i<cadena.size();i++)
	{
		if(cadena[i]=='-' and cadena[i-1]!='-') prim++;//primero
		if(cadena[i]=='-' and cadena[i-1]=='-') 
		{
			sig++;
		}
	}
	pena=prim*p+q*sig;
	return pena;
}
string cadenas(string coord,int m,int n, string acum)
{
	if(coord!="000")
	{
		if(coord[0]=='1')//100
		{
			string acumh=t[n-1]+acum;
			cadenas(ruta[m-1][n-1],m-1,n-1,acumh);
		}
		if(coord[1]=='1')//010
		{
			//fs<<acum<<endl;
			string acumi="-"+acum;
			///fs<<"cositas "<<ruta[m-1][n]<<"  "<<acum<<endl;
			cadenas(ruta[m-1][n],m-1,n,acumi);
		}
		if(coord[2]=='1')//001
		{
			string acumj=t[n-1]+acum;
			cadenas(ruta[m][n-1],m,n-1,acumj);
		}

	}
	else 
	{

	//fs<<s<<endl<<acum<<endl<<endl;
	//numero++;

	int tmp=penalidad(acum);
	if(tmp<minpen)minpen=tmp;
	resultTemp.push_back(make_pair(make_pair(s,acum),tmp));
	//cout<<acum<<"\t"<<penalidad(acum)<<endl;
	}
	//if(coord[0]=="1")

	return acum;
}

void filtro()
{
	for(int i=0;i<resultTemp.size();i++)
	{	if(resultTemp[i].second==minpen)
		{
			fs<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<endl;
			//cout<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<resultTemp[i].second<<endl;

			numero++;
		}
	}
}

int main()
{



	fs<<"s: ";
	cin>>s;
	fs<<s<<endl;
	fs<<endl<<"t: ";
	cin>>t;
	fs<<t<<endl;
	m=s.length();
	minpen=m;
	n=t.length();	
	if(m<n)
	{	swap(m,n);
		s.swap(t);
	}

	int mat[m+1][n+1];
	string route[m+1][n+1];
	t0=clock();
	///iniciañizacion
	mat[0][0]=0;	
	route[0][0]="000";					
	for(int i=1;i<=m;i++)
	{
		mat[i][0]=mat[i-1][0]-2;
		route[i][0]="010";
	}	


	for(int i=1;i<=n;i++)
	{
		mat[0][i]=mat[0][i-1]-2;
		route[0][i]="001";
	}	
	///llenado
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			{
				if(s[i-1]==t[j-1]) 
					a=mat[i-1][j-1]+1;
				else
					a=mat[i-1][j-1]-1; 
				b=mat[i-1][j]-2;
				c=mat[i][j-1]-2;
				maxi=max(a,max(b,c));
				route[i][j]="000";
				if(a==maxi) route[i][j][0]='1';
				if(b==maxi) route[i][j][1]='1';
				if(c==maxi) route[i][j][2]='1';
				//fs<<a<<" "<<b<<" "<<c<<endl;
				mat[i][j]=maxi;
			}
	t1 = clock();
	///impresion
	fs<<"\t"<<"-";
	for(int j=0;j<=n;j++)
		fs<<t[j-1]<<"\t";	
	fs<<endl;
	for(int i=0;i<=m;i++)
	{	if(i==0)	fs<<"-"<<"\t";
		else fs<<s[i-1]<<"\t";
		for(int j=0;j<=n;j++)
		{
			fs<<mat[i][j]<<" "<<route[i][j]<<"\t";
			aux.push_back(route[i][j]);
		}	
		ruta.push_back(aux);
		aux.clear();
		fs<<endl;
	}	
	///rutas
	fs<<"Alineamientos----------"<<endl;
	t2=clock();
	cadenas(route[m][n],m,n,"");
	filtro();
	t3=clock();
	fs<<"Total de alineamientos "<<numero<<endl;
	fs<<"Score------------------"<<endl;
	fs<<mat[m][n]<<endl;
	fs<<"Penalidad "<<minpen<<endl;
	 
	double time = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	double time2 = (double(t3-t2)/1000/*CLOCKS_PER_SEC*/);
	fs << "Tiempo de ejecucion DP: " << time << endl;
	fs << "Tiempo de ejecucion CADENAS: " << time2 << endl;
	fs.close();
	return 0;
}