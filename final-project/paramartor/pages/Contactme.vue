<template>
	<div>
		<h1>Contact</h1>
		<el-form
			:model="contactForm"
			ref="contactForm"
			name="contactForm"
			method="post"
			data-netlify="true"
			data-netlify-honeypot="bot-field"
		>
			<input type="hidden" name="form-name" value="contactForm" />

			<el-form-item
				prop="name"
				label="Name"
				:rules="[{ required: true, message: 'Enter your name', trigger: 'blur' }]"
			>
				<el-input v-model="contactForm.name"></el-input>
			</el-form-item>

			<el-form-item
				prop="email"
				label="Email"
				:rules="[
					{ required: true, message: 'Enter your email address.', trigger: 'blur' },
					{
						type: 'email',
						message: 'Enter a correct email address.',
						trigger: ['blur', 'change'],
					},
				]"
			>
				<el-input v-model="contactForm.email"></el-input>
			</el-form-item>

			<el-form-item
				prop="message"
				label="Message"
				:rules="[{ required: true, message: 'Enter your message.', trigger: 'blur' }]"
			>
				<el-input type="textarea" v-model="contactForm.message"></el-input>
			</el-form-item>

			<el-form-item>
				<el-button type="info" @click="submitForm('contactForm')">Send</el-button>
			</el-form-item>
		</el-form>
	</div>
</template>
<script>
import axios from 'axios'

export default {
	data() {
		return {
			contactForm: {
				name: '',
				email: '',
				message: '',
			},
		}
	},
	methods: {
		encode(data) {
			return Object.keys(data)
				.map(key => `${encodeURIComponent(key)}=${encodeURIComponent(data[key])}`)
				.join('&')
		},
		submitForm(formName) {
			this.$refs[formName].validate(valid => {
				if (valid) {
					const axiosConfig = {
						header: { 'Content-Type': 'application/x-www-form-urlencoded' },
					}
					axios.post(
						'/',
						this.encode({
							'form-name': 'contactForm',
							...this.contactForm,
						}),
						axiosConfig
					)
				} else {
					alert('Form not filled properly!')
					return false
				}
			})
			console.log('form saved!')
		},
	},
}
</script>

<style></style>
