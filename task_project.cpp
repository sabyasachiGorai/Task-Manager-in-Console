#include <bits/stdc++.h>
#include <iomanip> // For setw, left
#include <iostream>
#include <string>
using namespace std;

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

void saveToFile(taskNode *&head)
{
    // ofstream fout;
    // fout.open("tasks.txt");
    //     if (head == nullptr)
    // {
    //     fout << "==========================================" << endl;
    //     fout << "|            No Tasks Available          |" << endl;
    //     fout << "==========================================" << endl;
    //     return;
    // }

    // // Find the maximum length of task names
    // int maxNameLength = 9; // Minimum length for "Task Name" header
    // taskNode *temp = head;
    // while (temp != nullptr)
    // {
    //     maxNameLength = max(maxNameLength, (int)temp->task->taskName.length());
    //     temp = temp->next;
    // }

    // // Column widths
    // const int idWidth = 10;
    // const int priorityWidth = 10;
    // int nameWidth = maxNameLength + 2; // Add padding for better visuals

    // // Calculate total table width
    // int tableWidth = idWidth + nameWidth + priorityWidth + 7; // Include borders

    // // Print dynamic border
    // fout << string(tableWidth, '=') << endl;
    // fout << "| " <<  setw(idWidth) << "Task ID"
    //      << "| " << left << setw(nameWidth) << "Task Name"
    //      << "| " << left << setw(priorityWidth) << "Priority" << "|" << endl;
    // fout << string(tableWidth, '=') << endl;

    // // Print tasks dynamically
    // temp = head;
    // while (temp != nullptr)
    // {
    //     fout << "| " << left << setw(idWidth) << temp->task->taskId
    //          << "| " << left << setw(nameWidth) << temp->task->taskName
    //          << "| " << left << setw(priorityWidth) << temp->task->taskPriority << "|" << endl;
    //     temp = temp->next;
    // }

    // // Print dynamic footer
    // fout << string(tableWidth, '=') << endl;
    // fout.close();
}

void saveToFileCSV(taskNode *&head)
{
    ofstream fout;
    fout.open("tasks.txt");

    taskNode *temp = head;
    temp = head;
    while (temp != nullptr)
    {
        fout << temp->task->taskId << ","
             << temp->task->taskName << ","
             << temp->task->taskPriority << endl;
        temp = temp->next;
    }

    fout.close();
}

void fetchFromCSV(taskNode *&head, int &tid_max)
{
    ifstream fin;
    fin.open("tasks.txt");
    if (!fin.is_open())
    {
        cout << "File not Found";
    }
    string line;
    // int tid_max = 0;
    while (getline(fin, line))
    {
        stringstream ss(line);
        int tid, taskPriority;
        string taskName;

        string temp;
        getline(ss, temp, ','); //  extract ID
        tid = stoi(temp);
        tid_max = max(tid, tid_max);

        getline(ss, taskName, ','); // extract name

        getline(ss, temp, ','); //  extract priority
        taskPriority = stoi(temp);

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
    cout<<"Data fetching done."<<endl;
    fin.close();
}

taskNode *find_mid(taskNode *head)
{
    taskNode *slow = head;
    taskNode *fast = head->next;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

taskNode *merge_two_LL(taskNode *head1, taskNode *head2)
{
    Task *dummyTask = new Task("empty", 0, 0);
    taskNode *dummy = new taskNode(dummyTask);
    taskNode *dummyhead = dummy;
    while (head1 != nullptr && head2 != nullptr)
    {
        if (head1->task->taskPriority < head2->task->taskPriority)
        {
            dummy->next = head1;
            head1 = head1->next;
            dummy = dummy->next;
        }
        else
        {
            dummy->next = head2;
            head2 = head2->next;
            dummy = dummy->next;
        }
    }
    if (head1 != nullptr)
    {
        dummy->next = head1;
    }

    if (head2 != nullptr)
    {
        dummy->next = head2;
    }
    return dummyhead->next;
}

taskNode *sortFunction(taskNode *head)
{
    taskNode *middle = find_mid(head);

    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    taskNode *mid = find_mid(head);
    taskNode *lefthead = head, *righthead = mid->next;
    mid->next = nullptr;
    lefthead = sortFunction(lefthead);
    righthead = sortFunction(righthead);
    return merge_two_LL(lefthead, righthead);
}

void sortBYPriority(taskNode *&head)
{
    taskNode *temp = head;
    head = sortFunction(temp);
}

void *taskInput(taskNode *&head, int &tid_max)
{
    cin.ignore();

    static int tid = tid_max;
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
    int tid_max = 0;
    string choice = "0";
    while (x <= 30)
    {
        if (stoi(choice) == -1)
        {
            break;
        }
        cout << "-----------------" << endl;

        cout << "Create Task      --> 1" << endl
             << "Print Task       --> 2" << endl
             << "Delete By ID     --> 3" << endl
             << "Sort By Prority  --> 4" << endl
             << "Save and Exit    --> 5" << endl
             << "Fetch From CSV   --> 6" << endl
             << "Exit             --> -1" << endl
             << "Enter --> ";

        cin >> choice;
        try
        {
            int num = stoi(choice);
            if (num == -1)
            {
                break;
            }
            if (num > -1 && num < 7)
            {
                switch (num)
                {
                case 1:
                    taskInput(head, tid_max);
                    break;
                case 2:
                    printTask(head);
                    break;
                case 3:
                    printTask(head);
                    delete_by_id(head);
                    break;
                case 4:
                    sortBYPriority(head);
                    printTask(head);
                    break;
                case 5:
                    saveToFileCSV(head);
                    choice = "-1";
                    break;
                case 6:
                    fetchFromCSV(head, tid_max);
                    printTask(head);
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