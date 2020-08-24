# FLUSH+RELOAD training code.
# Created by JongHyeon Cho in kwangwoon uni. 2019
# Copyright @ 2019 JongHyeon Cho All right reserved.

import tensorflow as tf
import numpy as np
import math
import sys
#parameters
mcnt = 10
cnt = 0
nb_classes = 4

if len(sys.argv) is 1:
    print('Usage : python3 training.py <training CSV>\n')
    exit()
stepp = int(input("Input step: "))
l_rate= float(input("Input learning rate : "))
print("start {} training. learning rate : {}".format(cnt + 1, l_rate))
train_xy = np.loadtxt(sys.argv[1], delimiter=',' , dtype=np.float32, skiprows=1, usecols=range(0,6))

x_data = train_xy[:,0:-1]
y_data = train_xy[:,[-1]]

xcnt = len(x_data[0])
x = tf.compat.v1.placeholder(tf.float32, shape=[None, xcnt])
y = tf.compat.v1.placeholder(tf.int32, shape=[None,1])
Y_one_hot = tf.one_hot(y, nb_classes)  # one hot
Y_one_hot = tf.reshape(Y_one_hot, [-1, nb_classes])

w1 = tf.compat.v1.get_variable("w1", shape=[xcnt, 20], initializer = tf.contrib.layers.xavier_initializer())
b1 = tf.Variable(tf.random_normal([20]), name='b1')
layer1 = tf.nn.sigmoid(tf.matmul(x, w1) + b1)
    
w2 = tf.compat.v1.get_variable("w2", shape=[20, 10], initializer = tf.contrib.layers.xavier_initializer())
b2 = tf.Variable(tf.random_normal([10]), name='b2')
layer2 = tf.nn.relu(tf.matmul(layer1, w2) + b2)

w3 = tf.compat.v1.get_variable("w3", shape=[10, 7], initializer = tf.contrib.layers.xavier_initializer())
b3 = tf.Variable(tf.random_normal([7]), name='b3')
layer3 = tf.nn.relu(tf.matmul(layer2, w3) + b3)

w = tf.Variable(tf.random.normal([7,nb_classes]),name='weight')
b = tf.Variable(tf.random.normal([nb_classes]),name = 'bias')

logits = tf.matmul(layer3, w) + b
hypothesis = tf.nn.softmax(logits)

# Cross entropy cost/loss
cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits=logits,
                                                 labels=tf.stop_gradient([Y_one_hot]))
cost = tf.reduce_mean(cost_i)
#optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.05).minimize(cost)
optimizer = tf.compat.v1.train.AdamOptimizer(learning_rate=l_rate).minimize(cost)
prediction = tf.argmax(hypothesis, 1)
correct_prediction = tf.equal(prediction, tf.argmax(Y_one_hot, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

with tf.compat.v1.Session() as sess:
    sess.run(tf.global_variables_initializer())

    for step in range(stepp):
        sess.run(optimizer, feed_dict={x: x_data, y: y_data})
        if step % 1000 == 0:
            loss, acc = sess.run([cost, accuracy], feed_dict={
                                 x: x_data, y: y_data})
            print("Step: {:5}\tLoss: {:.8f}\tAcc: {:.2%}".format(
                step, loss, acc))
    saver = tf.train.Saver()
    saver.save(sess, "./metafile_deep/detect_deep_model")
