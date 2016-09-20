from PIL import Image, ImageFilter

image = Image.open("./Harambe.jpg")

box = (100, 100, 400, 400)
region = image.crop(box)
region = region.transpose(Image.ROTATE_90)
image.paste(region, box)

image.filter(ImageFilter.DETAIL).show()
