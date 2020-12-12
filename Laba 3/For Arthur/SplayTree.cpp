#include "Splay.h"

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

