#ifndef TRIE_HPP
#define TRIE_HPP

#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;


#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define AB_SIZE (26)
#define CtoI(c) ((int)c-(int)'a')

typedef struct trie_node trie_node_t;

struct trie_node{
    int value;
    trie_node_t *children[AB_SIZE];// Links to the other 26 characters
};

typedef struct trie trie_t;

struct trie{
    trie_node_t *root;
    int count;
};



trie_node_t *getNode(void);

// Initialise a trie
void initialise (trie_t *pTrie);

//inserting a key into trie
void insert(trie_t *pTrie, char key[]);

// Search a key in the trie pTrie, returns non-zero
int search(trie_t *pTrie,char key[]);


// check if prefix present in trie or not
int prefix(trie_t *pTrie, char key[]);

//Creates dictionary using the list
int create_dict();

#endif // !TRIE_HPP
