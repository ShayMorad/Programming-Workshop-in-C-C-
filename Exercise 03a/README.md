<div align="center">

# Exercise 03a - Markov Tweets



**Markov Tweets** is the third assignment (Part A) I completed in the *Programming Workshop in C/C++* course at the HUJI.

In this project, I implemented a basic **Natural Language Processing** system using the **Markov Chain model**. The program learns word transitions from a text corpus and generates pseudo-random tweets that mimic the input style. It also provided hands-on experience with **linked lists**, **dynamic memory allocation**, and **probabilistic modeling** in C.

[**« Return to Main Repository**](https://github.com/ShayMorad/Programming-Workshop-in-C-CPP)
</div>

## Running the Project

To compile and run the program locally:

1. Clone the repository:  
   `git clone <repo_url>`

2. Navigate to the exercise folder:  
   `cd Exercise 03a`

3. Compile the program using `gcc`:  
   ```
   gcc -o markov tweets_generator.c markov_chain.c markov_chain.h
   ```

4. To **generate tweets**, run:  
   ```
   ./markov <seed> <num_of_tweets> <corpus_path> [num_of_words_to_read]
   ```
   - `seed`: Random seed for reproducibility  
   - `num_of_tweets`: How many tweets to generate  
   - `corpus_path`: Path to the text file to learn from  
   - `num_of_words_to_read` (optional): Limit on words to read from the corpus

   **Examples:**
   ```
   ./markov 42 5 input.txt
   ./markov 123 3 input.txt 100
   ```



## Contributions

Contributions are encouraged! For any significant changes, it's best to open an issue first and start a discussion.



## License

This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

