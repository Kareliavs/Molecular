#include <bits/stdc++.h>
using namespace std;
///compila asi ---> g++ Alinemiento.cpp -o a
unsigned t0, t1,t2,t3;
string s, t,comienzo; 
int m, n,a,b,c,maxi,mt,nt,minpen;
vector<string> aux;
vector<vector<string> > ruta;
vector<pair< pair<string,string>,int> > resultTemp;
int numero=0;
int maxtotal=1;
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
string cadenas(string coord,int m,int n, string acum, string acum2)
{ //cout<<"CHOSES "<<coord<<endl;
	if(coord!="000" /*and coord[1]!='1'*/ )/////DESCOMENTE CONDICION PARA CORTAR EN GAP
	{	//cout<< coord<<endl;
		if(coord[0]=='1')//100
		{   
			string acumh=t[n-1]+acum;
			string acumh2=s[m-1]+acum2;
			cadenas(ruta[m-1][n-1],m-1,n-1,acumh,acumh2);
		}
		if(coord[1]=='1')//010
		{   //cout<<"ENTRe: "<<m<<" , "<<n<<" "<<coord<<endl;
			//fs<<acum<<endl;
			/*fs<<acum2<<endl<<acum<<endl<<endl;
			cout<<acum2<<endl<<acum<<endl<<endl;
			numero++;
			return acum;*/
			string acumi="-"+acum;
			string acumi2=s[m-1]+acum2;
			///fs<<"cositas "<<ruta[m-1][n]<<"  "<<acum<<endl;
			cadenas(ruta[m-1][n],m-1,n,acumi,acumi2);
		}
		if(coord[2]=='1')//001
		{
			string acumj=t[n-1]+acum;
			string acumj2="-"+acum2;
			//string acumj2=t[m-1]+acum2;
			cadenas(ruta[m][n-1],m,n-1,acumj,acumj2);
		}

	}
	else 
	{
		//if(coord!="000")return acum;
	//fs<<acum2<<endl<<acum<<endl<<endl;
	//cout<<m<<" ; "<<n<<endl;
	 cout<<acum2<<" "<<acum2.size()<<endl<<acum<<" "<<acum.size()<<endl<<endl;
	//numero++;

	int tmp=penalidad(acum)+penalidad(acum2);
	if(tmp<minpen)minpen=tmp;
	resultTemp.push_back(make_pair(make_pair(acum2,acum),tmp));
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
	cin>>s;
	cin>>t;
	m=s.length();
	minpen=m;
	n=t.length();
	if(m<n)
	{	swap(m,n);
		s.swap(t);
	}

	fs<<"s: ";
	fs<<s<<endl;
	fs<<endl<<"t: ";
	fs<<t<<endl;

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
				maxi=max(max(a,max(b,c)),0);
				route[i][j]="000";
				if(a==maxi) route[i][j][0]='1';
				if(b==maxi) route[i][j][1]='1';
				if(c==maxi) route[i][j][2]='1';
				
				if (maxi>maxtotal)
				{
					maxtotal=maxi;
					/*comienzo=route[i][j];
					mt=i;
					nt=j;*/
					//cout<<comienzo<<" "<<maxtotal<<endl;
				}

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
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{   //cout<<"\t"<<i<<","<<j<<"*"<<mat[i][j];
			if(mat[i][j]==maxtotal)
			{	cout<<"CAMINO "<<endl;
				cadenas(route[i][j],i,j,"","");
			}
		}
	}
	filtro();
	t3=clock();
	fs<<"Total de alineamientos "<<numero<<endl;
	fs<<"Score------------------"<<endl;
	fs<<maxtotal<<endl;
	fs<<"Penalidad "<<minpen<<endl;
	cout<<"SCORE: "<<maxtotal<<endl;
	double time = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	double time2 = (double(t3-t2)/1000/*CLOCKS_PER_SEC*/);
	fs << "Tiempo de ejecucion DP: " << time << endl;
	fs << "Tiempo de ejecucion CADENAS: " << time2 << endl;
	fs.close();
	return 0;
}