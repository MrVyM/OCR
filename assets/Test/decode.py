import glob
from PIL import Image, ImageDraw, ImageFont

import os

for filename in glob.glob("*.png") :
	
	im = Image.open(filename)
	for x in range(im.height) :
		for y in range(im.width) :
			if (im.getpixel((x,y))[0] > 170) :
				print(1, end="")
			else :
				print(0, end="")
	print(filename)
