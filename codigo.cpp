#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
/// compilar asi -->   g++ -std=c++11 codigo.cpp -o a
map<string, map<string,float> > matriz;
map<string, map<string,float> > matriz_global;
ofstream fs("salida_bien.txt"); 
string ini;
int ininum;

unsigned t0, t1;
double tiempo=0;

float minimo;
int coordminy,coordminx;
int iteraciones=1, maxiteraciones=1; 
map<string, float > distancias;

map<string, vector<float> > mapaincial;
vector<string> cabeceras;
int num_clusters=0;
void imprimir2(map<string, map<string,float> > matriz)
{	
	/*cout<<endl;
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
	for(int i=0; i<cabeceras.size(); i++)
	{   cout<<cabeceras[i]<<"\t";
		for(int j=0; j<cabeceras.size(); j++)
		{   
			cout<< matriz[ cabeceras[i] ][ cabeceras[j] ]<<"("<<cabeceras[i]<<","<<cabeceras[j] <<")"<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
	fs<<endl;*/
/*
	cout<<"k = "<<iteraciones<<"\t min: "<<cabeceras1[min(coordminx,coordminy)]<<cabeceras1[max(coordminx,coordminy)]<<"\t"<<minimo<<endl;
	fs<<"k = "<<iteraciones<<"\t min: "<<cabeceras1[min(coordminx,coordminy)]<<cabeceras1[max(coordminx,coordminy)]<<"\t"<<minimo<<endl;
	distancias[ cabeceras1[min(coordminx,coordminy)]+cabeceras1[max(coordminx,coordminy)] ]=minimo;
	iteraciones++;

	cout<<endl;
	fs<<endl;*/
	//cout<<"k = "<<iteraciones<<"\t min: "<<cabeceras[coordminx]<<cabeceras[coordminy]<<"\t"<<minimo<<endl;
	//fs<<"k = "<<iteraciones<<"\t min: "<<cabeceras[coordminx]<<cabeceras[coordminy]<<"\t"<<minimo<<endl;
	distancias[ cabeceras[coordminx]+cabeceras[coordminy] ]=minimo;
	//iteraciones++;
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
	matriz_global=matriz;
	imprimir2(matriz);

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
	matriz_global=matriz;
	imprimir2(matriz);

}
map<string, map<string,float> > agrupando(map<string, map<string,float> > matriz)
{
	vector<string>cabecerasanterior=cabeceras;
	int pos1 = coordminx;
	int pos2 = coordminy;

	cabeceras[pos1]= cabecerasanterior[pos1]+cabecerasanterior[pos2];
	//cout<<"THINGS HAPPEND: "<< cabeceras[pos1]<<"="<< cabecerasanterior[pos1]<<"+"<<cabecerasanterior[pos2]<<endl;
	string cluster = cabeceras[pos1];
	cabeceras.erase (cabeceras.begin()+pos2);
	
	map<string, map<string,float> > salida;

	salida=matriz;
	salida.erase(cabecerasanterior[pos1]);
	salida.erase(cabecerasanterior[pos2]);
	for (map<string, map<string,float> >::iterator  iteradorgrande=salida.begin(); iteradorgrande!=salida.end(); ++iteradorgrande)
	 {
	 	salida[iteradorgrande->first].erase(cabecerasanterior[pos1]);
	 	salida[iteradorgrande->first].erase(cabecerasanterior[pos2]);
	 }
	
	int tope=cabeceras.size();
	float temp;
	t0=clock();
	//cout<<"HOLA 1"<<endl;
	for(int i=0; i<tope; i++)
	{
		float valor=0;
		//valor= ( matriz[ cabecerasanterior[coordminx] ][ cabeceras[i] ] + matriz[ cabecerasanterior[coordminy] ][ cabeceras[i] ])/2;
		
		for(int j=0;j<cluster.size();j++)
		{
			//string ayuda=cluster[j];
			stringstream ss;
			string target;
			ss << cluster[j];
			ss >> target;
			valor=valor + matriz_global[ target ][ cabeceras[i] ];
		}
		valor=valor/(cluster.size());
		salida[ cluster ][ cabeceras[i] ] = valor;
		salida[ cabeceras[i] ][ cluster ] = valor;
	}
	//cout<<"HOLA 2"<<endl; //4.0458
	minimo = salida[ cabeceras[0] ][ cabeceras[1] ];
	coordminx =0;
	coordminy =1;
	//cout<<"HOLA 3"<<endl;
	for(int i=0; i<tope; i++)
	{   	//cout<<"HOLA 3.1"<<endl;
		for(int j=0; j<i; j++)
		{   	//cout<<"HOLA 3.2"<<endl;
			temp=salida[ cabeceras[i] ][ cabeceras[j] ];
			//cout<<cabeceras[i]<<cabeceras[j]<<"\t";
			if(temp<minimo)
			{   //cout<<"ENTRE"<<endl;
				minimo = temp;
				coordminx =min(i,j);
				coordminy =max(i,j);
			}//cout<<"HOLA 3.3"<<endl;
		}
		//cout<<endl;
	}
	//cout<<"HOLA 4"<<endl;
   // cout<<"---------------------------------------------------------------------"<<endl;
	/*int i=0, j;
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
	 	
	 }	*/
	
	t1 = clock();
	double time0 = (double(t1-t0)/1000/*CLOCKS_PER_SEC*/);
	tiempo =tiempo+time0;
	
	return salida;
}

