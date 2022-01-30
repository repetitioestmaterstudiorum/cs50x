// footer
// copyright year
document.querySelector('#copyright-year').innerHTML = new Date().getFullYear()

// clock
setInterval(() => {
	document.querySelector('#footer-date').innerHTML = new Date().toLocaleString()
}, 1000)
