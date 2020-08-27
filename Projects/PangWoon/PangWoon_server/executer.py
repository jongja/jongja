#  Trained model code.
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import store_dict as sdic
import attribute_dict as atdict
import Trained_model as Trained
import numpy as np
import Training_model as Train
import random as r

def IsCheckId(userid) : # check if existed id or not
    f = open('login_Information.csv', 'r')
    while True:
        line = f.readline() # read a line
        read_data = line.split(',')
        if userid == read_data[0] :
            f.close()
            return False # find existed id
        if not line:
            break # read all line
    f.close()
    return True # not found

def IsCheck_Id_Passwd(userid, passwd) : # check that id, passwd matches.
    f = open('login_Information.csv', 'r',encoding='UTF8')
    while True:
        line = f.readline()  # read a line
        if line is '':
            break # read all line
        read_Info = line.split(',')  # userid, passwd, sex, age
        #print(read_Info)
        read_userid = read_Info[0]
        read_passwd = read_Info[1]
        read_sex = read_Info[2]
        read_age = read_Info[3]

        if userid == read_userid : # find id
            if passwd == read_passwd : # check password.
                send_data = "Access/" + read_userid + "/" + read_passwd + "/" + read_sex + "/" + read_age + "\n" # 'Access/id/passwd/sex/25\n'
                f.close()
                #print(send_data) 
                return send_data # id and password match.
            else :
                f.close()
                return "NotAccess\n" # not match
    f.close()
    return "NoData\n" # not exist data

