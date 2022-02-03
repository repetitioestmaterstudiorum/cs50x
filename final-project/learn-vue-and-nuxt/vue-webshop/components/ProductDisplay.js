// source: https://github.com/Code-Pop/Intro-to-Vue-3

app.component('product-display', {
	props: {
		premium: {
			type: Boolean,
			required: true,
		},
	},
	template:
		/*html*/
		`<div class="product-display">
    	<div class="product-container">
      	<div class="product-image">
        <img v-bind:src="image">
      	</div>
      	<div class="product-info">
        <h1>{{ title }}</h1>

        <p v-if="inStock > 10">In Stock</p>
        <p v-else-if="inStock > 0">Only {{inStock}} left!</p>
        <p v-else>Out of Stock</p>

        <p>Shipping: {{ shipping }}</p>

        <div 
          v-for="(variant, index) in variants" 
          :key="variant.id" 
          @mouseover="updateVariant(index)" 
          class="color-circle" 
          :style="{ backgroundColor: variant.color }">
         </div>
        
		<div class="cart-buttons">
        <button 
		class="button" 
		:class="{ disabledButton: !inStock }" 
		:disabled="!inStock" 
		v-on:click="addToCart">
		Add to Cart
        </button>
		
        <button 
        class="button" 
        :class="{ disabledButton: !inStock }" 
        :disabled="!inStock" 
        @click="removeFromCart">
        Remove Item
		</button>
		</div>

		<review-list v-if="reviews.length" :reviews="reviews"></review-list>
		<review-form @review-submitted="addReview"></review-form>
      </div>
    </div>
  </div>`,
	data() {
		return {
			product: 'Bananas',
			brand: 'Fruitiana',
			selectedVariant: 1,
			variants: [
				{
					id: 2234,
					color: 'green',
					image: './assets/images/green-banana.jpeg',
					quantity: 50,
				},
				{
					id: 2235,
					color: 'yellow',
					image: './assets/images/yellow-banana.jpeg',
					quantity: 0,
				},
				{
					id: 2236,
					color: 'gray',
					image: './assets/images/expensive-banana.jpeg',
					quantity: 1,
				},
			],
			reviews: [],
		}
	},
	methods: {
		addToCart() {
			this.$emit('add-to-cart', this.variants[this.selectedVariant].id)
		},
		removeFromCart() {
			this.$emit('remove-from-cart', this.variants[this.selectedVariant].id)
		},
		updateVariant(index) {
			this.selectedVariant = index
		},
		addReview(productReview) {
			this.reviews.push(productReview)
		},
	},
	computed: {
		title() {
			return this.brand + "'s " + this.product
		},
		image() {
			return this.variants[this.selectedVariant].image
		},
		inStock() {
			return this.variants[this.selectedVariant].quantity
		},
		shipping() {
			if (this.premium) {
				return 'Free'
			}
			return 7.5
		},
	},
})
