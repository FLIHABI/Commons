#include "commons/tolkfile/tolk-file.hh"

#include <fstream>

namespace tolk
{

std::ostream& operator<<(std::ostream& stream, const std::vector<char>& vec)
{
  size_t size = vec.size();
  stream.write((char*)&size, sizeof (size_t));

  for (size_t i = 0; i < size; ++i)
    stream.write((char*) &vec[i], sizeof(char));

  return stream;
}

std::istream& operator>>(std::istream& stream, std::vector<char>& vec)
{
  vec.clear();

  size_t size = 0;
  stream.read((char*)&size, sizeof (size_t));

  vec.resize(size);

  for (size_t i = 0; i < size; ++i)
    stream.read((char*) &vec[i], sizeof(char));

  return stream;
}

std::shared_ptr<TolkFile> TolkFile::load(const std::string& filename)
{
  std::filebuf fb;
  if (!fb.open(filename.c_str(), std::ios::in))
    return nullptr;

  std::istream in(&fb);
  std::shared_ptr<TolkFile> tf = load(in);
  fb.close();

  return tf;
}

std::shared_ptr<TolkFile> TolkFile::load(std::istream& stream)
{
  TolkFile tf;

  for (int i = 0; i < 4; ++i)
    stream.read((char*) &tf._magic[i], sizeof (int8_t));
  stream.read((char*) &tf._entry_point, sizeof (char32_t));

  stream >> tf._symtable;
  stream >> tf._strtable;
  stream >> tf._functable;
  stream >> tf._structtable;
  stream >> tf._uniontable;
  stream >> tf._bytecode;

  return std::make_shared<TolkFile>(tf);
}

bool TolkFile::save(const std::string& filename) const
{
  std::filebuf fb;
  if (!fb.open(filename.c_str(), std::ios::out | std::ios::trunc))
    return false;

  std::ostream out(&fb);
  bool b = save(out);
  fb.close();

  return b;
}

bool TolkFile::save(std::ostream& stream) const
{
  for (int i = 0; i < 4; ++i)
    stream.write((char*) &_magic[i], sizeof (int8_t));
  stream.write((char*) &_entry_point, sizeof (char32_t));

  stream << _symtable;
  stream << _strtable;
  stream << _functable;
  stream << _structtable;
  stream << _uniontable;
  stream << _bytecode;

  return true;
}

std::ostream& operator<<(std::ostream& out, const TolkFile& tf)
{
  out << std::hex;

  out << "-- Header --" << std::endl;
  out << " - Magic:" <<
    " 0x" << tf._magic[0] << " 0x" << tf._magic[1] <<
    " 0x" << tf._magic[2] << " 0x" << tf._magic[3] << std::endl;
  out << " - Entry point: 0x" << tf._entry_point << std::endl;
  out << std::endl;

  out << "-- Symbol Table --" << std::endl;
  std::map<char32_t, Symbol> symtable = tf._symtable.get_table();
  for (auto sym = symtable.begin(); sym != symtable.end(); ++sym)
    out << " - " << std::dec << sym->first << ": "
        << std::hex << sym->second.offset << std::endl;
  out << std::endl;

  out << "-- String Table --" << std::endl;
  std::map<char32_t, std::string> strtable = tf._strtable.get_table();
  for (auto str = strtable.begin(); str != strtable.end(); ++str)
    out << " - " << std::dec << str->first << ": "
        << std::hex << str->second << std::endl;
  out << "" << std::endl;

  out << "-- Function Table --" << std::endl;
  std::map<char32_t, Function> functable = tf._functable.get_table();
  for (auto func = functable.begin(); func != functable.end(); ++func)
    out << " - " << std::dec << func->first << ": 0x"
        << std::hex << func->second.offset << ", 0x" << func->second.registers
        << ", 0x" << func->second.registers_offset << std::endl;

  return out;
}

}
