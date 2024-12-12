A Pproject using C++ specifiaclly OOP and LinkedList data structure:

Project Title:      Task Manager in Console

IDEA:   Develop a program to take task for user as input and save in linkedlist data structure also save the data to a file and if required fetch it from a file

Advancement:     Intially only project name and project id later make it more robust by integrating 
            - duedate 
            # - save task in file fetch from a file if required
            # - priority 
            # - sort accroding to priority
            - view pending task
            - mark tasks as completed
            - etc.

Now Work on:
    # - create the structure of the node
    # - create a task i.e input from the user
    # - delete it by id
    # - print 
    # - proper user input
    # - print in proper table format
Now Work on:
    # - sort them by Id
        --> also can be implemnted by priority queue but implemnted sorting 
        # LL mergesort
        # merge to sorted LL
        # find mid of a LL
    # - save to file  #<-- file  
    # - fetch from file
            # // duplicate tid fix
            # // should i always show by priority
            # // when fetching data getting reversed 
            # // ideas to fix them
            # // due date implement // due date cancelled creation time impplemented in cli duedate is overwhelming
            # // cli improve input handle
                    # tid_max = max(tid, tid_max);


# NEW LEARNINGS
-> pointer in depth
-> sorting
    -> merge two sorted array
    -> merge sort
    -> merge two sorted list
    -> find mid of the list
    -> merge sort in list

-> file
    -> ofstream
    -> ifstream
-> #include <iomanip>
    - setw # https://www.youtube.com/watch?v=SXLwnZG3KPI  <<
    - what left is doing here // done
#include <string>
    string(20, "s")
#include <ctime>
    # time_t
    #         // Convert epoch time to human-readable format
    #     time_t epochTime = static_cast<time_t>(temp->task->creationTime);

    #     struct tm *timeInfo = localtime(&epochTime);
    #     char timeStr[20];
    #     strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo); // Format time as YYYY-MM-DD HH:MM:SS
