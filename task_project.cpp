#include <bits/stdc++.h>
#include <iomanip> // For setw, left
#include <iostream>
#include <string>
using namespace std;
// try sorting the taskes by there priority

struct Task
{
    int taskId = 0;
    int taskPriority = 0;
    string taskName;
    Task(string taskName, int taskid, int taskPriority)
    {
        this->taskName = taskName;
        this->taskId = taskid;
        this->taskPriority = taskPriority;
    }
};
struct taskNode
{
    taskNode *prev;
    Task *task;
    taskNode *next;
    taskNode(Task *task)
    {
        this->task = task;
        // prev = nullptr;
        next = nullptr;
    }
};

void *taskInput(taskNode *&head)
{
    cin.ignore();

    static int tid = 0;
    tid++;

    string taskName;
    int taskPriority;
    cout << "-----------------" << endl;
    cout << "Enter Task Name: ";
    getline(cin, taskName);

    cout << "Enter Priority (0-9): ";
    cin >> taskPriority;

    Task *tocopy = new Task(taskName, tid, taskPriority);
    taskNode *newNode = new taskNode(tocopy);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

void delete_by_id(taskNode *&head)
{

    int id;
    cout << "Enter ID to delete: --> ";
    cin >> id;
    if (head == nullptr)
    {
        cout << "Task list is Empty !!" << endl;
        return;
    }
    if (head->task->taskId == id)
    {
        taskNode *temp = head;
        head = head->next;
        delete temp->task;
        delete temp;
        if (head == nullptr)
        {
            cout << "All task deleted" << endl;
        }
        return;
    }
    taskNode *curr = head;
    taskNode *prev = nullptr;
    while (curr != nullptr && curr->task->taskId != id)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == nullptr)
    {
        cout << "Id " << id << " not found";
    }
    taskNode *toDel = curr;
    prev->next = curr->next;
    delete toDel->task;
    delete toDel;
}

void printTask(taskNode *head)
{
    if (head == nullptr)
    {
        cout << "==========================================" << endl;
        cout << "|            No Tasks Available          |" << endl;
        cout << "==========================================" << endl;
        return;
    }

    // Find the maximum length of task names
    int maxNameLength = 9; // Minimum length for "Task Name" header
    taskNode *temp = head;
    while (temp != nullptr)
    {
        maxNameLength = max(maxNameLength, (int)temp->task->taskName.length());
        temp = temp->next;
    }

    // Column widths
    const int idWidth = 10;
    const int priorityWidth = 10;
    int nameWidth = maxNameLength + 2; // Add padding for better visuals

    // Calculate total table width
    int tableWidth = idWidth + nameWidth + priorityWidth + 7; // Include borders

    // Print dynamic border
    cout << string(tableWidth, '=') << endl;
    cout << "| " << left << setw(idWidth) << "Task ID"
         << "| " << left << setw(nameWidth) << "Task Name"
         << "| " << left << setw(priorityWidth) << "Priority" << "|" << endl;
    cout << string(tableWidth, '=') << endl;

    // Print tasks dynamically
    temp = head;
    while (temp != nullptr)
    {
        cout << "| " << left << setw(idWidth) << temp->task->taskId
             << "| " << left << setw(nameWidth) << temp->task->taskName
             << "| " << left << setw(priorityWidth) << temp->task->taskPriority << "|" << endl;
        temp = temp->next;
    }

    // Print dynamic footer
    cout << string(tableWidth, '=') << endl;
}

int main()
{
    taskNode *head = nullptr;
    int x = 1;
    string choice;
    while (x <= 30)
    {
        cout << "-----------------" << endl;

        cout << "Create Task   --> 1" << endl
             << "Print Task    --> 2" << endl
             << "Delete By ID  --> 3" << endl
             << "Escape (x_x) --> -1" << endl
             << "Enter --> ";

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