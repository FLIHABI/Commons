#include "commons/tolkfile/functable.hh"

namespace tolk
{
std::ostream& operator<<(std::ostream& out, const FuncTable& functable)
{
  char32_t size = functable._table.size();
  out.write((char*) &size, sizeof (char32_t));

  for (auto i = functable._table.begin(); i != functable._table.end(); ++i)
  {
    Function f = i->second;

    out.write((char*) &i->first, sizeof (char32_t));
    out.write((char*) &f.offset, sizeof (char32_t));
    out.write((char*) &f.registers, sizeof (char32_t));
    out.write((char*) &f.registers_offset, sizeof (int64_t));

    char32_t size_ = i->second.params.size();
    out.write((char*) &size_, sizeof (int64_t));
    for (auto c : f.params)
        out.write((char*) &c, sizeof (char32_t));
  }

  return out;
}

std::istream& operator>>(std::istream& in, FuncTable& functable)
{
  functable._table.clear();

  char32_t size = 0;
  in.read((char*) &size, sizeof (char32_t));

  for (char32_t i = 0; i < size; ++i)
  {
    char32_t id = 0;
    Function func(0, 0, 0);

    in.read((char*) &id, sizeof (char32_t));
    in.read((char*) &func.offset, sizeof (char32_t));
    in.read((char*) &func.registers, sizeof (char32_t));
    in.read((char*) &func.registers_offset, sizeof (int64_t));

    char32_t size_ = 0;
    in.read((char*) &size_, sizeof(char32_t));

    for (char32_t i = 0; i < size_; ++i)
    {
        char32_t component = 0;
        in.read((char*) &component, sizeof(char32_t));
        func.params.push_back(component);
    }

    functable._table.insert(std::pair<char32_t, Function>(id, func));
  }

  return in;
}
}
