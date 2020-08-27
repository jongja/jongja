#  Trained model code.
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import tensorflow as tf
import store_dict as sdic
import numpy as np
import os

def check_metaDir(userid) :
    DIR_names = os.listdir('./trained_meta')
    for DIR_name in DIR_names :
        if DIR_name == userid :
            return 0
    return 1 # not found Directory

def Recommand(receivedData) :
    ### Parameters ####
    LearningRate = 0.03  # the best result
    condition = 12
    nb_classes = len(sdic.store_dict)
    nb_step = 8001  # how many train
    ##################

    UserID = receivedData[1]
    input_data = receivedData[2:]
    print(UserID, input_data)

    data = np.array([input_data])

    x_data = data[0:] # [['0' '0' '1' '1' '0' '0' '0' '0' '0' '1' '0' '1']] (1, 12) <class 'numpy.ndarray'>
    x = tf.placeholder(dtype = tf.float32, shape = [None, condition])
    y = tf.placeholder(dtype = tf.int32, shape = [None, 1]) #for softmax

    y_one_hot = tf.one_hot(y, nb_classes)
    y_one_hot = tf.reshape(y_one_hot, [-1, nb_classes])
    with tf.Session() as sess:
        if check_metaDir(UserID) == 0 : # meta file existed
            saver = tf.train.import_meta_graph('./trained_meta/'+UserID+'/'+UserID+'.ckpt.meta')
            saver.restore(sess, tf.train.latest_checkpoint('./trained_meta/'+UserID+'/'))
        else :
            saver = tf.train.import_meta_graph('./trained_meta/basic_data/Trained_model.ckpt.meta') 
            saver.restore(sess, tf.train.latest_checkpoint('./trained_meta/basic_data/'))

        graph = tf.get_default_graph()
        print("Success for loading Trained model")
        w1 = sess.run(graph.get_tensor_by_name("weight1:0"))
        b1 = sess.run(graph.get_tensor_by_name("bias1:0"))
        layer1 = tf.nn.softmax(tf.matmul(x, w1) + b1)

        w2 = sess.run(graph.get_tensor_by_name("weight2:0"))
        b2 = sess.run(graph.get_tensor_by_name("bias2:0"))
        layer2 = tf.nn.softmax(tf.matmul(layer1, w2) + b2)

        w3 = sess.run(graph.get_tensor_by_name("weight3:0"))
        b3 = sess.run(graph.get_tensor_by_name("bias3:0"))
        layer3 = tf.nn.softmax(tf.matmul(layer2, w3) + b3)

        w = sess.run(graph.get_tensor_by_name("weight:0"))
        b = sess.run(graph.get_tensor_by_name("bias:0"))

        logits = tf.matmul(layer3,w) + b
        hypo = tf.nn.softmax(logits)

        prediction = tf.argmax(hypo,1)
        #cor_predict = tf.equal(prediction, tf.argmax(y_one_hot, 1))
        #accuracy = tf.reduce_mean(tf.cast(cor_predict, dtype=tf.float32))

        feed = {x:x_data}
        pred_value =sess.run(prediction, feed_dict=feed)
    f = open('./training_file/'+ UserID + '.csv', 'a')
    f.write(str(pred_value[0]))
    f.write('\n')
    f.close()
    return sdic.store_dict[pred_value[0]]

