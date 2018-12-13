#include "NystromMethodforIE.h"

void NystromSolver::computeGmatrix(){
	if(this->Dim == 1){
		for(int i=0; i<this->Dof; i++){
			Vector tem(1);
			tem[0] = this->refGausspts[0][i]; 
			Vector sampti = this->manifold->mapping(tem);
			for(int j=0; j<this->Dof; j++){
				tem[0] = this->refGausspts[0][j];
				Vector samptj = this->manifold->mapping(tem);
				double samwtj = this->manifold->arcLength(tem) * this->refWeights[j];
				(*this->GM)[i][j] = this->kernel->d(sampti , samptj) * samwtj\
			                    	*(-this->fredholmCoefficient);
			}
			(*this->GM)[i][i] += 1.0;
		}
	}
	if(this->Dim == 2){
		for(int i=0; i<this->Dof; i++){
			Vector tem(2);
			tem[0] = this->refGausspts[0][i]; tem[1] = this->refGausspts[1][i]; 
			Vector sampti = this->manifold->mapping(tem);
			for(int j=0; j<this->Dof; j++){
				tem[0] = this->refGausspts[0][j]; tem[1] = this->refGausspts[1][j];
				Vector samptj = this->manifold->mapping(tem);
				double samwtj = this->manifold->arcLength(tem) * this->refWeights[j];
				(*this->GM)[i][j] = this->kernel->d(sampti , samptj) * samwtj\
			                    	*(-this->fredholmCoefficient);
			}
			(*this->GM)[i][i] += 1.0;
		}
	}
}

void NystromSolver::computeRhs(){
	if(this->Dim == 1){
		for(int i=0; i<this->Dof; i++){
			Vector tem(1);
			tem[0] = this->refGausspts[0][i];
			Vector sampti = this->manifold->mapping(tem);
			(*this->RHS)[i] = this->rightFun->d(sampti);
		}
	}
	if(this->Dim == 2){
		for(int i=0; i<this->Dof; i++){
			Vector tem(2);
			tem[0] = this->refGausspts[0][i]; tem[1] = this->refGausspts[1][i];
			Vector sampti = this->manifold->mapping(tem);
			(*this->RHS)[i] = this->rightFun->d(sampti);
		}
	}
	
}

void NystromSolver::solve(){
	Vector v(this->Dof);    v=0.0;
	INT maxIter = 5000;
	DOUBLE tol = 1.0e-14;
	INT itrstep; DOUBLE res = 0.0;
	this->computeGmatrix();
	this->computeRhs();
	*(this->solution) = this->GM->solveGMRES(*(this->RHS), v, maxIter, tol, itrstep, res);
}

double NystromSolver::NystromInterpolant(Vector x){
	double intval = this->rightFun->d(x);
	for(int i=0; i<this->Dof; i++){
		Vector tem(1); 
		tem[0] = this->refGausspts[0][i];
		tem = this->manifold->mapping(tem);
		intval+=this->kernel->d(x, tem) * this->manifold->arcLength(tem)\
		        *this->refWeights[i] * (*this->solution)[i]*this->fredholmCoefficient;
	}
	
	return intval;
}

double NystromSolver::computeL2error(int refine){
	Vector tem(1);
	double error = 0.0;
	for(int i=0; i<refine; i++){
		tem[0] = -1.0+2.0*i/refine;
		error += (this->exactSol->d(tem)-this->NystromInterpolant(tem))*\
		         (this->exactSol->d(tem)-this->NystromInterpolant(tem));
		//cout<<this->NystromInterpolant(tem)<<endl;
	}
	
	return sqrt(error);
}








