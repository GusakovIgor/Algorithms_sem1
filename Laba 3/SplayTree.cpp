#include "Splay.h"

int main ()
{
//    FindTest   ();
//    MergeTest  ();
//    SplitTest  ();
//    InsertTest ();
//    RemoveTest ();
    
    return 0;
}


// Construct-Destruct
TreeType* ConstructNode ()
{
    TreeType* node = (TreeType*) calloc (1, sizeof (TreeType));
    return node;
}

TreeType* DestructTree  (TreeType* node)
{
    if (node->left)
        node->left  = DestructTree (node->left);
    if (node->right)
        node->right = DestructTree (node->right);
    
    if (!node->left && !node->right)
    {
        free (node);
        return NULL;
    }
}


TreePair* DestructPair  (TreePair* pair)
{
    pair->tree_1 = DestructTree (pair->tree_1);
    pair->tree_2 = DestructTree (pair->tree_2);
    
    free (pair);
    return NULL;
}
//----------------------



// Balance
void Splay (SplayNode* vertex)
{
    while (vertex && vertex->parent)
    {
        if (vertex == vertex->parent->left)
        {
            if (!vertex->parent->parent)
            {
                RotateRight (vertex->parent);
            }
            else if (vertex->parent == vertex->parent->parent->left)
            {
                RotateRight (vertex->parent->parent);
                RotateRight (vertex->parent);
            }
            else
            {
                RotateRight (vertex->parent);
                RotateLeft  (vertex->parent);
            }
        }
        else
        {
            if (!vertex->parent->parent)
            {
                RotateLeft (vertex->parent);
            }
            else if (vertex->parent == vertex->parent->parent->right)
            {
                RotateLeft (vertex->parent->parent);
                RotateLeft (vertex->parent);
            }
            else
            {
                RotateLeft  (vertex->parent);
                RotateRight (vertex->parent);
            }
        }
    }
}


void RotateLeft (SplayNode* vertex)
{
    
    SplayNode* saved_parent = vertex->parent;
    SplayNode* saved_right  = vertex->right;
    
    if (saved_parent != NULL)
        if (saved_parent->left == vertex)
            saved_parent->left = saved_right;
        else
            saved_parent->right = saved_right;
    
    SplayNode* tmp = saved_right->left;
    saved_right->left = vertex;
    vertex->parent = saved_right;
    
    vertex->right = tmp;
    saved_right->parent = saved_parent;
    
    if (vertex->right != NULL)
        vertex->right->parent = vertex;
}


void RotateRight (SplayNode* vertex)
{
    SplayNode* saved_parent = vertex->parent;
    SplayNode* saved_left   = vertex->left;
    
    if (saved_parent != NULL)
        if (saved_parent->right == vertex)
            saved_parent->right = saved_left;
        else
            saved_parent->left = saved_left;
    
    SplayNode* tmp = saved_left->right;
    saved_left->right = vertex;
    vertex->parent = saved_left;
    
    vertex->left = tmp;
    saved_left->parent = saved_parent;
    
    if (vertex->left != NULL)
        vertex->left->parent = vertex;
}
//----------------------



// Functions
TreeType* Find   (TreeType* root, KeyType target, int mode)
{
    if (root == NULL || root->value == target)
    {
        Splay (root);
        return root;
    }
    else if (target > root->value)
    {
        if (mode == NOT_EQUAL && !root->right)
        {
            Splay (root);
            return root;
        }
        else
        {
            return Find (root->right, target, mode);
        }
    }
    else
    {
        if (mode == NOT_EQUAL && !root->left)
        {
            Splay (root);
            return root;
        }
        else
        {
            return Find (root->left, target, mode);
        }
    }
}

TreeType* Merge  (TreeType* l_tree, TreeType* r_tree)    // All elements in l_tree < elements in r_tree
{
    while (l_tree->right)
        l_tree = l_tree->right;
    Splay (l_tree);
    
    l_tree->right = r_tree;
    r_tree->parent = l_tree;
    
    return l_tree;
}

TreePair* Split  (TreeType* tree, KeyType x)
{
    TreePair* splitted = (TreePair*) calloc (1, sizeof (TreePair));
    
    splitted->tree_1 = Find (tree, x, NOT_EQUAL);
    splitted->tree_2 = splitted->tree_1->right;
    
    splitted->tree_1->right  = NULL;
    splitted->tree_2->parent = NULL;
    
    return splitted;
}

TreeType* Insert (TreeType* tree, KeyType value)
{
    TreePair* temp = Split (tree, value);
    
    TreeType* new_root = ConstructNode ();
    new_root->value = value;
    
    new_root->left  = temp->tree_1;
    temp->tree_1->parent = new_root;
    
    new_root->right = temp->tree_2;
    temp->tree_2->parent = new_root;
    
    return new_root;
}

TreeType* Remove (TreeType* tree, KeyType value)
{
    TreeType* rem_elem = Find (tree, value, EQUAL);
    
    return Merge (rem_elem->left, rem_elem->right);
}
//----------------------



