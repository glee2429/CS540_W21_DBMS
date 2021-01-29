# CS540 DBMS Week 4: Constraints & DB Schema Normalization 

## Constraints in DB Schema
DBMS managers pose a restriction in data schema to ensure the integrity of databases. For example, SSN column only contains numerical values and people with the same ssn have the same name. Additionally, constraints are used to express rules, or common sense, and restrictions for inference. 

#### Challenges in Designing Constraints in Scalable Data 
- Difficult to check and guarantee the satifiability of the constraints as the number of edge cases grows as database scales up.

### Functional Dependency as an effective constraint type
- Basis of other DB schema constraints
- Given a set of attributes X and Y in relation R, a functional dependency X->Y indicates that *every* tuple in R that has the same value of X should have the exactly corresponding value in Y. 

#### Keys (Candidate Keys)
A key in R is a set of attributes of R that functionally determines *all* attributes in R. In other words, a key is a unique identifier that detmines values of other attributes. 
* Superkey: a set of attributes that contains a key. Keys are subsets of superkey. 
* Candidate key: the minimal set of superkeys

------------------------------------------------------
### How to find Functional Dependencies? 

- Check the *Closure* of a set of Functional Dependencies 

In other words, we can find keys from checking containment or *closure* by using functional dependencies to derive all attributes in a relation from given the attributes in a candidate key.

#### Rules to Verify Closure - "Armstrong's Axioms"

- Reflexivity: Given a functional dependency A_1,A_2,...A_n -> A1, you can infer A_1,A_2,...,A_n -> A_i,...,A_j when i is greater than 1 and j is smaller or equal to n. (Trivial)
- Augmentation: Add the same value to both LHS and RHS of FD rule
- Transitivity: If A_1,A_2,...-> B_1,B_2,...B_m and B_1,B_2,...,B_m -> C1,C2,...,C_k then, A_1,...,A_n -> C_1,...,C_k. In other words, if RHS of a FD_1 is equivalent to LHS of a FD_2, then we can directly derive LHS of FD_1 -> RHS of FD_2.

#### Let's check U+ = U

* U+ = containing all functional dependencies 
* U = a set of functional dependencies 

### Other Rules 

- Decomposition: If A_1,..A_n -> B_1,...B_m then A_1,...,A_n -> B_1, A_1,...,A_n -> B_2,..., A_1,...,A_n -> B_m.
- Union: If A_1,..A_n -> B_1,... and A_1,...,A_n -> B_m, then A_1,...,A_n -> B_1,...,B_m.


#### Example: 

```
Given a relation, movies(title, year, actor, cost, revenue, b-buster) and functional dependencies 
- FD_1: title, year, actor -> cost
- FD_2: title, year, actor -> revenue
- FD_3: cost, revenue -> b-buster 

First, apply union of FD_1 and FD_2 to get FD_4. Then, we get a new rule FD_4: title, year, actor -> cost, revenue 
Second, apply transitivity on FD_4 and FD_3 since we can see that RHS of FD_4 and LHS of FD_3 are the same. As a result, we get FD_5: title, year, actor -> b-buster
Finally, apply union on FD_4 and FD_5, so we get FD_6: title, year, actor -> cost, revenue, b-buster. 
```

##### What does functional dependency to DB?

- It prevents "anomalies" by enforcing functional depency and ensuring updated values do not violate the integrity constraints. 
- Consistency check of data schema can be simplified by changing schema!

### Normalization(=Data Schema Decomposition)

Basically, we change the structure of a relation to smaller relations so that we don't have to check functional depencneis. 

For example, we decompose a relation, Emp(ssn, name, address) into smaller chunks, Emp-name(ssn,name) and Emp-addr(ssn,address).

#### Benefits of Normalization (=Decomposition) 
1. We can avoid update/deletion/insertion anomaly.
2. We can remove redundancy in the data table. 


### Normalization Types 
- Boyce-Codd Normalization Form (BCNF)
- 3 Normal Form 

### I. BCNF 

Given a relation R, R is in BCNF if and only if: for each non-trivial FD: X->Y, X is a superkey of R. In other words, *every attribute in the relation is determined only by superkey.*

- Check the LHS of FD and see if it's candidate key for a relation. 
- If you don't have FD in a decomposed relation, it's already in BCNF. 

##### How to make BCNF? 

1. Find the closure of FDs in R. 
2. Find the *keys* for R. 
3. Pick a FD: A->B that violates the BCNF condition, A must be a superkey, in R. Then, select the largest possible B. 
4. Break down R into R1 and R2. R1 will have other attributes and A, and R2 will have A and B.
5. Repeat this process until there is no BCNF left out. 

```
Emp2(ssn, name, street, city, state, zip) 
FD_1: ssn -> name
FD_2: zip -> state

Key: {ssn, zip, state, zip}

FD_1 violated BCNF condition. Therefore, let's decompose Emp2!
Emp21(ssn,name)
Emp-addr(ssn,street,city,state,zip)


FD_2 violated BCNF condition in Emp-addr. Therefore, let's decompose Emp-addr. 
Emp21(ssn,name)
Emp-addr(ssn,street,city,zip) 
-- ssn and zip are in LHS that determine name and state, and street and city are standalone. So we should include street and city to keys.
Location(zip,state)
```

###### In this process, we can pick different functional dependencies, so there's no set order for picking FD to check the violation of BCNF condition. 

So far, we've seen the benefits of decomposition and how to make one. However, there's a limitation in BCNF normalization. 

##### Limitations of Normalization 

1. Losing information -- when we recover the original relation from decomposed relations by joining them, we might get some bogus tuple(s). To prevent information loss, we must ensure that the join attributes are keys in at least one relation.
2. Losing dependency 

#### Caveats 
* BCNF decomposition is **information lossless**, since JOIN does not produce any bogus tuples. This is primarily due to the join attribute is a key. In BCNF, we decompose the original relation into smaller ones, one of which is a relation that contains the LHS key of a FD and the other containing the key and other attributes.
* However, BCNF is *NOT* dependency preserving. A decomposed relation that contains no functional dependency is also considered BCNF, so it fails to preserve FDs. Intuitively, it makes sense. By transforming a relation to BCNF, we might erase functional depedencies. In other words, given a FD: A->B, if normalization puts A and B in different relations, it is not dependency preserving. 



### II. 3NF

3NF is *lossless* and *dependency-preserving* for the sake of consistency. 3NF is not as aggressive as BCNF.

#### Third-Normal Form Condition: 
1. Given FD: X->Y, X is a superkey.
OR
2. Y is a *part* of a key. In other words, Y is one of the attributes in a key for R. 

3NF is basically a superset(larger set) of BCNF. 

``` 
Emp(ssn, name, address)
Key is {name, address}

FD_1: ssn -> name
FD_2: address, name -> ssn 

Emp is 3NF, but not BCNF because "name" is a part of a key.
```

---------------
## Denormalization 

Generally, normalization improves data integrity, but there are some limitations. 
1. Slow performance: queries on normalized schemas need more JOINs. 
2. Low readability: normalized schemas are often hard to understand. 


Considering these drawbacks, there are two types of situation to make a case for denormalization. 

### Online Analytical Processing (OLAP)
- Analytical queries (mostly for pulling data and not much need for normalization)
- Model training 
- *No write* 
- ** Normalization is NOT useful for OLAP **

### Online Transaction Processing (OLTP)
- High frequency of updates (inserting, write) 
- Useful to normalize 
- ** Normalization is useful for OLTP **


