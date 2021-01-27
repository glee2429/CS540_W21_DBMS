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