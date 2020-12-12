#include "AVL.h"

int main ()
{
    UnitTests ();
    
    return 0;
}


char height (Node* vertex)
{
    return (vertex) ? vertex->height : 0;
}

char diff   (Node* vertex)
{   
    return height (vertex->left) - height (vertex->right);
}

void fix_height (Node* vertex)
{
    unsigned char hl = height (vertex->left);
    unsigned char hr = height (vertex->right);
    
    vertex->height = ((hl > hr) ? hl : hr) + 1;
}



// Turns
Node* SmallTurn (Node* vertex)
{
    assert (vertex);
    
    Node* sub_vertex = NULL;
    
    char difference = diff (vertex);
    
    if (difference == -1 || difference == -2)
    {
        sub_vertex = vertex->right;
        
        vertex->right = sub_vertex->left;
        if (sub_vertex->left)
            sub_vertex->left->parent = vertex;  // Changing parent
        
        if (vertex->parent)
        {
            sub_vertex->parent = vertex->parent;
            vertex->parent = sub_vertex;        // Changing parent
        }
        sub_vertex->left = vertex;
    }
    
    if (difference == 1 || difference == 2)
    {
        sub_vertex = vertex->left;
        
        vertex->left = sub_vertex->right;
        if (sub_vertex->right)
            sub_vertex->right->parent = vertex; // Changing parent
        
        if (vertex->parent)
        {
            sub_vertex->parent = vertex->parent;
            vertex->parent = sub_vertex;        // Changing parent
        }
            
        sub_vertex->right = vertex;
    }
    
    fix_height (vertex);
    fix_height (sub_vertex);
    
    return sub_vertex;
}

Node* Balance (Node* vertex)
{
    assert (vertex);
    
    fix_height (vertex);
    
    char difference = diff (vertex);
    if (difference == -2)
    {
        if (diff(vertex->right) > 0)
            vertex->right = SmallTurn (vertex->right);
        return SmallTurn (vertex);
    }
    if (difference == 2)
    {
        if (diff(vertex->left) < 0)
            vertex->left = SmallTurn (vertex->left);
        return SmallTurn (vertex);
    }
    
    return vertex;
}
//-----------------------------------



// Functions
Node* Insert (Node* tree, KeyType key)
{
    if (!tree)
        {
            Node* new_node = (Node*) calloc (1, sizeof(Node));
            *new_node = {key, NULL, NULL, NULL, 1};
            return new_node;
        }
    
    if (key > tree->value)
    {
        tree->right = Insert (tree->right, key);
        if (tree->right->parent != tree)
            tree->right->parent = tree;
    }
    else
    {
        tree->left = Insert (tree->left, key);
        if (tree->left->parent != tree)
            tree->left->parent = tree;
    }
    
    return Balance (tree);
}


Node* find_min (Node* tree)
{
    return (tree->left) ? find_min (tree->left) : tree;
}

Node* remove_min (Node* tree)
{
    if (!tree->left)
    {
        if (tree->right)
            tree->right->parent = tree->parent;
        return tree->right;
    }
    
    tree->left = remove_min (tree->left);
    return Balance (tree);
}


Node* Remove (Node* tree, KeyType key)
{
    if (!tree)
        return NULL;
    if (key > tree->value)
    {
        tree->right = Remove (tree->right, key);
    }
    else if (key < tree->value)
    {
        tree->left  = Remove (tree->left,  key);
    }
    else
    {
        Node* left_sub_tree = tree->left;
        Node* right_sub_tree = tree->right;
        
        Node* new_parent = tree->parent;
        free (tree);
        
        if (!right_sub_tree)
        {
            if (left_sub_tree)
                left_sub_tree->parent = new_parent;
            return left_sub_tree;
        }
        else
        {
            Node* min = find_min (right_sub_tree);

            min->right  = remove_min (right_sub_tree);
            min->left   = left_sub_tree;
            if (new_parent)
                min->parent = new_parent;
            
            if (min->left)
                min->left->parent  = min;
            
            if (min->right && min->right->parent != min)
                min->right->parent = min;
            
            return Balance (min);
        }
    }
    
    return Balance (tree);
}

Node* DestructAVL (Node* node)
{
    if (node->left)
        node->left  = DestructAVL (node->left);
    if (node->right)
        node->right = DestructAVL (node->right);
    
    if (!node->left && !node->right)
    {
        free (node);
        return NULL;
    }
}
//----------------------



// Functions for Arthur
bool Find (TreeType* tree, KeyType value)
{
    if (!tree)
        return false;
    
    if (value < tree->value)
        return Find (tree->left, value);
    else if (value > tree->value)
        return Find (tree->right, value);
    else
        return true;
}

void insert (TreeType* tree, KeyType value)
{
    tree = Insert (tree, value);
}

void Erase (TreeType* tree, KeyType value)
{
    tree = Remove (tree, value);
}
//----------------------



// Logs
void LogsMaker (Node* tree)
{
    
    FILE* GraphicLogs = fopen ("AVLLogs\\GraphicLogs.txt", "w");
    static int call = 0;
    
    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");
    
    if (tree)
    {
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \"#c81446\", label = \"{Root (%d) | {height = %d}}\"]\n", 
                                                                            tree, tree->value, tree->height);
        if (tree->left != NULL)
        {
            PrintSubTree (tree->left, GraphicLogs);
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", tree, tree->left);
        }
        if (tree->right != NULL)
        {
            PrintSubTree (tree->right, GraphicLogs);
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", tree, tree->right);
        }
    }
    else
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = red, label = \"{NULL}\"]\n", 0);
    }
    
    fprintf (GraphicLogs, "}\n");
    
    fclose (GraphicLogs);
    
    
    char* command_1 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg AVLLogs\\GraphicLogs.txt > AVLLogs\\GraphicLogs_%d.jpeg", call);
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_2, "start AVLLogs\\GraphicLogs_%d.jpeg", call);
    
    system (command_1);
    system (command_2);
    
    free (command_1);
    free (command_2);
    
    call++;
}

