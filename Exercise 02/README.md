<div align="center">

# Exercise 02 - Bus Lines


**Bus Lines** is the second assignment I completed in the *Programming Workshop in C/C++* course at the Hebrew University of Jerusalem.

In this project, I implemented a sorting program for public bus line data using both **bubble sort** and **quick sort** algorithms. The exercise focuses on core C concepts like **dynamic memory allocation**, **structs**, **arrays**, and **pointer manipulation**. It also includes a test mode that validates sorting correctness and memory safety.

[**« Return to Main Repository**](https://github.com/ShayMorad/C-CPP-Workshop)

</div>


## How to Run

To compile and run the program locally:

1. Clone the repository:  
   `git clone <repo_url>`

2. Navigate to the exercise folder:  
   `cd Exercise 02`

3. Compile the program using `gcc`:  
   ```
   gcc -o bus_lines main.c sort_bus_lines.c sort_bus_lines.h test_bus_lines.c test_bus_lines.h
   ```

4. To **run** the program (you will be prompted to enter bus line data):  
   ```
   ./bus_lines by_name        # Sort by name using bubble sort  
   ./bus_lines by_duration    # Sort by duration using quick sort  
   ./bus_lines by_distance    # Sort by distance using quick sort  
   ```

5. To **run tests**:  
   ```
   ./bus_lines test
   ```


## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.


## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).
