#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
	// reference pointer
	Contact * curr = this->headContactList;
	Info * currInfo = nullptr;
	// iteration through list
	while (curr != nullptr) {
		if (curr->first == first && curr->last == last) {
			cout << "Contact Name: " << first << " " << last << endl;
currInfo = curr->headInfoList;
			while (currInfo != nullptr) {
				cout << "\t" << currInfo->name << " | " << currInfo->value << endl;
				currInfo = currInfo->next;
			}
			return true;
		}
		curr = curr->next;
	}
    return false;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {
	// pointers
	Contact * currContact = this->headContactList;
	while (currContact != nullptr) {
		printContact(cout, currContact->first, currContact->last);
		currContact = currContact->next;
	}
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
	// variables
	Contact * buffer = new Contact(first, last, nullptr);
	Contact * curr = this->headContactList;
	// empty list
	if (count == 0) {
		this->headContactList = buffer;
		count++;
		return true;
	}
	// check for duplicates
	while (curr != nullptr) {
		if (curr->first == first && curr->last == last) {
			return false;
		}
		curr = curr->next;
	}
	// add to back
	curr = this->headContactList;
	while (curr != nullptr) {
		if (curr->next == nullptr) {
			curr->next = buffer;
			break;
		}
		curr = curr->next;
	}
	// update count
	count++;
    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
	// variables
	Contact * currContact = this->headContactList;
	Info * currInfo = nullptr;
	Info * newInfo = new Info(infoName, infoVal, nullptr);
	bool found = false;
	// check if valid contact	
	while (currContact != nullptr) {
		if (currContact->first == first && currContact->last == last) {
			found = true;
			break;
		}
		if (!found && currContact->next == nullptr) {
			return false;
		} 
		currContact = currContact->next;
	}
	// update info if info exists already
	// or add info to back if not
	if (currContact->headInfoList == nullptr) {
		currContact->headInfoList = newInfo;
		return true;
	}

	currInfo = currContact->headInfoList;
	while (1) {
		if (currInfo->name == infoName) {
			currInfo->value = infoVal;
			return true;
		}
		if (currInfo->next == nullptr) {
			currInfo->next = newInfo;
			return true;
		}
		currInfo = currInfo->next;
	}
	return true;
	/*
	while (currContact != nullptr) {
		if (currContact->first == first && currContact->last == last) {
			currInfo = currContact->headInfoList;
			while (currInfo != nullptr) {
				cout << "c" << endl;
				if (currInfo->name == infoName) {
					currInfo->value = infoVal;
					return true;
				}
				currInfo = currInfo->next;
			}
			currInfo = newInfo;
			cout << "b" << endl;
			return true;
		}	
	}
	return true;
	*/
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
	// variables
	Contact * ref = this->headContactList;
	Contact * prev = nullptr;
	Contact * newContact = new Contact(first, last, nullptr);
	// exceptions
	if (this->count == 0) { // empty list
		this->headContactList = newContact;
		this->count++;
		//cout << "a" << endl;
		return true;
	}
	// find order in list and add
	while (ref != nullptr) {
		if (ref->first == first && ref->last == last) { // already in list
			return false;
		}
		else if (ref->last == last) {
			if (ref->first > first && prev == nullptr) { // insert at beginning, not empty, same last name
				this->headContactList = newContact;
				newContact->next = ref;
				this->count++;
				//cout << "b" << endl;
				return true;
			}
			else if (ref->first > first && prev != nullptr) { // inserting between two items, same last name
				prev->next = newContact;
				newContact->next = ref;
				this->count++;
				//cout << "c" << endl;
				return true;
			}
		}
		else if (ref->last > last && prev == nullptr) { // insert at beginning, not empty, different last name
			this->headContactList = newContact;
			newContact->next = ref;
			this->count++;
			//cout << "f" << endl;
			return true;
		}
		else if (ref->last > last && prev != nullptr) { // insert between two items, different last name
			prev->next = newContact;
			newContact->next = ref;
			this->count++;
			//cout << "e" << endl;
			return true;
		}
		prev = ref;
		ref = ref->next;
	}
	if (ref == nullptr) { // inserting at end
		prev->next = newContact;
		this->count++;
		//cout << "d" << endl;
		return true;
	}

	// error
	cout << "something went wrong" << endl;
    return false;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
	// variables
	Contact * ref = this->headContactList;
	Info * newInfo = new Info(infoName, infoVal, nullptr);
	Info * refInfo = nullptr;
	Info * prevInfo = nullptr;
	// find contact	
	bool found = false;
	// check if valid contact	
	while (ref != nullptr) {
		if (ref->first == first && ref->last == last) {
			found = true;
			break;
		}
		if (!found && ref->next == nullptr) {
			//cout << "a" << endl;
			return false;
		} 
		ref = ref->next;
	}
	if (!found) {
		return false;
	}
	// add info within contact, ordered
	if (ref->headInfoList == nullptr) { // contact has no info
		ref->headInfoList = newInfo;
		newInfo->next = nullptr;
		//cout << "b" << endl;
		return true;
	}
	refInfo = ref->headInfoList;
	while (refInfo != nullptr) {
		if (refInfo->name == infoName) { // info already exists, so update values
			refInfo->value = infoVal;
			//cout << "c" << endl;
			return true;
		}
		else if (refInfo->name > infoName && prevInfo == nullptr) { // info is added to beginning of list
			ref->headInfoList = newInfo;
			newInfo->next = refInfo;
			//cout << "d" << endl;
			return true;
		}
		else if (refInfo->name > infoName && prevInfo != nullptr) { // info is inserted between two items
			prevInfo->next = newInfo;
			newInfo->next = refInfo;
			//cout << "e" << endl;
			return true;
		}
		prevInfo = refInfo;
		refInfo = refInfo->next;
	}
	if (refInfo == nullptr) { // info is inserted at end
		prevInfo->next = newInfo;
		return true;
	}
	// error
	cout << "????" << endl;
    return false;
}

// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
	// variables
	Contact * curr = this->headContactList;
	Contact * prev = nullptr;
	bool found = false;
	// find contact
	while (curr != nullptr) {
		if (curr->first == first && curr->last == last) {
			found = true;
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	// delete contact
	if (found) {
		if (prev != nullptr && curr->next != nullptr) { // deleting item in the middle of a list
			prev->next = curr->next;
			delete curr;
			this->count--;
			//cout << "a" << endl;
			return true;
		}
		else if (prev == nullptr && curr->next != nullptr) { // deleting head item of a list
			this->headContactList = curr->next;
			delete curr;
			this->count--;
			//cout << "b" << endl;
			return true;
		}
		else if (prev != nullptr && curr->next == nullptr) { // deleting tail item of a list
			prev->next = nullptr;
			delete curr;
			this->count--;
			//cout << "c" << endl;
			return true;
		}
		else if (prev == nullptr && curr->next == nullptr) { // deleting only item in a list
			this->headContactList = nullptr;
			delete curr;
			this->count--;
			//cout << "d" << endl;
			return true;
		}
	}
	else {
		//cout << "e" << endl;
		return false;
	}
	// error
	cout << "????" << endl;
    return false;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
	// variables
	Contact * currContact = this->headContactList;
	Info * currInfo = nullptr;
	Info * prevInfo = nullptr;
	bool found = false;
	// find contact
	while (currContact != nullptr) {
		if (currContact->first == first && currContact->last == last) {
			found = true;
			break;
		}
		currContact = currContact->next;
	}
	if (found) {
		currInfo = currContact->headInfoList;
		// find info
		while (currInfo != nullptr) {
			if (currInfo->name == infoName) {
				break;
			}
			prevInfo = currInfo;
			currInfo = currInfo->next;
		}
	}
	// delete info
	if (currInfo != nullptr) {
		if (prevInfo != nullptr && currInfo->next != nullptr) { // deleting item in the middle of a list
			prevInfo->next = currInfo->next;
			delete currInfo;
			cout << "a" << endl;
			return true;
		}
		else if (prevInfo == nullptr && currInfo->next != nullptr) { // deleting head item of a list
			currContact->headInfoList = currInfo->next;
			delete currInfo;
			cout << "b" << endl;
			return true;
		}
		else if (prevInfo != nullptr && currInfo->next == nullptr) { // deleting tail item of a list
			prevInfo->next = nullptr;
			delete currInfo;
			cout << "c" << endl;
			return true;
		}
		else if (prevInfo == nullptr && currInfo->next == nullptr) { // deleting only item in a list
			currContact->headInfoList = nullptr;
			delete currInfo;
			cout << "d" << endl;
			return true;
		}
	}
	// error
	cout << "????" << endl;
    return true;
}

// delete contacts within a contact list
void deleteList(Contact * inputContact) {
	if (inputContact->next != nullptr) { // if not tail, delete next nodes, then this one
		deleteList(inputContact->next);
		inputContact->next = nullptr;
	}
	if (inputContact->next == nullptr) { // if tail, delete tail
		cout << inputContact->first << endl; // name of contact deleted
		delete inputContact;
		return;
	}
}

// delete info within a contact
void deleteInfo(Info * inputInfo) { // same logic as above, different class
	if (inputInfo->next != nullptr) {
		deleteInfo(inputInfo->next);
		inputInfo->next = nullptr;
	}
	if (inputInfo->next == nullptr) {
		cout << inputInfo->name << endl;
		delete inputInfo;
		return;
	}
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
	// iterate through list, delete info, then contacts
	Contact * curr = this->headContactList;
	while (curr != nullptr) {
		if (curr->headInfoList != nullptr) {
			deleteInfo(curr->headInfoList);
		}
		curr = curr->next;
	}
	curr = this->headContactList;
	if (this->headContactList != nullptr) { 
		deleteList(curr);
	}
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {
	this->headContactList = new Contact();
	// variables
	Contact * currContact = src.headContactList;
	Contact * copyContact = this->headContactList;
	Contact * prevContact = nullptr;
	Info * currInfo = src.headContactList->headInfoList;
	Info * copyInfo = this->headContactList->headInfoList;
	Info * prevInfo = nullptr;
	// add contacts
	while (currContact != nullptr) {
		copyContact = new Contact(currContact->first, currContact->last);
		if (prevContact != nullptr) {
			prevContact->next = copyContact;
		}
		prevContact = copyContact;
		cout << copyContact->first << endl;
		copyContact = copyContact->next;
		currContact = currContact->next;
	}
	// add info to contacts
	copyContact = this->headContactList;
	currContact = src.headContactList;
	while (currContact != nullptr) {
		currInfo = currContact->headInfoList;
		copyInfo = copyContact->headInfoList;
		while (currInfo != nullptr) {
			copyInfo = new Info(currInfo->name, currInfo->value);
			if (prevInfo == nullptr) {
				prevInfo->next = copyInfo;
			}
			prevInfo = copyInfo;
			copyInfo = copyInfo->next;
			currInfo = currInfo->next;
		}
	}
	this->count = src.count;
}

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {

    }
    return *this;
}

