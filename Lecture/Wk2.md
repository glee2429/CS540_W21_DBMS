# CS540 W21 DBMS 
## Relational Algebra & Datalog (Continued)
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

To pull the data with NULL value, you have to specify it as 
``` 
SELECT * 
FROM Sells
WHERE price IS NULL
```

In most cases, NULL causes problems with databases. In other words, NULL is considered a bug. 

### Multi-relation Query: JOIN 
##### Question: find the coffee brands liked by at least one person who frequents 'Culture'
Given relations Likes(dname, cname), Frequents(dname, sname), juxtaposing both relations in FROM iff Frequent.dname = Likes.dname. 
```
SELECT cname
FROM Likes, Frequents
WHERE Frequents.sname = 'Culture' AND Frequents.dname = Likes.dname; -- This is EquiJoin as well as natural join since the condition is met on all common field, which is dname.
```
#### Various types of JOIN 
- Equijoin: when the condition is equality. 
- Natural join: EquiJoin on all common fields.
- Inner join: only returns the matching ones. 
- Outer join: 
a. Left(right) outer join keeps all tuples from the left(right) relation. Unmatching ones will be filled with null.  

#### Subqueries / Nested Queries
For specifying a conditon in WHERE or FROM clauses, we can use a subquery.

Given Sells(sname, cname, price), find the coffee shops that service Costa for the same price Culture charges for Kenya.
```
SELECT sname
FROM Sells
WHERE cname = 'Cost' AND price = (SELECT price FROM Sells WHERE sname = 'Culture' AND cname = 'Kenya');
```
First, we need to find the price Culture charges for Kenya beans. (subquery)
Then, pull the data with the matching price from the first step. 

#### Helpers for Subqueries -- ALL, ANY, IN
##### ALL & ANY
In many cases, the result of your subqueries is a set. Thus, we can use ALL or ANY drawing from the set. 

Given Sells(sname, cname, price), find the coffee shops that serve 'Kenya' for a cheaper price than the price that all coffee shops charge for 'Costa'.

Let's break it down! 
1. First, the subquery is to find out the *set of all prices for 'Costa'* and name it 'CostaPrice'
2. Then, use the set drawn from 1 and compare the price drawn with all values. 

```
First part (subquery): SELECT price FROM Sells WHERE cname = 'Costa'

Main part (main query): SELECT sname FROM Sells WHERE cname = 'Kenya' AND price < ALL (subquery)

Here, ALL is necessary. 
```
* What if we use ANY instead of ALL? 
It returns the coffee shops that serve 'Kenya' for a cheaper price than the price that at least one coffee shop charges for Costa. 

##### IN 
IN is used for checking the membership. 

Given Coffee(cname, producer) and Likes(dname, cname), find the producers of the coffee brands John likes. 

Let's break it down!
1. First, find the cname 'John' likes.
2. Then, find the producer of the coffee brand that falls into the set 1. 

```
First part (subquery): SELECT cname FROM Likes WHERE dname = 'John'

Main part (main query): SELECT producer FROM Coffee WHERE cname IN (subquery)
```



