<template>
  <div>
    <h2>Welcome to Programmers Jokes!</h2>
    <nuxt-link v-bind:to="'/jokes'"><button>Go to jokes!</button></nuxt-link>
  </div>
</template>

<script>
export default {
  head() {
    return {
      title: 'Welcome to Programmer Jokes',
      meta: [
        {
          hid: 'description',
          name: 'description',
          content: 'Random programmer jokes',
        },
      ],
    }
  },
}
</script>

<style></style>
