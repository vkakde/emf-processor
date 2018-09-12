# EMF Processor
EMF Query Processing Engine (C++ extended SQL processing engine). This application is based on idea presented in following papers -
1. "Querying Multiple Features of Groups in Relational Databases" by Damianos Chatziantoniou and Kenneth A. Ross (Department of Computer Science, Columbia University)

2. "Evaluation of Ad Hoc OLAP : In-Place Computation" by Damianos Chatziantoniou (Department of Computer Science, Columbia University)

The C++ application uses PostgreSQL's C interface (PGC) to process Extended-SQL operations. Extended-SQL is an innovated concept to solve complex OLAP queries. E-SQL is faster and easier/succinct to write, compared to regular SQL.  

# System/compiler Requirements 
1. gcc 7.2.0 (provided by MinGW 64 on Windows x64)
2. PostgresSQL 10 (with pgc)

# Input file format
2 (count of grouping variables)    
cust, year (gv0 variables)    
1_sum_quant, 2_count_quant (gv1-n variables)    
cust, year, 1_sum_quant, 2_count_quant (select/project variables)    
1.cust = cust, 2.year = year (SUCH THAT predicates)    

# Compile/link/run instructions
1. PGC->C conversion:    
$: ecpg generator.pgc  

2. Link and run C to generate exe:  
$: gcc -c -I [postgres include] generator.c   
[postgres include] ~= "C:\Program Files\PostgreSQL\10\include" on Windows  

    $: gcc -L [postgres lib] -lecpg generated.o -o generated.exe  
    [postgres lib] ~= "C:\Program Files\PostgreSQL\10\lib" on Windows  

3. Run  
$: generated.exe  
