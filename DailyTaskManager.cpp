#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. ABSTRACTION
// TaskBase is an abstract class. It provides a generalized template (abstraction) 
// without showing the complex implementation details.
class TaskBase {
private:
    // 2. ENCAPSULATION
    // 'id' is kept private and can only be accessed through the public getter method.
    int id;

public:
    TaskBase(int taskId) : id(taskId) {}
    virtual ~TaskBase() {}

    int getId() const {
        return id;
    }

    // Pure virtual function makes TaskBase an abstract class.
    // It guarantees that any derived class must implement this method.
    virtual void displayTask() const = 0; 
};

// 3. INHERITANCE
// Task inherits from TaskBase, gaining its properties and establishing an "is-a" relationship.
class Task : public TaskBase {
private:
    // 2. ENCAPSULATION
    // Data fields are private to protect them from unauthorized direct access.
    string title;
    string description;
    bool isCompleted;

public:
    Task(int taskId, string taskTitle, string taskDescription) 
        : TaskBase(taskId) {
        title = taskTitle;
        description = taskDescription;
        isCompleted = false;
    }

    // Public getter/setter methods to provide controlled access to private data
    void setTitle(string newTitle) { title = newTitle; }
    string getTitle() const { return title; }

    void setDescription(string newDesc) { description = newDesc; }
    string getDescription() const { return description; }

    bool getIsCompleted() const { return isCompleted; }

    void markComplete() {
        isCompleted = true;
    }

    // 4. POLYMORPHISM
    // Overriding the base class pure virtual function.
    void displayTask() const override {
        cout << "Task ID: " << getId() << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << (isCompleted ? "Completed" : "Pending") << endl;
        cout << "-----------------------" << endl;
    }
};

class TaskManager {
private:
    // Storing pointers to the base class allows us to store objects of any derived class.
    vector<TaskBase*> tasks;
    int nextId;

public:
    TaskManager() {
        nextId = 1;
    }

    ~TaskManager() {
        // Clean up dynamically allocated memory
        for (TaskBase* task : tasks) {
            delete task;
        }
    }

    void addTask() {
        string title, description;
        cout << "\nEnter Task Title: ";
        getline(cin >> ws, title); // ws consumes leading whitespace
        cout << "Enter Task Description: ";
        getline(cin, description);

        // Creating a Task but storing it as a TaskBase pointer
        TaskBase* newTask = new Task(nextId, title, description);
        tasks.push_back(newTask);
        nextId++;
        
        cout << "Task added successfully!" << endl;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "\nNo tasks available." << endl;
            return;
        }

        cout << "\n--- All Tasks ---" << endl;
        // 4. POLYMORPHISM in action
        // We use base class pointers to call the derived class method.
        // At runtime, the program determines the correct displayTask() to execute.
        for (TaskBase* task : tasks) {
            task->displayTask(); 
        }
    }

    void completeTask() {
        if (tasks.empty()) {
            cout << "\nNo tasks available to complete." << endl;
            return;
        }

        int idToComplete;
        cout << "\nEnter Task ID to mark as complete: ";
        cin >> idToComplete;

        bool found = false;
        for (TaskBase* baseTask : tasks) {
            if (baseTask->getId() == idToComplete) {
                // Since markComplete() is specific to Task, we cast the base pointer back to Task*.
                // This is safe because we know the vector only contains Task objects.
                Task* taskPtr = dynamic_cast<Task*>(baseTask);
                if (taskPtr != nullptr) {
                    taskPtr->markComplete();
                    cout << "Task marked as completed!" << endl;
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) {
            cout << "Task with ID " << idToComplete << " not found." << endl;
        }
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        cout << "\n=== Daily Task Manager ===" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Complete" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                manager.addTask();
                break;
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.completeTask();
                break;
            case 4:
                cout << "Exiting application. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
