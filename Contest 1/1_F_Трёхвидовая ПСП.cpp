#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_CAPACITY 1
#define POISON -1

struct MyStack
{
  size_t size;
  size_t capacity;
  char* array;
};

MyStack* StackConstruct (size_t capacity);
MyStack* StackDestruct  (MyStack* stk);
void StackExpansion (MyStack* stk);

void StackFree (MyStack* stk);

void StackPush (MyStack* stk, char elem);
char StackPop  (MyStack* stk);
char StackTop  (MyStack* stk);

bool SequenceCorrect (const int parentheses[], const int num_parentheses_types, MyStack* stk, char* sequence);
int WichType (const int parentheses[], const int num_parentheses_types, char elem);

int main ()
{
  const size_t start_size = 100000;
  MyStack* stk = StackConstruct (start_size);
  
  const int num_parentheses_types = 6;
  const int parentheses[num_parentheses_types] = {'(', '[', '{', ')', ']', '}'};
  
  const size_t max_size = 100000;
  char* sequence = (char*)calloc(max_size, sizeof(char));
  
  scanf("%s", sequence);
  
  (SequenceCorrect(parentheses, num_parentheses_types, stk, sequence)) ? printf("YES") : printf("NO");

  stk = StackDestruct (stk);
  return 0;
}

bool SequenceCorrect (const int parentheses[], const int num_parentheses_types, MyStack* stk, char* sequence)
{
  const int two = 2;
  int type = 0;
  char pair = 0;
  
  for (int i = 0; sequence[i] != '\0'; i++){
    type = WichType(parentheses, num_parentheses_types, sequence[i]);
    if (type < num_parentheses_types / two) {
      StackPush(stk, sequence[i]);
    }
    else {
      pair = StackPop(stk);
      if (pair != parentheses[type - num_parentheses_types / two]) {
        return false;
      }
    }
  }
  if ((stk->array[0]) != POISON) {
  return false;
  }

  return true;
}

int WichType (const int parentheses[], const int num_parentheses_types, char elem) {
  for (int i = 0; i < num_parentheses_types; i++) {
    if (elem == parentheses[i]) {
      return i;
    }
  }
}

MyStack* StackConstruct (size_t capacity) {
  MyStack* stk = (MyStack*) calloc (1, sizeof(MyStack));
  *stk = {0, capacity, NULL};

  stk->array = (char*) calloc (capacity, sizeof(char));
  StackFree (stk);

  return stk;
}

MyStack* StackDestruct (MyStack* stk) {
  free (stk->array);
  free (stk);

  return NULL;
}

void StackFree (MyStack* stk) {
  for (int i = 0; i < stk->capacity; i++) {
    stk->array[i] = POISON;
  }
  stk->size = 0;
}

void StackPush (MyStack* stk, char elem) {   
  if (stk->size != 0 && stk->size != stk->capacity-1) {
    stk->size++;
  } else if (stk->size == 0 && (stk->array[0]) != POISON) {
    stk->size++;
  } else if (stk->size == stk->capacity-1) {
    StackExpansion(stk);
    stk->size++;
  }
  stk->array[stk->size] = elem;
}

char StackPop (MyStack* stk) {
  char top = stk->array[stk->size];
  stk->array[stk->size] = POISON;
  if (stk->size != 0) {
    stk->size--;
  }

  return top;
}

char StackTop (MyStack* stk) {
  char top = stk->array[stk->size];

  return top;
}

void StackExpansion (MyStack* stk) {
  const int expansion_coef = 2;
  stk->array = (char*) realloc (stk->array, expansion_coef*(stk->capacity)*sizeof(char));

  size_t new_size = expansion_coef*stk->capacity;
  for (int i = stk->capacity; i < new_size; i++) {
    stk->array[i] = POISON;
  }
  
  stk->capacity = new_size;
}
