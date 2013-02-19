
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

//--------------------------------------------
//The nodeType
//--------------------------------------------
template <typename T, typename U>
class nodeType{
public:
	T key;
	U info;
	nodeType *link;
};

//--------------------------------------------
//For error handling
//--------------------------------------------
class Error {};

//--------------------------------------------
//The linked list base class.
//--------------------------------------------
//Complete the methods below.  You can use a singly or doubly linked list if you want.  These methods just must work as stated.
//Your linked list class needs to include functionality for
//a getCount method that returns an integer
//as well as a getItem (which retrieves the data matching a key), the return type is T&
//and a searchForKey (which checks if a node has that key), the return type is bool.
//deleteNodeWithKey doesn't delete nodes containing a certain value, it deletes nodes containing a certain key.
template <typename T, typename U>
class modifiedLinkedList {
protected:
	int count;
	nodeType<T, U> *first;
	nodeType<T, U> *last;
public:

	modifiedLinkedList();
	~modifiedLinkedList();
	void destroyList();
	int getCount();
	void insertLast(const T&, const U&);
	bool nodeWithKeyExists(const T&);
	U& searchForKey(const T&);
	void deleteNodeWithKey(const T&);
		//The iterator class. This is an inner class.
	class iterator {
	friend class modifiedLinkedList;  //friended so the linked list class can modify the iterator.
	public:
		iterator();
		T getKey() const;
		U& getValue() const;
		U& operator*() const;
		iterator operator++();
		bool operator==(const iterator& right) const;
		bool operator!=(const iterator& right) const;

	private:
		nodeType<T,U> *current;   //Where the iterator is pointing to
		bool pastBoundary;
	};

	iterator begin() const;
	iterator end() const;

};

template <typename T, typename U>
modifiedLinkedList<T, U>::modifiedLinkedList(){
	first = NULL;
	last = NULL;
	count = 0;
}

template <typename T, typename U>
modifiedLinkedList<T, U>::~modifiedLinkedList(){
	this->destroyList();
}

