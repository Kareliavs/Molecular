#include <bits/stdc++.h>
using namespace std;
///compila asi ---> g++ Alinemiento.cpp -o a
/*
5
ATTGCCATT
ATGGCCATT
ATCCAATTTT
ATCTTCTT
ACTGACC
*/

unsigned t0,t1,t2,t3;
string s,t;
double time1=0;
double time2=0;
int m, n,a,b,c,maxi,minpen;
vector<string> aux;
vector<vector<string> > ruta;	
vector<pair< pair<string,string>,int> > resultTemp;
vector<string> cadenas_finales;
//int numero=0;
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
			string acumi;
			//if(m>=n)
				acumi="-"+acum;
			//else
			//	{acumi=t[n-1]+acum;}
			///fs<<"cositas "<<ruta[m-1][n]<<"  "<<acum<<endl;
			cadenas(ruta[m-1][n],m-1,n,acumi);
		}
		if(coord[2]=='1')//001
		{   //cout<<"ENTRO AQUI"<<endl;	
			string acumj;
			//if(m>=n)
				acumj=t[n-1]+acum;
			//else
			//	{acumj="-"+acum;cout<<"CASO2"<<endl;}
			cadenas(ruta[m][n-1],m,n-1,acumj);
		}

	}
	else 
	{

	//fs<<s<<endl<<acum<<endl<<endl;
	//numero++;
	//cout<<"ACUM: "<<acum<<endl;
	int tmp=penalidad(acum);
	if(tmp<minpen)minpen=tmp;
	resultTemp.push_back(make_pair(make_pair(s,acum),tmp));
	//cout<<acum<<"\t"<<penalidad(acum)<<endl;
	}
	//if(coord[0]=="1")

	return acum;
}

string filtro()
{
	/*for(int i=0;i<resultTemp.size();i++)
	{	if(resultTemp[i].second==minpen)
		{
			//fs<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<endl;
			cout<<"ALINEAMIENTO:"<<endl<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<endl;
		}
	}*/
	//cout<<"# alin "<<resultTemp.size()<<endl;
	for(int i=0;i<resultTemp.size();i++)
	{	if(resultTemp[i].second==minpen)
		{
			//fs<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<endl;
			//cout<<"ALINEAMIENTO:"<<endl<<resultTemp[i].first.first<<endl<<resultTemp[i].first.second<<endl<<endl;
			return resultTemp[i].first.second;
			/*if(winner==resultTemp[i].first.first) 
				return resultTemp[i].first.second;
			else if(winner==resultTemp[i].first.second)
				return resultTemp[i].first.first;
			else
				return "HOLA";*/
			//numero++;
		}
		//if(i==resultTemp.size()-1)return resultTemp[i].first.second;
	}
	cout<<"AQUI"<<endl;
	return resultTemp[0].first.second;
}

pair<string,int> global(string a1,string b1)
{
	//cout<<"PAR:"<<endl<<a1<<endl<<b1<<endl<<endl;
	s=a1;
	t=b1;
	/*fs<<"s: ";
	cin>>s;
	fs<<s<<endl;
	fs<<endl<<"t: ";
	cin>>t;
	fs<<t<<endl;*/
	m=s.length();//tenia que ser la cadena mayor ahora la estatica 
	minpen=m;
	n=t.length();	
	/*if(m<n)
	{	swap(m,n);
		s.swap(t);
	}*/

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
	
	///impresion
	//fs<<"\t"<<"-";
	/*for(int j=0;j<=n;j++)
		fs<<t[j-1]<<"\t";	
	fs<<endl;*/
	for(int i=0;i<=m;i++)
	{	/*if(i==0)	fs<<"-"<<"\t";
		else fs<<s[i-1]<<"\t";*/
		for(int j=0;j<=n;j++)
		{
			//fs<<mat[i][j]<<" "<<route[i][j]<<"\t";
			aux.push_back(route[i][j]);
		}	
		ruta.push_back(aux);
		aux.clear();
		//fs<<endl;
	}	
	t1 = clock();
	///rutas
	//fs<<"Alineamientos----------"<<endl;
	t2=clock();
	cadenas(route[m][n],m,n,"");
	pair<string, int> rpta = make_pair(filtro(),mat[m][n]);
	t3=clock();
	/*fs<<"Total de alineamientos "<<numero<<endl;
	fs<<"Score------------------"<<endl;
	fs<<mat[m][n]<<endl;
	fs<<"Penalidad "<<minpen<<endl;*/
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
	vector<int> sumas;
	for(int i=0;i<num_cad;i++)
	{
		int aux=0;
		for(int j=0;j<num_cad;j++)
		{
			aux+=scores[i][j];
			cout<<scores[i][j]<<"\t";
			fs<<scores[i][j]<<"\t";
		}
		sumas.push_back(aux);
		cout<<" = "<<aux<<endl;
		fs<<" = "<<aux<<endl;
	}
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

	cadenas_finales.push_back(cadenas[pos]);
	int long_maxima=cadenas[pos].size();
	cout<<"Pesado"<<endl;
	for(int i=0;i<num_cad;i++)
	{
		if(i!=pos)
		{	//cout<<i<<": "<< cadenas[i]<<endl;
			string tmp = alineamientos_mem[pos][i];//global(cadenas_finales[0],cadenas[i]).first;
			cout<<i<<" : "<< tmp<<endl;
			if(long_maxima < tmp.size()) long_maxima=tmp.size();
			//cadenas_finales.push_back(tmp);
			completar_cadenas(long_maxima);
			
		}
	}
	cout<<endl<<"Alineamiento final"<<endl;
	fs<<endl<<"Alineamiento final"<<endl;
	for(int i=0;i<num_cad;i++)
	{
		cout<<cadenas_finales[i]<<endl;
		fs<<cadenas_finales[i]<<endl;
	}	
	int score_final=0;
	for(int k=0;k<long_maxima;k++)
	{
		for(int i=0;i<num_cad;i++)
		{
			for(int j=i+1;j<num_cad;j++)
			{
					score_final+=sc(cadenas_finales[i][k],cadenas_finales[j][k]);
					//cout<<"\t"<<score_final<<endl;
			}
		}	
		//cout<<endl<<"POR COLUMNA:"<<score_final<<endl;
	}
    fs <<endl<<"Score: " << score_final << endl;
    cout<<endl<<"Score: " << score_final << endl; 
    /*score_final=0;
    cadenas_finales.clear();
    cout<<"PARTIENDO DESDE "<<score_final<<cadenas_finales.size()<<endl;
    cadenas_finales.push_back("ATTGCCATT--");
    cadenas_finales.push_back("ATGGCCATT--");
    cadenas_finales.push_back("ATC-CAATTTT");
    cadenas_finales.push_back("ATCTTC-TT--");
    cadenas_finales.push_back("ACTGACC----");
    
	for(int k=0;k<long_maxima;k++)
	{
		for(int i=0;i<num_cad;i++)
		{
			for(int j=i+1;j<num_cad;j++)
			{
					score_final+=sc(cadenas_finales[i][k],cadenas_finales[j][k]);
					//cout<<"\t"<<score_final<<endl;
			}
		}	
		//cout<<endl<<"POR COLUMNA:"<<score_final<<endl;
	}
	cout << "Score2: " << score_final << endl; */


	fs << "Tiempo de ejecucion DP: " << time1 <<" ms"<< endl;
	fs << "Tiempo de ejecucion CADENAS: " << time2  <<" ms"<< endl;
	fs.close();
	return 0;
}
