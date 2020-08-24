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
l_rate = float(input("Input learning rate: "))

print("start {} training. learning rate : {}".format(cnt + 1, l_rate))
train_xy = np.loadtxt(sys.argv[1], delimiter=',' , dtype=np.float32, skiprows=1, usecols=range(0,6))

x_data = train_xy[:,0:-1]
y_data = train_xy[:,[-1]]

xcnt = len(x_data[0])
x = tf.placeholder(tf.float32, shape=[None, xcnt])
y = tf.placeholder(tf.int32, shape=[None,1])
Y_one_hot = tf.one_hot(y, nb_classes)  # one hot
Y_one_hot = tf.reshape(Y_one_hot, [-1, nb_classes])


w = tf.Variable(tf.random_normal([xcnt,nb_classes]),name='weight')
b = tf.Variable(tf.random_normal([nb_classes]),name = 'bias')

logits = tf.matmul(x, w) + b
hypothesis = tf.nn.softmax(logits)

# Cross entropy cost/loss
cost_i = tf.nn.softmax_cross_entropy_with_logits_v2(logits=logits,
                                                 labels=tf.stop_gradient([Y_one_hot]))
cost = tf.reduce_mean(cost_i)
#optimizer = tf.train.GradientDescentOptimizer(learning_rate=l_rate).minimize(cost)
optimizer = tf.train.AdamOptimizer(learning_rate=l_rate).minimize(cost)
prediction = tf.argmax(hypothesis, 1)
correct_prediction = tf.equal(prediction, tf.argmax(Y_one_hot, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())

    for step in range(stepp):
        sess.run(optimizer, feed_dict={x: x_data, y: y_data})
        if step % 1000 == 0:
            loss, acc = sess.run([cost, accuracy], feed_dict={
                                 x: x_data, y: y_data})
            print("Step: {:5}\tLoss: {:.8f}\tAcc: {:.2%}".format(
                step, loss, acc))
    saver = tf.train.Saver()
    saver.save(sess, "./metafile_loop/detect_model_loop")
