#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


	// Tablice ///////////////
	int parent[22][22]={0};
	int koszt[22][22]={0};
	int mapa[22][22]={0};
	int fTab[22][22]={0};
	int zamknieta[22][22]={0};
	int trasa[22][22]={0};
	int dostepnosc[22][22]={0};
	
		
	// wspó³rzêdne startu, celu
	int pozSX=20;
	int pozSY=1;
	int i=pozSX;
	int j=pozSY;
	int celX=1;
	int celY=20;
	int ParX=celX;
	int ParY=celY;
	int k;
	int l;
	int couter=0;


	int koniec=0;
	int kosztPol=0;


int readFile()
{
	std::fstream file;
    file.open( "grid.txt", std::ios::in | std::ios::out );
     
	if( file.good() == true )
	{
    	cout << "Uzyskano dostep do pliku!" << endl;
    	for(int i=0;i<22;i++)
    	{ 
            for( int j=0;j<22;j++)
            {
            	if(i==0 || i==21) mapa[i][j]=5;
				else if (j==0 || j==21) mapa[i][j]=5;
				 else file >> mapa[i][j];   
				 
  
            }
    	}
	} 
	else 
	{
		return 0;
	}
}


void set()
{
	mapa[pozSX][pozSY]=1;
	zamknieta[pozSX][pozSY]=1;
}


void setRoadblocks()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) trasa[q][z]=mapa[q][z];
	}
}


void availableFields(int posX, int posY)
{
	if(mapa[posX][posY+1]==0 && dostepnosc[posX][posY+1]==0) dostepnosc[posX][posY+1]=1; 
	if(mapa[posX-1][posY]==0 && dostepnosc[posX-1][posY]==0) dostepnosc[posX-1][posY]=1;  
	if(mapa[posX+1][posY]==0 && dostepnosc[posX+1][posY]==0) dostepnosc[posX+1][posY]=1; 
	if(mapa[posX][posY-1]==0 && dostepnosc[posX][posY-1]==0) dostepnosc[posX][posY-1]=1; 	
	
}


void parents(int posX, int posY)
{
		if(dostepnosc[posX][posY+1]==1 && zamknieta[posX][posY+1]==0 && parent[posX][posY+1]==0) parent[posX][posY+1]=4;
		if(dostepnosc[posX-1][posY]==1 && zamknieta[posX-1][posY]==0 && parent[posX-1][posY]==0) parent[posX-1][posY]=3;
		if(dostepnosc[posX+1][posY]==1 && zamknieta[posX+1][posY]==0 && parent[posX+1][posY]==0) parent[posX+1][posY]=1;
		if(dostepnosc[posX][posY-1]==1 && zamknieta[posX][posY-1]==0 && parent[posX][posY-1]==0) parent[posX][posY-1]=2;
}


void cost(int posX, int posY)
{
	kosztPol=koszt[posX][posY]+1;
	if(dostepnosc[posX][posY+1]==1 && (koszt[posX][posY+1]>kosztPol || koszt[posX][posY+1]==0)) koszt[posX][posY+1]=kosztPol;
	if(dostepnosc[posX-1][posY]==1 && (koszt[posX-1][posY]>kosztPol || koszt[posX-1][posY]==0)) koszt[posX-1][posY]=kosztPol;
	if(dostepnosc[posX+1][posY]==1 && (koszt[posX+1][posY]>kosztPol || koszt[posX+1][posY]==0)) koszt[posX+1][posY]=kosztPol;
	if(dostepnosc[posX][posY-1]==1 && (koszt[posX][posY-1]>kosztPol || koszt[posX][posY-1]==0)) koszt[posX][posY-1]=kosztPol;	
}

void fValues(int posX, int posY)
{
		if(dostepnosc[posX][posY+1]==1)	fTab[posX][posY+1]=sqrt((celX-posX)*(celX-posX)+(celY-(posY+1))*(celY-(posY+1)))+koszt[posX][posY+1]; else fTab[posX][posY+1]=99;
 		if(dostepnosc[posX-1][posY]==1)	fTab[posX-1][posY]=sqrt((celX-(posX-1))*(celX-(posX-1))+(celY-posY)*(celY-posY))+koszt[posX-1][posY]; else fTab[posX-1][posY]=99;
		if(dostepnosc[posX+1][posY]==1)	fTab[posX+1][posY]=sqrt((celX-(posX+1))*(celX-(posX+1))+(celY-posY)*(celY-posY))+koszt[posX+1][posY]; else fTab[posX+1][posY]=99;
 		if(dostepnosc[posX][posY-1]==1)	fTab[posX][posY-1]=sqrt((celX-posX)*(celX-posX)+(celY-(posY-1))*(celY-(posY-1)))+koszt[posX][posY-1]; else fTab[posX][posY-1]=99;
}

