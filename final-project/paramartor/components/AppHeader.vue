<template>
	<el-header>
		<el-row>
			<el-col :xs="8" :sm="7" :md="6" :lg="5" :xl="4">
				<nuxt-link to="/">
					<el-image class="logo" :src="'logo.png'"></el-image>
					<span class="logo-text">paramartor</span>
				</nuxt-link>
			</el-col>
			<el-col :xs="16" :sm="17" :md="18" :lg="19" :xl="20">
				<el-menu
					:default-active="activeIndex"
					mode="horizontal"
					@select="handleSelect"
					class="menubar"
				>
					<el-menu-item index="0">
						<nuxt-link to="/">Info</nuxt-link>
					</el-menu-item>
					<el-menu-item index="1"
						><nuxt-link to="/create">Create</nuxt-link>
					</el-menu-item>
				</el-menu>
			</el-col>
		</el-row>
	</el-header>
</template>

<script>
export default {
	name: 'AppHeader',
	data() {
		return {
			activeIndex: '0',
		}
	},
	methods: {
		handleSelect(key, keyPath) {
			console.log('handleSelect', key, keyPath)
		},
	},
}
</script>

<style>
.logo {
	width: 60px;
	height: 60px;
	position: absolute;
	left: -4px;
}

.logo-text {
	color: #25887a;
	text-shadow: 0px 2px 14px #34d0bac7;
	font-size: 1.2rem;
	position: absolute;
	top: 18px;
	left: 58px;
}

.menubar {
	position: absolute;
	right: 0;
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
