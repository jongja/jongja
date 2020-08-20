# Training code
#  Created by Imagic 2018
#  Copyright © 2018 Imaigc All rights reserved.


import tensorflow as tf
import numpy as np
import store_dict as sdic
    
### Parameters ####
LearningRate = 0.03 # the best result
condition = 12 
nb_classes = len(sdic.store_dict)
nb_step = 8001  #how many train
##################

data = np.loadtxt('Training_data.csv', delimiter = ',', dtype = np.float32)

x_data = data[:,0:-1]
y_data = data[:,[-1]]

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
cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits = logits, labels = y_one_hot)
cost = tf.reduce_mean(cost_i)

train = tf.train.AdamOptimizer(learning_rate=LearningRate).minimize(cost)
prediction = tf.argmax(hypo,1)
cor_predict = tf.equal(prediction, tf.argmax(y_one_hot,1))
accuracy = tf.reduce_mean(tf.cast(cor_predict, dtype=tf.float32))

return_val ='' #initializing return value
saver = tf.train.Saver()

###### Training #######
with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    feed = {x:x_data, y:y_data}
    print("Training start.")
    for step in range(nb_step):
        sess.run(train, feed_dict= feed)
        if step % 1000 ==0:
            print("Step: {}\t\tLoss: {}".format(step, sess.run(cost, feed_dict=feed)))
    print("End Train.")
    ############ TEST #################
    acc = sess.run(accuracy, feed_dict=feed)
    print("Accuracy {:.2%}".format(acc))
    saver.save(sess, './Trained_model.ckpt')
    tf.train.write_graph(sess.graph_def, ".", 'Trained_model.pb', as_text=False)

