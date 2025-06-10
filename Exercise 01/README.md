<div align="center">

# Exercise 01 - Cipher



**Cipher** is the first assignment I completed in the *Programming Workshop in C/C++* course at the Hebrew University of Jerusalem.

In this exercise, I implemented a Caesar Cipher encryption program in C. It supports both encoding and decoding of English alphabetic characters, with cyclic and non-cyclic behavior based on the shift value `k`. The program also includes a built-in test mode to validate various encoding and decoding scenarios.

[**« Return to Main Repository**](https://github.com/ShayMorad/Programming-Workshop-in-C-CPP)
</div>


## Running the Project

To compile and run the program locally:

1. Clone the repository:  
   `git clone <repo_url>`

2. Navigate to the exercise folder:  
   `cd Exercise 01`

3. Compile the program using `gcc`:  
   `gcc -o cipher cipher.c cipher.h tests.c tests.h`

4. To **run** the program:  
   ```
   ./cipher encode|decode <k> <input_file> <output_file>
   ```
   - Example:  
     `./cipher encode 3 input.txt encoded.txt`

5. To **run tests**:  
   ```
   ./cipher test
   ```


## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.


## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).
