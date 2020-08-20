#  Trained model code.
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.

import tensorflow as tf
import store_dict as sdic
import numpy as np

### Parameters ####
condition = 12
nb_classes = len(sdic.store_dict)
##################

def Recommandation(import_data):
    x = tf.placeholder(dtype = tf.float32, shape = [None, condition])
    y = tf.placeholder(dtype = tf.int32, shape = [None, 1]) #for softmax
    y_one_hot = tf.one_hot(y, nb_classes)
    y_one_hot = tf.reshape(y_one_hot, [-1, nb_classes])

    with tf.name_scope("layer1") as scope: ## layer 1  : condition -> 100
        w1 = tf.get_variable("w1", shape=[condition, 70], initializer = tf.contrib.layers.xavier_initializer())
        b1 = tf.Variable(tf.random_normal([70]))
        layer1 = tf.nn.softmax(tf.matmul(x, w1) + b1)

    with tf.name_scope("layer2") as scope: ## layer 2  : 100 -> 50
        w2 = tf.get_variable("w2", shape=[70, 50], initializer = tf.contrib.layers.xavier_initializer())
        b2 = tf.Variable(tf.random_normal([50]))
        layer2 = tf.nn.softmax(tf.matmul(layer1, w2) + b2)

    with tf.name_scope("layer3") as scope: ## layer 3  : 50 -> 30
        w3 = tf.get_variable("w3", shape=[50, 30], initializer = tf.contrib.layers.xavier_initializer())
        b3 = tf.Variable(tf.random_normal([30]))
        layer3 = tf.nn.softmax(tf.matmul(layer2, w3) + b3)

    w = tf.Variable(tf.random_normal([30, nb_classes]))
    b = tf.Variable(tf.random_normal([nb_classes]))

    logits = tf.matmul(layer3,w) + b
    hypo = tf.nn.softmax(logits)

    prediction = tf.argmax(hypo,1)

    return_val = 0 #initializing return value
    saver = tf.train.Saver()
    
    with tf.Session() as sess:
        saver = tf.train.import_meta_graph('Trained_model.ckpt.meta')
        saver.restore(sess, tf.train.latest_checkpoint('./'))
        ans = sess.run(prediction, feed_dict = {x:[import_data,]})
        return_val = ans[0]
    return return_val

