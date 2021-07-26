#include <iostream>
#include "myskiplist.h"

int main()
{
     skiplist<string, string> myskiplist(4);
	myskiplist.insert_element("abc", "a"); 
	myskiplist.insert_element("aabs", "b"); 
	myskiplist.insert_element("bacd", "c"); 
	myskiplist.insert_element("def", "d"); 
	myskiplist.insert_element("aac", "e"); 
	myskiplist.insert_element("aaac", "f"); 
	myskiplist.insert_element("abcc", "g"); 
    myskiplist.display_list();
    myskiplist.write_to_file("data.txt");
    myskiplist.delete_element("aabs"); 
    myskiplist.delete_element("def"); 
   myskiplist.display_list();

    skiplist<string, string> newskiplist(6);
    newskiplist.read_from_file("data.txt");
    newskiplist.display_list();
    return 0;
}