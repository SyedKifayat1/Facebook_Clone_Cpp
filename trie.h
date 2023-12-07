// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#include<string>
using namespace std;

// TrieNode class for each node in the Trie
class TrieNode {
public:
    class TrieNode* children[26]; // Array to hold children nodes for each character
    bool isWordEnd; // Indicates if a word ends at this node
};

// Returns a new Trie node with initialized values
class TrieNode* getNode(void) {
    class TrieNode* pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// Inserts a key into the Trie or marks a leaf node if the key is a prefix of the Trie node
void insert(class TrieNode* root, const string key) {
    class TrieNode* pCrawl = root;

    for (int level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // Mark the last node as a leaf node
    pCrawl->isWordEnd = true;
}

// Checks if the current node has a child or if all children are NULL
bool isLastNode(class TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Recursive function to print auto-suggestions for a given node
void suggestionsRec(class TrieNode* root, string currPrefix) {
    // Found a string in Trie with the given prefix
    if (root->isWordEnd) {
        cout << currPrefix << endl;
    }

    // All children class node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            // Append the current character to currPrefix string
            currPrefix.push_back(97 + i);

            // Recur over the rest of the characters
            suggestionsRec(root->children[i], currPrefix);
        }
    }
}

// Print suggestions for a given query prefix
int printAutoSuggestions(TrieNode* root, const string query) {
    class TrieNode* pCrawl = root;

    // Check if the prefix is present and find the node (of the last level) with the last character of the given string
    int level;
    int n = query.length();
    for (level = 0; level < n; level++) {
        int index = CHAR_TO_INDEX(query[level]);

        // No string in the Trie has this prefix
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    // Check if the prefix is present as a word
    bool isWord = (pCrawl->isWordEnd == true);

    // Check if the prefix is the last node of the tree (has no children)
    bool isLast = isLastNode(pCrawl);

    // If prefix is present as a word, but there is no subtree below the last matching node
    if (isWord && isLast) {
        cout << query << endl;
        return -1;
    }

    // If there are nodes below the last matching character
    if (!isLast) {
        string prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }
    return 0;
}
