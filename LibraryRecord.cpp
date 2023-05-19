//Author: Camilla Calle
//Date: March 4, 2023
//LibraryRecord.cpp
//This file is a subclass of ArrayBag and implements functions for our Library Record that were declared in our
//.hpp file.

#include "LibraryRecord.hpp"

/** @param:   A reference to a Book object to be checked in
    @return:  returns true if a book was successfully added to items_, false otherwise
    @post:    adds book to items_.
 **/

bool LibraryRecord::checkIn(const Book& books){
    if(add(books)){  
        return true;
    } else 
    return false;
 }
/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out books.
 **/
bool LibraryRecord::checkOut(const Book& books){ 
    if(remove(books)){
        checked_out_.push_back(books);
        return true;   
    } else
    return false;
}
/** @param:   A reference to a Book object to be checked out   
    @return:  returns true if a book was successfully removed from items_, false otherwise
    @post:    removes the book from the LibraryRecord and if remove was successful, it adds the book to the vector of checked-out books.
 **/
int LibraryRecord::getCheckOutHistory(const Book& checked_out) const{ //works
    int number = 0; 
    for(int i = 0; i < checked_out_.size(); i++){ //iterate through the vector
        if (checked_out == checked_out_[i]) //checked if input == element in checked out books vector 
        number++; //as iterates through vector if the same as user input we increase the counter by one 
        }
    return number; //returns number of times book checked out 
}

/**
    @post:    Outputs the names of the Books in the LibraryRecord and the number of times each Book has been cheked out

      For each Book in the LibraryRecord you will output:
             "[title_] is written by [author_]. Page Count: [page_count_]. [It is / It is not] available digitally.\n
             It has been checked out [_] times.\n"
  **/

//outputs the name of books in LR and the # of times each Book has been checked out 
void LibraryRecord::display() const { 
    for (int i = 0; i < item_count_; i++){ //for each Book in LR you will output 
        if(items_[i].isDigital()== true) { //array bag element is Digital 
        std::cout << items_[i].getTitle() << " is written by " << items_[i].getAuthor() << ". Page Count: " << items_[i].getPageCount() << ". It is available digitally.\n" << "It has been checked out " << getCheckOutHistory(items_[i]) << " times.\n";
        }
        else 
            std::cout << items_[i].getTitle() << " is written by " << items_[i].getAuthor() << ". Page Count: " << items_[i].getPageCount() << ". It is not available digitally.\n" << "It has been checked out " << getCheckOutHistory(items_[i])<< " times.\n";
        }
    }

/**
  @post:    Prints the title of each Book in the LibraryRecord
  Example:
  "title1, title2, title3, title4!\n" Note the commas and exclamation mark.
*/
void LibraryRecord::displayTitles() const //works
{
  for(int i = 0; i < getCurrentSize(); i++){ //increments 
    if(i > 0){ //for every element after position 0 ","
      std::cout << ", "; 
    }
    std::cout << items_[i].getTitle() << "";
    if(i == (getCurrentSize() - 1)){ //for last element in array "!"
      std::cout << "!\n";
    }
  }
}

/**
  @return:    Returns true if the LibraryRecord was successfully duplicated, false otherwise (there is nothing to
    duplicate or duplicating would exceed DEFAULT_CAPACITY).
  @post:      Duplicates all the items in the LibraryRecord
  Example: we originally have [book1, book2] and after duplication we have [book1, book2, book1, book2]
*/
// protected:
//   static const int DEFAULT_CAPACITY = 10; //max size of items_ at 10 by default for this project
//   ItemType items_[DEFAULT_CAPACITY];      // Array of bag items
//   int item_count_;                        // Current count of bag items

bool LibraryRecord::duplicateStock(){ 
    int capacity = getCurrentSize();
    if(getCurrentSize() <= 5){ 
        for (int i = 0; i < capacity; i++){
            add(items_[i]);
        } 
        return true;
        } else {
            return false;
    }
} 

/**
  @param:   A reference to a book
  @return: True if at least one copy of the referenced book was removed from items_, false otherwise 
  @post: remove all occurrences of the referenced book
*/
bool LibraryRecord::removeStock(const Book& book) {
    int num = 0;
    while(remove(book)){
        num++;
    }
    return num;
}

/**
  @param:   A reference to another LibraryRecord
  @return:  Returns true if the 2 library records have the same contents (including the same number of duplicates for each book), 
  regardless of their order.
   For example, if the current holdings of the LibraryRecord are [book1, book2, book3]
  and those of the referenced LibraryRecord are [book3, book1, book2], it will return true.

  However, [book1, book2, book2, book3] is not equivalent to [book1, book2, book3, book3], because it contains two copies of book2 
  and only one copy of book3*/
bool LibraryRecord::equivalentRecords(const LibraryRecord& another_library_record){
  bool equal = false;
  for(int i = 0; i < getCurrentSize(); i++) {
    if(getFrequencyOf(items_[i]) != another_library_record.getFrequencyOf(items_[i])){
        equal = false;
        break;
        }
        if(another_library_record.contains(items_[i]) == true){
            equal = true;
            }
        }
    return equal;
}

/**
    @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, including duplicates.
    Example: [book1, book2, book3] += [book1, book4] will produce [book1, book2, book3, book1, book4]

    IMPORTANT: We are carrying over the number of times a book has been checked out. For example, if we have LibraryRecord1 += LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the += operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
// operator+=

void LibraryRecord::operator+= (const LibraryRecord& object){
    if(getCurrentSize() + object.getCurrentSize() <= 10){ //Capacity
        int count;
        for(int i = 0; i < object.getCurrentSize(); i++){
            add(object.items_[i]);
            count = object.getCheckOutHistory(object.items_[i]);
            for(int j = 0; j < count; j++){
                checked_out_.push_back(object.items_[i]);
            }
        }
    }
}

/** @param:   A reference to another LibraryRecord object
    @post:    Combines the contents from both LibraryRecord objects, EXCLUDING duplicates.
    Example: [book1, book2, book3] /= [book1, book4] will produce [book1, book2, book3, book4]

    IMPORTANT: We are carrying over the nunber of times a book has been checked out. For example, if we have LibraryRecord1 /= LibraryRecord2 and
    book4 is in LibraryRecord2 and has been checked out 2 times, then it should still be checked out 2 times in LibraryRecord1 after the /= operation
    Hint: use getCheckOutHistory and the checkout history vector
*/
// operator/=

void LibraryRecord::operator/= (const LibraryRecord& object){
    if(getCurrentSize() + object.getCurrentSize() <= 10){
        int count;
        for(int i = 0; i < object.getCurrentSize(); i++){
            if (contains(object.items_[i]) == false) {
                add(object.items_[i]);
                count = object.getCheckOutHistory(object.items_[i]);
                for(int j = 0; j < count; j++){
                checked_out_.push_back(object.items_[i]);
                }
            }
        }
    }
}





