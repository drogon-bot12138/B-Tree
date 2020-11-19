## data base

​	**#define MAXM = 10**

**KeyType   --->  datatypes**

**struct TNode:**

​		**int  keynum**

​		**KeyType   data**

​		**struct TNode* kids[MAXM]**

 **struct list:**

​		**struct TNode* tnode**    #tree node

​		**struct list* next**             #next list that stores the tree  node

**struct status:**

​	**struct TNode* ptnode**   #tree node

​	**int flag**               #found or not 

​	**int pos**              #position index of Elem or the position index of the key suppose to be

## methos

//search the key in current TNode

**status search_node(TNode *p, KeyType k)** 

//insert the key in current TNode

**status insert_node(TNode *p, KeyType k)**

//search the key in rootTNode

**status search(TNode *root, KeyType k)**

//insert the keyfrom root TNode

**status insert(TNode *root, KeyType k)**



**void merge(TNode *p)**

**void adjust(TNode *p)**

**status split(TNode *p, KeyType k)**





**void init()**

**void aappend()**

**void displayall(TNode *root)**

**void displayone(KeyType k)**

