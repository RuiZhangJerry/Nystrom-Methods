#ifndef GEOMETRY_H
#define GEOMETRY_H


#include "vector.h"
#include "matrix.h"


class ManifoldGeometry{
	int dim; 
	double** vertex;
	public:
		ManifoldGeometry(int d, double** vtx){
			this->dim = d;
			if(this->dim == 1){
				this->vertex = new double* [2];
				for(int i=0; i<2; i++){
					this->vertex[i] = new double [1];
					this->vertex[i][0] = vtx[i][0];
				}
			}
			if(this->dim == 2){
				this->vertex = new double* [4];
				for(int i=0; i<4; i++){
					this->vertex[i] = new double [2];
					for(int j=0; j<2; j++){
						this->vertex[i][j] = vtx[i][j];
					}
				}
			}
		}
		~ManifoldGeometry(){
			delete[] this->vertex;
		}
		
		int getDimension(){
			return this->dim;
		}
		
		Vector mapping(Vector ref);
		Vector tanVect(Vector ref);
		Matrix fstTensor(Vector ref);
		double arcLength(Vector ref);
		Vector gradSurface(Vector ref);
		double divSurface(Vector ref);
		
		
};
#endif //GEOMETRY_H
