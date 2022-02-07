<template>
  <div>
    <AppHeader />
    <main>
      <nuxt />
    </main>
  </div>
</template>

<script>
import AppHeader from '../components/AppHeader.vue'

export default {
  components: {
    AppHeader,
  },
}
</script>

<style>
/* inspired by https://github.com/setetres/evenbettermotherfuckingwebsite/blob/master/index.html */
body {
  margin: 0 auto;
  background: #f2f2f2;
  color: #444444;
  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica,
    Arial, sans-serif;
  font-size: 16px;
  line-height: 1.8;
  text-shadow: 0 1px 0 #ffffff;
}

main {
  margin: 0 2rem;
}

a {
  color: #444444;
  text-decoration: none;
}

ul {
  list-style: none;
}

table {
  text-align: center;
}
</style>
