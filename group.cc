#include "group.h"
#include <iostream>
#include <fstream>

using namespace std;
	
/**JESSICA CHEN
 * Constructor when passed the const
 */
GroupOfNumbers::GroupOfNumbers(long defaultLimit):
_LIMIT(defaultLimit), _total(0){
	if(defaultLimit < default_LIMIT){
		_LIMIT = default_LIMIT;
	} //end if
	try{
		_group = new long[_LIMIT]; 
	} //END TRY
	catch(bad_alloc){
		cerr<<"GroupofNumbers: bad_alloc" <<endl;
		cerr<<"GroupofNumbers: allocation of size "<< _LIMIT << " failed" <<endl;
		cerr<<"GroupofNumbers: line: "<< (__LINE__ -5) <<endl; 
		cerr<<"GroupofNumbers: file: "<< __FILE__ <<endl;
		cerr<<"GroupofNumbers: exit: " <<1 <<endl;
		exit(1);
	}//end catch
}// end default constructor

/**
 * Copy constructor
 */
GroupOfNumbers::GroupOfNumbers(const GroupOfNumbers& G):
 _LIMIT(default_LIMIT), _total(0), _group(NULL){
	*this = G; 
}// end deep copy constructor

GroupOfNumbers::GroupOfNumbers(long lower, long upper, long total_requested):_LIMIT(total_requested), _total(0){
  if(total_requested < default_LIMIT){
		_LIMIT = default_LIMIT;
  } //end if
  if(lower > upper){
	cerr<<"GroupofNumbers: incorrect values for the arguments lower and upper: ("<< lower << ", " << upper << ")" << endl;
	cerr<<"GroupofNumbers: lower is required to be less than or equal to upper " << endl;
	cerr<<"GroupofNumbers: line: "<< (__LINE__ - 4) << endl; 
	cerr<<"GroupofNumbers: file: "<< __FILE__ << endl;
	cerr<<"GroupofNumbers: exit: " << 2 << endl;
	exit(2);
  }
  try{
		_group = new long[_LIMIT]; 
	} //END TRY
	catch(bad_alloc){
		cerr<<"GroupofNumbers: bad_alloc" <<endl;
		cerr<<"GroupofNumbers: allocation of size "<< _LIMIT << " failed" <<endl;
		cerr<<"GroupofNumbers: line: "<< (__LINE__ -5) <<endl; 
		cerr<<"GroupofNumbers: file: "<< __FILE__ <<endl;
		cerr<<"GroupofNumbers: exit: " <<1 <<endl;
		exit(1);
	}//end catch
  while(_total != total_requested){
	_group[_total++] = Equilikely(lower, upper);
  }
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
}

