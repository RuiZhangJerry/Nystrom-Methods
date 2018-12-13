#ifndef NYSTROMMETHODFORIE_H
#define NYSTROMMETHODFORIE_H

#include "quadrature.h"
#include "Geometry.h"

class integralKernel{
	public:
		integralKernel(){};
		~integralKernel(){};
		
		double d(Vector r, Vector rPrime){
			return 1.0-3.0*r[0]*rPrime[0];
		}
};

class RHSFun{
	public:
		RHSFun(){};
		~RHSFun(){};
		
		double d(Vector r){
			return 1.0-3.0*r[0];
		}	
};

class exactSolution{
	public:
		exactSolution(){};
		~exactSolution(){};
		
		double d(Vector r){
			return 2.0*(1.0-3.0*r[0])/3.0;
		}
};


class NystromSolver{
	int Dof, Dim;
	double fredholmCoefficient;
	Matrix* GM;
	Vector* RHS;
	Vector* solution;
	double* refWeights;
	Matrix refGausspts;
	ManifoldGeometry* manifold;
	integralKernel* kernel;
	RHSFun* rightFun;
	exactSolution* exactSol;
	public:
		NystromSolver(double lambda, ManifoldGeometry* geo, Quadrature* quad){
			this->manifold = geo;
			this->Dof = quad->getNPoints();
			this->Dim = this->manifold->getDimension();
			this->refGausspts = quad->getPoints();
			this->refWeights = quad->getWeights();
			this->fredholmCoefficient = lambda;
			this->GM = new Matrix(this->Dof, this->Dof);
			this->RHS = new Vector(this->Dof);
			this->solution = new Vector(this->Dof);
			
			this->kernel = new integralKernel();
			this->rightFun = new RHSFun();
			this->exactSol = new exactSolution();
		}
		~NystromSolver(){
			delete GM;
			delete RHS;
			delete solution;
		}
		
		void setRhs(Vector rhs){
			*(this->RHS) = rhs;
		}
		
		void computeGmatrix();
		void computeRhs();
		void solve();
		
		Vector* getSolution(){
			return this->solution;
		}
		double NystromInterpolant(Vector x);
		double computeL2error(int refine);
		
};

#endif //NYSTROMMETHODFORIE_H








