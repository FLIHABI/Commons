#include "commons/tolkfile/symtable.hh"

namespace tolk
{

std::ostream& operator<<(std::ostream& out, const SymTable& symtable)
{
  char32_t size = symtable._table.size();
  out.write((char*) &size, sizeof (char32_t));

  for (auto i = symtable._table.begin(); i != symtable._table.end(); ++i)
  {
    out.write((char*) &i->first, sizeof (char32_t));
    out.write((char*) &i->second.offset, sizeof (char32_t));
  }

  return out;
}

std::istream& operator>>(std::istream& in, SymTable& symtable)
{
  symtable._table.clear();

  char32_t size = symtable._table.size();
  in.read((char*) &size, sizeof (char32_t));

  for (char32_t i = 0; i < size; ++i)
  {
    char32_t id = 0;
    Symbol sym(0);

    in.read((char*) &id, sizeof (char32_t));
    in.read((char*) &sym.offset, sizeof (char32_t));

    symtable._table.insert(std::pair<char32_t, Symbol>(id, sym));
  }

  return in;
}

}
