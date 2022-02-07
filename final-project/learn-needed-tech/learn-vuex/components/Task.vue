<template>
  <div v-bind:class="`task ${task.done && 'is-complete'}`">
    <div class="content">
      {{ task.content }}
      <button @click="toggleTask">{{ task.done ? 'undo' : 'done' }}</button>
      <button @click="removeTask" class="delete">delete</button>
    </div>
  </div>
</template>

<script>
export default {
  props: ['task'],
  methods: {
    toggleTask(task) {
      this.$store.commit('toggleTask', this.task)
    },
    removeTask(task) {
      this.$store.commit('removeTask', this.task)
    },
  },
}
</script>

<style></style>
