<template>
	<p @click="setNav('/create')">
		<nuxt-link to="/create">Create your own art!</nuxt-link>
	</p>
</template>

<script>
export default {
	name: 'CreateLink',
	methods: {
		setNav(link) {
			this.$store.commit('setActiveNav', link)
		},
	},
}
</script>

<style></style>
