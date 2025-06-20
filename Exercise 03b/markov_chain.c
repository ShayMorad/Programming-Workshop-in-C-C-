#include "markov_chain.h"

#define EQUAL_STRINGS 0

/////////////////FUNCTION DECLARATIONS/////////////////////

/**
 * Get random number between 0 and max_number [0,max_number).
 * @param max_number maximal number to return (not including)
 * @return Random number
 */
int get_random_number (int max_number);

/**
 *  This function makes a new markov node and returns it.
 * @param word_data the word we create a markov node for.
 * @return the created markov node.
 */
MarkovNode *create_node (void *word_data);

/**
 * This function returns the total frequencies of other markov nodes for the
 * current markov node.
 * @param markov_node node to check for its following nodes frequencies.
 * @return total frequencies.
 */
int get_total_frequencies (MarkovNode *markov_node);

/**
 * This function returns the pointer index of the random node drawn by the
 * random int function.
 * @param markov_node node to check for its following node index.
 * @param randi the random integer drew by the random integer function.
 * @return arithmetic index for next random markov node.
 */
int get_random_node_pointer_index (MarkovNode *markov_node, int randi);

/////////////////FUNCTION DECLARATIONS/////////////////////


/////////////////IMPLEMENTATION/////////////////////

Node *add_to_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *node_to_add = get_node_from_database (markov_chain, data_ptr);

  if (node_to_add == NULL)
  {
    MarkovNode *node = create_node (NULL);
    if(node == NULL)
    {
      return NULL;
    }
    node->data = markov_chain->copy_func(data_ptr);
    if(node->data == NULL)
    {
      free(node);
      return NULL;
    }

    if (((add (markov_chain->database, node)) != 1) && (node != NULL))
    {
      return markov_chain->database->last;
    }
    free(node->data);
    node->data = NULL;
    free(node);
    node = NULL;
    return NULL;

  }
  else
  {
    return node_to_add;
  }
}

Node *get_node_from_database (MarkovChain *markov_chain, void *data_ptr)
{
  Node *node_from_database = markov_chain->database->first;
  if (node_from_database != NULL)
  {
    for (int i = 0; i < markov_chain->database->size; i++)
    {
      if (node_from_database == NULL)
      {
        return NULL;
      }
      if (markov_chain->comp_func (node_from_database->data->data, data_ptr) ==
          EQUAL_STRINGS)
      {
        return node_from_database;
      }
      node_from_database = node_from_database->next;
    }
  }
  return NULL;
}

MarkovNode *create_node (void *word_data)
{
  MarkovNode *node = malloc (sizeof (MarkovNode));
  if (node != NULL)
  {
    node->data = word_data;
    node->frequencies_list = NULL;
    node->frequency_list_size = 0;
    return node;
  }
  return NULL;
}

bool add_node_to_frequencies_list (MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain)
{
  MarkovNodeFrequency *freq_node = NULL;
  //checking if second node exists in first node freq list
  for (int i = 0; i < (first_node->frequency_list_size); i++)
  {
    //if second node exists, increase his freq by 1
    if (!markov_chain->comp_func((first_node->frequencies_list + i)
                                     ->markov_node->data, second_node->data))
    {
      freq_node = (first_node->frequencies_list) + i;
    }
  }
  if (freq_node == NULL)
  {
    first_node->frequency_list_size++;
    MarkovNodeFrequency *temp_freq_list = realloc
        (first_node->frequencies_list, first_node->frequency_list_size
                                       * sizeof (MarkovNodeFrequency));
    if (temp_freq_list != NULL)
    {
      first_node->frequencies_list = temp_freq_list;
      freq_node = (first_node->frequencies_list +
                   (first_node->frequency_list_size - 1));
      freq_node->markov_node = second_node;
      freq_node->frequency = 1;
      return 1;
    }
    return 0;
  }
  freq_node->frequency = freq_node->frequency + 1;
  return 1;
}

void free_database (MarkovChain **ptr_chain)
{
  if((*ptr_chain)->database==NULL)
  {
    free(*ptr_chain);
    *ptr_chain = NULL;
    return;
  }
  Node *first_node;
  first_node = (*ptr_chain)->database->first;
  while (first_node != NULL)
  {
    Node *next_node = first_node->next;
    // freeing memory by order: 1.frequency list 2.string data pointer
    // 3.markov node 4.linked list node
    free (first_node->data->frequencies_list);
    first_node->data->frequencies_list = NULL;
    (*ptr_chain)->free_data (first_node->data->data);
    first_node->data->data = NULL;
    free (first_node->data);
    first_node->data = NULL;
    free (first_node);
    first_node = next_node;
  }
  free((*ptr_chain)->database);
  (*ptr_chain)->database = NULL;
  free(*ptr_chain);
  *ptr_chain = NULL;
}

int get_random_number (int max_number)
{
  return (rand () % max_number);
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  Node *node = NULL;
  MarkovNode *markov_node = NULL;
  int correct = false;
  int max_node = markov_chain->database->size;
  while (correct != true)
  {
    node = markov_chain->database->first;
    int randi = get_random_number (max_node);
    while (randi > 0)
    {
      node = node->next;
      randi--;
    }
    markov_node = node->data;
    if ((!markov_chain->is_last (markov_node->data)) &&
        ((markov_node->frequency_list_size) > 0))
    {
      correct = true;
      break;
    }
  }
  return markov_node;
}

MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  int total_frequencies = get_total_frequencies (state_struct_ptr);
  int randi = get_random_number (total_frequencies);
  int next_random_index = get_random_node_pointer_index (state_struct_ptr,
                                                         randi);
  MarkovNode *next_random_node =
      ((state_struct_ptr->frequencies_list) + next_random_index)->markov_node;
  return next_random_node;
}

int get_total_frequencies (MarkovNode *markov_node)
{
  int frequency_nodes = markov_node->frequency_list_size;
  int total_frequencies = 0;
  for (int i = 0; i < frequency_nodes; i++)
  {
    // check this if fails
    int freq_node_freq = ((markov_node->frequencies_list) + i)->
        frequency;
    total_frequencies += freq_node_freq;
  }
  return total_frequencies;
}

int get_random_node_pointer_index (MarkovNode *markov_node, int randi)
{
  int pointer_i = 0;
  int next_nodes_frequencies = 0;
  while (next_nodes_frequencies <= randi)
  {
    // check this if fails
    next_nodes_frequencies += ((markov_node->frequencies_list) + pointer_i)
        ->frequency;
    if (next_nodes_frequencies > randi)
    {
      return pointer_i;
    }
    pointer_i++;
  }
  return pointer_i;
}

void generate_tweet (MarkovChain *markov_chain,
                               MarkovNode *first_node, int max_length)
{
  if (first_node == NULL)
  {
    first_node = get_first_random_node (markov_chain);
  }
  int tweet_length = 1;
  MarkovNode *next_node = NULL;
  MarkovNode *first = first_node;
  for (int i = 0; i < max_length; i++)
  {
    if (i == 0 && tweet_length <= max_length)
    {
      markov_chain->print_func (first->data);
      continue;
    }
    else
    {
      next_node = get_next_random_node (first);
      if (tweet_length < max_length
          && !markov_chain->is_last (next_node->data))
      {
        markov_chain->print_func (next_node->data);
        tweet_length++;
        first = next_node;
        continue;
      }
      break;
    }
  }
  if (tweet_length < max_length)
  {
    markov_chain->print_func (next_node->data);
  }
}

/////////////////IMPLEMENTATION/////////////////////