<template>
	<el-header class="header">
		<el-row>
			<el-col :xs="8" :sm="7" :md="6" :lg="5" :xl="4">
				<div @click="handleSelect('/')">
					<nuxt-link to="/">
						<img class="logo" src="~/assets/logo.png" />
						<span class="logo-text">paramartor</span>
					</nuxt-link>
				</div>
			</el-col>
			<el-col :xs="16" :sm="17" :md="18" :lg="19" :xl="20">
				<el-menu
					:default-active="$store.state.nav.activeIndex"
					mode="horizontal"
					@select="handleSelect"
					class="menubar"
				>
					<el-menu-item index="/"> Info </el-menu-item>
					<el-menu-item index="/create">Create </el-menu-item>
				</el-menu>
			</el-col>
		</el-row>
	</el-header>
</template>

<script>
export default {
	methods: {
		handleSelect(key) {
			this.$store.commit('setActiveNav', key)
			this.$router.push(key)
		},
	},
}
</script>

<style>
.header {
	padding-top: 7px;
}
.header a {
	border-bottom: none;
}

.logo {
	width: 49px;
	height: 49px;
	position: absolute;
	left: -4px;
	top: 7px;
}

.logo-text {
	color: #25887a;
	text-shadow: 0px 2px 14px #34d0bac7;
	font-size: 1.2rem;
	position: absolute;
	top: 18px;
	left: 55px;
}

.menubar {
	position: absolute;
	right: 0;
	top: -2px;
}

/* hacky element ui overrides */
.el-menu--horizontal > .el-menu-item.is-active,
.el-menu-item.is-active {
	border-bottom: 2px solid #34d0ba;
}

.el-menu--horizontal > .el-menu-item {
	height: 50px;
}

.el-menu-item {
	font-size: 14px;
	padding: 0 12px;
}
</style>
