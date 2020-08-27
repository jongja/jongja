# Training code
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import tensorflow as tf
import numpy as np
import store_dict as sdic
import os
import convStrtofloat as stf

### Parameters ####
LearningRate = 0.03 # the best result
condition = 12 
nb_classes = len(sdic.store_dict)
nb_step = 8001  #how many train
##################
def search_csvfile() :
    filenames = os.listdir('./training_file') # training_file 디렉토리의 모든 .csv 파일 list로 저장.
    for filename in filenames :
        print('All file : ', filenames)
        print ('File found : ', filename)
        Training_function(filename, 0)
        print(filename, 'training complete.')

def Training_function(filename, store_num) :
    if store_num != 0 :
        data = np.loadtxt('./training_file/' + filename + '.csv', delimiter=',', dtype='str')

        temp = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
        temp = np.r_[[temp]]

        for i in range(0, len(data)) :
            if i == 0 :
                temp_data = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
                temp_data = np.r_[[temp_data]]

            else :
                temp_data = np.vstack([temp_data, temp])
        stf.ConvertStringtofloat(data, temp_data, len(data))

        k = 0
        for i in temp_data :
            if k == 0 :
                k = 1
                temp = i
            if i[-1] == float(store_num[0]) :
                continue
            if i[-1] == float(store_num[1]) :
                continue
            if i[-1] == float(store_num[2]) :
                continue
            temp = np.vstack([temp, i])
        x_data = temp[:,0:-1]
        y_data = temp[:,[-1]]

    elif store_num == 0 :
        data = np.loadtxt('./training_file/' + filename, delimiter=',', dtype='str')

        temp = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
        temp = np.r_[[temp]]

        for i in range(0, len(data)):
            if i == 0:
                temp_data = np.array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
                temp_data = np.r_[[temp_data]]
            else:
                temp_data = np.vstack([temp_data, temp])
        stf.ConvertStringtofloat(data, temp_data, len(data))

        filename = filename.split('.')
        filename = filename[0]  # id.csv -> id
        x_data = temp_data[:,0:-1]
        y_data = temp_data[:,[-1]]

    x = tf.placeholder(dtype = tf.float32, shape = [None, condition])
    y = tf.placeholder(dtype = tf.int32, shape = [None, 1]) #for softmax
    y_one_hot = tf.one_hot(y, nb_classes)
    y_one_hot = tf.reshape(y_one_hot, [-1, nb_classes])

    #with tf.name_scope("layer1") as scope: ## layer 1  : condition -> 100
    w1 = tf.get_variable("weight1", shape=[condition, 70], initializer = tf.contrib.layers.xavier_initializer())
    b1 = tf.Variable(tf.random_normal([70]), name = "bias1")
    layer1 = tf.nn.softmax(tf.matmul(x, w1) + b1)

    #with tf.name_scope("layer2") as scope: ## layer 2  : 100 -> 50
    w2 = tf.get_variable("weight2", shape=[70, 50], initializer = tf.contrib.layers.xavier_initializer())
    b2 = tf.Variable(tf.random_normal([50]), name = "bias2")
    layer2 = tf.nn.softmax(tf.matmul(layer1, w2) + b2)

    #with tf.name_scope("layer3") as scope: ## layer 3  : 50 -> 30
    w3 = tf.get_variable("weight3", shape=[50, 30], initializer = tf.contrib.layers.xavier_initializer())
    b3 = tf.Variable(tf.random_normal([30]), name = "bias3")
    layer3 = tf.nn.softmax(tf.matmul(layer2, w3) + b3)

    w = tf.Variable(tf.random_normal([30, nb_classes]), name="weight")
    b = tf.Variable(tf.random_normal([nb_classes]), name = 'bias')

    logits = tf.matmul(layer3, w) + b
    hypo = tf.nn.softmax(logits)
    cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits = logits, labels = y_one_hot)
    cost = tf.reduce_mean(cost_i)

    train = tf.train.AdamOptimizer(learning_rate=LearningRate).minimize(cost)
    prediction = tf.argmax(hypo,1)
    cor_predict = tf.equal(prediction, tf.argmax(y_one_hot,1))
    accuracy = tf.reduce_mean(tf.cast(cor_predict, dtype=tf.float32))

    #return_val ='' #initializing return value
    saver = tf.train.Saver()

    ###### Training #######
    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        feed = {x: x_data, y: y_data}
        print("Training start.")
        for step in range(nb_step):
            sess.run(train, feed_dict= feed)
            if step % 1000 == 0:
                print("Step: {}\t\tLoss: {}".format(step, sess.run(cost, feed_dict=feed)))
        print("End Train.")
        ############ TEST #################
        acc = sess.run(accuracy, feed_dict=feed)
        print("Accuracy {:.2%}".format(acc))
        saver.save(sess, './trained_meta/'+ filename + '/'+filename+'.ckpt')
        tf.train.write_graph(sess.graph_def, ".", 'Trained_model.pb', as_text=False)

        training_data = temp_data[len(temp_data)-1][0:-1]
        training_data = np.r_[[training_data]]

        feed = {x: training_data}
        pred_value = sess.run(prediction, feed_dict=feed)

    tf.reset_default_graph()

    if store_num != 0:
        temp_data[len(temp_data)-1][-1] = pred_value[0] # renew re-recommending food number
        f = open('./training_file/' + filename + '.csv', 'w')
        for i in range(0, len(temp_data)) : # re-store all data.
            for j, k in zip(temp_data[i], range(0, len(temp_data[i]))) :
                f.write('%d' % j)
                if k != len(temp_data[i]) - 1 :
                   f.write(',')
            f.write('\n')
        f.close()

    return sdic.store_dict[pred_value[0]]