# CS 540 W21 DBMS
## Lecture 1 - Course Overview

### Databases
- When we focus on multiple entities and their relationships, data is significantly more useful and informative than a single entity by discovering interesting insights.
### Handling Data
1. Querying: explore the data to know it better. (Pattern -> Data)
2. Learning: discover interesting patterns in the data (Data -> Pattern)
3. Statistical Inference: predict what patterns will appear in the data? (Pattern -> Data w/ Probabilities)

### Learning Objectives of CS540
#### 1) Relational Model & Languages
Goal: Learn to query relational data
- How to model relational data?
- How to express queries or rules in relational data?
- Review of SQL
- Other relational languages, such as Datalog

#### 2) Data Constraints
Goal: Learn to express data constraints and organize the data to evaluate them efficiently
- How to express data constraints?
- How to infer new data constraints from the given ones?
- How to organize data to evaluate rules efficiently?
- How to keep the data consistent to obey the rules?

#### 3) File Structures & Indexing
Problem: large data stored on *very slow* secondary storage, as the reads/writes on hard disks are much slower than RAM.

Goal 1: Learn to tune the data system and pick proper indexes and structures to run queries fast.

Goal 2: Learn to develop file structures and indexes for other data-driven systems

- How to make the data systems that efficiently store data
- How to create data structures to access data fast on disk (index)
- How to build data systems that support some file structures/indexes --> for reducing the running time of a query by orders of magnitude

#### 4) Query Processing & Optimization
Goal 1: Learn to check whether the data system picks the right query processing methods

Goal 2: Learn to develop data processing algorithms for other data-driven systems

- How to write algorithms to run SQL queries fast on large data with large files and tables
- How to optimize SQL queries with algorithms by removing unnecessary conditions
- How to make support system for query processing/optimization methods that help users pick the right methods and reduce the running time

#### 5-1) Transaction Management - Concurrency Control
Multiple users may update/read the database concurrently, which might interfere with each other's work and result in inconsistent data.

Goal: Learn to use the right locking protocol to keep data consistent

- How can users access the data concurrently without any problem by using concurrency control methods and locking protocols

#### 5-2) Transaction Management - Failure Recovery
The system may crash/restart during data processing due to power outage, which can cause inconsistent data after restart.

Goal 1: Learn to set the right failure recovery based on application's needs

Goal 2: Develop failure recovery for data-centric applications outside data systems -- how to deal with crash when processing a large user activity log file?

- How to develop support methods for consistent recovery from failures
- How to avoid slowing down query processing due to additional backups

#### 6) Learning over Relational Data
Problem: challenges with learning new patterns over *large relational data*

Goal: Learn algorithms to learn over relational data

- How to add learning abilities/statistical inference algorithms to an existing data system?
- How to develop algorithms to learn patterns over large relational data efficiently and effectively
