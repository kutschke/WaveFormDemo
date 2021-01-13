#ifndef ArrayView_hh
#define ArrayView_hh
//
// Not a real class; just a view into one variable length waveform held inside
// the collection object.
//

#include <iosfwd>

class ArrayView{
public:

  ArrayView()  = delete;
  ~ArrayView() = delete;
  ArrayView( ArrayView const&)  = delete;
  ArrayView( ArrayView const&&) = delete;
  ArrayView& operator=( ArrayView const&)   = delete;
  ArrayView& operator=( ArrayView const&&)  = delete;

  int size()    const { return _size; }
  int at(int i) const;

  int operator[](int i) const { return _v[i]; }

  int const* data() const { return _v; }

private:
  const int _size;
  int _v[];
};

std::ostream& operator<<(std::ostream& ost, const ArrayView& wf );

#endif // ArrayView_hh
