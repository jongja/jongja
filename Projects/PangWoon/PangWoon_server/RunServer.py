#  Trained model code.
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import tcpServer
import executer
import datetime
import time
import Training_model as train
from multiprocessing import Queue

# make public queue
commandQueue = Queue()
# init module
andRaspTCP = tcpServer.TCPServer(commandQueue, "192.168.0.12", 34343) # "" -> Host, 34343-> port number
andRaspTCP.start()

# set module to executer
commandExecuter = executer.Executer(andRaspTCP)

print("Imagic Server started. Server version : 1.0.0")
while True:
    
    try: 
        now = datetime.datetime.now()
        #print('current time : ', now.hour,':',now.minute,':',now.second)
        timeInfo = str(now.hour) + str(now.minute) + str(now.second)
        if timeInfo == '20510' : #when training time set, start training.
            time.sleep(1)
            train.search_csvfile()
        time.sleep(1)
        if commandQueue.empty() :
            continue
        command = commandQueue.get() #print data
        commandExecuter.startCommand(command[0], command[1]) # [0] : port number, [1] : data(=command)
    except:
        pass