GroupOfNumbers::GroupOfNumbers(const char* fname, long total_requested):_LIMIT(total_requested), _total(0){
  if(total_requested < default_LIMIT){
		_LIMIT = default_LIMIT;
  } //end if
  ifstream myfile;
  myfile.exceptions ( ifstream::failbit | ifstream::badbit ); //this defines the errors.
  try{
	myfile.open(fname);
	} //END TRY
  catch(ifstream::failure e){
		cerr<<"GroupofNumbers: "<< fname <<": No such file" << endl;
		cerr<<"GroupofNumbers: line: "<< (__LINE__ - 4) <<endl; 
		cerr<<"GroupofNumbers: file: "<< __FILE__ <<endl;
		cerr<<"GroupofNumbers: exit: " << 3 <<endl;
		exit(3);
	}//end catch
  int a;
  int b;
  myfile >> a;
	try{
	_group = new long[_LIMIT]; 
	} //END TRY
	catch(bad_alloc){
		cerr<<"GroupofNumbers: bad_alloc" <<endl;
		cerr<<"GroupofNumbers: allocation of size "<< _LIMIT << " failed" <<endl;
		cerr<<"GroupofNumbers: line: "<< (__LINE__ -6) <<endl;
		cerr<<"GroupofNumbers: file: "<< __FILE__ <<endl;
		cerr<<"GroupofNumbers: exit: " <<1 <<endl;
		myfile.close();
		exit(1);
	}//end catch
  int count = 0;
  if(a < total_requested){
  	cerr << "GroupOfNumbers: Insufficient number of entries in file: " << fname<< endl;
	cerr << "GroupOfNumbers: Number requested from file: " << total_requested << endl;
	cerr << "GroupOfNumbers: Number reputedly available: " << a << endl;
	cerr << "GroupOfNumbers: line: " << (__LINE__ - 4) << endl;
	cerr << "GroupOfNumbers: file: " << __FILE__ << endl;
	myfile.close();
	exit(4);
  }
  try{
  while(count != total_requested){
  	myfile >> b;
	_group[_total] = b;
	_total++;
        count++;
  }
  } //end try
  catch(ifstream::failure e){
   cerr<<"GroupOfNumbers: Insufficient number of entries in file: " << fname << endl;
   cerr<<"GroupOfNumbers: Number requested from file: " << total_requested << endl;
   cerr<<"GroupOfNumbers: Number reputedly available: " << (a) << endl;
   cerr<<"GroupOfNumbers: Number actually available: " << count << endl;
   cerr<<"GroupOfNumbers: line: " << (__LINE__ - 12) << endl;
   cerr<<"GroupofNumbers: file: "<< __FILE__ <<endl;
   cerr<<"GroupofNumbers: exit: " << 5 <<endl;
   myfile.close();
   exit(5);
  }//end catch
  myfile.close();
} //end constructor


GroupOfNumbers::~GroupOfNumbers(){
	delete[] _group; 
}// end destructor

bool GroupOfNumbers::isEmpty() const{
	return (_total == 0);
}// end isEmpty

long GroupOfNumbers::total() const{
	return _total;
}// end total

void GroupOfNumbers::displayGroupOfNumbers() const{
	long i;
	cout.setf(ios::right);
	for(i = 0; i< _total; i++){
	if((i%10) ==0)
		cout <<'\n' << setw(8) << _group[i]; 
	else
		cout << setw(8) << _group[i]; //setw sets the width of the column to 8.
	}
		cout << endl;
}// end displayGroupOfNumbers

void GroupOfNumbers::writeGroupOfNumbersTo(const char* fname) const{
  ofstream myfile(fname);
  myfile << _total << endl;
  int i;
  for(i = 0; i< _total; i++){
	if(((i%10) ==0)&& (i != 0))
		myfile <<'\n' << setw(8) << _group[i];
	else
		myfile << setw(8) << _group[i]; //setw sets the width of the column to 8.
	}
		cout << endl;
  myfile.close();
}// end writeGroupOfNumbersTo

bool GroupOfNumbers::add(const long& newNumber){
	bool success = _total < _LIMIT;
	if(success){
		_group[_total++] = newNumber;
	}
	return success;
}

bool GroupOfNumbers::remove(const long& entry){
	bool success;
	long i;
 	for (i = 0; ((i < _total) && _group[i] != entry); i++){}// end for	
	success = i < _total;
	if (success){
	 _group[i] = _group[(--_total)]; //decrements total and swaps them.
	} //end if
	return success;
}// end remove

//*this is an object. &this is an object.
GroupOfNumbers & GroupOfNumbers::operator=(const GroupOfNumbers& G){
  if(this != &G){ //compares the addresses rather than the objects themselves. *this != G then you compare the actual objects. in which case you have to overload the != and compare EVERYTHING in the objects.
	 delete [] _group;
	 try{
	   	_group = new long[G._LIMIT];
	 } //end try
	 catch(bad_alloc){
	   	cerr<<"GroupOfNumbers: bad_alloc" <<endl;
		  cerr<<"GroupOfNumbers: allocation of size "<< _LIMIT << " failed" <<endl;
		  cerr<<"GroupOfNumbers: line: "<< (__LINE__ -5) <<endl; //minus 5 becauseit hsows where the actual issues occur.
		  cerr<<"GroupOfNumbers: file: "<< __FILE__ <<endl;
		  cerr<<"GroupOfNumbers: exit: " <<1 <<endl;
		  exit(1);
	 }//end catch cathes the bad allocation.
	 _LIMIT = G._LIMIT; // the size of the array is 
	 long i;
	 for(i = 0; i < G._total; i++){
	 	 _group[i] = G._group[i];
	  }
	//update total using G._total
	 _total = G._total;
  }
	return *this;
}

