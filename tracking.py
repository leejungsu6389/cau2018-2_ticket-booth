import numpy as np
import cv2
import math
DISTANCE = 130.0
DEADLINE = 15
cap = cv2.VideoCapture("C:\\Users\\kimin\\OneDrive\\바탕 화면\\sample.mp4")  # Open video file
print("(", cap.get(3), cap.get(4), ")")
bgSub = cv2.createBackgroundSubtractorKNN(dist2Threshold=400,detectShadows=False)
mid_x = int(cap.get(3)/2)
mid_y = int(cap.get(4)/2)
frame_sz = (500,300)
kernelOp = np.ones((3,3),np.uint8)
kernelCl = np.ones((11,11),np.uint8)
count = 0
cv2.namedWindow("Demo",0)
object_id  = [[],[],[],[]]

object_id_timer = [0,0,0,0]
object_enum = [0,0,0,0] #안에서 시작된 물체:1  밖에서 시작된 물체:2
while (cap.isOpened()):
    (ret, frame) = cap.read()  # read a frame
    try:
        count = count + 1
        for i in range(0, 4):
            if object_id_timer[i] > DEADLINE:
                print(i ," is deleted")
                object_id[i].clear()
                object_id_timer[i] = 0
                object_enum[i] = 0

        frame = cv2.resize(frame, frame_sz)
        original = frame
        frame = cv2.cvtColor(frame,cv2.COLOR_RGB2GRAY)
        frame = cv2.GaussianBlur(frame,(3,3),0)
        frame = cv2.morphologyEx(frame, cv2.MORPH_OPEN, kernelOp)
        frame = cv2.morphologyEx(frame, cv2.MORPH_CLOSE, kernelCl)
        frame = bgSub.apply(frame)
        cv2.threshold(frame,200,255,cv2.THRESH_BINARY)
        frame = cv2.morphologyEx(frame,cv2.MORPH_OPEN,kernelOp)
        frame = cv2.morphologyEx(frame, cv2.MORPH_OPEN, kernelOp)
        frame = cv2.morphologyEx(frame, cv2.MORPH_CLOSE, kernelCl)
        frame = cv2.morphologyEx(frame, cv2.MORPH_CLOSE, kernelCl)
        _, contours, hierarchy = cv2.findContours(frame,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
        obj_isUpd = [False, False, False, False]

        for cnt in contours:
            area = cv2.contourArea(cnt)
            if area>10000:
                M = cv2.moments(cnt)
                cx = int(M['m10'] / M['m00'])
                cy = int(M['m01'] / M['m00'])
                x, y, w, h = cv2.boundingRect(cnt)
                cv2.circle(original, (cx, cy), 3, (0, 0, 255), -1)
                cv2.rectangle(original, (x, y), (x + w, y + h),(0,255,2),2)
                checked = False
                for i in range(0, 4):
                    if len(object_id[i]) != 0:
                        check = object_id[i].pop()
                        object_id[i].append(check)
                        dist = math.sqrt((cx - check[0]) * (cx - check[0]) + (cy - check[1]) * (cy - check[1]))
                        if dist < DISTANCE:
                            print(i, " is used");
                            ignore = True
                            object_id[i].append((cx, cy))
                            object_id_timer[i] = 0
                            obj_isUpd[i] = True
                            checked = True
                            break
                if checked == False :
                    for j in range(0, 4):
                        if len(object_id[j]) == 0:
                            object_id[j].append((cx, cy))
                            object_id_timer[j] = 0
                            obj_isUpd[j] = True
                            if cx < 400 :
                                object_enum[j] = 1
                            else :
                                object_enum[j] = 2
                            break


        for i in range(0,4):
            if len(object_id[i]) > 1:
                for j in range(0,len(object_id[i])-1) :
                    if object_enum[i] == 1:
                        original = cv2.line(original, object_id[i][j], object_id[i][j+1], (0, 0, 255), 3)
                    elif object_enum[i] == 2:
                        original = cv2.line(original, object_id[i][j], object_id[i][j+1], (255, 0, 0), 5)
        original = cv2.line(original,(400,0),(400,300),(255,0,0),2)
        original = cv2.putText(original,"IN",(350,250),cv2.FONT_HERSHEY_SIMPLEX,1,(0,0,255),2)
        original = cv2.putText(original, "OUT", (420, 250), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        cv2.imshow("Demo", original)
        for i in range(0, 4):
            if obj_isUpd[i] == False:
                object_id_timer[i] = object_id_timer[i] +1
    except:
        print("EOF")
        break
    k = cv2.waitKey(30)
    if k > 0:
        a = int(input("1누르면 재진행"))
        continue
cap.release()
cv2.destroyAllWindows()
