<template>
	<el-footer class="footer">
		<p>
			© {{ year }} ,
			<span @click="unsetNav">
				<nuxt-link to="/contactme">Contact</nuxt-link> ,
				<nuxt-link to="/legal">Legal</nuxt-link>
			</span>
		</p>
	</el-footer>
</template>

<script>
export default {
	computed: {
		year() {
			return new Date().getFullYear()
		},
	},
	methods: {
		unsetNav() {
			this.$store.commit('setActiveNav')
		},
	},
}
</script>

<style>
.footer {
	width: 100%;
	text-align: center;
	position: fixed;
	bottom: 0;
	background-color: rgb(52 208 186 / 32%);
	z-index: 1000000;
	height: 50px !important; /* hacky override */
}
</style>
