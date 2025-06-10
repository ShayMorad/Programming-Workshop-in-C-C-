<div align="center">

# Exercise 05 - Movie Recommender



**Movie Recommender** is the fifth assignment I completed in the *Programming Workshop in C/C++* course at the Hebrew University of Jerusalem.

This exercise focuses on building a movie recommendation system using both **content-based filtering** and **collaborative filtering (CF)** methods. It involves working with **STL data structures**, **smart pointers**, and modular C++ design, emphasizing memory safety and software architecture. The system reads movie features and user ratings from files, calculates similarity metrics, and generates predictions for unseen movies.

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
   cd Exercise 05
   ```

3. Compile using `g++` with all source files:  
   ```bash
   g++ -std=c++11 main.cpp RecommendationSystem.cpp UsersLoader.cpp \
       RecommendationSystemLoader.cpp User.cpp Movie.cpp -o recommender
   ```

4. Run the program with two input files:  
   ```bash
   ./recommender movies.txt users.txt
   ```

   - `movies.txt` – Contains movie names, release years, and feature vectors  
   - `users.txt` – Contains usernames and corresponding ratings for the movies

5. The program will:
   - Load all movies and users
   - Print content-based and collaborative filtering recommendations for each user


## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.



## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

