import glob
from PIL import Image, ImageDraw, ImageFont

import os

image_path = "Dataset"

width = 28 
height = 28 

WHITE = (255, 255, 255)

image = Image.new('RGB', (width, height), WHITE)

# Obtention du contexte graphique
draw = ImageDraw.Draw(image)


BLACK = (0, 0, 0)
#draw.text((20, 20), "Cercle trigonométrique", fill=BLACK)
ttf_files = glob.glob("Font/*.ttf")

for ttf_file in ttf_files:
    name_font=ttf_file.split("/")[-1]
    font = ImageFont.truetype(ttf_file, size=22)
    for number in range(0,10) :
        if (number != 0) : 
            draw.text((9,1),str(number),fill=BLACK,font=font)
        image.save(f"{image_path}/dataset_{name_font}_{number}","png")
        draw.rectangle([(0,0),(width,height)],fill=WHITE)