class Executer:
    def __init__(self, tcpServer):
        self.andRaspTCP = tcpServer

    def startCommand(self, port_num, command):
        command = command.split('\n')
        command = command[0]
        #print(command)
        if command[0:8] == 'Register':  # command : Register/2013722024/jh1994/sex/25
            userInfo = command.split('/')  # store data in divided '/'
            userid = userInfo[1]
            passwd = userInfo[2]
            sex = userInfo[3]
            age = userInfo[4]
            f = open('login_Information.csv', 'a')
            if not IsCheckId(userid):  # check existed id. True : register, False : already existed
                #print("Existed")
                self.andRaspTCP.sendAll(port_num, "Existed\n") 

            else:  # not existed -> register data
                f.write(userid + ',') 
                f.write(passwd + ',')  
                f.write(sex + ',') 
                f.write(age + '\n')
                #print("RegisterOk")
                self.andRaspTCP.sendAll(port_num, "RegisterOk\n") 
            f.close()

        elif command[0:5] == 'login' : # command : login/2014722011/passwd
            login_data = command.split('/')
            userid = login_data[1]  # 2014722011
            passwd = login_data[2]  # password
            self.andRaspTCP.sendAll(port_num, IsCheck_Id_Passwd(userid, passwd))

        elif command[0] == '0' : # 0 2014722011 information # 0/2014722011/0/1/1/0/.....
            receivedData = command.split('/')
            userid = receivedData[1]
            User_info = receivedData[2:]
            # 1. add user's data in csv file [flag, userid, dataset]
            ######################################################
            f = open('./training_file/'+userid+'.csv', 'a')
            for i in User_info :
                f.write(i + ',')
            f.close()
            ######################################################

            # 2. send data result through meta file.
            ######################################################
            first_data = Trained.Recommand(receivedData) # first recommand data in Recommand func.
            tempKeylist = []

            # get second data
            for key in atdict.attribute_dict :
                length = len(atdict.attribute_dict[key])       
                
                if atdict.attribute_dict[key].count(first_data) == 1 and tempKeylist.count(key) == 0 :
                    tempKeylist.append(key)

            while True :
                IndexRand = r.randint(0, len(tempKeylist) - 1)
                length = len(atdict.attribute_dict[tempKeylist[IndexRand]])
                index = r.randint(0, length-1)
                
                second_data = atdict.attribute_dict[tempKeylist[IndexRand]][index] # first recommand data using attribute dictionary
                if second_data != first_data :
                    break

            tempKeylist.clear()

            # get third data 
            while True :
                IndexRand = r.randint(0, 6)
                tempFood = atdict.attribute_number[IndexRand]
                length = len(atdict.attribute_dict[tempFood])
                index = r.randint(0, length-1)
               
                third_data = atdict.attribute_dict[tempFood][index]
                if third_data != first_data and third_data != second_data :
                    break
            for i in range(0, len(sdic.store_dict)) :
                food_name = sdic.store_dict.get(i)
                if food_name == first_data :
                    first_data = i
                elif food_name == second_data :
                    second_data = i
                elif food_name == third_data :
                    third_data = i

            send_data = 'RecommendOk/' + str(first_data) + '/' + str(second_data) + '/' + str(third_data)           
            print('Send Data : ', send_data)
            self.andRaspTCP.sendAll(port_num, send_data+'\n')
            ###################################################################
            #Find password protocol  
        elif command[0:8] == 'Findpass' : # command : Findpass/2013722024/남/25
            receivedData = command.split('/')
            userid = receivedData[1]
            gender = receivedData[2]
            age = receivedData[3]
            splited_data = []
            send_data = ''
            f = open('login_Information.csv','r')
            find = 0
            data = f.readline()
            while data is not '' :
                splited_data = data.split(',')
                splited_data[3] = splited_data[3].split('\n')
                #print(splited_data)
                if splited_data[0] == userid and splited_data[2] == gender and splited_data[3][0] == age :
                    find = 1
                    break
                data = f.readline()

            if find :
                send_data = 'FindSuccess' + '/' + splited_data[1]
            else :
                send_data = 'FindFail'
            self.andRaspTCP.sendAll(port_num, send_data+'\n') # Success/password or Fail          

            ######################################################
        elif command[0:7] == 'Rerecom' : # command : Rerecom/userid/store number1/store number2/store number3/
            receivedData = command.split('/')
            userid = receivedData[1]
            store_num = receivedData[2:]

            first_data = Train.Training_function(userid, store_num) # second parameter is not recommanded by learning
            tempKeylist = []
            # get second data
            for key in atdict.attribute_dict :
                length = len(atdict.attribute_dict[key])       
                
                if atdict.attribute_dict[key].count(first_data) == 1 and tempKeylist.count(key) == 0 :
                    tempKeylist.append(key)
            while True :
                IndexRand = r.randint(0, len(tempKeylist) - 1)
                length = len(atdict.attribute_dict[tempKeylist[IndexRand]])
                index = r.randint(0, length-1)
                
                second_data = atdict.attribute_dict[tempKeylist[IndexRand]][index] # first recommand data using attribute dictionary
                if second_data != first_data :
                    break

            tempKeylist.clear()
            # get third data 
            while True :
                IndexRand = r.randint(0, 6)
                tempFood = atdict.attribute_number[IndexRand]
                length = len(atdict.attribute_dict[tempFood])
                index = r.randint(0, length-1)
               
                third_data = atdict.attribute_dict[tempFood][index]
                if third_data != first_data and third_data != second_data :
                    break
		
            for i in range(0, len(sdic.store_dict)) :
                food_name = sdic.store_dict.get(i)
                if food_name == first_data :
                    first_data = i
                elif food_name == second_data :
                    second_data = i
                elif food_name == third_data :
                    third_data = i

            send_data = 'RerecomOk/' + str(first_data) + '/' + str(second_data) + '/' + str(third_data) + '/'
            print('Send Data : ', send_data)
            self.andRaspTCP.sendAll(port_num, send_data+'\n')
            ###################################################################################
            # Send store review and star score to client 
        elif command[0:6] == 'Review' : # command : Review/지지고
            receivedData = command.split('/')
            f = open('./review_data/' + receivedData[1])
            star = f.readline().split('/')[0]
            reviews = f.readline()
            if reviews == '\n':
                reviews = f.readline()
            send_data = star + '||' + reviews
            f.close()
            self.andRaspTCP.sendAll(port_num, "ReviewOk/" + send_data+'\n') # 4.55||review|review|review....
            ##################################################################################
            # Receive store review and star score to server.
            # Client send starscore and review simuteneously.
        elif command[0:9] == 'Sndreview': # command : Sndreview/작은집/9/review message
            receivedData = command.split('/')
            f = open('./review_data/' + receivedData[1], 'r+')
            star = f.readline().split('/')
            star[1] = star[1].split('\n')[0]
            all = float(star[0]) * float(star[1])
            candi = int(star[1]) + 1
            all = (all + float(receivedData[2])) / (float(star[1]) + 1)
            f.seek(0,0)
            f.write(str(round(all,1)) + '/' + str(candi) + ' ' + '\n')
            f.close()
            f = open('./review_data/' + receivedData[1], 'a')
            if receivedData[3][0] is '\n':
                f.write(receivedData[3][1:]+'->'+receivedData[2] + '|')
            else:
                f.write(receivedData[3]+'->'+receivedData[2] + '|')
            f.close()
            f = open('./review_data/' + receivedData[1])
            star = f.readline().split('/')[0]
            reviews = f.readline()
            if reviews == '\n':
                reviews = f.readline()
            send_data = star + '||' + reviews
            f.close()
            self.andRaspTCP.sendAll(port_num, "ReviewWriteOk/" + send_data + '\n') #send updated review and starscore data.
        else:
            ""
            self.andRaspTCP.sendAll(port_num, "")
