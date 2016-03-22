/* Lingfei Lu A91046735
 * Junxi Li A91105747
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <utility>
 using namespace std;
/**
 * Multiway node, includes an array to its children, iskey boolean
 * max_freq represents the max freq possible in the subtree under this node
 */
 class Multiway_Node
 {
 public:
  //reate a arr to store multiway node pointer
  Multiway_Node* arr[27] = {0};
  bool isKey;
  unsigned int max_freq;
  unsigned int freq;
  string code = "";
  //constructor
  Multiway_Node(bool isKey, int freq, int max_freq);
};


class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
    bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
    bool find(std::string word) const;

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
std::vector<std::string>
predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
~DictionaryTrie();

private:
  Multiway_Node* root;
};

#endif // DICTIONARY_TRIE_HPP
