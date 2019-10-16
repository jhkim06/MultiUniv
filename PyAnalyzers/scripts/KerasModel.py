from keras.models import Sequential
from keras.layers.core import Dense, Activation, Dropout
from keras.layers.normalization import BatchNormalization
from keras import initializers
from keras.optimizers import SGD

# Define initialization
def normal(shape, name=None):
  return initializers.normal(shape, scale=0.05, name=name)

# Generate model
class KerasModel():

  def __init__(self):
    self.model = Sequential()


  def defineModel_3layer(self,input_dim_):
    # Define model
    # we can think of this chunk as the input layer
    self.model.add(Dense(256, input_dim=input_dim_, init='uniform'))
    self.model.add(BatchNormalization())
    self.model.add(Activation('relu'))
    self.model.add(Dropout(0.5))

    # we can think of this chunk as the input layer
    self.model.add(Dense(128, init='uniform'))
    self.model.add(BatchNormalization())
    self.model.add(Activation('relu'))
    self.model.add(Dropout(0.5))

    # we can think of this chunk as the hidden layer    
    self.model.add(Dense(64, init='uniform'))
    self.model.add(BatchNormalization())
    self.model.add(Activation('relu'))
    self.model.add(Dropout(0.5))

    # we can think of this chunk as the output layer
    self.model.add(Dense(2, init='uniform'))
    self.model.add(BatchNormalization())
    self.model.add(Activation('softmax'))

    #self.model.add(Dense(64, kernel_initializer=initializers.he_normal(seed=None), activation='relu', input_dim=input_dim_))
    #self.model.add(Dense(32, kernel_initializer=initializers.he_normal(seed=None), activation='relu'))
    #self.model.add(Dense(2, kernel_initializer=initializers.he_normal(seed=None), activation='softmax'))

  def compile(self,loss_='categorical_crossentropy',
		   optimizer_=SGD(lr=0.1,decay=1e-5),
		   metrics_=['accuracy',]
	     ):
    # Set loss and optimizer
    self.model.compile(loss=loss_, optimizer=optimizer_, metrics=metrics_)

  def save(self, modelName="model.h5"):
    self.model.save(modelName)
  
  def summary(self):
    self.model.summary()

	       
		  
