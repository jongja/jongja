from PIL import Image     
from pytesseract import * 
import cv2
import multiprocessing

def ocrToStr(img, lang, idx, rd): 
    # zoom twice.
    img_result = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)
  #  Page segmentation modes(psm):
 # 0    Orientation and script detection (OSD) only.
 # 1    Automatic page segmentation with OSD.
 # 2    Automatic page segmentation, but no OSD, or OCR.
 # 3    Fully automatic page segmentation, but no OSD. (Default)
 # 4    Assume a single column of text of variable sizes.
 # 5    Assume a single uniform block of vertically aligned text.
 # 6    Assume a single uniform block of text.
 # 7    Treat the image as a single text line.
 # 8    Treat the image as a single word.
 # 9    Treat the image as a single word in a circle.
 #10    Treat the image as a single character.
 #11    Sparse text. Find as much text as possible in no particular order.
 #12    Sparse text with OSD.
 #13    Raw line. Treat the image as a single text line,
 #      bypassing hacks that are Tesseract-specific.
    #oem(OCR Engine Modes)

 # 0    Legacy engine only.
 # 1    Neural nets LSTM engine only.
 # 2    Legacy + LSTM engines.
 # 3    Default, based on what is available.

    outText = image_to_string(img_result, lang=lang, config='--psm 3 --oem 1 -c preserve_interword_spaces=1')
    rd[idx] = outText
    return outText

def loop(lis, step, rd):
    job = []
    for i in lis: # make 12 process for parallel processing.
        process = multiprocessing.Process(target=ocrToStr, args=(i[0], 'kor+eng', step, rd))
        job.append(process)
        pos = i[1]
        step = step + 1
    for i in job: # Operation start
        i.start()
    for i in job: # Operation end
        i.join()

def ImgToText(lis, core):  #Image to text function
    last = int(len(lis)/core) 
    step = 0
    return_dict = multiprocessing.Manager().dict() # for save result.
    if last is 0:
        loop(lis[step:], step, return_dict)
    for i in range(last):
        if i is last - 1:
            loop(lis[step:], step, return_dict)
        else: 
            loop(lis[step:step + core], step, return_dict)
        step = step + core
    step = 0
    for i in lis:
        i[0] = return_dict[step]
        
        step = step + 1
    return lis # list form ===> lis[i][0] = TEXT, lis[i][1] = Coordinate.
