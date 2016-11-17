// LinkListExample1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

// list Node Class
class node
{
	char artist[20];
	char song[20];
	node *next;
public:
	node();
	node(char a[], char s[]);
	void setNode(char artist[], char song[]);
	friend class linkedList;
};

node::node()
{
	strcpy_s(artist, " ");
	strcpy_s(song, " ");
	next = NULL;
}

node::node(char a [], char s[])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}

void node::setNode(char a[], char s[])
{
	strcpy_s(artist, a);
	strcpy_s(song, s);
	next = NULL;
}

// Linked List Class
class linkedList
{
	char filename[100];
	node *head;
	node *tail;
public:
	linkedList();
	void userLoop();
	void setFilename(char f[]);
	void readFile();
	void addNodeToEnd(node *nptr);
	void addNodeToHead(node *nptr);
	int insertAfter(node *ptr, char i[]);
	int removeNode(char i[]);
	void showList();
	node * findItem(char i[]);
};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

void linkedList::userLoop()
{
	node *ptr;
	ptr = head;
	int answer = 0;
	while (answer != 9)
	{
		cout << "artist: " << ptr->artist << ", " << " song: " << ptr->song << endl;
		cout << "what do you want to do?" << endl;
		cout << "1 for play, 2 for skip, 3 for delete, or 9 for quit" << endl;
		cin >> answer;
		cin.clear();
		cin.ignore();
		if (answer == 1)
		{
			cout << "playing: " << ptr->artist << ", " << ptr->song << endl;
			cin;
			cin.clear();
			cin.ignore();
		}
		else if (answer == 2)
		{
			int skip = 0;
			cout << "how many songs do you want to skip?" << endl;
			cin >> skip;
			skip -= 1;
			cin.clear();
			cin.ignore();

			for (int i = 0; i < skip; i++)
			{
				ptr = ptr->next;
			}
		}
		else if (answer == 3)
		{
			removeNode(ptr->artist);
		}
		else if (answer == 9)
		{
			cout << "goodbye" << endl;
			return;
		}
		else
		{
			cout << "invalid entry" << endl;
		}
		if (ptr->next == NULL)
		{
			ptr = head;
		}
		else
		{
			ptr = ptr->next;
		}
	}
}

void linkedList::setFilename(char f[])
{
	strcpy_s(filename, f);
}

void linkedList::readFile()//NOT SURE IF THIS WORKS, ASK ABOUT FILENAMES
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		node *ptr;
		char artist[20];
		char song[20];

		infile.getline(artist, 20, ',');
		if (strlen(artist))
		{
		infile.getline(song, 20, ',');
		ptr = new node();
		ptr->setNode(artist, song);
		addNodeToEnd(ptr);
		}	
	}
}

void linkedList::showList()
{
	node *ptr;
	ptr = head;
	cout << "****  List Contents *****" << endl;
	if (ptr == NULL)
	{
		cout << "list is empty " << endl;
		return;
	}
	cout << "(head is " << head->artist << " tail is " << tail->artist << ")" << endl;
	while (ptr != NULL)
	{
		cout << "data is " << ptr->artist << ", " << ptr->song << endl;
		ptr = ptr->next;
	}
}

void linkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkedList::addNodeToHead(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int linkedList::insertAfter(node *z, char i [])
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (strcmp(ptr->artist, i) == 0)// we found the node to insert after
		{
			z->next = ptr->next;
			ptr->next = z;
			if (tail == ptr) // repoint tail if we added to end
				tail = z;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

node * linkedList::findItem(char i[])
{
	node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (strcmp(ptr->artist, i) == 0)
		{
			cout << "found it!" << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Not found" << endl;
	return NULL;
}


int linkedList::removeNode(char i[])
{
	node *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (strcmp(head->artist, i) == 0)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && strcmp((ptr->next)->artist, i) == 0)
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	char file[50];
	linkedList *mylist = new linkedList();
	cout << "please enter full path filename" << endl;
	cin >> file;
	cin.clear();
	cin.ignore();
	mylist->setFilename(file);
	mylist->readFile();
	//mylist->userLoop();
	// test if list is empty
	if (mylist->removeNode("taylor swift"))
		cout << "failed to remove" << endl;
	node *newnode = new node("taylor swift", "love story");
	mylist->addNodeToEnd(newnode);
	mylist->showList();
	mylist->addNodeToEnd(new node("rise against", "paper wings"));
	mylist->showList();
	mylist->addNodeToEnd(new node("staind", "zoe jane"));
	mylist->showList();
	mylist->addNodeToHead(new node("eminem", "beautiful"));
	mylist->showList();
	mylist->insertAfter(new node("linkin park", "numb"), "taylor swift");
	mylist->showList();
	//if (mylist->removeNode("rise against"))
	//	cout << "failed to remove" << endl;
	/*if (mylist->removeNode("staind"))
		cout << "failed to remove" << endl;
	if (mylist->removeNode("taylor swift"))
		cout << "failed to remove" << endl;
	if (mylist->removeNode("eminem"))
		cout << "failed to remove" << endl;
	mylist->showList();*/
	cout << "(searching for item 'taylor swift')\n";
	mylist->findItem("taylor swift");
	cout << "(searching for item 'staind')\n";
	mylist->findItem("staind");
	mylist->userLoop();
	return 0;
}