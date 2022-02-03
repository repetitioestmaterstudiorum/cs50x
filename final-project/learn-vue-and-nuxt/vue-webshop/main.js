// source: https://github.com/Code-Pop/Intro-to-Vue-3

const app = Vue.createApp({
	data() {
		return {
			cart: [],
			premium: false,
		}
	},
	methods: {
		updateCart(id) {
			this.cart.push(id)
			if (this.cart.length > 3) this.premium = true
		},
		removeById(id) {
			const index = this.cart.indexOf(id)
			if (index > -1) {
				this.cart.splice(index, 1)
			}
		},
	},
})
