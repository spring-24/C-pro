import cv2 as cv
import sys

img_jjh = cv.imread('jjh.jpg')

if img_jjh is None:
    sys.exit('파일 불러오기 실패')

cv.imshow('original_RGB', img_jjh)
cv.imshow('Upper left half', img_jjh[0:img_jjh.shape[0]//2, 0:img_jjh.shape[1]//2, :])
cv.imshow('Center half', img_jjh[img_jjh.shape[0]//4:3*img_jjh.shape[0]//4, img_jjh.shape[1]//4:3*img_jjh.shape[1]//4, :])

cv.imshow('R channel', img_jjh[:, :, 2])
cv.imshow('G channel', img_jjh[:, :, 1])
cv.imshow('B channel', img_jjh[:, :, 0])

B_channel = img_jjh[:, :, 0]
G_channel = img_jjh[:, :, 1]
R_channel = img_jjh[:, :, 2]


gray_jjh = 0.299 * R_channel + 0.587 * G_channel + 0.114 * B_channel

gray_jjh = gray_jjh.astype('uint8')


cv.imshow('gray_jjh', gray_jjh)

cv.waitKey()
cv.destroyAllWindows()
