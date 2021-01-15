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
##### EXISTS or NOT EXISTS
Check whether the result of the subquery is empty or not.

Given Coffee(cname, producer), find the coffee brands that are the only brandmade by their producers. 

Let's break it down!
1. First, when we have ONLY, it's easier to answer the negation and get the negation of the negation. Find producers that produce more than a single brand of coffee. 
2. Then, negate 1 from the whole set. 

```
First part (subquery): SELECT * FROM Coffee WHERE producer = b1.producer AND cname <> c1.cname

Main part (main query): SELECT cname FROM Coffee c1 WHERE NOT EXISTS (subquery);
```

##### DISTINCT 
Bags (Duplicates OK) vs. Set (No Duplicates)
e.g., {a, a, b, b, b} is okay!

Generally, the result of SQL queries are bags with duplicate values. 

If you'd like to remove the duplicate values, use DISTINCT. 

#### Set Operations with the Same Schema for Compatibility
1. R UNION S
2. R INTERSECT S -- AND 
```
(SELECT * FROM Likes) -- the coffee drinkers likes the brand 
INTERSECT 
(SELECT dname, cname FROM Frequents, Sells WHERE Frequents.sname = Sells.sname) -- the drinker frequenst at the coffeeshop that serves the brand
```
The schema of both queries should be compatible. Both queries have the schema of dname, cname

3. R EXCEPT S

* Caveats: since the set operations remove duplicate values (because they involves set), if you'd like dupliaces, use ALL. 

#### Aggregation Functions 
Aggregate functions map a set of value into *a single value*. Generally, Aggregate functions do not consider NULL values. 
1. COUNT
2. SUM
3. AVG
4. MIN
5. MAX
```
SELECT COUNT(price) -- does not consider entries with price = NULL, so if you'd like to COUNT the number of entry, use COUNT(*) or COUNT(cname) -- with the primary key
FROM Sells
WHERE sname = 'Culture'
```

#### Aggregate Functions Over Groups 
```
SELECT cname, MIN(price) AS minprice
FROM Sells
GROUP BY cname;
```
GROUP BY usually comes last, which categorizes the price by the specified column. 

#### Aggregation Function CANNOT be used in WHERE clause
Never put Aggregation functions in WHERE
- Instead, you can used HAVING, which is similiar to WHERE but can be used with aggregate functions
- HAVING comes after GROUP BY
