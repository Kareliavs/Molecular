#include <bits/stdc++.h>
using namespace std;
///compila asi ---> g++ Alinemiento.cpp -o a
unsigned t0, t1;
string s, t; 
int m, n,a,b,c,maxi;
vector<string> aux;
vector<vector<string> > ruta;

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
			//cout<<acum<<endl;
			string acumi="-"+acum;
			///cout<<"cositas "<<ruta[m-1][n]<<"  "<<acum<<endl;
			cadenas(ruta[m-1][n],m-1,n,acumi);
		}
		if(coord[2]=='1')//001
		{
			string acumj=t[n-1]+acum;
			cadenas(ruta[m][n-1],m,n-1,acumj);
		}

	}
	else cout<<s<<endl<<acum<<endl<<endl;
	//if(coord[0]=="1")
	return acum;
}
int main()
{
	cout<<"s: ";
	cin>>s;
	cout<<endl<<"t: ";
	cin>>t;
	m=s.length();
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
		mat[i][0]=0;
		route[i][0]="000";
	}	


	for(int i=1;i<=n;i++)
	{
		mat[0][i]=0;
		route[0][i]="000";
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
				//cout<<a<<" "<<b<<" "<<c<<endl;
				mat[i][j]=maxi;
			}
	t1 = clock();
	///impresion
	cout<<"\t"<<"-";
	for(int j=0;j<=n;j++)
		cout<<t[j-1]<<"\t";	
	cout<<endl;
	for(int i=0;i<=m;i++)
	{	if(i==0)	cout<<"-"<<"\t";
		else cout<<s[i-1]<<"\t";
		for(int j=0;j<=n;j++)
		{
			cout<<mat[i][j]<<" "<<route[i][j]<<"\t";
			aux.push_back(route[i][j]);
		}	
		ruta.push_back(aux);
		aux.clear();
		cout<<endl;
	}	
	///rutas
	cout<<"Alineamientos----------"<<endl;
	cadenas(route[m][n],m,n,"");
	cout<<"Score------------------"<<endl;
	cout<<mat[m][n]<<endl;
	 
	double time = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	cout << "Tiempo de ejecucion: " << time << endl;
	return 0;
}
