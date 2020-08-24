# CSCA detector run code.
# Created by JongHyeon Cho in kwangwoon uni. 2019
# Copyright @ 2019 JongHyeon Cho All right reserved.

import subprocess
import os
import numpy as np
import time
import sys
import tensorflow as tf

cur_line = 0 #for skip line.
pid = os.fork()
filecnt = 1

if pid == 0: #must execute this code root authority.
    subprocess.call(['./pcm-icsl.x','-e','icsl','-csv=./log/pcm.csv'])
    os._exit(0)
else:
    time.sleep(1.6)
    pr_flag = 1 #print flag. for printing detection message only once.

    #tensorflow session open and restore weight and bias from meta file
    sess = tf.Session()
    saver = tf.train.import_meta_graph('./metafile_loop/detect_model_loop.meta')
    saver.restore(sess,tf.train.latest_checkpoint('./metafile_loop/'))

    x = tf.placeholder(tf.float32, shape=[None, 5])
    y = tf.placeholder(tf.float32, shape=[None, 1])

    graph = tf.get_default_graph()
    w = sess.run(graph.get_tensor_by_name('weight:0'))
    b = sess.run(graph.get_tensor_by_name('bias:0'))

    # set hypothesis
    logits = tf.matmul(x, w) + b
    hypo = tf.nn.softmax(logits)

    prediction = tf.argmax(hypo, 1)
    tf.global_variables_initializer()

    #start program.
    print("\nDetecting Unit program started.\n")
    print("Detecting..")
    while 1:
        input = np.loadtxt('./log/pcm.csv', delimiter=',' , dtype=np.float32, skiprows=1+cur_line, usecols=range(0,7))
        if len(input) is 0:
            continue
        if sys.getsizeof(input[0]) > 30:
            input = input[len(input)-1]
        input_func = [input[0], input[3], input[4], input[5], input[6]]
        #print(input_func)
        result = sess.run(prediction, feed_dict={x: [input_func, ]})
        #print result.
        if result[0] == 1:
                print("\nFLUSH+RELOAD Detected.")
        elif result[0] == 2:
                print("\nFLUSH+FLUSH Detected.")
        elif result[0] == 3:
                print("\nPRIME+PROBE Detected.")
        else:
                print("..", end='')	
        cur_line = cur_line + 1
        time.sleep(1)
	

        if cur_line is 20: #truncate file and save log data
            #cmd = "cp ./log/pcm.csv ./log/pcm_" + str(filecnt) + ".csv"
            #filecnt = filecnt + 1
            #os.system(cmd)
            cur_line = 0
            f = open('./log/pcm.csv','r+')
            f.truncate()
            f.close()
            time.sleep(1.9)