int noPath()
{
	couter=0;
		for(int a=1;a<21;a++)
	{
		for(int b=1;b<21;b++) 
		{
			if(dostepnosc[a][b]==1) couter++;
		}
		
	}
	return couter;
}

int program(int min,int k, int l)
{
	if(fTab[k][l]==min && zamknieta[k][l]==0)
	{ 	
		dostepnosc[k][l]=5;
		zamknieta[k][l]=1;
			
		availableFields(k,l);	
		parents(k,l);			
		cost(k,l);
		fValues(k,l);		
		
		if(zamknieta[celX][celY]==1) return 1;
	}
		
}






void rest()
{
	int duplicates=0;
	int min=9999;
	int minCost=0;
		 

	for(int a=1;a<21;a++)
	{
		for(int b=1;b<21;b++) 
		{
			 if(fTab[a][b]!=0 && fTab[a][b]<min && zamknieta[a][b]==0)
			 {
				min=fTab[a][b];
				k=a;
				l=b;
				minCost=koszt[a][b];
			}
		}	
	}
	
		for(int a=1;a<21;a++)
	{
		for(int b=1;b<21;b++) 
		{
			 if(fTab[a][b]==min  && zamknieta[a][b]==0 && koszt[a][b]<minCost)
			{
				k=a;
				l=b;
			}
		}	
	}
	
	if(program(min,k,l)==1) koniec=1;
}





void patch()
{
	do
	{
		if(ParX==pozSX && ParY==pozSY) parent[ParX][ParY]=1;
		if(parent[ParX][ParY]==3)
		{
			trasa[ParX][ParY]=3;
			ParX=ParX+1;
		}
		if(parent[ParX][ParY]==4)
		{
			trasa[ParX][ParY]=3;
			ParY=ParY-1;
		}
		if(parent[ParX][ParY]==2)
		{
			trasa[ParX][ParY]=3;
			ParY=ParY+1;
		}
		if (parent[ParX][ParY]==1)
		{
			trasa[ParX][ParY]=3;
			ParX=ParX-1;
		}		
	}while(parent[pozSX][pozSY]==0);
}

void showMap()
{
		for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) cout<<mapa[q][z]<<" ";
		cout<<endl;
	}	
	cout<<"\n";
}

void showCostAr()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) if(koszt[q][z]<10) cout<<koszt[q][z]<<"  "; else cout<<koszt[q][z]<<" ";
		cout<<endl;
	}
	cout<<"\n";
}

void showFAr()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++)
		{
		if (fTab[q][z]<10)cout<<fTab[q][z]<<"  ";
		if (fTab[q][z]>10)cout<<fTab[q][z]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void showClosedAr()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) cout<<zamknieta[q][z]<<" ";
		cout<<endl;
	}	
	cout<<endl;
}

void showParentAr()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) cout<<parent[q][z]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

void ShowPathAr()
{
	for(int q=0;q<22;q++)
	{
		for(int z=0;z<22;z++) cout<<trasa[q][z]<<" ";
		cout<<endl;
	}
	cout<<endl;
}



int main(int argc, char** argv) {
	

		
	if(readFile()==0) 
	{
	cout<<"Brak dostepu do pliku"<<endl;	
	return 0;
	}
		
	set();
	setRoadblocks();
	availableFields(i,j);
	parents(i,j);
	cost(i,j);
	fValues(i,j);	

do{
    if(noPath()==0) 
    {
		cout<<endl<<"Brak drogi";
   		return 0;
	}
	rest();

	
}while(koniec!=1);

patch();



showMap();
//showCostAr();
//showFAr();
//showClosedAr();
//showParentAr();
ShowPathAr();

	
	return 0;
}
