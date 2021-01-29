## CS 540 DBMS - Data Storage

So far, we've looked at the schema (relational model). We're moving toward a more concrete level, the physical storage and covering related concepts, such as files and indexes. 

##### Modern Data Systems: 
- The logical level (schema) is separted from the physical level (implementation). 
- This physical data independence allows users to only consider relational data systems when quering data.

#### Physical Data Storage Level 
- Main memory (RAM): expensive, volatile
- Secondary storage (HDD, SSD): cheap, durable, data is stored/retrieved in *blocks*. As a result, data access is significantly lower than main memory. 

##### Slow data access in Secondary Storage 
- The total time consists of seek time + rotational latency + transfer time 
- Mostly *seek time* and *rotational delay* are the bottleneck.

Therefore, I/O access signficantly impacts the time for data analysis and processing. 


#### Suggested Solution to Big Data Storage

1. Differentiate data storage level: main memory (RAM) for currently used data vs. secondary storage (disk) for the main database.
2. Reduce the bottleneck, *seek time* and *rotational delay* to lower I/O cost. 
3. Choose the access pattern 

##### Random Access vs. Sequential Access
- Random access: seek time + rotational latency + transfer time
- Sequential access: only transfer time; the advantage is already sequenced pages for enhancing the speed.

###### Sequential Access: *pre-fetching* several pages at a time which helps with reducing time. 


##### Stroage Management 
Lowest layer of DBMS software that manages space on disk. This level is called upon by higher levels when allocating a page or reading/writing a page. 

* A request for a sequence of pages must be satisfied by allocating the pages sequentially on disk. 

###### Buffer Management 

- Data must be in RAM for DMBS to operate on it. 
- Important question to consider: *what if a buffer is already full?*
