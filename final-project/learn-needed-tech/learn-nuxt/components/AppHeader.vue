<template>
  <header>
    <h1>Programmer Jokes</h1>
    <ul>
      <li>
        <nuxt-link to="/">Home</nuxt-link>
        <nuxt-link to="/jokes">Jokes</nuxt-link>
        <nuxt-link to="/about">About</nuxt-link>
      </li>
    </ul>
  </header>
</template>

<script>
export default {
  name: 'AppHeader',
}
</script>

<style>
header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1rem;
  border-bottom: 1px dotted grey;
  background-color: #282d38;
}

header h1 {
  margin-left: 2rem;
  color: #eee;
}

header ul {
  display: flex;
}

header a {
  display: inline-block;
  color: #eee;
  padding: 0.3rem 1rem;
  margin-right: 0.5rem;
}

header > ul > li {
  font-size: 2rem;
}
</style>
