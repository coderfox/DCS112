#include <bits/stdc++.h>
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
ListNode *mergeKLists(vector<ListNode *> &lists)
{
    ListNode *tmp1 = lists[0];
    ListNode *tmp2 = lists[1];
    ListNode *tmp3 = lists[2];

    ListNode *target;
    ListNode *head = new ListNode(0);
    ListNode *tmp = new ListNode(0);
    target = head;

    while (tmp1 || tmp2 || tmp3)
    {
        if (tmp1 && (tmp1->val <= tmp2.val && tmp1->val <= tmp3->val))
        {
            head->val = tmp1->val;
            tmp1 = tmp1->next;
        }
        else if (tmp2 && (tmp2->val <= tmp1->val && tmp2->val <= tmp3->val))
        {
            head->val = tmp2->val;
            tmp2 = tmp2->next;
        }
        else if (tmp3)
        {
            head->val = tmp3->val;
            tmp3 = tmp3->next;
        }

        if (tmp1 != nullptr && tmp2 != nullptr && tmp3 != nullptr)
        {
            head->next = tmp;
            head = tmp;
            tmp = new ListNode(0);
        }
        else
        {
            head->next = nullptr;
            delete tmp;
        }
    }

    return target;
}

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