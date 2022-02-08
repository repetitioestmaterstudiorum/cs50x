<template>
	<el-row :gutter="2" display="block">
		<el-col :md="2" :lg="4" :xl="6"><div class="cutoff"></div></el-col>
		<el-col :md="20" :lg="16" :xl="12">
			<AppHeader />
			<el-main style="overflow: inherit">
				<nuxt />
			</el-main>
			<AppFooter />
		</el-col>
		<el-col :md="2" :lg="4" :xl="6"><div class="cutoff"></div></el-col>
		<el-backtop />
	</el-row>
</template>

<script>
export default {}
</script>

<style>
body {
	font-family: 'Helvetica';
}

.cutoff {
	min-height: 1px;
}

a {
	text-decoration: none;
}
</style>
