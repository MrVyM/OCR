import glob
from PIL import Image, ImageDraw, ImageFont

import os

for i in range(0,90) :
	print((i+10)%90)

im = Image.open("5.png")
for x in range(im.height) :
	for y in range(im.width) :
		if (im.getpixel((x,y))[0] > 170) :
			print(1, end="")
		else :
			print(0, end="")