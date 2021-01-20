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
### Homomorphism 
- A homomorphism h:q2->q1 is a function from var(q2) to var(q1) such tha for each atom R(x, y, ..) in q1 there is an atom R(h(x), h(y),...) in q2. 
- h leaves the constants in q2 intact. 

##### Example
q1(x) :- R(x, y), R(y, z), R(z, w). 
q2(x) :- R(x, y), R(y, z). 

We treat head variables,'x', as constants so that the same in q1 and q2. 
h: q2->q1 : h(y)=y, h(z)=z.

#### Homomorphism Theorem 
Given conjunctive queries q1 and q2, we have q1 is a subset of q2 if and only if there exists a homomorphism h: q2 -> q1. 

##### Example 
```
q1(x) :- R(x, y), R(y, 'Joe'). 
q2(x) :- R(x, y), R(y, z). 
```
If we want to define q1 is a subset of q2, then we should show the homomorphism. 

The homomorphism exists as h: q2->q1 :(where) h(y) = y, h(z) = 'Joe' as a result, q1 is a subset of q2. 

-- We don't have to specify the head atom, since it's implied in the conditon already. 

##### Example 2
```
q1(x) :- R(x, y), R(y, z), R(z, x). 
q2(x) :- R(x, y), R(y, x). 
```

There is no homomorphism: since we can't map x to z (x appears in the head). 

```
q1(x) :- R(x, y), R(y, y).
q2(x) :- R(x, y), R(y, z), R(z, t).
```
There exists a homomorphism that h: q2->q1 : h(y)=y, h(z)=y, h(t)=y so that q1 is a subset of q2.

You have to cover every variable in q2. Don't miss out t!




