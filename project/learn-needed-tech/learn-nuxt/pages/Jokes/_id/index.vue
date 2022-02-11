<template>
  <div>
    <p>
      <i>joke ID {{ $route.params.id }}</i>
    </p>

    <h2>
      {{ joke }}
    </h2>

    <nuxt-link to="/jokes"><button>Back to jokes</button></nuxt-link>

    <br /><br />

    <table>
      <thead>
        <tr>
          <th>flag</th>
          <th>indication</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="(value, key, index) in jokeFlags" v-bind:key="index">
          <td>{{ capitalize(key) }}</td>
          <td>{{ value }}</td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  methods: {
    capitalize(word) {
      return word.charAt(0).toUpperCase() + word.slice(1, word.length)
    },
  },
  data() {
    return {
      joke: '',
      jokeFlags: {},
    }
  },
  async created() {
    console.log('this.$route :>> ', this.$route.path)
    const id = this.$route.params.id
    const jokeRes = await axios.get(
      `https://v2.jokeapi.dev/joke/programming?idRange=${id}-${id}`
    )
    this.joke = jokeRes.data.joke
    this.jokeFlags = jokeRes.data.flags
  },
}
</script>

<style></style>