// Logs
void SplayTreeLogs (TreeType* root)
{
    FILE* GraphicLogs = fopen ("SplayLogs\\SplayGraphicLogs.txt", "w");
    static int call = 0;
    
    //
    while (root->parent)
        root = root->parent;
    //
    
    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");
    
    if (root)
    {
        PrintNode (root, GraphicLogs);
        
        if (root->left)
        {
            PrintSubTree (root->left, GraphicLogs);
            PrintArrow   (root, root->left, GraphicLogs);
        }
        if (root->right)
        {
            PrintSubTree (root->right, GraphicLogs);
            PrintArrow   (root, root->right, GraphicLogs);
        }
    }
    
    fprintf (GraphicLogs, "}\n");
    
    fclose (GraphicLogs);
    
    MakeOpenPhoto (call);
    
    call++;
}

void PrintSubTree (TreeType* root, FILE* GraphicLogs)
{
    PrintNode (root, GraphicLogs);
    
    if (root)
        fprintf (GraphicLogs, "\"%p\" -> \"%p\" [color = white]\n", root, root->parent);
    
    if (root)
    {
        PrintSubTree (root->left, GraphicLogs);
        PrintArrow   (root, root->left, GraphicLogs);
    }
    
    if (root)
    {
        PrintSubTree (root->right, GraphicLogs);
        PrintArrow   (root, root->right, GraphicLogs);
    }
}


void PrintNode  (TreeType* node, FILE* GraphicLogs)
{
    if (node)
    {
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = darkorange, label = \"{%lg}\"]\n", 
                                                                                    node, node->value);
    }
    else
    {
        static int num_of_nulls = 1;
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = blueviolet, label = \"{NULL}\"]\n", 
                                                                                0 - num_of_nulls);
        num_of_nulls++;
    }
}

void PrintArrow (TreeType* beginning, TreeType* ending, FILE* GraphicLogs)
{
    if (ending)
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", beginning, ending);
    else
    {
        static int num_of_nulls = 1;
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", beginning, 0 - num_of_nulls);
        
        num_of_nulls++;
    }
}

void MakeOpenPhoto (int call)
{
    char* command_1 = (char*) calloc (100, sizeof(char));
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg SplayLogs\\SplayGraphicLogs.txt > SplayLogs\\SplayGraphicLogs_%d.jpeg", call);
    sprintf (command_2, "start SplayLogs\\SplayGraphicLogs_%d.jpeg", call);
    
    system (command_1);
    system (command_2);
    
    free (command_1);
    free (command_2);
}
//----------------------



// Unit-Tests
void FindTest ()
{
    TreeType* root = ConstructSimpleTree (1);
    
    SplayTreeLogs (root);
    
    SplayNode* target = Find (root, 5, EQUAL);
    
    SplayTreeLogs (root);
    
    DestructTree  (root);
}


void MergeTest ()
{
    TreeType* tree_1 = ConstructSimpleTree (1);
    TreeType* tree_2 = ConstructSimpleTree (6);
    
    SplayTreeLogs (tree_1);
    SplayTreeLogs (tree_2);
    
    TreeType* tree_12 = Merge (tree_1, tree_2);
    SplayTreeLogs (tree_12);
    
    DestructTree  (tree_12);
}


void SplitTest ()
{
    TreeType* tree_1 = ConstructSimpleTree (1);
    TreeType* tree_2 = ConstructSimpleTree (6);
    
    TreeType* tree_12 = Merge (tree_1, tree_2);
    SplayTreeLogs (tree_12);
    
    TreePair* pair = Split (tree_12, 3.5);
    
    SplayTreeLogs (pair->tree_1);
    SplayTreeLogs (pair->tree_2);
    
    pair = DestructPair (pair);
}


void InsertTest ()
{
    TreeType* tree_1 = ConstructSimpleTree (1);
    TreeType* tree_2 = ConstructSimpleTree (6);
    
    TreeType* tree_12 = Merge (tree_1, tree_2);
    SplayTreeLogs (tree_12);
    
    tree_12 = Insert (tree_12, 2.25);
    SplayTreeLogs (tree_12);
    
    DestructTree  (tree_12);
}


void RemoveTest ()
{
    TreeType* tree_1 = ConstructSimpleTree (1);
    TreeType* tree_2 = ConstructSimpleTree (6);
    
    TreeType* tree_12 = Merge (tree_1, tree_2);
    
    tree_12 = Insert (tree_12, 2.25);
    SplayTreeLogs (tree_12);
    
    tree_12 = Remove (tree_12, 7);
    SplayTreeLogs (tree_12);
    
    DestructTree  (tree_12);
}


TreeType* ConstructSimpleTree (int start_value)
{
    TreeType* tree_1 = ConstructNode ();
    tree_1->value = start_value + 3;
    
    tree_1->right = ConstructNode ();
    tree_1->right->value  = start_value + 4;
    tree_1->right->parent = tree_1;
    
    tree_1->left  = ConstructNode ();
    tree_1->left->value  = start_value + 1;
    tree_1->left->parent = tree_1;
    
    tree_1->left->left = ConstructNode ();
    tree_1->left->left->value  = start_value;
    tree_1->left->left->parent = tree_1->left;
    
    tree_1->left->right = ConstructNode ();
    tree_1->left->right->value  = start_value + 2;
    tree_1->left->right->parent = tree_1->left;
    
    return tree_1;
}
//----------------------
