#  Recommandation prototype app.
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import Trained_model as tr
import store_dict as sdic

list = []
### Ask sex ###
s = int(input("성별을 입력해주세요\n1. 남성\t2. 여성\ninput >> "))
list.append(s-1)

print("")

### Ask age ###
while(1):
    age = int(input("귀하의 나이를 입력해주세요\ninput >> "))
    if age < 20:
        print("20살 이상만 입력해주세요.\n")
        continue
    elif age >= 20 and age < 23:
        list.append(0)
        break
    elif age >= 23 and age < 26:
        list.append(1)
        break
    elif age >= 26 and age < 30:
        list.append(2)
        break
    elif age >= 30:
        list.append(3)
        break

print("")

### Ask price ###
price = int(input("가격대는 어느정도를 원하십니까?\ninput >> "))
if price < 5000:
    list.append(0)
elif price >= 5000 and price < 8000:
    list.append(1)
else:
    list.append(2)
print("")

### Ask freq ###
freq =int(input("오늘 몇 번째 밥을 드시는 거죠?\n1. 처음입니다.\n2. 두 끼입니다.\n3. 세 끼 이상입니다.\ninput >> "))
list.append(freq)
print("")

### Ask people ###
peop =int(input("동행 인원이 몇 명 입니까?\n1. 혼자입니다.\n2. 2~4명 입니다.\n3. 5명 이상입니다..\ninput >> "))
list.append(peop)
print("")

### Ask Menu ###
while(1):
    print("오늘 메뉴로 괜찮은 것을 순서대로 선택해 주세요.\n-----------------------------------------------------------------")
    print("1. 백반  2. 덮/컵/볶음+밥  3. 중화요리\n4. 돈까스 5. 면류 6. 분식 7. 패스트푸드  \n-----------------------------------------------------------------")
    print("(Usage : '나는 오늘 밥이 먹고싶어' -> input >> 1 1 1 0 0 0 0)")
    print("input >> ", end = '')
    menu = [[int(x) for x in input().split()]for y in range(1)]
    if len(menu[0])!=7:
        print("\n잘못된 입력입니다. 0과 1중, 7개의 data만 입력해주세요.\n")
        continue
    check = 0
    for i in range(7):
        if menu[0][i] > 1 or menu[0][i] < 0:
            check = 1
            break
    if check is 1:
        print("\n잘못된 입력입니다. 0과 1중, 7개의 data만 입력해주세요.\n")
        continue
    for i in range(7):
        list.append(menu[0][i])
    break

ans = tr.Recommandation(list)

print("오늘의 추천식당은 '{}'입니다!".format(sdic.store_dict[ans]))
print("맘에 드시나요?\n1. 네\n2. 아니오")
yes = int(input("input >> "))
if yes != 1:
    a = 0
    st_num = 0
    while not a:
        print("\n맘에 들지 않으시다면 오늘 드실 식당 이름을 적어주세요.\n")
        want = input("input >> ")
        for i in range(1, len(sdic.store_dict)+1):
            if sdic.store_dict[i] == want:
                a = 1
                st_num = i
                break
        if not a:
            print("식당 이름이 잘못된것 같아요.\n")
            print("<식당 목록>")
            for i in range(1, len(sdic.store_dict)+1):
                print("{}. {}\t".format(i, sdic.store_dict[i]), end = '')
                if len(sdic.store_dict[i]) < 6:
                    print("\t", end = '')
                if i%3==0:
                    print("")
            print("")
    list.append(st_num)
else:
    list.append(ans)
        ## Save response data ##
f = open("response_data.csv", "a")
for i in range(13):
    f.write(str(list[i]))
    if i != 12:
        f.write(',')
f.write('\n')
f.close()


    ## To Do ##
# 1. View 3 store list for user to choice. -> MinSub
# 2. If there was no user's want, input store what user want to eat. -> Heawul
# 3. Save trained model. -> MyungO





