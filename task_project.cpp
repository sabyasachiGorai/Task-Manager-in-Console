#include <bits/stdc++.h>
using namespace std;
// try sorting the taskes by there ID
// create a task structure and another task node inside that tasknode structure store task object and next and prev pointer instead of storing everything inside a node of a linkedlist 

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
// function to validate users input in number choice
bool isNumber(const string &str)
{
    if (str.empty())
    {
        return false;
    }
}
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

taskNode *delete_by_id(taskNode *head)
{
    int id;
    cout << "Enter ID to delete:" << endl;
    cin >> id;
    if (head == nullptr)
    {
        return nullptr;
    }
    if (head->taskId == id)
    {
        taskNode *temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    taskNode *curr = head;
    taskNode *prev = nullptr;
    while (curr->taskId != id)
    {
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
    string choice;
    while (x <= 10)
    {
        cout << "1. Create Task" << endl
             << "2.Print Task" << endl
             << "3.Delete By ID" << endl
             << "Escape(-1)" << endl;
        cin >> choice;
        try
        {
            int num = stoi(choice);
            if (num == -1)
            {
                break;
            }
            if (num > -1 && num <= 3)
            {
                switch (num)
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
                default:
                    break;
                }
            }
            else
            {
                cout << "-----------------" << endl;
                cout << "Invalid Choice" << endl;
                cout << "-----------------" << endl;
            }
        }
        catch (...)
        {
            cout << "-----------------" << endl;
            cout << "Invalid Choice" << endl;
            cout << "-----------------" << endl;
        }

        x++;
    }

    return 0;
}