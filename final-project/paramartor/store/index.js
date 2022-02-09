export const state = () => ({
	nav: {
		activeIndex: '',
	},
})

export const mutations = {
	setActiveNav(state, index = '') {
		state.nav.activeIndex = index
	},
}
