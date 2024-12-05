#include <bits/stdc++.h>
#include <iostream>
#include <iomanip> // For setw, left
#include <string>
#include <ctime>
using namespace std;

struct Task
{
    int taskId = 0;
    int taskPriority = 0;
    int creationTime;
    string taskName;
    Task(string taskName, int taskid, int taskPriority, int creationTime)
    {
        this->taskName = taskName;
        this->taskId = taskid;
        this->taskPriority = taskPriority;
        this->creationTime = creationTime;
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
             << temp->task->taskPriority << ","
             << temp->task->creationTime << endl;
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
    while (getline(fin, line))
    {
        stringstream ss(line);
        int tid, taskPriority, time;
        string taskName;

        string temp;
        getline(ss, temp, ','); //  extract ID
        tid = stoi(temp);
        tid_max = max(tid, tid_max);

        getline(ss, taskName, ','); // extract name

        getline(ss, temp, ','); //  extract priority
        taskPriority = stoi(temp);

        getline(ss, temp, ','); // extract time
        time = stoi(temp);

        Task *tocopy = new Task(taskName, tid, taskPriority, time);
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
    cout << "Data fetching done." << endl;
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

taskNode *merge_two_LL(taskNode *head1, taskNode *head2, bool var)
{
    Task *dummyTask = new Task("empty", 0, 0, 0);
    taskNode *dummy = new taskNode(dummyTask);
    taskNode *dummyhead = dummy;
    int a, b;

    while (head1 != nullptr && head2 != nullptr)
    {
        if (var == true)
        {
            a = head1->task->creationTime;
            b = head2->task->creationTime;
        }
        else
        {
            a = head1->task->taskPriority;
            b = head2->task->taskPriority;
        }
        if (a < b)
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

taskNode *sortFunction(taskNode *head, bool var)
{

    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }
    taskNode *mid = find_mid(head);
    taskNode *lefthead = head, *righthead = mid->next;
    mid->next = nullptr;
    lefthead = sortFunction(lefthead, var);
    righthead = sortFunction(righthead, var);
    return merge_two_LL(lefthead, righthead, var);
}

void sortBYPriority(taskNode *&head)
{
    taskNode *temp = head;
    // var = false; // for sort by priority
    if (temp != nullptr)
        head = sortFunction(temp, false);
}

void sortBYCT(taskNode *&head)
{
    taskNode *temp = head;
    if (temp != nullptr)
    {
        // var = true; // for sort by creation time
        head = sortFunction(temp, true);
    }
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
    time_t currentTime = time(0);
    Task *tocopy = new Task(taskName, tid, taskPriority, currentTime);
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
    cout << "Enter ID to Mark as done and delete: --> ";
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
    const int timeWidth = 20;          // Width for "Creation Time" column

    // Calculate total table width
    int tableWidth = idWidth + nameWidth + priorityWidth + timeWidth + 9; // Include borders

    // Print dynamic border
    cout << string(tableWidth, '=') << endl;
    cout << "| " << left << setw(idWidth) << "Task ID"
         << "| " << left << setw(nameWidth) << "Task Name"
         << "| " << left << setw(priorityWidth) << "Priority"
         << "| " << left << setw(timeWidth) << "Creation Time" << "|" << endl;
    cout << string(tableWidth, '=') << endl;

    // Print tasks dynamically
    temp = head;
    while (temp != nullptr)
    {
        // Convert epoch time to human-readable format
        time_t epochTime = static_cast<time_t>(temp->task->creationTime);

        struct tm *timeInfo = localtime(&epochTime);
        char timeStr[20];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo); // Format time as YYYY-MM-DD HH:MM:SS

        // if required time only
        //  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", timeInfo);

        // Print task data with creation time
        cout << "| " << left << setw(idWidth) << temp->task->taskId
             << "| " << left << setw(nameWidth) << temp->task->taskName
             << "| " << left << setw(priorityWidth) << temp->task->taskPriority
             << "| " << left << setw(timeWidth) << timeStr << "|" << endl;

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
        // system("cls"); // For Windows

        cout << string(40, '-') << endl;            // Divider
        cout << setw(20) << "Task Manager" << endl; // Title
        cout << string(40, '-') << endl;            // Divider

        cout << "1. Create Task" << endl
             << "2. Print Task" << endl
             << "3. Done By ID" << endl
             << "4. Sort By Cr Time" << endl
             << "5. Save and Exit" << endl
             << "6. Fetch From CSV" << endl
             << "(-1) Exit" << endl
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
                    sortBYPriority(head);
                    system("cls");
                    printTask(head);
                    break;
                case 3:
                    system("cls");
                    printTask(head);
                    delete_by_id(head);
                    break;
                case 4:
                    system("cls");
                    sortBYCT(head);
                    printTask(head);
                    break;
                case 5:
                    saveToFileCSV(head);
                    choice = "-1";
                    break;
                case 6:
                    system("cls");
                    fetchFromCSV(head, tid_max);
                    sortBYPriority(head);
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