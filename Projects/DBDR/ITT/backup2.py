from PIL import Image     
from pytesseract import * 
import configparser       # ini 파일 포맷을 이용하여 환경 설정  
import os                 # 특정 디렉토리 내의 파일 목록을 구하려고
import cv2
import multiprocessing
#Config Parser 초기화
config = configparser.ConfigParser()
#Config File 읽기
config.read(os.path.dirname(os.path.realpath(__file__)) + os.sep + 'envs' + os.sep + 'property.ini')

#이미지 -> 문자열 추출
def ocrToStr(img, lang, idx, rd): #디폴트는 영어로 추출
    #이미지 경로
    #img = Image.open(fullPath)
    #txtName = os.path.join(outTxtPath,fileName.split('.')[0])

    # 원본 이미지
    #img_source = cv2.imread(fullPath)

    # 2배 이미지
    img_result = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)
    #img_result = img
    #img_result = cv2.cvtColor(img_result, cv2.COLOR_BGR2GRAY)
    # cv2.imshow("x2", img_result)
    # cv2.waitKey(0)

    #추출(이미지파일, 추출언어, 옵션)
    #preserve_interword_spaces : 단어 간격 옵션을 조절하면서 추출 정확도를 확인한다.
    #psm(페이지 세그먼트 모드 : 이미지 영역안에서 텍스트 추출 범위 모드)
    
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

    step = 2.1 # zoom은 3배부터 시작.
    #while step < 2.5:
    outText = image_to_string(img_result, lang=lang, config='--psm 3 --oem 1 -c preserve_interword_spaces=1')
    #print(outText)
       #if outText is '':
       #   img_result = cv2.resize(img_result, None, fx=step, fy=step, interpolation=cv2.INTER_CUBIC)
#      #    img_result = cv2.cvtColor(img_result, cv2.COLOR_BGR2GRAY)
       #   print("Zoom "+ str(step) +" times.")
       #   step = step + 0.1
       #else:
       #   break
    #출력
    #print('Extract FileName : ', fileName)
    #if outText is '':
    #   print("Fail to convert " + fileName + ". check please.")
    #else:
    #   print(outText)
    #print('\n')
    #추출 문자 텍스트 파일 쓰기
    #strToTxt(txtName, outText)
    rd[idx] = outText
    return outText

def loop(lis, step, rd):
    job = []
    for i in lis:
        process = multiprocessing.Process(target=ocrToStr, args=(i[0], 'kor+eng', step, rd))
        job.append(process)
        pos = i[1]
        step = step + 1
        #return_dict[idx] = et_text + "_" + pos
    for i in job:
        i.start()
    for i in job:
        i.join()

#메인 시작
#if __name__ == "__main__":
def ImgToText(lis, core):
    #텍스트 파일 저장 경로
    #outTxtPath = os.path.dirname(os.path.realpath(__file__))+ config['Path']['OcrTxtPath']

    #OCR 추출 작업 메인
    #for root, dirs, files in os.walk(os.path.dirname(os.path.realpath(__file__)) + config['Path']['OriImgPath']):
    #    for fname in files:
    #        fullName = os.path.join(root, fname)
            
    #        if fname == ".DS_Store": #exception handling..
    #            continue
            #print(fname)
            #print(fullName)
            #한글+영어 추출(kor, eng , kor+eng)
    #sep = int(len(lis) / core)
    #res = []
    last = int(len(lis)/core)
    step = 0
    return_dict = multiprocessing.Manager().dict()
    for i in range(last):
        if i is last - 1:
            loop(lis[step:], step, return_dict)
        else: 
            loop(lis[step:step + core], step, return_dict)
        step = step + core
    #pool.close()
    #pool.join() 
    #for i in range(last):
    #    print(step)
    #    if i is last - 1:
    #        process = multiprocessing.Process(target=loop, args=(step, lis[step:], return_dict))
    #    else:
    #        process = multiprocessing.Process(target=loop, args=(step, lis[step:step + sep - 1], return_dict))
    #    step = step + sep
    #    res.append(process)
    #step = 0;
    #for i in res:
    #    print(step, end='')
    #    i.run()
    #    step = step + 1
    step = 0
    for i in lis:
        i[0] = return_dict[step]
        step = step + 1
    return lis
