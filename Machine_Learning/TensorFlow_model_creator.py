import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import pickle
import numpy as np
import pandas as pd

def read_and_decode_single_example():
    filename_queue = tf.train.string_input_producer(['shapes_data.csv'])

    reader = tf.TextLineReader()
    key, value = reader.read(filename_queue)

    record_defaults = [[0]] * 401
    columns = tf.decode_csv(records = value, record_defaults = record_defaults)
    features = tf.stack(list(columns)[:-1])

    with tf.Session() as sess:
      # Start populating the filename queue.
      coord = tf.train.Coordinator()
      threads = tf.train.start_queue_runners(coord=coord)

      # Retrieve a single instance:
      image, label = sess.run([features, columns[-1]])

      coord.request_stop()
      coord.join(threads)
      return (label, image)

# get single example
label, image = read_and_decode_single_example()
# groups examples into batches randomly
image = tf.cast(image, tf.float32) / 255
# simple model
x = tf.placeholder(tf.float32, [None, 400])
W = tf.Variable(tf.zeros([400, 3]))
b = tf.Variable(tf.zeros([3]))
y = tf.nn.softmax(tf.matmul(x, W) + b)

y_ = tf.placeholder(tf.float32, [None, 3])

cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))

train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

sess = tf.InteractiveSession()
init = tf.global_variables_initializer().run()

for _ in range(1):
    images_batch, labels_batch = tf.train.batch([image, label], batch_size = 10)
    tf.train.start_queue_runners(sess)
    images_batch = images_batch.eval()
    labels_batch = labels_batch.eval()
    sess.run(train_step, feed_dict={x: images_batch, y_: [[1,0,0]]*10})