void repetir(map<string, map<string,float> > matriz)
{
	while(cabeceras.size()>0 and cabeceras.size()!= maxiteraciones)
	{   //cout<<cabeceras.size()<<"!="<<maxiteraciones<<endl;
		matriz = agrupando(matriz);
		imprimir2(matriz);
		/*if((cabeceras.size())%50 ==0)
		{
			cout<<endl << "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
			fs <<endl<< "Tiempo de ejecucion: " << tiempo/1000 <<"	segundos"<< endl<<endl;
		}*/
		/*for(int i =0;i< cabeceras.size();i++)
		{	cout<<"cluster "<<i+1<<" "<< cabeceras[i]<<endl;
			fs<<"cluster "<<i+1<<" "<< cabeceras[i]<<endl;
		}*/
		if(cabeceras.size()==50 or cabeceras.size()==100 or cabeceras.size()==150 or cabeceras.size()==200 )
		{	
			cout<<cabeceras.size()<<"------------------------------------------------------"<<endl;
			fs<<cabeceras.size()<<"------------------------------------------------------"<<endl;	
			
			for(int i =0;i< cabeceras.size();i++)
			{	cout<<"cluster "<<i+1<<" "<< cabeceras[i]<<endl;
				fs<<"cluster "<<i+1<<" "<< cabeceras[i]<<endl;
			}

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
	float anterior=0;
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
			
			cout<<"\t"<<element.second<<": \t";
			fs<<"\t"<<element.second<<": \t";

			
				cout<<element.second/2-anterior/2<<"\t"<<element.second/2<<endl;
				fs<<element.second/2-anterior/2<<"\t"<<element.second/2<<endl;
			
			anterior=element.second;

		}
	}	

}
int main()
{
	cout<<"Seleccione tipo de entrada"<<endl;
	cout<<"1	Texto plano sin procesar"<<endl;
	cout<<"2	Matriz de distancias"<<endl;
	int entrada;
	cin>>entrada;
	cout<<endl;
	cout<<"Ingrese numero de clusters"<<endl;
	cin>>maxiteraciones;
	cout<<endl;
	if(entrada==1)
	{
		leer();
		hacer_matriz();
		repetir(matriz);
		arbol();
	}
	else
	{	
		inicio(); 
		repetir(matriz);
		arbol();
		
	}
	

	cout<<endl << "Tiempo de ejecucion total: " << tiempo/1000 <<"	segundos"<< endl;
	fs <<endl<< "Tiempo de ejecucion total: " << tiempo/1000 <<"	segundos"<< endl;

	fs.close();
	return 0;
}
