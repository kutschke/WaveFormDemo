#include "ArrayView.hh"

#include <iostream>
#include <stdexcept>
#include <string>

int ArrayView::at(int i) const {
  if ( i >= _size ){
    std::string arg{"ArrayView::at index out of range: "};
    arg += std::to_string(i);
    arg += " Max allowed: ";
    arg += std::to_string(_size);
    throw std::out_of_range ( arg );
  }
  return _v[i];
}

std::ostream& operator<<(std::ostream& ost,
                         const ArrayView& wf ){
  for ( int i=0; i< wf.size(); i++){
    if ( i != 0 ) ost << " ";
    ost << wf[i];
  }
  return ost;
}
