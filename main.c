#include <iostream>
#include <math.h>
#include "NystromMethodforIE.h"

using namespace std;

int main(){
	int dim = 1, np = 2;    double lambda = 1.0;
	double** vtx = new double* [2];
	for(int i=0; i<2; i++)
		vtx[i] = new double[1];
	vtx[0][0] = 0.0; vtx[1][0] = 1.0;
	Quadrature* quad = new Quadrature(INTERVAL, GAUSS_QUADRATURE);
	quad->permuteData(np);
	ManifoldGeometry* gem = new ManifoldGeometry(dim, vtx);
	NystromSolver* solver = new NystromSolver(lambda, gem, quad);
	solver->solve();
	
//	Vector* solution = solver->getSolution();
//	cout<<*solution<<endl;

	cout<<"This is a Nystrom Solver for the First Fredholm Intergral Equation !-)"<<endl;
	cout<<"Dimesion = "<<dim<<";	"<<"Number of Collocation Points = "<<np<<endl;
	
	cout<<"The L2 Error = "<<setprecision(15)<<solver->computeL2error(50)<<endl;
	
}
