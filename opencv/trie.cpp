#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<string.h>

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

//Creating and Returning a new node
trie_node_t *getNode(void){
	trie_node_t *pNode = NULL;
	pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
	//If sufficient memory is allocate
	if(pNode){
		pNode->value = 0;
		for(int i=0;i<AB_SIZE;i++)
		pNode->children[i]=NULL;
	}
	
	return pNode;
}

// Initialise a trie
void initialise (trie_t *pTrie){
	pTrie->root = getNode();
	pTrie->count = 0;
}		

//inserting a key into trie
void insert(trie_t *pTrie, char key[]){
	int index;
	int len = strlen(key);
	trie_node_t *pCrawl;
	pTrie->count++;
	pCrawl = pTrie->root;
	
	for( int level = 0; level<len;level++)
	{
		index = CtoI(key[level]);
		if(!pCrawl->children[index]){
			pCrawl->children[index]=getNode();
		}
		pCrawl = pCrawl->children[index];
	
	}
	//Marking the word by the count
	pCrawl->value=pTrie->count;
	
}
// Search a key in the trie pTrie, returns non-zero
int search(trie_t *pTrie,char key[]){
	int index;
	int len = strlen(key);
	trie_node_t *pCrawl;
	pCrawl = pTrie->root;
	
	for( int level = 0; level<len;level++)
	{
		index = CtoI(key[level]);
		if(!pCrawl->children[index]){
			//This means that word doesn't exists
			return 0;
		}
		pCrawl = pCrawl->children[index];
	
	}
	
	if(pCrawl->value) return 1;
	else return 0;
}

int main(){

// Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie_t trie;
 
    char output[][32] = {"Not present in trie", "Present in trie"};
 
    initialise(&trie);
 
    // Construct trie
    for(int i = 0; i < ARRAY_SIZE(keys); i++)
    {
        insert(&trie, keys[i]);
    }
	printf("Words Inserted\n");
    //Search for different keys
    printf("%s --- %s\n", "the", output[search(&trie, "the")] );
    printf("%s --- %s\n", "these", output[search(&trie, "these")] );
    printf("%s --- %s\n", "their", output[search(&trie, "their")] );
    printf("%s --- %s\n", "thaw", output[search(&trie, "thaw")] );
 
    return 0;

}
	

