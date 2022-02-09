<template>
	<div id="create">
		<h1>Create your own art</h1>
		<p>Change the parameters and see what happens! You can download your work anytime.</p>
		<div class="controls" v-loading="loading">
			<div class="pr-10">
				<el-button @click="reset" size="small" type="warning" plain>Reset</el-button>
			</div>
			<div class="aligh-items-center pr-10">
				<span class="pr-4">Background: </span>
				<el-color-picker v-model="params.bgColor" size="small"></el-color-picker>
			</div>
			<div class="aligh-items-center pr-10">
				<span class="pr-4">Stroke: </span>
				<el-color-picker v-model="params.strokeColor" size="small"></el-color-picker>
			</div>
			<div class="aligh-items-center pr-10">
				<span class="pr-4">Width: </span>
				<el-input-number
					v-model="params.width"
					:step="10"
					:precision="0"
					:min="100"
					:max="params.MAX_WIDTH"
					size="small"
					@change="resize"
				></el-input-number>
			</div>
			<div class="aligh-items-center pr-10">
				<span class="pr-4">Height: </span>
				<el-input-number
					v-model="params.height"
					:step="10"
					:precision="0"
					:min="100"
					:max="3000"
					size="small"
					@change="resize"
				></el-input-number>
			</div>
			<div class="slider">
				<span class="pr-10">Innermost circle size:</span>
				<el-slider v-model="params.initialSize" :step="1" :min="1" :max="9" show-stops>
				</el-slider>
			</div>
			<div
				v-for="(value, key, i) in params.drawDirections"
				class="aligh-items-center pr-10"
				v-bind:key="i"
			>
				<span class="pr-4">Draw {{ key }}:</span>
				<el-switch @change="redraw(key, value)" v-model="params.drawDirections[key]">
				</el-switch>
			</div>
			<div>
				<el-button @click="download" size="small" type="success" plain>Download</el-button>
			</div>
		</div>
	</div>
</template>

<script>
import isEmpty from 'lodash.isempty'
import cloneDeep from 'lodash.clonedeep'

const initialParams = {
	bgColor: '#D7D7D7',
	strokeColor: '#000',
	MAX_WIDTH: 2000, // overwritten on component mount, constant thereafter
	width: 600,
	height: 400,
	initialSize: 5,
	drawDirections: {
		up: true,
		down: true,
		left: true,
		right: true,
	},
}

export default {
	data() {
		// could be saved in vuex if needed elsewhere someday
		return {
			p5: {}, // p5 library code
			c: {}, // p5 canvas reference
			loading: true,
			cEmpty: true,
			params: cloneDeep(initialParams), // drawing parameters
		}
	},
	async mounted() {
		if (process.client) {
			// import the library and store it in this component's instance
			const { default: P5 } = await import('p5')
			this.p5 = P5

			// start drawing
			this.draw()

			// move canvas in dom, remove loading indicator
			this.canvasLifecycle()
		}
	},
	methods: {
		draw({ up = true, down = true, left = true, right = true } = {}) {
			// delete previous canvases (if any)
			this.remove()

			// specify canvas dimensions
			// get client div width or default value
			this.params.MAX_WIDTH = document.querySelector('#create').clientWidth
			this.params.width = Math.floor(this.params.MAX_WIDTH / 10) * 10
			// golden ratio height based on longer side width
			const goldenRatioSmallerSide = this.params.width / ((1 + Math.sqrt(5)) / 2)
			this.params.height = Math.round(goldenRatioSmallerSide / 10) * 10 // rounded to 10

			// define what to draw
			const sketch = s => {
				s.setup = () => {
					const cnv = s.createCanvas(this.params.width, this.params.height)
					s.pixelDensity(2) // default is 1
					s.frameRate(1) // default is 60 frames per second
					s.noFill() // art piece specific
					cnv.id('paramartorCnv')
				}

				s.draw = () => {
					s.background(this.params.bgColor)
					s.stroke(this.params.strokeColor)

					// heavily inspired by https://natureofcode.com/book/chapter-8-fractals/
					function drawCircle(x, y, radius) {
						s.ellipse(x, y, radius, radius)
						if (radius > 12) {
							if (up) drawCircle(x, y - radius / 2, radius / 2)
							if (down) drawCircle(x, y + radius / 2, radius / 2)
							if (left) drawCircle(x - radius / 2, y, radius / 2)
							if (right) drawCircle(x + radius / 2, y, radius / 2)
						}
					}
					drawCircle(
						this.params.width / 2,
						this.params.height / 2,
						this.params.width / (10 - this.params.initialSize)
					)
				}

				s.windowResized = () => {
					s.resizeCanvas(this.params.width, this.params.height)
				}
			}
			// draw
			this.c = new this.p5(sketch)
		},
		reset() {
			this.params = cloneDeep(initialParams)

			// start drawing
			this.draw()

			// move canvas in dom, remove loading indicator
			this.canvasLifecycle()
		},
		download() {
			if (!isEmpty(this.c)) this.c.saveCanvas(`paramartor-${Date.now()}`)
		},
		remove() {
			if (!isEmpty(this.c)) this.c.remove()
		},
		resize() {
			if (!isEmpty(this.c)) this.c.windowResized()
		},
		redraw(key, value) {
			// get current settings and overwrite them with new selection, then draw the canvas anew
			const drawDirections = { ...cloneDeep(this.params.drawDirections), [key]: !value }
			this.draw(drawDirections)

			// move canvas in dom, remove loading indicator
			this.canvasLifecycle()
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
#paramartorCnv {
	padding-bottom: 1rem;
}

.controls {
	padding-bottom: 1rem;
	display: flex;
	flex-wrap: wrap;
	align-items: center;
}

.aligh-items-center {
	display: flex;
	align-items: center;
	height: 40px;
}

.pr-4 {
	padding-right: 4px;
}

.pr-10 {
	padding-right: 10px;
}

.slider {
	padding-right: 20px;
	display: flex;
	align-items: center;
}
/* hacky override */
.slider .el-slider {
	width: 110px;
	padding-left: 5px;
}
</style>
