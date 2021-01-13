## CS540 W21 DBMS 
### Relational Algebra & Datalog (Continued)
#### Equivalency 
#### Unsafe Relational Algebra & Datalog 
- each element in a relational algebra / datalog should be referenced at least once to be safe. 
#### SQL 
- WHERE Clause & LIKE Operator: 
```
WHERE dname like 'T%' -- this will return dname starting with T
```
The above line will filter the corresponding column with regular expressions. However, this operation is quite slow. 

#### Null Values 
'Null' is not like any other value; Potentially the admin didn't enter the data or know the value. 

Null is used to represent the lack of information of the corresponding attribute. 
