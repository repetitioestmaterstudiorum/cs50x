<template>
  <div>
    <h2>Jokes</h2>
    <button @click="onClick">load new jokes...</button>
    <Joke
      v-for="joke in jokes"
      v-bind:key="joke.id"
      v-bind:id="joke.id"
      :joke="joke.joke"
    />
  </div>
</template>

<script>
import axios from 'axios'

export default {
  data() {
    return {
      jokes: [],
    }
  },
  created() {
    this.loadJokes()
  },
  methods: {
    async loadJokes() {
      try {
        const jokesRes = await axios.get(
          'https://v2.jokeapi.dev/joke/programming?type=single&amount=5'
        )
        this.jokes = jokesRes.data?.jokes
      } catch (err) {
        console.error(err)
      }
    },
    onClick() {
      this.loadJokes()
    },
  },
  head() {
    return {
      title: 'Programmer Jokes',
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