//Destroy the list, and reclaim all memory.
template <typename T, typename U>
void modifiedLinkedList<T, U>::destroyList() {
	nodeType<T, U> *temp;
	while (first != NULL) {
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}

//Returns the number of nodes in this linked list.
template <typename T, typename U>
int modifiedLinkedList<T,U>::getCount() {
	return count;
}

//Add/insert an node onto the end of the list.
template <typename T, typename U>
void modifiedLinkedList<T,U>::insertLast(const T& key, const U& value) {
	//TODO: Complete this:
}

template <typename T, typename U>
bool modifiedLinkedList<T, U>::nodeWithKeyExists(const T& key) {
	//TODO: Complete this:
	return true;
}

template <typename T, typename U>
U& modifiedLinkedList<T, U>::searchForKey(const T& key) {
	//TODO: Complete this:
	throw Error();
}

template <typename T, typename U>
void modifiedLinkedList<T, U>::deleteNodeWithKey(const T& key) {
	//TODO: Complete this:
}


//The linked list's begin() method, which returns an iterator object pointing to the first of the list
template <typename T, typename U>
typename modifiedLinkedList<T, U>::iterator modifiedLinkedList<T,U>::begin() const {
	typename modifiedLinkedList<T, U>::iterator temp;
	temp.current = this->first;
	temp.pastBoundary = true;
	return temp;
}

//The linked list's end() method, which returns an iterator object pointing to the first of the list
template <typename T, typename U>
typename modifiedLinkedList<T, U>::iterator modifiedLinkedList<T, U>::end() const {
	typename modifiedLinkedList<T, U>::iterator temp;
	temp.current = this->last;
	temp.pastBoundary = true;
	return temp;
}

//***********************************
//The linked list iterator inner class
//***********************************

//The iterator's constructor
template <typename T, typename U>
modifiedLinkedList<T, U>::iterator::iterator() {
	current = NULL;
	pastBoundary = false;
}

//returns the key this iterator is pointing to
template <typename T, typename U>
T modifiedLinkedList<T, U>::iterator::getKey() const{
	return current->key;
}

//Returns the value this iterator is pointing to
template <typename T, typename U>
U& modifiedLinkedList<T, U>::iterator::getValue() const{
	return current->info;
}

//The iterator's dereference/indirection overloaded operator
template <typename T, typename U>
U& modifiedLinkedList<T, U>::iterator::operator*() const{
	return current->info;
}

template <typename T, typename U>
typename modifiedLinkedList<T, U>::iterator modifiedLinkedList<T,U>::iterator::operator++() {
	pastBoundary = false;
	if (current->link == NULL)
	{
		pastBoundary = true;
	}
	else
	{
		current = current->link;
	}
	return *this;
}

//Compares if two iterators are the same
template <typename T, typename U>
bool modifiedLinkedList<T, U>::iterator::operator==(const iterator& right) const {
	return (current == right.current && pastBoundary == right.pastBoundary);
}

//Compares if two iterators are different
template <typename T, typename U>
bool modifiedLinkedList<T, U>::iterator::operator!=(const iterator& right) const {
	return (current != right.current || pastBoundary != right.pastBoundary);
}

//***********************************
//The hash table class
//***********************************

template <typename T, typename U>
class hashTable{
public:

	hashTable() {}
	hashTable(int(*hashFunction)(const void *));
	~hashTable();


	void add(const T& key, const U& value);
	bool exists(const T& key) const;
	void remove(const T& key);

	U item(const T& key) const;
	U& operator[](const T& key) const;

	//friended so the checkTest function can have access to private data members of this class.
	friend void testSimpleIntHash();
	friend void testHashOfObjects();

	class iterator {
	friend class hashTable;  //friended so the hashTable class can modify the iterator.
	public:
		iterator();
		U& operator*() const;
		iterator operator++();
		bool operator==(const iterator& right) const;
		bool operator!=(const iterator& right) const;
		T getKey() const;
		U& getValue() const;
	private:
	     typename modifiedLinkedList<T,U>::iterator currentIterator;
		int currentLinkedList;
		bool pastBoundary;
		modifiedLinkedList<T, U> *linkedListArray;
	};

	iterator begin() const;
	iterator end() const;

protected:
	//NOTE: This is hard coded for a linked list class called doublyLinkedList.  If your linked list
	//class has a different name, change it both here and in the constructor a few lines down below.
	modifiedLinkedList<T, U> *linkedListArray; //The array of linked lists
	int hash(const T& key) const;
private:
	int getWorstBucket() const;
	int getTotalCount() const;
	int(*hashFunction)(const void*);
	static const int numberOfLinkedLists = 1000;
};

template <typename T, typename U>
hashTable<T,U>::hashTable(int(*hashFunction)(const void*)) {

	this->hashFunction = hashFunction;


	//Initialize an array of 1000 linked lists


}

template <typename T, typename U>
hashTable<T, U>::~hashTable() {
	delete[] linkedListArray;
}

template <typename T, typename U>
void hashTable<T, U>::add(const T& key, const U& value)  {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists


}

template <typename T, typename U>
bool hashTable<T, U>::exists(const T& key) const {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists
	return true;
}

template <typename T, typename U>
U hashTable<T, U>::item(const T& key) const {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists

	U temp; //Just to compile
	return temp;
}

template <typename T, typename U>
U& hashTable<T, U>::operator[](const T& key) const {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists


	U temp; //Just to compile
	return temp;
}

template <typename T, typename U>
int hashTable<T, U>::hash(const T& key) const {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists
	return (*hashFunction)(&key);
}

template <typename T, typename U>
void hashTable<T, U>::remove(const T& key)  {
	//hash the key hash(key)
	//Get the returned index
	//use that index in your array of linked lists


}

template <typename T, typename U>
int hashTable<T, U>::getWorstBucket() const{
	int count;
	int highest = 0;
	for (int i = 0; i < 1000; i++) {
		count = linkedListArray[i].getCount();
		if (count > highest) {
			highest = count;
		}
	}
	return highest;
}

template <typename T, typename U>
int hashTable<T, U>::getTotalCount() const{
	int count;
	int sum = 0;
	for (int i = 0; i < 1000; i++) {
		count = linkedListArray[i].getCount();
		sum += count;
	}
	return sum;
}


template <typename T, typename U>
typename hashTable<T, U>::iterator hashTable<T,U>::begin() const {
     //TODO Extra: (this is not required, but is a challenge that many students requested).
	typename hashTable<T, U>::iterator temp;

	return temp;
}

//The linked list's end() method, which returns an iterator object pointing to the first of the list
template <typename T, typename U>
typename hashTable<T, U>::iterator hashTable<T, U>::end() const {
	typename hashTable<T, U>::iterator temp;
	temp.pastBoundary = true;
	temp.currentLinkedList = 999;
	temp.currentIterator = linkedListArray[999].end();
	temp.linkedListArray = linkedListArray;
	return temp;
}

//***********************************
//The hashtable's iterator inner class
//***********************************

//The iterator's constructor
template <typename T, typename U>
hashTable<T, U>::iterator::iterator() {
}

//The iterator's dereference/indirection overloaded operator
template <typename T, typename U>
U& hashTable<T, U>::iterator::operator*() const{
	return *currentIterator;
}

template <typename T, typename U>
typename hashTable<T, U>::iterator hashTable<T,U>::iterator::operator++() {
	//TODO Extra: (this is not required, but is a challenge that many students requested).

	return *this;
}

//Compares if two iterators are the same
template <typename T, typename U>
bool hashTable<T, U>::iterator::operator==(const iterator& right) const {
	return (currentIterator == right.currentIterator && currentLinkedList == right.currentLinkedList && pastBoundary == right.pastBoundary);
}

//Compares if two iterators are different
template <typename T, typename U>
bool hashTable<T, U>::iterator::operator!=(const iterator& right) const {
	return (currentIterator != right.currentIterator || currentLinkedList != right.currentLinkedList || pastBoundary != right.pastBoundary);
}

//Retrieves the current key of the key/value pair.
template <typename T, typename U>
T hashTable<T, U>::iterator::getKey() const {
	return currentIterator.getKey();
}
//Retrieves the current value of the key/value pair.
template <typename T, typename U>
U& hashTable<T, U>::iterator::getValue() const {
	return currentIterator.getValue();
}

//--------------------------------------------
//Two hash functions for you to complete
//--------------------------------------------

int hashFunctionInt(const void *void_key) {


	//Get that parameter back into an int pointer.
	int *temp = static_cast<int *>(const_cast<void *>(void_key));
	int key = *temp;
	//TODO: Complete this



	return 0;

};

int hashFunctionString(const void *void_key) {
	string *temp = static_cast<string *>(const_cast<void *>(void_key));
	string key = *temp;
	//TODO: Complete this


	return 0;
};


//--------------------------------------------
//A quick and dirty class that simulates a student record for one student.
//--------------------------------------------
class studentRecord {
public:
	void setAge(int age);
	void setGPA(float GPA);
	void setName(const string&);
	string getName();
	string getAllInfo();
private:
	string name;
	int age;
	float GPA;
};
void studentRecord::setAge(int age) {
	this->age = age;
}
void studentRecord::setGPA(float GPA) {
	this->GPA = GPA;
}
void studentRecord::setName(const string& name) {
	this->name = name;
}

string studentRecord::getName() {
	return name;
}
string studentRecord::getAllInfo() {
	stringstream ss;
	ss << "Name: " << name << ", Age: " << age << ", GPA:" << GPA << endl;
	return ss.str();
}




//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been blank. " << endl;
		} else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		}
		return false;
	}
}

