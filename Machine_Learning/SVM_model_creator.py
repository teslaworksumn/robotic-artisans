from sklearn import datasets, metrics, svm
from sklearn.preprocessing import scale
from sklearn.model_selection import train_test_split
import numpy as np
import pickle
import numpy as np

# create a SVM model of the dataset, and save the object with pickle
def makeModel():
    # for sklearn, the labels need to be as an int, for Tensorflow its better as the file is
    def convertLabelsToInt(table):
        array = []
        for y in table:
            for x in range(len(y)):
                if(y[x] == 1):
                    array += [x]
        return array

    # Split the 'digits' data into training and test sets
    # separate the data from the target attributes
    X_train = np.loadtxt('train/images_train.csv', delimiter=',')
    Y_train = convertLabelsToInt(np.loadtxt('train/labels_train.csv', delimiter=','))
    X_test = np.loadtxt('train/images_test.csv', delimiter=',')
    Y_test = convertLabelsToInt(np.loadtxt('train/labels_test.csv', delimiter=','))

    # Create the svc model
    svc_model = svm.SVC(gamma = 0.001, C = 100., kernel = 'linear')

    # Fit the data to the SVC model
    svc_model.fit(X_train, Y_train)

    # Train and score a new classifier with the grid search parameters
    print(svm.SVC(C=10, kernel = 'rbf', gamma = 0.001).fit(X_train, Y_train).score(X_test, Y_test))

    # Predict the label of `X_test`
    print(svc_model.predict(X_test))

    # Print `y_test` to check the results
    print(Y_test)

    # Assign the predicted values to 'predicted'
    predicted = svc_model.predict(X_test)

    # Print the classification report of `y_test` and `predicted`
    print(metrics.classification_report(Y_test, predicted))

    # Print the confusion matrix
    print(metrics.confusion_matrix(Y_test, predicted))

    # Save model for later use
    file = open("svc_model.p", "wb")
    pickle.dump(svc_model, file)

# load the pickle file and predict the input image with the model
def predict(img_arr):
    with open('svc_model.p', 'rb') as input_file:
        predictor = pickle.load(input_file)
    return predictor.predict(img_arr)

if __name__ == '__main__':
    makeModel()
