// State Management
let tasks = [];
let nextId = 1;

// DOM Elements
const taskForm = document.getElementById('taskForm');
const taskTitleInput = document.getElementById('taskTitle');
const taskDescriptionInput = document.getElementById('taskDescription');
const taskListContainer = document.getElementById('taskList');

// Initial Render
function renderTasks() {
    taskListContainer.innerHTML = '';
    
    if (tasks.length === 0) {
        taskListContainer.innerHTML = '<p style="color: #8d99ae; text-align: center; padding: 20px;">No tasks available. Add one above!</p>';
        return;
    }

    tasks.forEach(task => {
        const isCompleted = task.isCompleted;
        
        const taskCard = document.createElement('div');
        taskCard.className = `task-card ${isCompleted ? 'completed' : 'pending'}`;
        
        taskCard.innerHTML = `
            <div class="task-content">
                <h3>${task.title}</h3>
                <p>${task.description}</p>
                <span class="status-badge ${isCompleted ? 'completed' : 'pending'}">
                    ${isCompleted ? '✓ Completed' : 'Pending'}
                </span>
            </div>
            ${!isCompleted ? '<button class="complete-btn" onclick="markComplete(' + task.id + ')">Mark Complete</button>' : ''}
        `;
        
        taskListContainer.appendChild(taskCard);
    });
}

// Add Task
taskForm.addEventListener('submit', (e) => {
    e.preventDefault();
    
    const title = taskTitleInput.value.trim();
    const description = taskDescriptionInput.value.trim();
    
    if (title && description) {
        // Create new task object
        const newTask = {
            id: nextId++,
            title: title,
            description: description,
            isCompleted: false
        };
        
        // Add to array
        tasks.push(newTask);
        
        // Clear form
        taskForm.reset();
        
        // Re-render
        renderTasks();
    }
});

// Complete Task
window.markComplete = function(taskId) {
    const task = tasks.find(t => t.id === taskId);
    if (task) {
        task.isCompleted = true;
        renderTasks();
    }
};

// Start
renderTasks();
