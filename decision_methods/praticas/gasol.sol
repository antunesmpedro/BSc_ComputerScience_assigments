Problem:    gasol
Rows:       14
Columns:    15
Non-zeros:  57
Status:     OPTIMAL
Objective:  z = 923700 (MAXimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 z            B         923700                             
     2 rest1        NU         14000                       14000            66 
     3 rest2        B          14000          3000               
     4 rest3        NL          2000          2000                        -0.1 
     5 rest4        NL          1000          1000                        -0.1 
     6 rest5[1]     B              0                        5000 
     7 rest5[2]     B              0                        5000 
     8 rest5[3]     B              0                        5000 
     9 rest61       B           -140                          -0 
    10 rest62       B        -140000                          -0 
    11 rest71       B              0                          -0 
    12 rest72       B              0                          -0 
    13 rest81       B              0                          -0 
    14 rest82       B              0                          -0 

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 x[1]         B          14000             0               
     2 x[2]         NL             0             0                        -9.9 
     3 x[3]         NL             0             0                       -19.9 
     4 y[1,1]       NL             0             0                         -45 
     5 y[1,2]       NL             0             0                         -35 
     6 y[1,3]       NL             0             0                         -25 
     7 y[2,1]       NL             0             0                         -45 
     8 y[2,2]       NL             0             0                         -35 
     9 y[2,3]       NL             0             0                         -25 
    10 y[3,1]       NL             0             0                         -45 
    11 y[3,2]       NL             0             0                         -35 
    12 y[3,3]       NL             0             0                         -25 
    13 p[1]         NL             0             0                          -1 
    14 p[2]         B            200             0               
    15 p[3]         B            100             0               

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 3.64e-12 on row 2
        max.rel.err = 1.30e-16 on row 2
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 2.22e-16 on column 14
        max.rel.err = 7.40e-17 on column 14
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
