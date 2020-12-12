#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int KeyType;

struct Node
{
    KeyType value;

    Node* parent;
    Node* left;
    Node* right;

    char height;
};

typedef Node TreeType;
// Snake_case для оболочек и вспомогательных функций
// Большие буковки для норм функций

char height     (Node* vertex);
char diff       (Node* vertex);
void fix_height (Node* vertex);

// Turns
Node* SmallTurn (Node* vertex);
Node* Balance   (Node* vertex);
void  FixUp     (Node* vertex);
//----------------------


// Functions
Node* Insert (Node* tree, KeyType key);

Node* find_min   (Node* tree);
Node* remove_min (Node* tree);

Node* Remove (Node* tree, KeyType key);

Node* DestructAVL (Node* node);

//----------------------


// Functions for Arthur
bool Find   (TreeType* tree, KeyType value);

void insert (TreeType* tree, KeyType value);

void Erase  (TreeType* tree, KeyType value);
//----------------------


// Logs
void LogsMaker (Node* tree);
void PrintSubTree     (Node* tree, FILE* GraphicLogs);

void UnitTests     ();

void SmallTurnTest ();
void BalanceTest   ();
void InsertTest    ();
void RemoveTest    ();
//----------------------
