'''
    Create a Convolutional Neural Network using the Tensorflow API
    to classify images of shapes
'''

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import tensorflow as tf
import numpy as np

tf.logging.set_verbosity(tf.logging.INFO)

width, height = 48, 48
shape_classes = 3

def cnn_model_fn(features, labels, mode):
    '''model function for CNN'''
    # input layer
    # input tensors must have shape of [batch_size, image_width, image_height, channels]
    # -1 for batch size means it will be dynamically computed
    input_layer = tf.reshape(features["x"], [-1, width, height, 1])

    #convolutional layer #1
    #conv1 has shape of [batch_size, 48, 48, 32]
    conv1 = tf.layers.conv2d(
        inputs=input_layer,     #input tensor
        filters=32,             #specifies the number of filters to apply
        kernel_size=[5,5],      #dimensions of the filters as [width, height]
        padding="same",         #takes either "valid" or "same" as arg. Same prevents resizing of output
        activation=tf.nn.relu   #activation function -- ReLU activation
    )

    #pooling layer #1
    #pool1 shape is [batch_size, 24, 24, 32]
    pool1 = tf.layers.max_pooling2d(inputs=conv1, pool_size=[2,2], strides=2)

    #convolutional layer #2
    #conv2 has shape [batch_size, 24, 24, 64]
    conv2 = tf.layers.conv2d(
        inputs=pool1,
        filters=64,
        kernel_size=[5,5],
        padding="same",
        activation=tf.nn.relu
    )

    #pooling layer #2
    #pool2 has shape [bathch_size, 12, 12, 64]
    pool2 = tf.layers.max_pooling2d(inputs=conv2, pool_size=[2,2], strides=2)

    #dense layer
    pool2_flat = tf.reshape(pool2, [-1, int(width/4*height/4)*64])
    dense = tf.layers.dense(inputs=pool2_flat, units=1024, activation=tf.nn.relu)
    dropout = tf.layers.dropout(inputs=dense, rate=0.4, training=mode == tf.estimator.ModeKeys.TRAIN)

    #final layer in network. return the raw values for predictions
    #create a dense layer with 3 neurons, one for each target (square, circle, triangle)
    #has shape [batch_size, 3]
    logits = tf.layers.dense(inputs=dropout, units=3)

    predictions = {
        #generate predictions (for PREDICT and EVAL mode)
        "classes":tf.argmax(input=logits, axis=1),
        #add 'softmax_tensor' to the graph it it used for PREDICT and by the 'logging_hook'
        "probabilities":tf.nn.softmax(logits, name="softmax_tensor")
    }

    if mode == tf.estimator.ModeKeys.PREDICT:
        return tf.estimator.EstimatorSpec(mode=mode, predictions=predictions)

    #calculate loss (for both TRAIN and EVAL modes)
    onehot_labels = tf.one_hot(indices=tf.cast(labels, tf.int32), depth=shape_classes)
    loss = tf.losses.softmax_cross_entropy(onehot_labels=onehot_labels, logits=logits)

    #configure the training op
    if mode == tf.estimator.ModeKeys.TRAIN:
        optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.001)
        train_op = optimizer.minimize(loss=loss, global_step=tf.train.get_global_step())
        return tf.estimator.EstimatorSpec(mode=mode, loss=loss, train_op=train_op)

    #add evaluation metrics
    eval_metric_ops = {
        "accuracy":tf.metrics.accuracy(labels=labels, predictions=predictions['classes'])
    }
    return tf.estimator.EstimatorSpec(mode=mode, loss=loss, eval_metric_ops=eval_metric_ops)

def main(unused_argv):
    #load training and eval datasets
    train_data = np.loadtxt('train/images_train.csv', delimiter=',', dtype=np.float32)
    train_labels = np.loadtxt('train/labels_train.csv', delimiter=',', dtype=np.int32)
    eval_data = np.loadtxt('train/images_test.csv', delimiter=',', dtype=np.float32)
    eval_labels = np.loadtxt('train/labels_test.csv', delimiter=',', dtype=np.int32)

    #create the estimator
    clf = tf.estimator.Estimator(model_fn=cnn_model_fn, model_dir="/tmp/model")

    #set up logging for predictions
    #log the values in the "softmax" tensor with label "probabilities"
    tensors_to_log = {"probabilities":"softmax_tensor"}
    logging_hook = tf.train.LoggingTensorHook(tensors=tensors_to_log, every_n_iter=50)

    #train the model_f
    train_input_fn = tf.estimator.inputs.numpy_input_fn(
        x={"x": train_data},
        y=train_labels,
        batch_size=100,
        num_epochs=None,
        shuffle=True
    )
    clf.train(
        input_fn=train_input_fn,
        steps=20000,
        hooks=[logging_hook]
    )

    #evaluate the model and print results
    eval_input_fn = tf.estimator.inputs.numpy_input_fn(
        x={"x": eval_data},
        y=eval_labels,
        num_epochs=1,
        shuffle=False
    )
    eval_results = clf.evaluate(input_fn=eval_input_fn)
    print(eval_results)

if __name__ == "__main__":
    tf.app.run()
