#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef double KeyType;

struct SplayNode
{
    KeyType value;

    SplayNode* parent;
    SplayNode* left;
    SplayNode* right;
};

typedef SplayNode TreeType;

struct TreePair
{
    TreeType* tree_1;
    TreeType* tree_2;
};


enum find_modes {     EQUAL = 1,
                  NOT_EQUAL = 2 };


// Construct-Destruct
TreeType* ConstructNode ();
TreeType* DestructTree  (TreeType* node);
TreePair* DestructPair  (TreePair* pair);
//----------------------


// Balance
void Splay (SplayNode* vertex);

void RotateLeft  (SplayNode* vertex);
void RotateRight (SplayNode* vertex);
//----------------------


// Functions
TreeType* Find   (TreeType* root, KeyType target, int mode);
TreeType* Merge  (TreeType* l_tree, TreeType* r_tree);
TreePair* Split  (TreeType* tree, KeyType x, int mode);
TreeType* Insert (TreeType* tree, KeyType value);
TreeType* Remove (TreeType* tree, KeyType value);
//----------------------


// Logs
void SplayTreeLogs (TreeType* root);
void PrintSubTree  (TreeType* root, FILE* GraphicLogs);

void PrintNode     (TreeType* node, FILE* GraphicLogs);
void PrintArrow    (TreeType* beginning, TreeType* ending, FILE* GraphicLogs);
void MakeOpenPhoto (int call);
//----------------------


// Unit_Tests
void FindTest   ();
void MergeTest  ();
void SplitTest  ();
void InsertTest ();
void RemoveTest ();

TreeType* ConstructSimpleTree (int start_value);
//----------------------


