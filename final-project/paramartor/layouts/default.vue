<template>
	<div>
		<el-row :gutter="2" display="block">
			<el-col :md="2" :lg="4" :xl="6"><div class="cutoff"></div></el-col>
			<el-col :md="20" :lg="16" :xl="12">
				<AppHeader />
				<el-main>
					<nuxt />
				</el-main>
			</el-col>
			<el-col :md="2" :lg="4" :xl="6"><div class="cutoff"></div></el-col>
		</el-row>
		<el-backtop />
		<AppFooter />
	</div>
</template>

<script>
export default {
	mounted() {
		this.$store.commit('setActiveNav', window.location.pathname)
	},
}
</script>

<style>
body {
	font-family: 'Helvetica';
	min-height: 100vh;
	margin: 0;
}

.cutoff {
	min-height: 1px;
}

.el-main {
	margin-bottom: 35px;
	overflow: inherit;
}

.el-backtop {
	right: 30px !important;
	bottom: 70px !important;
}

p,
li {
	font-weight: 200;
}

strong {
	font-weight: 400;
}

h1,
h2,
h3 {
	font-weight: 400;
}
h1 {
	font-size: 1.3rem;
}
h2 {
	font-size: 1.2rem;
}
h3 {
	font-size: 1.1rem;
}

a {
	text-decoration: none;
	border-bottom: 1px dashed #08201c;
}
a:visited {
	color: inherit;
}
</style>