void PrintSubTree (Node* tree, FILE* GraphicLogs)
{   
    static int check = -1;
    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", label = \"{%d | {%d}}\"]\n", 
                                                                                tree, tree->value, tree->height);
    if (tree->parent != NULL)                                                                            
        fprintf (GraphicLogs, "\"%p\" -> \"%p\" [color = pink]\n", tree, tree->parent);
    
    if (tree->left != NULL)
    {
        PrintSubTree (tree->left, GraphicLogs);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", tree, tree->left);
    }
    else
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = red, label = \"{NULL}\"]\n", check);
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", tree, check);
        check--;
    }
    
    
    if (tree->right != NULL)
    {
        PrintSubTree (tree->right, GraphicLogs);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", tree, tree->right);
    }
    else
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = red, label = \"{NULL}\"]\n", check);
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", tree, check);
        check--;
    }
}


void UnitTests ()
{
//    SmallTurnTest ();
//    BalanceTest ();
//    InsertTest ();
    RemoveTest ();
}

void SmallTurnTest ()
{
    TreeType* tree = (Node*) calloc (1, sizeof(Node));
    
    tree->value = 5;
    tree->height = 2;
    
    
    tree->left = (Node*) calloc (1, sizeof (Node));
    tree->left->value = 3;
    tree->left->parent = tree;
    tree->left->height = 0;
    
    tree->right = (Node*) calloc (1, sizeof (Node));
    tree->right->value = 10;
    tree->right->parent = tree;
    tree->right->height = 1;
    
    tree->right->left = (Node*) calloc (1, sizeof (Node));
    tree->right->left->value = 7;
    tree->right->left->parent = tree->right;
    tree->right->left->height = 0;
    
    tree->right->right = (Node*) calloc (1, sizeof (Node));
    tree->right->right->value = 12;
    tree->right->right->parent = tree->right;
    tree->right->right->height = 0;
    
    Node* root = (Node*) calloc (1, sizeof(Node));
    root->parent = NULL;
    root->left = NULL;
    root->right = tree;
    root->height = 3;
    root->value = 0;
    
    tree->parent = root;
    
    LogsMaker (root);
    
    root->right = SmallTurn (root->right);
    
    LogsMaker (root);
    
    root->right = SmallTurn (root->right);
    
    LogsMaker (root);
    
    tree = DestructAVL (tree);
}

void BalanceTest ()
{
    TreeType* tree = (Node*) calloc (1, sizeof(Node));
    
    tree->value = 5;
    tree->height = 2;
    
    
    tree->left = (Node*) calloc (1, sizeof (Node));
    tree->left->value = 3;
    tree->left->parent = tree;
    tree->left->height = 0;
    
    tree->right = (Node*) calloc (1, sizeof (Node));
    tree->right->value = 10;
    tree->right->parent = tree;
    tree->right->height = 1;
    
    tree->right->left = (Node*) calloc (1, sizeof (Node));
    tree->right->left->value = 7;
    tree->right->left->parent = tree->right;
    tree->right->left->height = 0;
    
    tree->right->right = (Node*) calloc (1, sizeof (Node));
    tree->right->right->value = 12;
    tree->right->right->parent = tree->right;
    tree->right->right->height = 0;
    
    Node* root = (Node*) calloc (1, sizeof(Node));
    root->parent = NULL;
    root->left = NULL;
    root->right = tree;
    root->height = 3;
    root->value = 0;
    
    tree->parent = root;
    
    root->right = SmallTurn (root->right);
    
    root->left = (Node*) calloc (1, sizeof(Node));
    root->left->parent = root;
    root->left->left = NULL;
    root->left->right = NULL;
    root->left->value = -3;
    root->left->height = 0;
    
    LogsMaker (root);
    
    root = Balance (root);
    
    LogsMaker (root);
    
    tree = DestructAVL (tree);
}

void InsertTest ()
{
    TreeType* tree = (Node*) calloc (1, sizeof(Node));
    
    insert (tree, 5);
    tree = Insert (tree, 7);
    tree = Insert (tree, 1);
    
    tree = Insert (tree, 99);
    tree = Insert (tree, -11);
    
    for (int i = 1; i < 10; i++)
    {
        tree = Insert (tree, i*6);
    }
    
    LogsMaker (tree);
    
    tree = DestructAVL (tree);
}

void RemoveTest ()
{
    TreeType* tree = (Node*) calloc (1, sizeof(Node));
    
    tree = Insert (tree, 5);
    LogsMaker (tree);
    
    tree = Insert (tree, 7);
    LogsMaker (tree);
    
    tree = Insert (tree, 1);
    LogsMaker (tree);
    
    tree = Insert (tree, 99);
    LogsMaker (tree);
    
    tree = Insert (tree, -11);
    LogsMaker (tree);
    
    for (int i = 1; i < 10; i++)
    {
        tree = Insert (tree, i*6);
        LogsMaker (tree);
    }
    
    
    
    
    for (int i = 1; i < 10; i++)
    {
        tree = Remove (tree, i*6);
        LogsMaker (tree);
    }
    
    Erase (tree, -11);
    LogsMaker (tree);
    
    Erase (tree, 99);
    LogsMaker (tree);
    
    Erase (tree, 1);
    LogsMaker (tree);
    
    tree = Remove (tree, 7);
    LogsMaker (tree);
    
    tree = Remove (tree, 5);
    LogsMaker (tree);
    
    tree = DestructAVL (tree);
    LogsMaker (tree);
}

//-----

