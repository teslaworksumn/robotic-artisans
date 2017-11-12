import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import pickle
import numpy as np

IMG_DIMENSIONS = (100, 100)
IMG_SIZE = IMG_DIMENSIONS[0]*IMG_DIMENSIONS[1]

def read_and_decode_single_example(files):
    filename_queue = tf.train.string_input_producer([files['images']])
    labels_queue = tf.train.string_input_producer([files['labels']])
    reader = tf.TextLineReader()
    labelreader = tf.TextLineReader()
    key, value = reader.read(filename_queue)
    key, label_list = labelreader.read(labels_queue)

    record_defaults = [[0]] * IMG_SIZE
    columns = tf.decode_csv(records = value, record_defaults = record_defaults)
    features = tf.stack(list(columns))
    label_columns = tf.decode_csv(records = label_list, record_defaults = [[0]] * 3)
    with tf.Session() as sess:
      # Start populating the filename queue.
      coord = tf.train.Coordinator()
      threads = tf.train.start_queue_runners(coord=coord)

      # Retrieve a single instance:
      image, label = sess.run([features, label_columns])

      coord.request_stop()
      coord.join(threads)
      return (label, image)

# get single example
label, image = read_and_decode_single_example({'images': 'train/images_train.csv', 'labels': 'train/labels_train.csv'})
# groups examples into batches randomly
image = tf.cast(image, tf.float32) / 255
# simple model
x = tf.placeholder(tf.float32, [None, IMG_SIZE])
W = tf.Variable(tf.zeros([IMG_SIZE, 3]))
b = tf.Variable(tf.zeros([3]))
y = tf.nn.softmax(tf.matmul(x, W) + b)

y_ = tf.placeholder(tf.float32, [None, 3])

cross_entropy = tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(y), reduction_indices=[1]))

train_step = tf.train.GradientDescentOptimizer(0.5).minimize(cross_entropy)

sess = tf.InteractiveSession()
init = tf.global_variables_initializer().run()

for _ in range(10):
    images_batch, labels_batch = tf.train.batch([image, label], batch_size = 20)
    tf.train.start_queue_runners(sess)
    images_batch = images_batch.eval()
    labels_batch = labels_batch.eval()

correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
image_test, label_test = read_and_decode_single_example({'images': 'train/images_test.csv', 'labels': 'train/labels_test.csv'})
image_test = tf.cast(image_test, tf.float32) / 255
label_test_batch, image_test_batch = tf.train.batch([image_test, label_test], batch_size = 29)
tf.train.start_queue_runners(sess)
label_test_batch = label_test_batch.eval()
image_test_batch = image_test_batch.eval()

sess.run(train_step, feed_dict={x: images_batch, y_: labels_batch})
tf.train.start_queue_runners(sess)

print(sess.run(accuracy, feed_dict = {x: image_test_batch, y_: label_test_batch}))
