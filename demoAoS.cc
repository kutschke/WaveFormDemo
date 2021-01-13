//
// Demo of an Arrary of Structures proof of principle for a collection of raw hit
// objects, each with a variable length waveform.
//
// Each hit object has the content of:
//    channelID
//    TDC value
//    variable length waveform (ADC values)
//
// The code writes a test pattern with:
//   channelID   TDC   Waveform
//     10       1001   100
//     11       2001   200, 201
//     12       3001   300, 301, 3020
//

#include "ArrayView.hh"

#include <iostream>
#include <array>
#include <vector>

using namespace std;

// Not a real class; just a view into one RawView held inside an object of the collection type.
class RawView{
public:

  RawView()  = delete;
  ~RawView() = delete;
  RawView( RawView const&)  = delete;
  RawView( RawView const&&) = delete;
  RawView& operator=( RawView const&)   = delete;
  RawView& operator=( RawView const&&)  = delete;

  int chanID()  const { return _id; }
  int tdc()     const { return _tdc; }
  int size()    const { return _size; }

  ArrayView const& waveform() const { return (ArrayView const&)(*(&_size)); }

private:
  int _id;
  int _tdc;
  int _size;
  int _v[];
};

inline std::ostream& operator<<(std::ostream& ost,
                                const RawView& wf ){
  ost << wf.chanID() << " "
      << wf.tdc() << " "
      << wf.waveform();
  return ost;
}

// The actual data payload class.
class RawCollection{
public:

  // c'tor for testing only with patterned data.  No real c'tor yet.
  RawCollection( int n, int size);

  RawView const& at(int i) const { return (RawView const&)(_storage.at(_index.at(i))); }

  // Also provide Struct of Arrays style accesors
  int chanID( int i)  const { return at(i).chanID(); }
  int tdc( int i)     const { return at(i).tdc();    }
  int size( int i)    const { return at(i).size();   }

  ArrayView const& waveform( int i) const { return at(i).waveform(); }

  int const* storage() const { return &_storage.front(); }


private:
  std::vector<int> _index;
  std::vector<int> _storage;
};

// c'tor to test the principle; fill the collection with patterned data.
RawCollection::RawCollection( int n, int size):_index(n),_storage(size){

  int next=0;
  for ( int i=0; i<n; ++i ){
    int chanID = 10+i;
    int length = i+1;
    int tdc    = 1000*(i+1) + 1;

    _index[i] = next;
    _storage[next++] = chanID;
    _storage[next++] = tdc;
    _storage[next++] = length;
    for ( int j=0; j<length; j++){
      _storage[next++]=100*(i+1) + j;
    }
  }

  // Debug
  cout << "Dump of buffer content: " << endl;
  for ( int i=0; i<next; ++i){
    cout << i << " : "<< _storage[i] << endl;
  }

}

int main(){
  constexpr int n=3;

  // Make the patterned data; the second arg is just safely big.
  RawCollection  w(n,25);

  // View the patterned data.
  cout << "\nView data as objects: " << endl;
  for ( int i=0; i<n;  ++i ){
    cout << i << " : " << w.at(i) << endl;
  }

  // View the same data using the Struct of Arrays style interface
  cout << "\nView data using SoA style accessors: " << endl;
  for ( int i=0; i<n;  ++i ){
    cout << i << " : " << w.chanID(i) << " " << w.tdc(i) << " " << w.waveform(i) << endl;
  }

  return 0;
}