long GroupOfNumbers::Equilikely(long a, long b){ // use a < b
  return (a + (long) (( b - a + 1) * Random()) );
} // end Equilikely

void GroupOfNumbers::quicksort(long left, long right)
{
   if( left + CutOff <= right){
    long pivot = median_of_3(left, right);
    long i = left, j = right - 1;
    for( ; ;){
      while(_group[++i] < pivot ) { }
      while(pivot < _group[--j]) { }
      if( i < j){
	     swap( _group[i], _group[j]);
      }
      else
	     break;
    }
    swap( _group[ i ], _group[ right - 1] ); // Restore pivot
    quicksort(left, i-1);
    quicksort(i + 1, right);
  }
  else
    insertion_sort(left, right);
}

void GroupOfNumbers::insertion_sort(long left, long right){
  long j;
  for(long p = left + 1; p < right + 1; p++){
    long tmp = _group[p];
    for(j = p; j > left && tmp < _group[j-1]; j--){
      _group[j] = _group[j-1];
    }
    _group[j] = tmp;
  } 
}

void GroupOfNumbers::heapsort(){
 for( int i = _total / 2; i>=0; i--){
   percolate_down( i, _total);
 }
 for( long j = _total - 1; j > 0; j--){
   swap(_group[0], _group[j]);
   percolate_down( 0, j);
 }
}

// Used to generate a min binary heap so it is easier to visualize and uses smaller constants
// accessing the group of numbers.
void GroupOfNumbers::percolate_up(long i, long n){
  long child;
  long tmp;
  for( tmp = _group[i]; left_child(i) < n; i = child){
    child = left_child(i);
    if(child != n-1 && _group[child] > _group[child +1])
      child++;
    if(tmp > _group[child]){
      _group[i] = _group[child];
    }
    else
      break;
  }
  _group[i] = tmp;
}


void GroupOfNumbers::percolate_down(long i, long n){
  long child;
  long tmp;
  for( tmp = _group[i]; left_child(i) < n; i = child)
  {
    child = left_child(i);
    if(child != n-1 && _group[child] < _group[child +1])
      child++;
    if(tmp < _group[child])
    {
      _group[i] = _group[child];
      
    }
    else
      break;
  }
  _group[i] = tmp;
}

void GroupOfNumbers::mergesort(long *temp_group, long left, long right){
   if( left < right)
  {
    long center = (left + right) /2;
    mergesort(temp_group, left, center);
    mergesort(temp_group, center + 1, right);
    merge(temp_group, left, center + 1 , right);
  }
}

void GroupOfNumbers::merge(long *temp_group, long leftPos, long rightPos, long rightEnd){
  long leftEnd = rightPos - 1;
  long tmpPos = leftPos;
  long numElements = rightEnd - leftPos + 1;
 
  while( leftPos <= leftEnd && rightPos <= rightEnd)
    if(_group[leftPos] <= _group[rightPos])
    {
      temp_group[tmpPos++] = _group[leftPos++];
    }
    else
    {
      temp_group[tmpPos++] = _group[rightPos++];
    }
    
  while(leftPos <= leftEnd)
    temp_group[tmpPos++] = _group[leftPos++];
  
  while(rightPos <= rightEnd)
    temp_group[tmpPos++] = _group[rightPos++];

  for( int i = 0; i < numElements; i++, rightEnd--)
  {
    _group[rightEnd] = temp_group[rightEnd];
  }
}

