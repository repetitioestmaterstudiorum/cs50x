<template>
	<div id="create">
		<h1>Create</h1>
		<p>
			Move the sliders and see what happens! If you want, you can download an image of your
			art at any time.
		</p>
		<div v-loading="loading" class="controls">
			<el-button type="info" @click="download">Download</el-button>
		</div>
	</div>
</template>

<script>
import isEmpty from 'lodash.isempty'

export default {
	data() {
		// could be saved in vuex if needed elsewhere someday
		return {
			p5: {}, // p5 library code
			c: {}, // p5 canvas reference
			loading: true,
			cEmpty: true,
			params: {}, // drawing parameters
		}
	},
	async mounted() {
		if (process.client) {
			// import the library and store it in this component's instance
			const { default: P5 } = await import('p5')
			this.p5 = P5

			// start drawing
			this.draw()

			this.canvasLifecycle()
		}
	},
	methods: {
		draw() {
			// delete previous canvases, if any
			this.remove()

			// specify canvas dimensions
			// get client div width or default value
			this.params.width = document.querySelector('#create').clientWidth || 600
			// golden ratio height based on longer side width
			this.params.height = this.params.width / ((1 + Math.sqrt(5)) / 2)

			// define what to draw
			const sketch = s => {
				s.setup = () => {
					const cnv = s.createCanvas(this.params.width, this.params.height)
					s.pixelDensity(2)
					s.background(240)
					s.noLoop()
					s.noFill()
					cnv.id('paramartorCnv')
				}

				s.draw = () => {
					// heavily inspired by https://natureofcode.com/book/chapter-8-fractals/
					function drawCircle(x, y, radius) {
						s.ellipse(x, y, radius, radius)
						if (radius > 16) {
							drawCircle(x + radius / 2, y, radius / 2)
							drawCircle(x - radius / 2, y, radius / 2)
							// drawCircle(x, y + radius / 2, radius / 2)
							// drawCircle(x, y - radius / 2, radius / 2)
						}
					}
					drawCircle(this.params.width / 2, this.params.height / 2, 400)
				}
			}
			// draw
			this.c = new this.p5(sketch)
		},
		download() {
			if (!isEmpty(this.c)) this.c.saveCanvas(`paramartor-${Date.now()}`)
		},
		remove() {
			if (!isEmpty(this.c)) this.c.remove()
		},
		async canvasLifecycle() {
			const source = document.querySelector('#paramartorCnv')
			const destination = document.querySelector('#create')
			if (source && destination) {
				// move canvas into component (it gets appended at the end of main by default)
				destination.appendChild(source)

				// remove the loading symbol
				this.loading = false
			} else {
				await new Promise(resolve => setTimeout(() => resolve(), 10)) // wait 10ms
				this.canvasLifecycle() // try to move it again
			}
		},
	},
}
</script>

<style>
.controls {
	padding-bottom: 1rem;
}

#paramartorCnv {
	padding-bottom: 1rem;
}
</style>
