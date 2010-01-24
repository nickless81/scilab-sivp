/***********************************************************************
 * SIVP - Scilab Image and Video Processing toolbox
 * Copyright (C) 2007  Roger Liu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 ***********************************************************************/


#include "common.h"

int int_ind2rgb (char *fname)
{
  static int l1, m1, n1, l2, m2, n2, l3, m3, n3;
  static int minlhs = 1, maxlhs = 1, minrhs = 2, maxrhs = 2;
  int mL, nL, ms, ns, lc2, it, mi, ni, mn, inc, zero, count;
  int si[3];
  static char *Str[]= { "hm","dims","entries"};
  double *var, *temp;
  SciIntMat ssi, M;

  /* Input Validation */
  CheckRhs (minrhs, maxrhs);
  CheckLhs (minlhs, maxlhs);

  if ((GetType(1)!=sci_ints)|| (GetType(2)!=sci_matrix))
  {
	  sciprint("Argument 1 should be integer matrix and 2 should be Nx3 double matrix");
      return 0;
  }
  GetRhsVar (1, "I", &m1, &n1, &M);
  mn = m1*n1;
  inc  = 1;
  zero = 0;


  if (M.it==1)
  {
	  sciprint("index matrix should be real integer!\n");
	  return 0;
  }
    
  GetRhsCVar(2, "d", &it, &m2, &n2, &l2, &lc2);
  
  if (it==1)
  {
	  sciprint("colormap should be real matrix!\n");
	  return 0;
  }
  if ((n2!=3))
  {
	  sciprint("colormap should be Nx3 matrix!\n");
      return 0;
  }

  si[0] = m1;
  si[1] = n1;
  si[2] = 3;
  ssi.m = 1;
  ssi.n = 3;
  ssi.l = 100;
  ssi.it = 4;
  ssi.D = si;
  var = (double*)malloc(m1*n1*3*sizeof(double));
  temp = (double*)malloc(m1*n1*sizeof(double));


  C2F(tpconv)(&M.it,&zero,&mn, M.D, &inc, temp, &inc);
  for(count=0;count<m1*n1;count++)
  {
     if ((int)(temp[count]) < 1)
	 {
         var[count] = stk(l2)[0];
		 var[count+m1*n1] = stk(l2)[m2];
		 var[count+2*m1*n1] = stk(l2)[2*m2];
	 }
	 if ((int)(temp[count]) < m2)
	 {
		 var[count]=stk(l2)[(int)(temp[count])-1];
		 var[count+m1*n1]=stk(l2)[(int)(temp[count])+m2-1]; 
		 var[count+m1*n1*2]=stk(l2)[(int)(temp[count])+2*m2-1];
	 }
	 else
	 {
		 var[count] = stk(l2)[m2-1];
		 var[count+m1*n1] = stk(l2)[2*m2-1];
		 var[count+2*m1*n1] = stk(l2)[3*m2-1];
	 }
  }
  free(temp);
  mi = 1;
  ni = 3;
  ms = 1;
  ns = 3;
  mL = 3;
  nL = 1;
  m3 = m1*n1*3;
  n3 = 1;
  CreateVar(3, "m", &mL, &nL, &l3);
  CreateListVarFromPtr(3,1,"S",&ms,&ns,Str);
  CreateListVarFromPtr(3,2,"I",&mi,&ni,&ssi);
  CreateListVarFromPtr(3,3,"d",&m3, &n3, &var);
  free(var);
  LhsVar(1) = 3;
 
  return 0;
}