long GroupOfNumbers::median_of_3(long left, long right){
  long center = ( left + right) / 2;
  if( _group[center] < _group[left])
  {
    swap( _group[left], _group[center]);
  }
  if( _group[right] < _group[left])
  { 
    swap( _group[left], _group[right]);
  }
  if(_group[right] < _group[center])
  {
    swap(_group[center], _group[right]);
  }
  swap(_group[center], _group[right - 1]);
  return _group[right-1];
}

void GroupOfNumbers::mergesort(){
  long* temp;
  try{
    temp = new long[_LIMIT];
	} //end try
  catch(bad_alloc)
      {
	cerr<<"GroupOfNumbers: bad_alloc" <<endl;
	cerr<<"GroupOfNumbers: allocation of size "<< _LIMIT << " failed" <<endl;
	cerr<<"GroupOfNumbers: line: "<< (__LINE__ -5) <<endl; //minus 5 becauseit hsows where the actual issues occur.
	cerr<<"GroupOfNumbers: file: "<< __FILE__ <<endl;
	cerr<<"GroupOfNumbers: exit: " <<1 <<endl;
	exit(1);
	}//end catch cathes the bad allocation.
  if(_total > 0){
  mergesort(temp, 0, _total-1);
  }
  delete[] temp;
}

void GroupOfNumbers::insertion_sort(){
  if(_total - 1 != 0)
  {
  insertion_sort(0, _total-1);
  }
}

void GroupOfNumbers::quicksort(){
  quicksort(0, _total - 1);  
}

void GroupOfNumbers::quick_choose_first(){
 quick_choose_first(0, _total - 1); 
}

void GroupOfNumbers::quick_choose_middle(){
 quick_choose_middle(0, _total - 1); 
}

void GroupOfNumbers::quick_choose_last(){
 quick_choose_last(0, _total - 1); 
}

void GroupOfNumbers::quick_choose_first(long left, long right)
{
  if( left + CutOff <= right)
  {
    long pivot = _group[left];
    long i = left, j = right + 1;
    for( ; ;){
      while(i < right && _group[++i] < pivot ) { }
      while(j >= left && pivot < _group[--j]) { }
      if( i < j){
	       swap( _group[i], _group[j]);
      }
      else
	       break;
    }
    swap( _group[ j ], _group[ left ] ); // Restore pivot
    quick_choose_first(left, j - 1);
    quick_choose_first(j + 1, right);
  }
  else
    insertion_sort(left, right);
}

void GroupOfNumbers::quick_choose_middle(long left, long right)
{
       if( left + CutOff <= right)
  {
    long center = (left+right)/2;
    swap(_group[center], _group[right]);
    long pivot = _group[right];
    long i = left - 1 , j = right;
    for( ; ;)
    {
      while(_group[++i] < pivot ) { }
      while(j > left &&pivot < _group[--j]) { }
      if( i < j)
      {
	swap( _group[i], _group[j]);
      }
      else
	break;
    }
    swap( _group[ i ], _group[ right] ); // Restore pivot
    quick_choose_middle(left, i - 1);
    quick_choose_middle(i + 1, right);
  }
  else
    insertion_sort(left, right);
}

