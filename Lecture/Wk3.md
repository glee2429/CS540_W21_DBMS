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
* q1(x) :- R(x, y), R(y, z), R(z, w). 
* q2(x) :- R(x, y), R(y, z). 

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
There exists a homomorphism such that h: q2->q1 : h(y)=y, h(z)=y, h(t)=y so that q1 is a subset of q2.

You have to cover every variable in q2. Don't miss out t!

### Query Minimization 
A conjunctive query q is minial if for every other conjunctive query q', if q' is equivalent to q (which means it maintains the same meaning) and q' has at least as many atoms as q, then q' uses fewer JOINs and faster than q. 

##### Example
q1(x) :- R(x, z), R(x, z).

q2(x) :- R(x, z). 

#### How to minimize a query? (faster, shorter, but with the same result)
1. Remove an atom from q. Let's call this a new query q'.
2. Since we just dropped an atom, q is a subset of q'.
3. Check if q' is a subset of q (see if there's a homomorphism). if then, remove the atom permanently. 

##### Example
q1(x) :- R(x, z), R(z, t), R(x, w). 

q2(x) :- R(x, z), R(z, t). 

First, drop the last atom. Then q1 wil become R(x, z), R(z, t). 
Then, we can check q1' has a homomorphism with q2. 
Finally, see if q1' and q2 are equivalent. 


## Query Containment & Minimization Continued (1/21/2021)

So far, we've seen the queries with conjunctions (AND). However, in many times, we need to use OR for writing queries. 

##### Example: queries involving multiple rules combined with OR 
Movies that were produced in 1998 OR made more than $2,000
```
Q1(y) :- Movie(x,y,1998,z).
Q1(y) :- Movie(x,y,z,t), t>2000.
```
-- Containment checking for Union of Conjunctive Queries (UCQ)is NP-complete.

### Is SQL sufficient? 
#### Recursive SQL
As an alternative to alleviate the limitation of SQL that recursive queries can not be expressed, Common Table Expression (CTE) was invented in MySQL. 

##### CTE: Relation variable within the scope of a single query. 
Common Table Expression (CTE) is similar to CREATE VIEW.

1. State the base case. 
2. Express how recursion is used based on the previous steps.
```sql
with cte (col1, col2) as (
                          select 1, 2
                          union all 
                          select 3, 4
                          )
select col1, col2 from cte;
```
