Problem:    p7_ib
Rows:       11
Columns:    6 (6 integer, 6 binary)
Non-zeros:  26
Status:     INTEGER OPTIMAL
Objective:  z = 2 (MAXimum)

   No.   Row name        Activity     Lower bound   Upper bound
------ ------------    ------------- ------------- -------------
     1 z                           2                             
     2 cardinL[B,A]                1                           1 
     3 cardinL[B,E]                1                           1 
     4 cardinL[B,C]                1                           1 
     5 cardinL[A,E]                0                           1 
     6 cardinL[A,D]                0                           1 
     7 cardinL[C,D]                0                           1 
     8 cardinL[C,F]                1                           1 
     9 cardinL[D,E]                0                           1 
    10 cardinL[D,F]                1                           1 
    11 cardinL[E,F]                1                           1 

   No. Column name       Activity     Lower bound   Upper bound
------ ------------    ------------- ------------- -------------
     1 x[A]         *              0             0             1 
     2 x[B]         *              1             0             1 
     3 x[C]         *              0             0             1 
     4 x[D]         *              0             0             1 
     5 x[E]         *              0             0             1 
     6 x[F]         *              1             0             1 

Integer feasibility conditions:

KKT.PE: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