//This helps with testing, do not modify.
bool checkEmpty(string testName, string whatItIs) {

	if (whatItIs != "") {
		cout << "Passed " << testName << ", the data was " << whatItIs << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   No data was found! "<< endl;
		return false;
	}
}
//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "   Output was "<< whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
		return false;
	}
}



//This helps with testing, do not modify.
void testSimpleIntHash() {

	//Create a hashTable. We want this to be a hash table with int keys, string object values,
	//And we also supply the hash function we want to use for integers..

	hashTable<int, string> myHash(&hashFunctionInt);

	//Test #1, add "Jazz" into our hash with a key of 6.  Try to retrieve it.
	myHash.add(6, "Jazz");
	checkTest("testSimpleIntHash #1", "Jazz", myHash.item(6));

	//Test #2, attempt to get the Jazz using the operator[] code.
	checkTest("testSimpleIntHash #2", "Jazz", myHash[6]);

	//Test #3, attempt to change the value at this location:
	myHash[6] = "Nuggets";
	checkTest("testSimpleIntHash #3", "Nuggets", myHash[6]);

	//Test #4,
	//See if we can find it
	if (myHash.exists(6)) {
		checkTest("testSimpleIntHash #4", "", "");
	} else {
		checkTest("testSimpleIntHash #4", "This test should have found an item with key 6", "This test did NOT find an item with key 6");
	}

	//Test #5, see if we can find something that doesn't exist yet.
	if (myHash.exists(1234)) {
		checkTest("testSimpleIntHash #5", "This test should NOT have found an item with key 1234.", "This test found an item with key 1234");
	} else {
		checkTest("testSimpleIntHash #5", "", "");
	}

	//Test #6, removing it from the hash
	myHash.remove(6);
	if (myHash.exists(6)) {
		checkTest("testSimpleIntHash #6", "This test should NOT have found an item with key 6.", "This test found an item with key 6");
	} else {
		checkTest("testSimpleIntHash #6", "", "");
	}

	//Add more into the hash
	myHash.add(13, "Lakers");
	myHash.add(25, "Bulls");
	myHash.add(101, "Hornets");
	myHash.add(77, "Bucks");
	myHash.add(12, "Thunder");
	myHash.add(42, "Nets");
	myHash.add(97, "Timberwolves");
	myHash.add(123, "Bobcats");

	//Attempt to retrieve some
	checkTest("testSimpleIntHash #7", "Thunder", myHash.item(12));
	checkTest("testSimpleIntHash #8", "Bucks", myHash.item(77));
	checkTest("testSimpleIntHash #9", "Bobcats", myHash.item(123));

	//Now count up how many are in there
	checkTest("testSimpleIntHash #9", 8, myHash.getTotalCount());

	//Now just verify that they aren't all going into the same bucket
	int worst = 0;
	worst = myHash.getWorstBucket();
	if (worst > 4) {
		cout << "Failed testSimpleIntHash #10!  One bucket has " << worst << " items in it.  That's too many!" << endl;
	} else {
		cout << "Passed testSimpleIntHash #10." << endl;
	}

	//Now go crazy and throw in 1000 more items.
	int key = 0;
	for(int i = 0; i < 1000; i++){
		//this next part just helps create some variation in generated W#s...
		if (i % 2 == 0) {
			key += 107;
		} else if (i % 3 == 0) {
			key += 91;
		} else if (i % 5 == 0) {
			key += 113;
		} else if (i % 7 == 0) {
			key += 13;
		} else {
			key += 61;
		}
		myHash.add(key, "a"); //Just add a bunch of letter a's
	}

	//Make sure they all go in there.
	checkTest("testSimpleIntHash #11", 1008, myHash.getTotalCount());

	//Now test how good your int hash function is.
	worst = myHash.getWorstBucket();
	if (worst > 10) {
		cout << "Failed testSimpleIntHash #12!  One bucket has " << worst << " items in it, it shouldn't be more than 10." << endl;
	} else {
		cout << "Passed testSimpleIntHash #12." << endl;
	}


}


