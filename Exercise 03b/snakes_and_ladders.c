#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60
#define STRTOL_BASE 10
#define ARGC_AMOUNT 3
#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

static void print_func (void *data);

static int comp_func (void *data1, void *data2);

static void free_data (void *data);

static void *copy_generic_data (void *data);

static bool is_last (void *data);
/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell
{
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case
    // there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error (char *error_msg, MarkovChain **database)
{
  printf ("%s", error_msg);
  if (database != NULL)
  {
    free_database (database);
  }
  return EXIT_FAILURE;
}

static int create_board (Cell *cells[BOARD_SIZE])
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    cells[i] = malloc (sizeof (Cell));
    if (cells[i] == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free (cells[j]);
      }
      handle_error (ALLOCATION_ERROR_MASSAGE, NULL);
      return EXIT_FAILURE;
    }
    *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
  }

  for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
  {
    int from = transitions[i][0];
    int to = transitions[i][1];
    if (from < to)
    {
      cells[from - 1]->ladder_to = to;
    }
    else
    {
      cells[from - 1]->snake_to = to;
    }
  }
  return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database (MarkovChain *markov_chain)
{
  Cell *cells[BOARD_SIZE];
  if (create_board (cells) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  MarkovNode *from_node = NULL, *to_node = NULL;
  size_t index_to;
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    add_to_database (markov_chain, cells[i]);
  }

  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    from_node = get_node_from_database (markov_chain, cells[i])->data;

    if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
    {
      index_to = MAX(cells[i]->snake_to, cells[i]->ladder_to) - 1;
      to_node = get_node_from_database (markov_chain, cells[index_to])
          ->data;
      add_node_to_frequencies_list (from_node, to_node, markov_chain);
    }
    else
    {
      for (int j = 1; j <= DICE_MAX; j++)
      {
        index_to = ((Cell *) (from_node->data))->number + j - 1;
        if (index_to >= BOARD_SIZE)
        {
          break;
        }
        to_node = get_node_from_database (markov_chain, cells[index_to])
            ->data;
        add_node_to_frequencies_list (from_node, to_node, markov_chain);
      }
    }
  }
  // free temp arr
  for (size_t i = 0; i < BOARD_SIZE; i++)
  {
    free (cells[i]);
  }
  return EXIT_SUCCESS;
}

static void print_func (void *data)
{
  char *ladder_to_str = "-ladder to ";
  char *snake_to_str = "-snake to ";
  if (((Cell *) data)->ladder_to == EMPTY && ((Cell *) data)->snake_to ==
                                             EMPTY)
  {
    if (is_last (data))
    {
      fprintf (stdout, "[%d]", ((Cell *) data)->number);
    }
    else
    {
      fprintf (stdout, "[%d] -> ", ((Cell *) data)->number);
    }
  }
  else if (((Cell *) data)->ladder_to != EMPTY)
  {
    if (is_last (data))
    {
      fprintf (stdout, "[%d]%s%d", ((Cell *) data)->number, ladder_to_str,
               ((Cell *) data)->ladder_to);
    }
    else
    {
      fprintf (stdout, "[%d]%s%d -> ", ((Cell *) data)->number, ladder_to_str,
               ((Cell *) data)->ladder_to);
    }
  }
  else if (((Cell *) data)->snake_to != EMPTY)
  {
    if (is_last (data))
    {
      fprintf (stdout, "[%d]%s%d", ((Cell *) data)->number, snake_to_str,
               ((Cell *) data)->snake_to);
    }
    else
    {
      fprintf (stdout, "[%d]%s%d -> ", ((Cell *) data)->number, snake_to_str,
               ((Cell *) data)->snake_to);
    }
  }
}

static int comp_func (void *data1, void *data2)
{
  return (((Cell *) data1)->number - ((Cell *) data2)->number);
}

static void free_data (void *data)
{
  free (((Cell *) data));
}

static void *copy_generic_data (void *data)
{
  void *copy = malloc (sizeof (Cell));
  if (copy == NULL)
  {
    return NULL;
  }
  //check this
  memcpy (copy, data, sizeof (Cell));
  return copy;
}

static bool is_last (void *data)
{
  return (((Cell *) data)->number == BOARD_SIZE);
}

static int create_database (MarkovChain *markov_chain);

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */

int main (int argc, char *argv[])
{
  if (argc != ARGC_AMOUNT)
  {
    fprintf (stdout, "Usage: wrong arg count. Use program in following "
                     "template:\n "
                     "<program_path> <seed> <num_of_paths>\n");
    return EXIT_FAILURE;
  }
  struct MarkovChain *markov_chain = malloc (sizeof (struct MarkovChain));
  if (markov_chain == NULL)
  {
    printf ("%s", ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  if (create_database (markov_chain))
  {
    return EXIT_FAILURE;
  }
  unsigned int seed = strtol (argv[1], NULL, STRTOL_BASE);
  srand (seed);
  int num_of_paths = strtol (argv[2], NULL, STRTOL_BASE);
  int res = fill_database (markov_chain);
  if (res == EXIT_FAILURE)
  {
    free_database (&markov_chain);
    return EXIT_FAILURE;
  }
  MarkovNode *first_cell = markov_chain->database->first->data;
  int pathway = 1;
  while (pathway < num_of_paths + 1)
  {
    fprintf (stdout, "Random Walk %d: ", pathway);
    generate_tweet (markov_chain, first_cell,
                    MAX_GENERATION_LENGTH);
    pathway++;
    putchar ('\n');
  }
  free_database (&markov_chain);
  return EXIT_SUCCESS;
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
