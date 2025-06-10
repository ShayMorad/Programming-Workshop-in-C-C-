<div align="center">

# Exercise 03b - Snakes and Ladders



**Snakes and Ladders** is the third assignment (Part B) I completed in the *Programming Workshop in C/C++* course at the HUJI.

In this project, I implemented a simulation of the classic *Snakes and Ladders* board game using **Markov Chains** and **generic programming** in C. The program constructs a probabilistic model of game transitions and performs randomized walks through the game board to simulate possible playthroughs. This exercise also introduced the use of a **Makefile** for building the project.

[**« Return to Main Repository**](https://github.com/ShayMorad/Programming-Workshop-in-C-CPP)
</div>


## Running the Project

To compile and run the program locally:

1. Clone the repository:  
   `git clone <repo_url>`

2. Navigate to the exercise folder:  
   `cd Exercise 03b`

3. Compile the program using `make`:  
   ```
   make
   ```

4. To **run the simulation**, use the following command:  
   ```
   ./snakes_and_ladders <seed> <num_of_paths>
   ```
   - `seed`: Random seed to ensure reproducibility  
   - `num_of_paths`: Number of random board playthroughs to generate

   **Example:**
   ```
   ./snakes_and_ladders 42 5
   ```



## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.



## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

