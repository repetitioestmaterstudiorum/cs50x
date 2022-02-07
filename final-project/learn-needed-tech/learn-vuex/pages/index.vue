<template>
  <main>
    <h1>Tasks</h1>
    <p>Create a list of tasks</p>

    <div class="create-new">
      <input
        type="text"
        v-model="newTask"
        placeholder="enter a new task"
        @keypress.enter="addTask"
      />
      <button @click="addTask">add</button>
    </div>

    <div class="tasks">
      <Task
        v-for="(task, i) in $store.state.tasks"
        v-bind:key="i"
        v-bind:task="task"
      />
    </div>
  </main>
</template>

<script>
export default {
  data() {
    return {
      newTask: '',
    }
  },
  methods: {
    addTask() {
      if (this.newTask) {
        this.$store.commit('addTask', this.newTask)
        this.newTask = ''
      }
    },
  },
}
</script>
