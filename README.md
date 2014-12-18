1) I assumed that the if table name is xyz then xyz.txt is schema file and xyz.csv is data file which should be present in the folder.\par
2) In where condition if coloumn = string than string should be in quotes . Ex NAME = "dhwanit". \par
3) I assumed that schema file has a certain format in which 1 coloumn contain field name , 2nd coloumn contain datatype  and 5th coloumn contain if primary key.\par
4) select distinct(col) will work with any number of coloumn and where condition.\line Ex ; select col1, col2 , distinct(col3) from temp where col1 = col2;\par
5) I assumed that input query must be end by ; .\par
6) If user want to redirect it in file then he should type file name after |.\line Ex : select * from airports | result;

Compile : make
Run ./a.out
sample query : select * from airport;
