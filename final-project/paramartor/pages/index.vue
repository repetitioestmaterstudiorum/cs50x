<template>
	<div id="info">
		<h1>Welcome to paramartor!</h1>
		<p>What's paramartor?</p>
		<p>
			.. is an invented word derived from <strong>parametrized visual art generation</strong>.
		</p>
		<h2>p5.js library</h2>
		<p>
			This website uses the
			<a href="https://p5js.org/" target="_blank" rel="noopener noreferrer">p5.js library</a>,
			a library that enables creative coding.
		</p>
		<p>This is an example of what can be created using p5.js on this website:</p>
		<img src="~/assets/example.png" alt="" />
		<CreateLink />
		<div class="faq">
			<h3>FAQ</h3>
			<el-collapse accordion>
				<el-collapse-item title="Where can I learn more about programming art?">
					<div>
						I can recommend this website:
						<a
							href="https://natureofcode.com/book/chapter-8-fractals/"
							target="_blank"
							rel="noopener noreferrer"
							>The Nature Of Code</a
						>,
					</div>
				</el-collapse-item>
				<el-collapse-item title="Do I need to know programming to use this website?">
					<div>No! It's easy to use for anyone.</div>
				</el-collapse-item>
				<el-collapse-item title="How can I create my own art?">
					<div>Simplify go to the Create page on this website:</div>
					<CreateLink />
				</el-collapse-item>
			</el-collapse>
		</div>
	</div>
</template>

<script>
export default {}
</script>

<style>
.example {
	background-color: lightgrey;
}

img {
	width: 100%;
	max-width: 1000px;
}

.faq {
	padding: 1rem 0;
}

/* hacky overrides */
.el-collapse-item__header {
	font-size: 0.8rem;
}
.el-collapse-item__content {
	font-size: 1rem;
}
</style>
