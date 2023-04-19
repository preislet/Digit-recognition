# Digit recognition
Semestral project for subject: Programing in C++

## About program
The program is designed as a learning platform for a better understanding of neural networks and their weaknesses. 
**The program is now focused on MLP networks** (one of the expansions may be to add other types of networks). The user can insert any images of numbers [0-9], which are subsequently recognized by the neural network. User can use a pre-trained network (92% success rate), create and train his own network. Both the creation and training of the network is included in the user interface, so the user does not need to know how to code neural networks, but is still able to use the program. If the user develops and trains a network, he can choose to save it. In this case, the program remembers the network and can be used even after restarting the program

## About code
The neural network is written using standard libraries only (the neural network libraries are not used at all). Winforms are used for GUI. Tests can be started by adding argument -test: `./digit-recognition -test`.

## important files
Neural network is designed especially for MNIST dataset in .csv format. You can download dataset in .csv format here:
- [Train file](https://drive.google.com/file/d/156TQ-3QJC6vaDW-GeF6V6TKsuOJtKumA/view?usp=share_link)
- [Test.file](https://drive.google.com/file/d/1I67mUbpdDnrOYxavNFyRgkU9uRtppQmb/view?usp=share_link)

These two files need to be inserted into folder with source files if user want to train his own neural netwrok.
