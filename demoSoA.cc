//  Demo the struct of arrays implemenation.  See README.txt
//
// For n hits, the storage is laid out as:
// Index Range   Content
//   0 ... n-1    channelID
//   n ...2n-1    tdc value
//  2n ...3n-1    index into the waveform store
//  3n ...        waveform store
//
// Within the waveform store, each waveform is stored as
//   int size
//   int val0
//   int val1
//    ... and so on.
//

#include "ArrayView.hh"

#include <iostream>
#include <array>
#include <vector>

using namespace std;

// The actual data payload class.
class RawCollections{
public:

  // c'tor for testing only with patterned data.  No real c'tor yet.
  RawCollections( size_t nEntries, size_t totalSize );

  size_t size()           const { return _n; }
  int    chanID(size_t i) const { return _storage.at(channel_index(i)); }
  int    tdc(size_t i)    const { return _storage.at(tdc_index(i));     }
  int    size(size_t i)   const { return _storage.at(data_index(i));    }

  ArrayView const& waveform(size_t i) const { return (ArrayView const&)(_storage.at(data_index(i))); }

  int const* storage() const { return &_storage.front(); }

private:
  size_t channel_index( size_t i) const { return      i;}
  size_t tdc_index    ( size_t i) const { return   _n+i;}
  size_t index_index  ( size_t i) const { return 2*_n+i;}
  size_t data_index   ( size_t i) const { return _storage[index_index(i)];}

  size_t _n;
  std::vector<int> _storage;
};

// c'tor to test the principle; fill the collection with patterned data.
RawCollections::RawCollections( size_t n, size_t size):_n(n),_storage(size){

  int next = _n*3;
  for ( size_t i=0; i<_n; ++i ){
    int chanID=10+i;
    int length=i+1;
    int tdc   =1000*(i+1) + 1;
    _storage.at(channel_index(i)) = chanID;
    _storage.at(tdc_index(i))     = tdc;
    _storage.at(index_index(i))   = next;
    _storage.at(next++) = length;
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

  // Make the patterned data
  RawCollections w(n,25);

  // View the patterned data.
  cout << "\nView data ordered by hit: " << endl;
  for ( int i=0; i<n;  ++i ){
    cout << i << " : " << w.chanID(i) << " " << w.tdc(i) << " " << w.waveform(i) << endl;
  }

  return 0;
}
