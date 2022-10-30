import glob
from PIL import Image, ImageDraw, ImageFont

width = 28 
height = 28 

WHITE = (255, 255, 255, 0)

image = Image.new('RGB', (width, height), WHITE)

# Obtention du contexte graphique
draw = ImageDraw.Draw(image)


BLACK = (0, 0, 0)
#draw.text((20, 20), "Cercle trigonométrique", fill=BLACK)
ttf_files = glob.glob("*.ttf")
print(len(ttf_files))
for ttf_file in ttf_files:
    font = ImageFont.truetype(ttf_file, size=22)
    for number in range(1,10) : 
        draw.text((9,1),str(number),fill=BLACK,font=font)
        image.save(f"{ttf_file}_{number}","png")
        image = Image.new('RGB',(width,height),WHITE)
