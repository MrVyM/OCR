import glob
from PIL import Image, ImageDraw, ImageFont

import os

image_path = "Dataset"

width = 28 
height = 28 
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

if os.path.exists(image_path+"/data.txt") : 
    os.remove(image_path + "/data.txt")
    print("Data remove...")


if os.path.exists(image_path+"/lines.txt") : 
    os.remove(image_path + "/lines.txt")
    print("Lines remove...")


def addFile(image,number) :
    filename = image_path + "/data.txt"
    f = open(filename, "a")
    for x in range(width) :
        for y in range(width) : 
            f.write(str(0 if image.getpixel((x,y))[0] < 10 else 1))
    f.write(str(number)+"\n")
    print(str(number))
    f.close()

def noise(x,y,theta) :
    if (theta+x+y < 3) :
        return None
    for i in range(0,28**2,x+y+theta) :
        draw.point((i%28,i/12),fill=BLACK)

def noiseWhite(x,y,theta) :
    if (theta+x+y < 3) :
        return None
    for i in range(0,28**2,x+y+theta) :
        draw.point((i/25,i%25),fill=WHITE)
        draw.point(((i+1)/25,(i+1)%25),fill=WHITE)


#draw.text((20, 20), "Cercle trigonométrique", fill=BLACK)
ttf_files = glob.glob("Font/*.ttf")
count = 0

for ttf_file in ttf_files:
    name_font=(ttf_file.split("/")[-1]).split(".ttf")[0]
    font = ImageFont.truetype(ttf_file, size=22)
    print("Generate for the font :",name_font)
    for theta in range(0,30,10) :
        for y in range(-2,2) :
            for x in range(-5,5,2) :
                for number in range(0,10) :
                    image = Image.new('RGB', (width, height), WHITE)
                    draw = ImageDraw.Draw(image);
                    if (number != 0) : 
                        draw.text((9+x,1+y),str(number),fill=BLACK,font=font)
                    noiseWhite(int(x/4),int(y/4),theta) 
#                    noise(x,y,theta)
                    count += 1
                    addFile(image,number)
                    #image = image.rotate(theta,fillcolor=WHITE)
                    print(f"{image_path}/dataset_{name_font}_({x},{y},{theta})_{number}")
                    image.save(f"{image_path}/dataset_{name_font}_({x},{y},{theta})_{number}","png")

f = open(image_path +"/lines.txt","a")
f.write(str(count))
f.close()
