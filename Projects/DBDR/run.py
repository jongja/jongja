# Imagic Graduation
# Document Recognition based on Deep Learning 
# 2019

import timeit
import sys
from ITT import ImgToText as itt # tesseract function as itt
from OpenCV import ex_table as extable
img_path = "./Images"
res_path = "./Result"
total_time = float()
total_time = 0
if len(sys.argv) is 1:
    print('Usage : python3 run.py <image file>\n')
    exit()
print("\nImagic Graduation")
print("Document Recognition based on Deep Learning ver 1.0\n")

######## Table Extract #########
print("(1/3) Extract table..")
start = timeit.default_timer()
pack = extable.StartTableExtract(sys.argv[1])
end = timeit.default_timer()
print("Execution time > {:.2f}s".format(end-start))
total_time = total_time + (end - start)
######## Image To text ########
print("(2/3) Convert Image to text..")
start = timeit.default_timer()
pack = itt.ImgToText(pack, 12) #convert img to text file.
print(len(pack))
end = timeit.default_timer()
print("Execution time > {:.2f}s".format(end-start))
total_time = total_time + (end - start)
######## Merge and export Excel ########
print("(3/3) Merge and export Excel file..")
start = timeit.default_timer()
extable.StoretoExcel(pack)
end = timeit.default_timer()
print("Execution time > {:.2f}s".format(end-start))
total_time = total_time + (end - start)

print("Total execution time >>> {:.4f}s".format(total_time))
