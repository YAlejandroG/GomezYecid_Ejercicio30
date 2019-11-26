#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double D = 1;
double S = 1;
double Xmin = -1;
double Xmax = 1;

double **FTCS(int Nx,int Nt);
double **DPSI(double **PSI,int Nx,int Nt);
string convergence(int Nx,int Nt);

int main(){
    
    ofstream outfile;
    outfile.open("resultado.dat");
    
    int Nx = 10;
    int Nt;
    double dX;
    
    for(int i=0;i<8;i++){
        dX = (Xmax-Xmin)/Nx;
        Nt = 10*2*D/pow(dX,2);
        
        outfile<<convergence(Nx,Nt)<<endl;
        
        Nx += 10;
    }
    outfile.close();
    
    return 0;
}

double **FTCS(int Nx,int Nt){
    double dX = (Xmax-Xmin)/Nx;
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
            PSI[i+1][j] = (PSI[i][j+1]+PSI[i][j-1])/2+S/(2*D/pow(dX,2));
        }
    }
    
    return PSI;
}

double **DPSI(double **PSI,int Nx,int Nt){
    
    double **dPSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        dPSI[i] =new double[Nx+1];
    }
    
    for(int j=0; j<=Nx; j++){    
        dPSI[0][j] = 0;
    }
    
    
    for(int i=1; i<=Nt; i++){
        for(int j=0; j<=Nx; j++){
            dPSI[i][j] = abs(PSI[i][j]-PSI[i-1][j]);
        }
    }
    
    return dPSI;
}

string convergence(int Nx,int Nt){
    
    double **PSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        PSI[i] =new double[Nx+1];
    }
    PSI = FTCS(Nx,Nt);
    
    double **dPSI = new double *[Nt+1];
    for (int i=0;i<=Nt;i++){
        dPSI[i] =new double[Nx+1];
    }
    dPSI = DPSI(PSI,Nx,Nt);
    
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
    
    while(dPmax/Pmax>pow(10,-6)){
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
    int centro = Nx/2;
        
    double error = (PSI[Nt][centro]-PSI[i][centro])/PSI[Nt][centro];
    
    return to_string(Nx)+" "+to_string(i)+" "+to_string(error)+" "+to_string(dPmax/Pmax);
}
