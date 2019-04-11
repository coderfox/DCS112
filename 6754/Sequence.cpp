#include <algorithm>
#include "Sequence.h"

using namespace std;

typedef struct list
{
    int data;
    struct list *next;
    list(int num, struct list *p = NULL)
    {
        data = num;
        next = p;
    }
} list;
list *head;
void Sequence::swap(Sequence &seq2)
{
    list *currentPtr = head;
    //list* previousPtr=NULL;
    int array1[msize];
    int array2[seq2.msize];
    int i, j;
    for (i = 0, currentPtr = head; i < msize && currentPtr != NULL; i++, currentPtr = currentPtr->next)
    {
        array1[i] = currentPtr->data;
    }
    for (j = 0; j < seq2.msize; j++)
    {
        array2[j] = seq2.at(j);
    }
    int mark1 = msize;
    int mark2 = seq2.msize;
    clear();
    seq2.clear();
    for (i = 0; i < mark2; i++)
    {
        insert(array2[i]);
    }
    for (j = 0; j < mark1; j++)
    {
        seq2.insert(array1[j]);
    }
}
void Sequence::reverse(int fir, int las)
{
    int array[las - fir];
    int i = 0, j = 0;
    list *currentPtr = head;
    while (i != las)
    { //
        if (i >= fir && i <= las - 1)
        {
            array[j] = currentPtr->data;
            currentPtr = currentPtr->next;
            j++;
            i++;
        }
        else
        {
            i++;
            currentPtr = currentPtr->next;
        }
    }
    i = 0;
    j = las - fir - 1;
    currentPtr = head;
    while (i != las)
    {
        if (i >= fir && i <= las - 1)
        {
            currentPtr->data = array[j];
            currentPtr = currentPtr->next;
            j--;
            i++;
        }
        else
        {
            i++;
            currentPtr = currentPtr->next;
        }
    }
}
void Sequence::reverse()
{
    list *currentPtr = head;
    //list* previousPtr=NULL;
    int array[msize];
    int i;
    for (i = 0, currentPtr = head; i < msize && currentPtr != NULL; i++, currentPtr = currentPtr->next)
    {
        array[i] = currentPtr->data;
    }
    for (i = msize - 1, currentPtr = head; i >= 0 && currentPtr != NULL; i--, currentPtr = currentPtr->next)
    {
        currentPtr->data = array[i];
    }
}
int &Sequence::at(int pos)
{
    int i = 0;
    list *currentPtr = head;
    list *previousPtr = NULL;
    while (i != pos)
    {
        i++;
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
    }
    a = &(currentPtr->data);
    return *a;
}
//void Sequence::
void Sequence::replace(int value1, int value2)
{
    //list* previousPtr=NULL;
    list *currentPtr = head;
    while (currentPtr != NULL)
    {
        if (currentPtr->data == value1)
            currentPtr->data = value2;
        //previousPtr=currentPtr;
        currentPtr = currentPtr->next;
    }
}
void Sequence::clear()
{
    while (head != NULL)
    {
        list *tempPtr = head;
        head = head->next;
        delete tempPtr;
    }
    head = NULL;
    msize = 0;
    mempty = true;
}
Sequence::~Sequence()
{
    clear();
    head = NULL;
}
bool Sequence::find(int value)
{
    if (!empty())
    {
        list *currentPtr = head;
        //list* previousPtr=NULL;
        while (currentPtr != NULL)
        {
            if (currentPtr->data == value)
                return true;
            else
            {
                //previousPtr=currentPtr;
                currentPtr = currentPtr->next;
            }
        }
        return false;
    }
    else
        return false;
}
int Sequence::size()
{
    return msize;
}
bool Sequence::empty()
{
    if (head != NULL)
    {
        mempty = false;
        return mempty;
    }
    else
    {
        mempty = true;
        return mempty;
    }
}
int Sequence::back()
{
    if (!empty())
    {
        list *currentPtr = head;
        list *previousPtr = NULL;
        while (currentPtr != NULL)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        return previousPtr->data;
    }
    return 0;
}
int Sequence::front()
{
    if (!empty())
        return head->data;
    else
        return 0;
}
Sequence::Sequence()
{
    head = NULL;
    a = NULL;
    msize = 0;
    mempty = true;
}

void Sequence::insert(int pos, int value)
{
    list *currentPtr = head;
    list *previousPtr = NULL;
    int i = 0;
    while (i != pos)
    {
        i++;
        previousPtr = currentPtr;
        currentPtr = currentPtr->next;
    }
    list *newPtr = new list(value);
    if (pos == 0)
    {
        head = newPtr;
    }
    else
    {
        newPtr->next = currentPtr;
        previousPtr->next = newPtr;
    }
    msize++;
    mempty = false;
}

void Sequence::insert(int value)
{
    list *currentPtr = head;
    list *previousPtr = NULL;
    if (currentPtr == NULL)
    {
        list *newPtr = new list(value);
        head = newPtr;
    }
    else
    {
        while (currentPtr != NULL)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        list *newPtr = new list(value);
        previousPtr->next = newPtr;
    }
    msize++;
    mempty = false;
}