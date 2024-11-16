#include <bits/stdc++.h>
using namespace std;
struct taskNode
{
    int taskId = 0;
    string taskName;
    // taskNode *prev; // implemnet later in doubly
    taskNode *next;

    taskNode(string taskName, int taskid)
    {
        this->taskName = taskName;
        next = nullptr;
        this->taskId = taskid;
    }
};

void *taskInput(taskNode *&head)
{
    static int tid = 0;
    tid++;
    string taskName;
    cout << "Enter a Task:";
    cin >> taskName;
    taskNode *newNode = new taskNode(taskName, tid);
    if (head == nullptr)
    {
        head = newNode;
        // return head;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    // return head;
}

taskNode* delete_by_id(taskNode*head){
    int id;
    cout<<"Enter ID to delete:"<<endl;
    cin>>id;
    if(head == nullptr){
        return nullptr;
    }
    if(head->taskId == id){
        taskNode*temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    taskNode *curr = head;
    taskNode *prev = nullptr;
    while(curr->taskId != id){
        prev = curr;
        curr = curr->next;
    }
    taskNode *toDel = curr;
    prev->next = curr->next;
    delete toDel;
    return head;
}
// think about how the task input finction will work
void printTask(taskNode *head)
{
    taskNode *temp = head;
    cout << "-----------------" << endl;
    cout << "[Task id] " << "task" << endl;
    while (temp != nullptr)
    {
        cout << "[" << temp->taskId << "] " << temp->taskName << endl;
        temp = temp->next;
    }
    cout << "-----------------" << endl;
}

int main()
{
    taskNode *head = nullptr;
    // taskNode *t2 = taskInput(t);
    // taskNode *t3 = taskInput(t2);
    // printTask(t3);
    int x = 1;
    int choice;
    while (x <= 10)
    {
        cout << "1. Create Task" << endl
             << "2.Print Task" << endl
             << "3.Delete By ID" << endl
             << "Escape(-1)" << endl;
        cin >> choice;
        if (choice == -1)
        {
            break; // apply condition to check input thing is integer or not
        }
        else if (choice > 3)
        {
            cout << "-----------------" << endl;
            cout << "Invalid Choice" << endl;
            cout << "-----------------" << endl;
        }
        switch (choice)
        {
        case 1:
            taskInput(head);
            break;
        case 2:
            printTask(head);
            break;
        case 3:
            printTask(head);
            delete_by_id(head);
            break;
        case -1:
            break;

        default:
            break;
        }
        x++;
    }

    return 0;
}