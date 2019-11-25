#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double D = 1;
double S = 1;
double T = 1;
double Xmin = -1;
double Xmax = 1;
int Nt = 450;
int Nx = 30;

int FTCS(int Nt,int Nx,string nombre);

int main(){
    string nombre = "difusion.dat";
    FTCS(Nt,Nx,nombre);
    
    return 0;
}

int FTCS(int Nt,int Nx,string nombre){
    
    double **PSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        PSI[i] =new double[Nx+1];
    }
    
    double dT = T/Nt;
    double dX = (Xmax-Xmin)/Nx;
    
    for(int i=0; i<=Nt; i++){
        for(int j=0; j<=Nx; j++){
            if(i==0){
                PSI[i][j] = 0;
            }
            
            if(j==0 | j==Nx){
                PSI[i][j] = 0;
            }
        }
    }
    
    for(int i=0; i<Nt; i++){
        for(int j=1; j<Nx; j++){
            PSI[i+1][j] = PSI[i][j]+D*dT*(PSI[i][j+1]-2*PSI[i][j]+PSI[i][j-1])/pow(dX,2)+dT*S;
        }
    }
    
    ofstream outfile;
    outfile.open(nombre);
    
    double time = 0;
    
    for(int i=0; i<=Nt; i++){
        outfile<<time<<"\t";
        time += dT;
        for(int j=0; j<=Nx; j++){
            outfile<<PSI[i][j]<<"\t";
        }
        outfile<<endl;
    }
    
    double x = -1;
    outfile<<0<<"\t";
    for(int j=0; j<=Nx; j++){
        outfile<<x<<"\t";
        x += dX;
    }
    outfile.close();
    
    return 0;
}
