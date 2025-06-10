#include "markov_chain.h"
#define FILE_LINE_LENGTH 1001
#define TWEET_LENGTH 20
#define NO_WORDS_CAP 4
#define WORDS_CAP 5
#define STRTOL_BASE 10

/**
 * Fills the linked list database with nodes that contain all the necessary
 * data.
 * @param fp file path to open.
 * @param words_to_read if filled by user, caps amount of words read from file.
 * @param markov_chain
 * @return 0 on success, 1 on failure.
 */
int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);

/**
 * Creates tweets and prints them to stdout.
 * @param seed
 * @param tweets
 * @param corpus
 * @param words_to_read
 * @return 0 on success, 1 on failure.
 */
int tweets_generator (int tweets, char *corpus, int
words_to_read);

int main (int argc, char *argv[])
{
  if (argc != NO_WORDS_CAP && argc != WORDS_CAP)
  {
    fprintf (stdout, "Usage: wrong arg count. Use program in following "
                     "template:\n "
                     "<program_path> <seed> <num_of_tweets> "
                     "<corpus_path> <num_of_words_to_read> (words to read is"
                     " optional)\n");
    return EXIT_FAILURE;
  }
  int words_to_read = -1;
  char *corpus = argv[3];
  unsigned int seed = strtol (argv[1], NULL, STRTOL_BASE);
  srand (seed);
  int tweets = strtol (argv[2], NULL, STRTOL_BASE);
  if (argc == WORDS_CAP)
  {
    words_to_read = strtol (argv[4], NULL, STRTOL_BASE);
  }
  int res = tweets_generator (tweets, corpus, words_to_read);
  return res;
}

int fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char words_from_file[FILE_LINE_LENGTH];
  Node *cur_word = NULL;
  Node *prev_word = NULL;
  while (fgets (words_from_file, FILE_LINE_LENGTH, fp))
  {
    char *string = strtok (words_from_file, " \n\t\r");
    while (string != NULL)
    {
      char *string_null = calloc (1, strlen (string) + 1);
      if (string_null == NULL)
      {
        fprintf (stdout, "Allocation failure: Could not allocate memory.");
        return EXIT_FAILURE;
      }
      // adding nul char to string because strtok removes it
      memcpy (string_null, string, strlen (string) + 1);
      cur_word = add_to_database (markov_chain, string_null);
      if (prev_word != NULL)
      {
        if (add_node_to_frequencies_list (prev_word->data,
                                          cur_word->data) == 0)
        {
          fprintf (stdout, "Allocation failure: Could not allocate necessary "
                           "memory.\n ");
          return EXIT_FAILURE;
        }
      }
      prev_word = cur_word;
      string = strtok (NULL, " \n\t\r");
      words_to_read = words_to_read - 1;
      if (words_to_read == 0)
      {
        return EXIT_SUCCESS;
      }
    }
  }

  return EXIT_SUCCESS;
}

int tweets_generator (int tweets, char *corpus, int
words_to_read)
{
  FILE *text_corpus = fopen (corpus, "r");
  if (text_corpus == NULL)
  {
    fprintf (stdout, "Error: Could not open corpus file.\n");
    return EXIT_FAILURE;
  }
  MarkovChain markov_chain, (*markov_chain_pointer);
  LinkedList list;
  list.first = NULL;
  list.last = NULL;
  list.size = 0;
  markov_chain.database = &list;
  markov_chain_pointer = &markov_chain;
  int res = fill_database (text_corpus, words_to_read, markov_chain_pointer);
  if (res == 0)
  {
    int i = 1;
    while (i < tweets + 1)
    {
      fprintf (stdout, "Tweet %d: ", i);
      generate_tweet (markov_chain_pointer, NULL, TWEET_LENGTH);
      i++;
    }
    fclose (text_corpus);
    free_database (&markov_chain_pointer);
    markov_chain_pointer->database = NULL;
    markov_chain_pointer = NULL;
    return EXIT_SUCCESS;
  }
  fclose (text_corpus);
  free_database (&markov_chain_pointer);
  markov_chain_pointer->database = NULL;
  markov_chain_pointer = NULL;
  return EXIT_FAILURE;
}
