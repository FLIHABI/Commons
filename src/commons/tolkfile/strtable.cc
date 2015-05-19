#include "commons/tolkfile/strtable.hh"

namespace tolk
{

std::ostream& operator<<(std::ostream& out, const StrTable& strtable)
{
  char32_t size = strtable._table.size();
  out.write((char*) &size, sizeof (char32_t));

  for (auto i = strtable._table.begin(); i != strtable._table.end(); ++i)
  {
    char32_t size = i->second.size();

    out.write((char*) &i->first, sizeof (char32_t));
    out.write((char*) &size, sizeof (char32_t));

    const char *buffer = i->second.c_str();
    out.write(buffer, size * sizeof (char));
  }

  return out;
}

std::istream& operator>>(std::istream& in, StrTable& strtable)
{
  strtable._table.clear();

  char32_t size = 0;
  in.read((char*) &size, sizeof (char32_t));

  for (char32_t i = 0; i < size; ++i)
  {
    char32_t id = 0;
    char32_t size = 0;

    in.read((char*) &id, sizeof (char32_t));
    in.read((char*) &size, sizeof (char32_t));

    char *buffer = new char[size + 1];
    in.read(buffer, size * sizeof (char));
    buffer[size] = '\0';

    strtable._table.insert(std::pair<char32_t, std::string>(id, std::string(buffer)));

    free(buffer);
  }

  return in;
}

}
