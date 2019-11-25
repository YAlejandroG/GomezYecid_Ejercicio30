#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double D = 1;
double S = 1;
double Xmin = -1;
double Xmax = 1;

double **FTCS(int Nx);
double **dPSI(double **PSI,int Nx);
int convergence(double **PSI,double **dPSI,int Nx);

int main(){
    
    int Nx = 30;
    
    return 0;
}

double **FTCS(int Nx){
    
    double dX = (Xmax-Xmin)/Nx;
    int Nt = 2*D/pow(dX,2);
    
    double **PSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        PSI[i] =new double[Nx+1];
    }
    
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
            PSI[i+1][j] = (PSI[i][j+1]+PSI[i][j-1])/2+S/Nt;
        }
    }
    
    return PSI;
}

double **dPSI(double **PSI,int Nx){
    
    double dX = (Xmax-Xmin)/Nx;
    int Nt = 2*D/pow(dX,2);
    
    double **dPSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        dPSI[i] =new double[Nx+1];
    }
    
    for(int j=0; j<=Nx; j++){    
        dPSI[0][j] = 0;
    }
    
    
    for(int i=1; i<=Nt; i++){
        for(int j=0; j<Nx; j++){
            dPSI[i][j] = abs(PSI[i][j]-PSI[i-1][j]);
        }
    }
    
    return dPSI;
}

int convergence(double **PSI,double **dPSI,int Nx){
    
    int i = 1;
    double Pmax = PSI[1][0];
    double dPmax = dPSI[1][0];
    
    for(int j=1;j<=Nx;j++){
        if(PSI[1][j]>Pmax){
            Pmax = PSI[1][j];
        }
        if(dPSI[1][j]>dPmax){
            dPmax = dPSI[1][j];
        }
    }
    
    while(dPmax/Pmax>pow(10,-5)){
        i++;
        for(int j=1;j<=Nx;j++){
            if(PSI[i][j]>Pmax){
                Pmax = PSI[i][j];
            }
            if(dPSI[i][j]>dPmax){
                dPmax = dPSI[i][j];
            }
        }    
    }
    
    return i;
}
