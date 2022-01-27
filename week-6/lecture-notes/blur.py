from PIL import Image, ImageFilter

# ---

before = Image.open("tower.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("tower-blurred.bmp")