/* Lingfei Lu A91046735
 * Junxi Li A91105747
 */
#include "DictionaryTrie.hpp"
#include <queue>
#include <iostream>
 using namespace std;
 typedef pair<Multiway_Node*, int> p;

//create a mapping
 const unsigned char MAPPING[] = {
  'a',
  'b',
  'c',
  'd',
  'e',
  'f',
  'g',
  'h',
  'i',
  'j',
  'k',
  'l',
  'm',
  'n',
  'o',
  'p',
  'q',
  'r',
  's',
  't',
  'u',
  'v',
  'w',
  'x',
  'y',
  'z',
  ' '
};

int REVERSE_MAPPING[122];

/*
 * create revverse mapping, input a character return a number
 */
 void createReverseMapping(){

  for(int i=0; i<27; i++){
    REVERSE_MAPPING[MAPPING[i]] = i;
  }
}

/*
 * Max comparator for frontier to compare max_freq
 */
 class MaxComparator	{
 public:
  bool operator()(p& lhs, p& rhs) const{
      //compare frequency
    if(lhs.second != rhs.second)
      return lhs.second < rhs.second;
      //compare alphbebatic roder
    return lhs.first->code < rhs.first->code;
  }
};
/*
 * Min comparator for loader to compare freq
 */
 class MinComparator {
 public:
  bool operator()(p& lhs, p&rhs) const{
      //if not equal, then compare freq
    if(lhs.second != rhs.second)
      return lhs.second > rhs.second;
      //if equal, then compare lexographical order
    return lhs.first->code < rhs.first->code;
  }
};

/*
 * Multiway_Node is the back_end structure for DictionaryTrie class, it has
 * bool value isKey to determine if current node is a key and freq keep track
 * of the frequency of word
 */
 Multiway_Node::Multiway_Node(bool isKey, int freq, int max_freq){
  //initialize isKey and freq
  this->isKey = isKey;
  this->freq = freq;
  this->max_freq = max_freq;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
  //initializr DictionaryTrie object
  root =  new Multiway_Node(false, 0, 0);
}
/*
 * Passed in a word and its freq, insert it into DictionaryTrie.
 * If the word already exists in the DictionaryTrie, then return false
 * else, insert and return true
 */
 bool DictionaryTrie::insert(string word, unsigned int freq)
 {
  createReverseMapping();
  if(word.length() == 0)
    return false;

  Multiway_Node *curr = root;
  //if the word already there, return false
  if(this->find(word))
    return false;

  for(unsigned int i = 0; i < word.length(); i++)
  {
    //if the word suffix does not exist, then create it
    if(curr->arr[REVERSE_MAPPING[(int)word[i]]] == 0)
    {
      Multiway_Node *child = new Multiway_Node(false, 0, 0);
      curr->arr[REVERSE_MAPPING[(int)word[i]]] = child;
      //store the strng in the node
      curr->arr[REVERSE_MAPPING[(int)word[i]]]->code = curr->code + word[i];
    }
    //update max freq
    if(curr->arr[REVERSE_MAPPING[(int)word[i]]]->max_freq < freq)
      curr->arr[REVERSE_MAPPING[(int)word[i]]]->max_freq = freq;

    //go to the next node
    curr = curr->arr[REVERSE_MAPPING[(int)word[i]]];
  }
  //last node is the real string node, therefore, it has freq and iskey is true
  curr->freq = freq;
  curr->isKey = true;
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(string word) const
{
  //create reverse mapping
  createReverseMapping();
  Multiway_Node * curr = root;
  //loop through word
  for(unsigned int i = 0; i < word.length(); i++)
  {
    //check if we can go to next node
    if(curr->arr[REVERSE_MAPPING[(int)word[i]]] != 0)
      curr = curr->arr[REVERSE_MAPPING[(int)word[i]]];
    else 
      return false;
  }
  //is curr is a key return key
  if(curr->isKey)	return true;
  return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
vector<string> DictionaryTrie::predictCompletions(string prefix, unsigned int num_completions)
{
  //create reverse mapping for the arr
  createReverseMapping();
  vector<string> words(0);
  if(num_completions <= 0 && prefix.length() == 0)  return words;

  Multiway_Node* curr = root;
  for(unsigned int i = 0; i < prefix.length(); i++)
  {
    if(curr->arr[REVERSE_MAPPING[(int)prefix[i]]] == 0 || 
      (prefix[i] < 'a' && prefix[i] != ' ') || (prefix[i] > 'z'))
      //if does exist such prefix or illegal character, return empty vector
      return words;
    //go to next one
    curr = curr->arr[REVERSE_MAPPING[(int)prefix[i]]];
  }
  //////////////////
  //loader is the real strings that are potentially most frequent
  priority_queue<p, vector<p>, MinComparator> loader;
  //frontier contains what possible be explore, min heap
  priority_queue<p, vector<p>, MaxComparator> frontier;
  //push the prefix root into the frontier
  frontier.push(p(curr, curr->max_freq));

  do{
    //if frontier top is a key, then it is possibly one output
    //need to push into the loader
    if(frontier.top().first->isKey){
      loader.push(p(frontier.top().first, frontier.top().first->freq));
    }
    //once loader size exceeds num_completions, pop out the least.
    if(loader.size() > num_completions){
      loader.pop();
    }
    //before the top pops, get the top first in order to explore its children
    curr = frontier.top().first;
    frontier.pop();

    //exploring its children
    for(int i = 0; i < 27; i++){
      if(curr->arr[i] != 0){
        frontier.push(p(curr->arr[i], curr->arr[i]->max_freq));
      }
    }
  }while(!frontier.empty() && 
   (loader.size() < num_completions || loader.top().second < frontier.top().second));
  //do-while condition: 1. if frontier is not empty, means we still have 
  //available string to explore, don't stop. 2. if loader is not full, 
  //or the minimum element in the loader is not greater than 
  //the maximum element in the frontier, then continue the loop


  //transfer elements from loader to words
  while(loader.size() > 0){
    words.insert(words.begin(), loader.top().first->code);
    loader.pop();
  }
  return words; 
}
/*
 * delete all 
 */
 void deleteAll(Multiway_Node* node){
  if(node == 0)   return;
  //delete array
  for(int i = 0; i < 27; i++){
    deleteAll(node->arr[i]);
  }
  //delete node
  delete node;
}
/* Destructor */

DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}
