//*****************************************************
// Header file group.h for the GroupOfNumbers class.
// Array-based implementation.
// CS 303 Algorithms
// Project 3
// Fall 2012
//*****************************************************
#ifndef _GROUP_
#define _GROUP_

#include <cstdlib>  // include for the function exit()
#include <iostream> // include for the input/output members
#include <iomanip>  // include for input/output formatting
#include <fstream>  // include for the file i/o members

using namespace std;

extern double Random(void);

class GroupOfNumbers {

 public:
  // constructors
  // ============
  GroupOfNumbers(long defaultLimit = default_LIMIT);
  // The default constructor.  If the user gives no default
  // limit on the maximum possible size of the group of numbers,
  // default_LIMIT is assumed.  But the limit on the total
  // number of entries that can be represented using the
  // GroupOfNumbers class object should be the maximum of
  // default_Limit and whatever limit the user provides.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object with defaultLimit entries.

  GroupOfNumbers(const GroupOfNumbers & G);
  // The default copy constructor (deep copy).
  // The deep copy should be identical in every respect.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object identical to G.

  GroupOfNumbers(long lower, long upper, long total_requested);
  // Given integer values lower < upper, initialize the new
  // GroupOfNumbers object by using a random number generator
  // to generate entries in the range [lower, upper].  The 
  // total number of entries that are initialized (i.e., active)
  // in the GroupOfNumbers object should be total_requested,
  // but the limit on the maximum number of entries that can be
  // represented using the GroupOfNumbers class object should be
  // the maximum of (total_requested,default_LIMIT).
  // The initialization should allow duplicate points.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object with total_requested entries.
  //
  //  exits with 2 if lower > upper.

  GroupOfNumbers(const char* fname, long total_requested);
  // Initialize the new GroupOfNumbers object by reading in
  // the numbers from the file fname.  The first value on the
  // first line of the file fname is expected to contain
  // the number of entries available in the file.
  // The user may request fewer---possibly far fewer
  // ---entries than are actually contained in the file.
  // The limit on the maximum number of entries that can be
  // represented using the GroupOfNumbers class object should
  // be the maximum of (total_requested,default_LIMIT).
  // The initialization should allow duplicate points.
  // Closes the file before returning.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  create a GroupOfNumbers object with total_requested entries.
  //
  //  exits with 3 if the file fname cannot be opened/found.
  //
  //  exits with 4 if the number of entries available in the
  //  file fname, as indicated by the first value on the first
  //  line of the file, is less than total_requested.
  //
  //  exits with 5 if the number of entries actually available
  //  in the file fname is discovered to be fewer than
  //  total_requested.

  // destructor
  // ==========
  ~GroupOfNumbers();

  // accessors
  // =========
  bool isEmpty() const;
  // Returns true if the group is empty;
  // otherwise, returns false.
  long total() const;
  // Returns the total number of entries in the group.
  void displayGroupOfNumbers() const;
  // Displays the numbers in the group, separated by one blank
  // space, with a carriage return after every 10 numbers.
  void writeGroupOfNumbersTo(const char* fname) const;
  // Writes to the file fname:
  // - the number of entries in the group (which should be the first
  //   entry on the first line of the file, followed by a carriage return)
  // - all the numbers in the group (each separated by one blank
  //   space, with a carriage return after every 10 numbers).
  // Closes the file before returning.

  // Each of the following methods returns the kth smallest
  // number in the group in the argument kth_smallest.
  // The original group is unchanged.
  // The return value for each of these methods is true if the
  // value of k is valid (i.e., 1 <= k <= total()); otherwise,
  // the return value of each of these methods is false.
  // The difference is in the algorithm used, and thus in the
  // time complexity that can either be expected (or guaranteed).
  bool sort_select(long k, long & kth_smallest) const;
  bool partial_sort_select(long k, long & kth_smallest) const;
  bool min_heap_select(long k, long & kth_smallest) const;
  bool partial_max_heap_select(long k, long & kth_smallest) const;
  bool quick_select(long k, long & kth_smallest) const;
  bool linear_select(long k, long & kth_smallest) const;

  // mutators
  // ========
  bool add(const long& newNumber);
  // If possible, adds newNumber to the group---duplicates
  // allowed; returns true if newNumber can be added to
  // the group and false if the addition of newNumber
  // to the group is not possible because the array is full.
  bool remove(const long& Number);
  // If Number is contained in the group, remove one instance of
  // Number from the group; i.e., if the group contains more than
  // one entry with the same value as Number (duplicates are
  // allowed), only one instance is removed. Returns false if
  // Number is not contained in the group; otherwise, returns true.
  GroupOfNumbers & operator=(const GroupOfNumbers & G);
  // The assignment should be identical in every respect.
  // Error handling:
  //  exits with 1 if there is insufficient memory available to
  //  assign an identical copy of G to the attached object.

  // Below are four different sorting methods to order the
  // numbers in the group.
  void insertion_sort();
  void heapsort();
  void mergesort();
  void quicksort();

  // For experimenting, we add the following new methods.
  void quick_choose_first();
  // always uses the first element as the pivot for quicksort
  void quick_choose_middle();
  // always uses the middle element as the pivot for quicksort
  void quick_choose_last();
  // always uses the last element as the pivot for quicksort

 protected:
  long Equilikely(long lower, long upper);  // use lower < upper

  // protected method for insertion sort
  void insertion_sort(long left, long right);

  // protected methods for heapsort
  void percolate_down(long i, long n);
  void percolate_up(long i, long n);

  inline long left_child(long i) {
    return 2*i + 1;
  } // end leftChild

  // protected methods for mergesort
  void mergesort(long *temp_group, long left, long right);
  void merge(long *temp_group, long leftPos, long rightPos, long rightEnd);

  // protected methods for quicksort
  void quicksort(long left, long right);
  long median_of_3(long left, long right);

  // protected methods for quicksort with new pivot rules
  void quick_choose_first(long left, long right);
  // always uses the first element of the partition
  // (left) as the pivot for quicksort
  void quick_choose_middle(long left, long right);
  // always uses the middle element of the partition
  // ((left + right)/2) as the pivot for quicksort
  void quick_choose_last(long left, long right);
  // always uses the last element of the partition
  // (right) as the pivot for quicksort
  void quickSelect(long left, long right, long k);
  void linearSelect(long left, long right, long k);
  long median_of_5(long left, long right, long k);
  
 private:
  static const long default_LIMIT = 10; // default max size of the array
  // All GroupOfNumbers objects are guaranteed to be able to
  // represent at least default_Limit numbers in the group.

  static const long CutOff = 5;  // recommended range: 5-20
  // when to switch quicksort to insertion sort; must be > 1!!!
  // (or median_of_3 is not defined)

  long  _LIMIT; // signifies the limit on the size of the actual
                // array (which must be >= default_LIMIT)
  long  _total; // signifies the number of entries
                // currently active in the array
  long* _group; // pointer to the array of numbers

}; // end class GroupOfNumbers
#endif
