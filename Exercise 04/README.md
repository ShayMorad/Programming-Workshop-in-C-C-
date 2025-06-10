<div align="center">

# Exercise 04 - Image Recognition (Neural Network)



**Image Recognition, Neural Network** is the fourth assignment I completed in the *Programming Workshop in C/C++* course at the HUJI.

In this project, I implemented a simple **feedforward neural network** (MLP - Multi-Layer Perceptron) for handwritten digit classification using C++. The program loads pre-trained weights and biases from binary files, processes input images, and outputs the predicted digit along with its probability.

This exercise provided hands-on experience with object-oriented programming in C++, matrix operations, file handling, and image classification logic.

[**« Return to Main Repository**](https://github.com/ShayMorad/Programming-Workshop-in-C-CPP)
</div>


## Running the Project

To compile and run the program locally:

1. Clone the repository:  
   ```bash
   git clone <repo_url>
   ```

2. Navigate to the exercise folder:  
   ```bash
   cd Exercise 04
   ```

3. Compile using `g++` (or use the provided Makefile if available):  
   ```bash
   g++ -std=c++11 main.cpp MlpNetwork.cpp Matrix.cpp Dense.cpp Activation.cpp -o mlpnetwork
   ```

4. Run the program with all required model parameters:  
   ```bash
   ./mlpnetwork w1 w2 w3 w4 b1 b2 b3 b4
   ```

   - `w1` to `w4` – Paths to the binary weight files for layers 1–4  
   - `b1` to `b4` – Paths to the binary bias files for layers 1–4  

5. Once running, input image file paths when prompted, or type `q` to quit.  
   Example interaction:
   ```
   Please insert image path:
   data/img_0.bin
   Image processed:
   <Matrix output>
   Mlp result: 7 at probability: 0.91
   ```



## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.



## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

