#include "AVL.h"

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
Node* InsertTreapAVL (Node* tree, KeyType key)
{
    if (!tree)
        {
            Node* new_node = (Node*) calloc (1, sizeof(Node));
            *new_node = {key, NULL, NULL, NULL, 1};
            return new_node;
        }
    
    if (key > tree->value)
    {
        tree->right = InsertTreapAVL (tree->right, key);
        if (tree->right->parent != tree)
            tree->right->parent = tree;
    }
    else
    {
        tree->left = InsertTreapAVL (tree->left, key);
        if (tree->left->parent != tree)
            tree->left->parent = tree;
    }
    
    return Balance (tree);
}


Node* find_min (Node* tree)
{
    return (tree->left) ? find_min (tree->left) : tree;
}

Node* RemoveTreap_min (Node* tree)
{
    if (!tree->left)
    {
        if (tree->right)
            tree->right->parent = tree->parent;
        return tree->right;
    }
    
    tree->left = RemoveTreap_min (tree->left);
    return Balance (tree);
}


Node* RemoveTreap (Node* tree, KeyType key)
{
    if (!tree)
        return NULL;
    if (key > tree->value)
    {
        tree->right = RemoveTreap (tree->right, key);
    }
    else if (key < tree->value)
    {
        tree->left  = RemoveTreap (tree->left,  key);
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

            min->right  = RemoveTreap_min (right_sub_tree);
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

void InsertTreap (TreeType* tree, KeyType value)
{
    tree = InsertTreapAVL (tree, value);
}

void Erase (TreeType* tree, KeyType value)
{
    tree = RemoveTreap (tree, value);
}
//----------------------