void testHashOfObjects() {

	//Create a hashTable. We want this to be a hash table with int keys, string object values,
	//And we also supply the hash function we want to use for integers..

	hashTable<string, studentRecord> myHash(&hashFunctionString);

	//Test #1, add in a studentObject.  Try to retrive it.
	studentRecord studentObject;
	studentObject.setAge(25);
	studentObject.setGPA(3.14);
	studentObject.setName("Bob");
	myHash.add("W0000001", studentObject);
	checkTest("testHashOfObjects #1", "Bob", myHash.item("W0000001").getName());

	//Test #2, attempt to get the Jazz using the operator[] code.
	checkTest("testHashOfObjects #2", "Bob", myHash["W0000001"].getName());

	//Test #3, attempt to change the value at this location:
	studentObject.setAge(18);
	studentObject.setGPA(4.0);
	studentObject.setName("Alice");
	myHash["W0000001"] = studentObject;
	checkTest("testHashOfObjects #3", "Alice", myHash["W0000001"].getName());

	//Test #4,
	//See if we can find it
	if (myHash.exists("W0000001")) {
		checkTest("testHashOfObjects #4", "", "");
	} else {
		checkTest("testHashOfObjects #4", "This test should have found an item with key W0000001", "This test did NOT find an item with key W0000001");
	}

	//Test #5, see if we can find something that doesn't exist yet.
	if (myHash.exists("W00001234")) {
		checkTest("testHashOfObjects #5", "This test should NOT have found an item with key W00001234.", "This test found an item with key W00001234");
	} else {
		checkTest("testHashOfObjects #5", "", "");
	}

	//Test #6, removing it from the hash
	myHash.remove("W0000001");
	if (myHash.exists("W0000001")) {
		checkTest("testHashOfObjects #6", "This test should NOT have found an item with key W0000001.", "This test found an item with key W0000001");
	} else {
		checkTest("testHashOfObjects #6", "", "");
	}



	//Now throw in 1000 more items.
	int value = 0;
	string key;
	stringstream out;
	for(int i = 0; i < 1000; i++){
		//this next part just helps create some variation in generated W#s...
		if (i % 2 == 0) {
			value += 107;
		} else if (i % 3 == 0) {
			value += 91;
		} else if (i % 5 == 0) {
			value += 113;
		} else if (i % 7 == 0) {
			value += 13;
		} else {
			value += 61;
		}
		key = "W0000";
		out.str("");
		if (value < 1000)
			key = key + "0";
		if (value < 100)
			key = key + "0";
		if (value < 10)
			key = key + "0";
		out << value;
		key = key + out.str();
		//Whew, that took a while, but the W# is in key, and is ready to go

		//Create the student record, and load in values.
		studentObject.setName("Temp name");
		studentObject.setAge(rand() % 41 + 23);
		studentObject.setGPA(rand() % 3002 / 1003.0);

		//Testing the hash table "add" method
		myHash.add(key,studentObject);
	}

	//Make sure one went in correctly.  Retrieve it.
	checkEmpty("testHashOfObjects #7", myHash["W00000366"].getAllInfo());

	//Make sure they all go in there.
	checkTest("testHashOfObjects #8", 1000, myHash.getTotalCount());


	//Now test how good your int hash function is.
	int worst = myHash.getWorstBucket();
	if (worst > 10) {
		cout << "Failed testHashOfObjects #9!  One bucket has " << worst << " items in it, it shouldn't be more than 10." << endl;
	} else {
		cout << "Passed testHashOfObjects #9." << endl;
	}


}

