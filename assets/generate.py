import glob
from PIL import Image, ImageDraw, ImageFont

import os

image_path = "Dataset"

width = 28 
height = 28 
WHITE = (255, 255, 255)


def noise(x,y,theta) :
    if (theta+x+y < 3) :
        return None
    for i in range(0,28**2,x+y+theta) :
        draw.point((i%28,i/14),fill=BLACK)

BLACK = (0, 0, 0)
#draw.text((20, 20), "Cercle trigonométrique", fill=BLACK)
ttf_files = glob.glob("Font/*.ttf")

for ttf_file in ttf_files:
    name_font=(ttf_file.split("/")[-1]).split(".ttf")[0]
    font = ImageFont.truetype(ttf_file, size=22)

    for theta in range(0,30,10) :
        for y in range(-2,2) :
            for x in range(-5,5,2) :
                for number in range(1,10) :
                    image = Image.new('RGB', (width, height), WHITE)
                    draw = ImageDraw.Draw(image);
                    if (number != 0) : 
                        draw.text((9+x,1+y),str(number),fill=BLACK,font=font)
                    noise(x,y,theta)
                    #image = image.rotate(theta,fillcolor=WHITE)
                    image.save(f"{image_path}/dataset_{name_font}_({x},{y},{theta})_{number}","png")
