## Query Containment (01/19/2021) 
### Question: is q1 a subset of q2? 
```
q1(x) :- R(x,y), R(y,z), R(z, w).
q2(x) :- R(x,y), R(y,z). 

-- q1 is more restrictive than q2. Therefore, q1 is a subset of q2. 
```
```
q1(x) :- R(x,y), R(y,'Joe').
q2(x) :- R(x,y), R(y,z). 

-- q1 is more restrictive than q2. Even when the instance doesn't include 'Joe', q1 will return an empty set, which is a subset of any set. 
```
```
q1(x) :- R(x,y), R(y,z), R(z,x).
q2(x) :- R(x,y), R(y,x). 

-- q1 is a cyclical query and it's difficult to define the scope of either q1 or q2. 
-- if the prefix matches, we can find out the scope of each query, but that's not the case. 
```
