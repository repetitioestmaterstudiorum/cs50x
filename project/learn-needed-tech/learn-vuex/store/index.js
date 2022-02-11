export const state = () => ({
  tasks: [
    {
      content: 'create a task',
      done: false,
    },
    {
      content: 'start up the app',
      done: true,
    },
  ],
})

export const mutations = {
  addTask(state, newTask) {
    state.tasks = [{ content: newTask, done: false }, ...state.tasks]
  },
  removeTask(state, task) {
    state.tasks.splice(state.tasks.indexOf(task), 1)
  },
  toggleTask(state, task) {
    task.done = !task.done
  },
}
