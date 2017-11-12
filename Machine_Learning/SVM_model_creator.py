from sklearn import datasets, metrics, svm
from sklearn.preprocessing import scale
from sklearn.model_selection import train_test_split
import numpy as np
import pickle
import numpy as np

# Location of the shapes dataset
dataset = '../dataset_processor/shapes_data.txt'
# load the CSV file as a numpy matrix
dataset = np.loadtxt(dataset, delimiter=" ")
# separate the data from the target attributes
X = dataset[:,0:249999]
y = dataset[:,250000]

# Split the 'digits' data into training and test sets
X_train, X_test, Y_train, Y_test = train_test_split(X, y, test_size = 0.25, random_state = 42)

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
