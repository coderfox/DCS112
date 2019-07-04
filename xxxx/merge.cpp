#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Input:
 * 1->4->5->nullptr
 * 1->3->4->nullptr
 * 2->6->nullptr
 *
 * Output:
 * 1->1->2->3->4->4->5->6->nullptr
 *
 */
#include <climits>

ListNode *mergeKLists(vector<ListNode *> &lists)
{

    ListNode *res = nullptr;
    vector<int> nodes;

    for (auto &list : lists)
    {
        while (list)
        {
            nodes.push_back(list->val);

            list = list->next;
        }
    }
    sort(nodes.begin(), nodes.end());

    for (auto i = nodes.rbegin(); i != nodes.rend(); i++)
    {
        ListNode *tmp = new ListNode(*i);
        tmp->next = res;
        res = tmp;
    }

    return res;
}

// Code below for testing only
void printList(ListNode *head)
{
    while (head)
    {
        cout << head->val << "->";
        head = head->next;
    }

    cout << "nullptr" << endl;
}

int main()
{
    ListNode *listA[] = {new ListNode(1), new ListNode(4), new ListNode(5)};
    ListNode *listB[] = {new ListNode(1), new ListNode(3), new ListNode(4)};
    ListNode *listC[] = {new ListNode(2), new ListNode(6)};
    listA[0]->next = listA[1];
    listA[1]->next = listA[2];

    listB[0]->next = listB[1];
    listB[1]->next = listB[2];

    listC[0]->next = listC[1];

    vector<ListNode *> lists = {listA[0], listB[0], listC[0]};
    printList(mergeKLists(lists));
    return 0;
}