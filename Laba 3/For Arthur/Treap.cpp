#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int elem_t;

struct Treap {
    elem_t value;
    elem_t priority;
    int number;
    
    Treap* prev;
    Treap* left;
    Treap* right;
};

struct Pair {
    Treap* first;
    Treap* second;
};

Pair Split  (Treap* treap, int k);
Treap* Merge  (Treap* treap_1, Treap* treap_2);
Treap* InsertTreapTreap (Treap* treap, Treap* node);
Treap* RemoveTreapTreap (Treap* treap, Treap* node);
Treap* RemoveLeft (Treap* treap);

Treap* TreapConstruct  (Treap* array, Treap* true_array[], int size);
int BuildTree (Treap* treap, elem_t** array);
int Comparator (const void* first, const void* second);

void LogicalLogsMaker (Treap* treap);
void PrintSubTree     (Treap* treap, FILE* GraphicLogs);


int main ()
{
    
    int N = 0;
    
    scanf ("%d", &N);
    Treap array[N] = {};
    for (int i = 0; i < N; i++)
    {
        scanf ("%d %d", &array[i].value, &array[i].priority);
        array[i].number = i + 1;
    }
    
    Treap* treap = TreapConstruct (array, true_array, N);
    
    printf ("YES\n");
    for (int i = 1; i <= N; i++)
    {
        printf ("%d ", (true_array[i]->prev == NULL) ? 0 : true_array[i]->prev->number);
        printf ("%d ", (true_array[i]->left == NULL) ? 0 : true_array[i]->left->number);
        printf ("%d", (true_array[i]->right == NULL) ? 0 : true_array[i]->right->number);
        printf ("\n");
    }
    
    return 0;
}



// Functions
Pair Split (Treap* treap, int k)
{
    
    if (treap == NULL)
    {
        return {NULL, NULL};   
    }
    
    if (treap->value < k)
    {
        Pair result = Split (treap->right, k);
        treap->right = result.first;
        
        return  {treap, result.second};
    }
    else
    {
        Pair result = Split (treap->left, k);
        treap->left = result.second;
        
        return {result.first, treap};
    }
}

Treap* Merge (Treap* treap_1, Treap* treap_2)
{
    if (treap_1 == NULL)
    {
        return treap_2;
    }
    if (treap_2 == NULL)
    {
        return treap_1;
    }
    if (treap_1->priority < treap_2->priority)
    {
        treap_1->right = Merge (treap_1->right, treap_2);
        treap_1->right->prev = treap_1;
        return treap_1;
    }
    else
    {
        treap_2->left = Merge (treap_1, treap_2->left);
        treap_2->left->prev = treap_2;
        return treap_2;
    }
}

Treap* InsertTreap (Treap* treap, Treap* node)
{
    Pair result = Split (treap, node->value);
    result.first = Merge (result.first, node);
    treap = Merge (result.first, result.second);
    
    return treap;
}

Treap* RemoveTreap (Treap* treap, Treap* node)
{
    Pair result = Split (treap, node->value);
    result.second = RemoveLeft (result.second);
    treap = Merge (result.first, result.second);
    
    return treap;
}

Treap* RemoveLeft (Treap* treap)
{
    Treap* temp = treap;
    
    while (temp->left->left != NULL)
    {
        temp = temp->left;
    }
    
    temp->left = NULL;
    
    return temp;
}
//----------



// Construct
Treap* TreapConstruct (Treap* array, Treap* true_array[], int size)
{
    qsort (array, size, sizeof(Treap), Comparator);
    
    true_array[array[0].number] = &array[0];
    
    for (int i = 1; i < size; i++)
    {
        InsertTreap (array, &array[i]);
        true_array[array[i].number] = &array[i];
    }
    
    return array;
}

int Comparator (const void* first, const void* second)
{    
    return ((Treap*) first)->priority - ((Treap*) second)->priority;
}
//----------
