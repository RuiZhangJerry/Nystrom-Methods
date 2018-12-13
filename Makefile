##############################################################################
#Copyright:	WANGBO
#Date:		May, 2013

#file:		Makefile (for mesh)
#############################################################################

# SHELL = /bin/sh
cCOMP = g++
cFLAGS=  -O3 -Wno-deprecated -g -o

#WORK_DIR= /home/wang-bo/work_by_c/lib
WORK_DIR= /home/zr/c++/lib
#WORK_DIR= /Users/wangbo/Dropbox/lib
DIR_INC= -I/usr/include -I $(WORK_DIR)/utilities -I $(WORK_DIR)/algebra -I $(WORK_DIR)/grid\
      	-I $(WORK_DIR)/grid3D -I $(WORK_DIR)/sparselib++/include -I $(WORK_DIR)/sparselib++/mv/include -I $(WORK_DIR)/iml++\
        -I $(WORK_DIR)/femObjects -I $(WORK_DIR)/tetgen -I $(WORK_DIR)/interface

LIB_DIR = -L $(WORK_DIR)/utilities -L $(WORK_DIR)/algebra -L $(WORK_DIR)/grid \
          -L $(WORK_DIR)/grid3D -L $(WORK_DIR)/sparselib++/lib -L $(WORK_DIR)/femObjects\
          -L $(WORK_DIR)/tetgen -L $(WORK_DIR)/interface

LIB= -Xlinker "-(" -lm -lrt -lgslcblas -lgsl -lalgebra -lutil  -lmesh -lmesh3d  -ltet -lmv -lspblas  -lsparse  -lfe -linterface -llapack -lblas -lsuitesparseconfig -lamd -lcolamd -lcholmod -lumfpack -lgfortran -Xlinker "-)"
#LIB= -lutil -lalgebra -lm -lmesh -lmesh3d -ltet  -lfe -lmv -lsparse -lspblas -lgslcblas -lgsl
#############################################################

FLAGS = -D _3D_SUPPORTING_ $(cFLAGS)
INCLUDE = $(DIR_INC)

SRC = *.c *.h

OBJS	= main

FORCE = .force


$(OBJS):$(SRC) change
	$(cCOMP) $(FLAGS)  $(OBJS) $(SRC) $(INCLUDE)  $(LIB_DIR) $(LIB)

change:
	touch *