void GroupOfNumbers::quick_choose_last(long left, long right)
{
  if( left + CutOff <= right)
  {
    long pivot = _group[right];
    long i = left - 1, j = right;
    for( ; ;)
    {
      while(i <= right && _group[++i] < pivot) { }
      while(j > left && pivot < _group[--j]) { }
      if( i < j)
      {
	swap( _group[i], _group[j]);
	}
      else
	break;
      
    }
    swap( _group[ i ], _group[ right ] ); // Restore pivot
    quick_choose_last(left, i - 1);
    quick_choose_last(i + 1, right);
  }
  else
    insertion_sort(left, right);
}

  bool GroupOfNumbers::sort_select(long k, long & kth_smallest) const
  {
    if(k > _total || k <= 0){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    temp.quicksort();
    kth_smallest = temp._group[k - 1];
    return true;
  }
  
   bool GroupOfNumbers::partial_sort_select(long k, long & kth_smallest) const{
    if(k > _total || k <= 0){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    temp.quicksort(0, k - 1);
    for(int i = k; i < temp._total; i++){
      if(temp._group[i] < temp._group[k-1]){
        temp._group[k-1] = temp._group[i];
        for(long p = k-1; p >0; p--){
          if(temp._group[p] < temp._group[p-1]){
            swap(temp._group[p], temp._group[p-1]);
          }
          else{
            break; //As first k items are sorted. No need to check further.
          }
        }
      }
    }
    kth_smallest = temp._group[k - 1];
    return true;
  }

   bool GroupOfNumbers::min_heap_select(long k, long & kth_smallest) const{
    if(k > _total || k <= 0){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    for( int i = temp._total / 2; i>=0; i--){
      temp.percolate_up( i, temp._total);
    }
    for(int i = 0; i < k - 1 ; i++){
      swap(temp._group[0], temp._group[--temp._total]);
	    temp.percolate_up(0, temp._total);
    }
	 kth_smallest = temp._group[0];
	 return true;
  }

   bool GroupOfNumbers::partial_max_heap_select(long k, long & kth_smallest) const{
    if(k > _total || k <= 0){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    for( int i = k / 2; i>=0; i--){
      temp.percolate_down( i, k);
    }
    for(int j = k; j <= temp._total - 1; j++){
	     if(temp._group[0] > temp._group[j]){
		    swap(temp._group[j], temp._group[0]);
		    temp.percolate_down( 0, k);
	     }
    }
	 kth_smallest = temp._group[0];
	 return true;
  }
   
   bool GroupOfNumbers::quick_select(long k, long & kth_smallest) const{ 
    if(k > _total || k <= 0){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    temp.quickSelect(0, temp._total-1, k);   
    kth_smallest = temp._group[k - 1];
    return true;
   }

   void GroupOfNumbers::quickSelect(long left, long right, long k){
   if( left + CutOff <= right){
    long pivot = median_of_3(left, right);
    long i = left, j = right - 1;
    for( ; ;)
    {
      while(_group[++i] < pivot ) { }
      while(pivot < _group[--j]) { }
      if( i < j){
        swap( _group[i], _group[j]);
      }
      else
  break;
    }
    swap( _group[ i ], _group[ right - 1] ); // Restore pivot
    if( k <= i)
      quickSelect(left, i - 1, k);
    else if( k > i + 1)
      quickSelect(i + 1, right, k);
  }
  else
    insertion_sort(left, right);
	}

bool GroupOfNumbers::linear_select(long k, long & kth_smallest) const{
    if(k > _total || k < 1){
      return false;
    }
    GroupOfNumbers temp;
    temp = GroupOfNumbers(*this);
    temp.linearSelect(0, temp._total - 1, k);   
    kth_smallest = temp._group[k - 1];
    return true;
}

   void GroupOfNumbers::linearSelect(long left, long right, long k){
    if( left + CutOff <= right){
      long pivot = median_of_5(left, right, k);
      long i = left, j = right + 1;
      for( ; ;){
        while(i < right && _group[++i] < pivot ) { }
          while(j >= left &&pivot < _group[--j]) { }
            if( i < j){
              swap( _group[i], _group[j]);
            }
            else
              break;
          }
      swap( _group[ j ], _group[ left ] ); // Restore pivot
      if( k <= j)
        linearSelect(left, j, k);
      else if( k > j + 1)
        linearSelect(j + 1, right, k);
    }
    else
      insertion_sort(left, right);
  }

  long GroupOfNumbers::median_of_5(long left, long right, long k){
    for(long i = left; i + 4 <= right; i = i + 5){
      quicksort(i, i+4);
      swap(_group[left + (i-left) / 5], _group[i + 2]);
    }
    long tot = (right + 1 - left)/ 5;
    if(!(tot % 2)){
      tot = tot / 2;
    }
    else{
      tot = tot / 2;
      tot++;

    }
    tot--;
    linearSelect(left, left + (right - left) / 5 , tot + left );
    swap(_group[left], _group[tot + left]);
    return _group[left];
  }
