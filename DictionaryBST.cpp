/* Lingfei Lu A91046735
 * Junxi Li A91105747
 */
#include "DictionaryBST.hpp"
#include <set>

 using namespace std;
/* Create a new Dictionary that uses a BST back end */
 DictionaryBST::DictionaryBST()
 {
 	BST = new set<string>();
 }

/* Insert a word into the dictionary. */
 bool DictionaryBST::insert(std::string word)
 {
  //insert return a pair<iterator, bool>, return whatever the bool is
 	return BST->insert(word).second;
 }

/* Return true if word is in the dictionary, and false otherwise */
 bool DictionaryBST::find(std::string word) const
 {
  //if not found, it would return a iterator pointing to the end
  //of the set, therefore, check if it is the end of the set
 	return (BST->find(word) != BST->end());
 }

/* Destructor */
 DictionaryBST::~DictionaryBST()
 {
  //clear and delete the set
 	BST->clear();
 	delete BST;
 }
