#include "markov_chain.h"
#define FILE_LINE_LENGTH 1001
#define TWEET_LENGTH 20
#define NO_WORDS_CAP 4
#define WORDS_CAP 5
#define STRTOL_BASE 10
#define WORDS_BASE (-1)

/**
 * Fills the linked list database with nodes that contain all the necessary
 * data.
 * @param fp file path to open.
 * @param words_to_read if filled by user, caps amount of words read from file.
 * @param markov_chain
 * @return 0 on success, 1 on failure.
 */
static int fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain);

/**
 * Creates tweets and prints them to stdout.
 * @param seed
 * @param tweets
 * @param corpus
 * @param words_to_read
 * @return 0 on success, 1 on failure.
 */
static void tweets_generator (int tweets, MarkovChain
*markov_chain_pointer);

static int create_database (MarkovChain *markov_chain);

static void print_func (void *data);

static int comp_func (void *data1, void *data2);

static void free_data (void *data);

static void *copy_generic_data (void *data);

static bool is_last (void *data);

int main (int argc, char *argv[])
{
  if (argc != NO_WORDS_CAP && argc != WORDS_CAP)
  {
    fprintf (stdout, "Usage: wrong arg count. Use program in following "
                     "template: <program_path> <seed> <num_of_tweets> "
                     "<corpus_path> <num_of_words_to_read> \n");
    return EXIT_FAILURE;
  }
  int words_to_read = WORDS_BASE;
  char *corpus = argv[3];
  unsigned int seed = strtol (argv[1], NULL, STRTOL_BASE);
  srand (seed);
  int tweets = strtol (argv[2], NULL, STRTOL_BASE);
  if (argc == WORDS_CAP)
  {
    words_to_read = strtol (argv[4], NULL, STRTOL_BASE);
  }
  FILE *text_corpus = fopen (corpus, "r");
  if (text_corpus == NULL)
  {
    fprintf (stdout, "Error: Could not open corpus file.\n");
    return EXIT_FAILURE;
  }
  struct MarkovChain *markov_chain = malloc (sizeof (struct MarkovChain));
  if (markov_chain == NULL)
  {
    fclose (text_corpus);
    printf ("%s", ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  if (create_database (markov_chain))
  {
    fclose (text_corpus);
    return EXIT_FAILURE;
  }
  int res = fill_database (text_corpus, words_to_read, markov_chain);
  if (res == 0)
  {
    tweets_generator (tweets, markov_chain);
    fclose (text_corpus);
    return EXIT_SUCCESS;
  }
  fclose (text_corpus);
  free_database (&markov_chain);
  return EXIT_FAILURE;
}

static int comp_func (void *data1, void *data2)
{
  char *dataa1 = (char *) data1;
  char *dataa2 = (char *) data2;
  int result = strcmp (dataa1, dataa2);
  return result;
}

static void free_data (void *data)
{
  free (((char *) data));
}

static bool is_last (void *data)
{
  char *dataa = (char *) data;
  if (dataa[strlen (dataa) - 1] != '.')
  {
    return false;
  }
  return true;
}

static void *copy_generic_data (void *data)
{
  char *dataa = (char *) data;
  void *new_data = malloc (sizeof (char) * (strlen (dataa) + 1));
  if (new_data == NULL)
  {
    return NULL;
  }
  memcpy (new_data, data, sizeof (char) * (strlen (dataa) + 1));
  return new_data;
}

static void print_func (void *data)
{
  char *dataa = (char *) data;
  if (is_last (data))
  {
    fprintf (stdout, "%s", dataa);
    return;
  }
  else
  {
    fprintf (stdout, "%s ", dataa);
  }
}

static int fill_database (FILE *fp, int words_to_read, MarkovChain
*markov_chain)
{
  char words_from_file[FILE_LINE_LENGTH];
  Node *cur_word = NULL;
  Node *prev_word = NULL;
  while (fgets (words_from_file, FILE_LINE_LENGTH, fp))
  {
    char *string = strtok (words_from_file, " \n\t\r");
    while (string != NULL)
    {
      cur_word = add_to_database (markov_chain, string);
      if (cur_word == NULL)
      {
        fprintf (stdout, "%s", ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
      }
      if (prev_word != NULL)
      {
        if (add_node_to_frequencies_list (prev_word->data,
                                          cur_word->data, markov_chain) == 0)
        {
          fprintf (stdout, "%s", ALLOCATION_ERROR_MASSAGE);
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

static void tweets_generator (int tweets, MarkovChain *markov_chain_pointer)
{
  int i = 1;
  while (i < tweets + 1)
  {
    fprintf (stdout, "Tweet %d: ", i);
    generate_tweet (markov_chain_pointer, NULL, TWEET_LENGTH);
    printf ("\n");
    i++;
  }
  free_database (&markov_chain_pointer);
}

static int create_database (MarkovChain *markov_chain)
{
  markov_chain->database = malloc (sizeof (struct LinkedList));
  if (markov_chain->database == NULL)
  {
    free (markov_chain);
    printf ("%s", ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  markov_chain->database->first = NULL;
  markov_chain->database->last = NULL;
  markov_chain->database->size = 0;
  markov_chain->copy_func = &copy_generic_data;
  markov_chain->comp_func = &comp_func;
  markov_chain->print_func = &print_func;
  markov_chain->is_last = &is_last;
  markov_chain->free_data = &free_data;
  return EXIT_SUCCESS;
}
