#include "trie.hpp"

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
void insert(trie_t *pTrie,string key){
    int index;
    int len = key.size();
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

//Creates dictionary using the list
int create_dict(){
    string line;
    ifstream file;
    file.open("dict.txt");
    trie_t trie;
    
    char output[][32] = {"Not present in trie", "Present in trie"};
    
    initialise(&trie);
    
    // Construct trie
    if (file.is_open())
    {
        while (getline(file,line))
        {
            insert(&trie,line);
        }
        file.close();
    }
    else cout << "Unable to open file";
    
    printf("Words Inserted\n");
    //Search for different keys
    printf("%s --- %s\n", "Aniket", output[search(&trie,"Aniket")] );
    printf("%s --- %s\n", "these", output[search(&trie,"these")] );
    printf("%s --- %s\n", "procrastinate", output[search(&trie,"procrastinate")] );
    printf("%s --- %s\n", "thor", output[search(&trie,"Thor")] );
}