//This helps with testing, do not modify.
void testHashofHashes() {

	//A rather complicated declaration, but it works!
	hashTable< string, hashTable<int, int> > studentAssignments(&hashFunctionString);

	hashTable<int, int> *tempHash1 = new hashTable<int, int>(&hashFunctionInt);
	studentAssignments.add("Alice", *tempHash1);

	hashTable<int, int>  *tempHash2 = new hashTable<int, int>(&hashFunctionInt);
	studentAssignments.add("Bob", *tempHash2);

	hashTable<int, int>  *tempHash3 = new hashTable<int, int>(&hashFunctionInt);
	studentAssignments.add("Karl", *tempHash3);

	//Give alice some assignment scores
	studentAssignments["Alice"].add(1,73);
	studentAssignments["Alice"].add(2,65);
	studentAssignments["Alice"].add(4,91);
	//Ensure it went in
	checkTest("testHashofHashes #1", 65, studentAssignments["Alice"][2]);

	//And Bob
	studentAssignments["Bob"].add(1,90);
	studentAssignments["Bob"].add(3,84);
	studentAssignments["Bob"].add(4,99);

	//And Karl
	studentAssignments["Karl"].add(1,92);
	studentAssignments["Karl"].add(2,92);
	studentAssignments["Karl"].add(3,87);
	studentAssignments["Karl"].add(4,10);

	//Now find the average of assignment 4 scores
	int average = (studentAssignments["Alice"][4] + studentAssignments["Bob"][4] + studentAssignments["Karl"][4]) / 3;
	checkTest("testHashofHashes #2", 66, average);

}

void testHashIterator() {
	//Coming Feb 15
	//This part is NOT required.  It is extra work that many students were interested in and requested the option of doing.
	//It does not give you extra credit.
	hashTable<string, int> myHash(&hashFunctionString);
	myHash.add("a",1);
	myHash.add("b",2);
	myHash.add("c",3);
	myHash.add("d",4);
	myHash.add("e",5);
	myHash.add("f",6);
	myHash.add("g",7);
	myHash.add("h",8);
	myHash.add("i",9);
	myHash.add("j",10);

	//now display everything
	for (hashTable<string, int>::iterator iter = myHash.begin(); iter != myHash.end(); ++iter) {
		cout << iter.getKey() << ":" << iter.getValue() << endl;
	}
}
int main(){

	testSimpleIntHash();
	testHashOfObjects();
	testHashofHashes();
     //testHashIterator();

	system("pause");
	return 0;
}
