/* Lingfei Lu A91046735
 * Junxi Li A91105747
 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>

 using namespace std;
/*
 * Test the run time of DictionaryTrie. each case run 5 times and take the average
 */
 void testTrie(int min_size, int step_size, int num_iterations, string dict_filename)
 {

 	ifstream in;
	//result is used to store dictionary size and time to search
 	vector<int> result(0);
 	DictionaryTrie* dictionary_trie;
	//use loop to increase the dictionary size
 	for(int i = 0; i < num_iterations; i++)
 	{

 		dictionary_trie = new DictionaryTrie();
		//open dictionary
 		in.open(dict_filename, ios::binary);
		//create a dictionary trie
 		Utils::load_dict(*dictionary_trie, in, (min_size + step_size * i));
 		in.close();

 		long long sum = 0;
		//run 10 cases 5 times and take the average
 		for(int j = 0; j < 5; j++){
 			Timer T;
 			vector<string> results;
 			long long time_duration;
 			T.begin_timer();
			//10 cases
 			dictionary_trie->find("does nt stop is");
 			dictionary_trie->find("dakota fanling");
 			dictionary_trie->find("zymologi");
 			dictionary_trie->find("faces mo");
 			dictionary_trie->find("inue aovjn fgl ljv weak");
 			dictionary_trie->find("will beter back next weak");
 			dictionary_trie->find("i acnosi bvml oeirtu xklvn");
 			dictionary_trie->find("will be back hext aosid");
 			dictionary_trie->find("eoriyu sdjfn backd asd weak");
 			dictionary_trie->find("next gb dfd osdig");
 			time_duration = T.end_timer();
 			sum += time_duration;
 		}
		//add dictionary size and time used to search
 		result.push_back(min_size + step_size * i);
 		result.push_back(sum/10);

 	}

 	cout << "DictionaryTrie" << endl;
	//print out the result
 	for(int i = 0; i < num_iterations*2-1; i+=2){
 		cout << result[i] << "\t" << result[i+1] << endl;
 	}
 	delete dictionary_trie;
 }

/*
 * Test the run time of DictionaryBST. each case run 5 times and take the average
 */
 void testBST(int min_size, int step_size, int num_iterations, string dict_filename)
 {

 	ifstream in;
	//result is used to store dictionary size and time to search
 	vector<int> result(0);
 	DictionaryBST* dictionary_BST;
	//use loop to increase the dictionary size
 	for(int i = 0; i < num_iterations; i++)
 	{

 		dictionary_BST = new DictionaryBST();
		//open dictionary
 		in.open(dict_filename, ios::binary);
 		Utils::load_dict(*dictionary_BST, in, (min_size + step_size * i));
 		in.close();

 		long long sum = 0;
		//run 10 cases 5 times and take the average
 		for(int j = 0; j < 5; j++){
 			Timer T;
 			vector<string> results;
 			long long time_duration;
 			T.begin_timer();
			//10 cases
 			dictionary_BST->find("does nt stop is");
 			dictionary_BST->find("dakota fanling");
 			dictionary_BST->find("zymologi");
 			dictionary_BST->find("faces mo");
 			dictionary_BST->find("inue aovjn fgl ljv weak");
 			dictionary_BST->find("will beter back next weak");
 			dictionary_BST->find("i acnosi bvml oeirtu xklvn");
 			dictionary_BST->find("will be back hext aosid");
 			dictionary_BST->find("eoriyu sdjfn backd asd weak");
 			dictionary_BST->find("next gb dfd osdig");
 			time_duration = T.end_timer();
 			sum += time_duration;
 		}
		//add dictionary size and time used to search
 		result.push_back(min_size + step_size * i);
 		result.push_back(sum/10);

 	}

 	cout << "DictionaryBST" << endl;
	//print out the result
 	for(int i = 0; i < num_iterations*2-1; i+=2){
 		cout << result[i] << " " << result[i+1] << endl;
 	}
 	delete dictionary_BST;
 }

/*
 * Test the run time of DictionaryBST. each case run 5 times and take the average
 */
 void testHashTable(int min_size, int step_size, int num_iterations, string dict_filename)
 {

 	ifstream in;
	//result is used to store dictionary size and time to search
 	vector<int> result(0);
	//use loop to increase the dictionary size
 	DictionaryHashtable *dictionary_HashTable;
 	for(int i = 0; i < num_iterations; i++)
 	{

 		dictionary_HashTable = new DictionaryHashtable();
		//open dictionary
 		in.open(dict_filename, ios::binary);
 		Utils::load_dict(*dictionary_HashTable, in, (min_size + step_size * i));
 		in.close();

 		long long sum = 0;
		//run 10 cases 5 times and take the average
 		for(int j = 0; j < 5; j++){
 			Timer T;
 			vector<string> results;
 			long long time_duration;
 			T.begin_timer();
			//10 cases
 			dictionary_HashTable->find("does nt stop is");
 			dictionary_HashTable->find("dakota fanling");
 			dictionary_HashTable->find("zymologi");
 			dictionary_HashTable->find("faces mo");
 			dictionary_HashTable->find("hacker is fgl ljv weak");
 			dictionary_HashTable->find("well be back next weak");
 			dictionary_HashTable->find("unique word oeirtu xklvn");
 			dictionary_HashTable->find("aerospace hext aosid");
 			dictionary_HashTable->find("zzzzzzz backd asd weak");
 			dictionary_HashTable->find("next one dfd osdig");
 			time_duration = T.end_timer();
 			sum += time_duration;
 		}
		//add dictionary size and time used to search
 		result.push_back(min_size + step_size * i);
 		result.push_back(sum/10);

 	}

 	cout << "DictionaryHashTable" << endl;
	//print out the result
 	for(int i = 0; i < num_iterations*2-1; i+=2){
 		cout << result[i] << " " << result[i+1] << endl;
 	}
 	delete dictionary_HashTable;
 }

 int main(int argc, char *argv[])
 {
	//check if there 4 arguments
 	if(argc != 5){
 		cout << "Incorrect number of arguments." << endl;
 		cout << "\t First argument: name of dictionary file." << endl;
 		cout << endl;
 		exit(-1);
 	}
	//convert string to int
 	int min_size = atoi(argv[1]);
 	int step_size = atoi(argv[2]);
 	int num_iterations = atoi(argv[3]);
	//calll testcases
 	testTrie(min_size, step_size, num_iterations, argv[4]);
 	testBST(min_size, step_size, num_iterations, argv[4]);
 	testHashTable(min_size, step_size, num_iterations, argv[4]);

 }