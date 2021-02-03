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

###### Buffer Management (Buffer Pool)

- Data must be in RAM for DMBS to operate on it. 
- Important question to consider: *what if a buffer is already full?*
- Buffer pool is useful for putting things there and fetching information by relying on previously done operations.

Buffer Replacement Policy 

- Least-Recently-Used (LRU)
- Most-Recently-Used (MRU) 

These are dependent on user behavior. For example, a sequential flooding happens when repeated sequential scans occurs with LRU. 

#### Record Formats
- Reducing *time* is much more important than reducing *space*. 

Types: 
1. Un-spanned: each record belongs to only one block (fixed sized)
2. Spanned: records may be stored across multiple blocks. 

### Files of Records 
Page or block is fine with I/O operations, but higher levels of DBMS operate on *records&, and *files of records*.

#### Files of Records 
A collection of pages, each containing a collection of records. 
- Insert/delete/modify record
- Read a particular record (specified using *record id*)
- Scan all records, possibly with some conditions on the records to be retrieved.

#### System Catalog
##### For each iteration, 
- Name, file name, file structure (e.g., heap file)
- Attribute name and type for each attribute
- Index name for each index 
- Integrity constrinats 

##### For each view: 
- View name and definition 

**Catalogs are stored as relations**

### Access Paths
The methods that RDBMS uses to retrieve data. 
- Attribute values -> Tuples 
There are two types of queries 
1. Point query over *Coffee(cname, producer)* 
```
Select * From coffee Where cname = 'Costa';
```
2. Range query over *Shell(sname, cname, price)*
```
Select * From Shells Where price > 2 AND price < 10;
```

### Types of Access Pathes
#### 1. Heap files
- No order in the file
- New blocks are inserted at the end of the file

#### 2. Sorted files 
- Ordered based on some key
- Physically contiguouos or using links 

#### Cost comparison (I/O Access) of heap vs. sorted files 
The dominant factor in time complexity is I/O, so we can only consider how many I/O required for each operation.
#### Search
- O(N) for heap file (sequential scan)
- O(LogN) for sorted file (binary search)
#### Insertion/Update
- O(1) in heap (we can just go to the end of the file)
- O(LogN + N) -- you might have to shift things around. 
#### Deletion:
We need to find the item and delete it. 
- O(1) for heap: once you find the file, it only takes O(1).
- O(LogN) for sorted file: deletion takes search 


#### Summary: 
- Heap files are great for insertion. You only need O(1), but it's bad for search, as it requires O(n).
- Sorted files are great for search, but it's inefficient for insertion and update. 
- Therefore, what would be a middle ground that is great for both search and insertion? 
- Suggested solution: **INDEXING**

## Indexing 
Index is a key used for looking up data. 
- Search key: it doesn't have to be the (primary) key. 

### Two layers 
- Data file: storing the table data
- Index file: storing the index data structure, which is smaller than the data file. (e.g., (k,r) where k is the search key, and r is the point to a record, record it.)

### Index Categorization - Two Types 
1. Cluster -- data file is sorted
2. Unclustered -- data file is not sorted

Index files are sorted based on the search key. If the data file has the same order as the index file, sorted based on the *search key*, we call it **clustered**. Otherwise, we call indexing **unclustered**.

Let's say we have a datafile sorted based on id. There is only one index that is assigned to the index of your choice. 

1. Dense -- every record has a pointer for every record in the data file and faster to look up but takes more space.
2. Sparse -- only a single pointer per block/page is slower since you have to go through every single block to look up a value. 

1. Primary -- if the search key is the primary key or key of a relation, then it's called primary index.
2. Secondary -- Otherwise. 

#### Problem: when there's a duplicate search key 
We only keep track of the *first* record with a specific search key. (Clustered & dense).

With a duplicate search key, it might be impossible to point a tuple that is not at the beginning of the block. 

**Therefore, we must point to the LOWEST NEW SEARCH KEY in every block.**

##### Caveats: when data records are unsorted (unclustered), it is impossible to use sparse(blockwise) indexing since it's impossible to know what's in the block. Therefore, unclustered should be only DENSE!
