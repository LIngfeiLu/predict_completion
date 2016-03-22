/* Lingfei Lu A91046735
 * Junxi Li A91105747
 */
#include "DictionaryHashtable.hpp"
#include <unordered_set>

 using namespace std;
/* Create a new Dictionary that uses a Hashset back end */
 DictionaryHashtable::DictionaryHashtable()
 {
 	hashTable = new unordered_set<string>();
 }

/* Insert a word into the dictionary. */
 bool DictionaryHashtable::insert(std::string word)
 {
  //insert returns a pair<iterator, bool>, return whatever the bool is
 	return hashTable->insert(word).second;
 }

/* Return true if word is in the dictionary, and false otherwise */
 bool DictionaryHashtable::find(std::string word) const
 {
  //if not found, it would return an iterator pointing at the end of 
  //hashtable, check if it is equal to end of hashtable
 	return (hashTable->find(word) != hashTable->end());
 }

/* Destructor */
 DictionaryHashtable::~DictionaryHashtable()
 {
  //clear and delete the hashtable
 	hashTable->clear();
 	delete hashTable;
 }
