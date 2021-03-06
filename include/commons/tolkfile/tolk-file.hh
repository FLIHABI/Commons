#ifndef TOLK_FILE_HH_
# define TOLK_FILE_HH_

# include <string>
# include <vector>
# include <map>
# include <memory>
# include <algorithm>
# include <iostream>

# include "commons/tolkfile/symtable.hh"
# include "commons/tolkfile/strtable.hh"
# include "commons/tolkfile/functable.hh"
# include "commons/tolkfile/structtable.hh"

# define MAGIC_1 0x54
# define MAGIC_2 0x52
# define MAGIC_3 0x4F
# define MAGIC_4 0x4C

namespace tolk
{

  class TolkFile
  {
  private:
    int8_t _magic[4] = {MAGIC_1, MAGIC_2, MAGIC_3, MAGIC_4};
    char32_t _entry_point = 0x0;
    char32_t _register_number = 0x0;

    SymTable    _symtable;
    StrTable    _strtable;
    FuncTable   _functable;
    StructTable _structtable;
    StructTable _uniontable;
    SymTable    _arraytable;

    std::vector<char> _bytecode;

  public:

    static std::shared_ptr<TolkFile> load(const std::string& filename);
    static std::shared_ptr<TolkFile> load(std::istream& stream);

    bool save(const std::string& filename) const;
    bool save(std::ostream& stream) const;

    inline char32_t get_entry_point() const
    {
      return _entry_point;
    }

    inline void set_entry_point(char32_t entry_point)
    {
      _entry_point = entry_point;
    }

    inline char32_t get_register_number() const
    {
      return _register_number;
    }

    inline void set_register_number(char32_t register_number)
    {
      _register_number = register_number;
    }

    inline const SymTable& get_symtable() const
    {
      return _symtable;
    }

    inline void set_symtable(const SymTable& symtable)
    {
      _symtable = symtable;
    }

    inline const StrTable& get_strtable() const
    {
      return _strtable;
    }

    inline void set_strtable(const StrTable& strtable)
    {
      _strtable = strtable;
    }

    inline const FuncTable& get_functable() const
    {
      return _functable;
    }

    inline void set_functable(const FuncTable& functable)
    {
      _functable = functable;
    }

    inline const StructTable& get_structtable() const
    {
      return _structtable;
    }

    inline void set_structtable(const StructTable& structtable)
    {
      _structtable = structtable;
    }

    inline const StructTable& get_uniontable() const
    {
      return _uniontable;
    }

    inline void set_uniontable(const StructTable& uniontable)
    {
      _uniontable = uniontable;
    }

    inline const SymTable& get_arraytable() const
    {
      return _arraytable;
    }

    inline void set_arraytable(const SymTable& arraytable)
    {
      _arraytable = arraytable;
    }

    inline const std::vector<char>& get_bytecode() const
    {
      return _bytecode;
    }

    inline void set_bytecode(char *bytecode, size_t size)
    {
      std::copy(bytecode, bytecode + size, std::back_inserter(_bytecode));
    }

    inline void set_bytecode(std::vector<char>& bytecode)
    {
      _bytecode = std::move(bytecode);
    }

    friend std::ostream& operator<<(std::ostream& out, const TolkFile& tf);
  };

}

#endif /* !TOLK_FILE_HH_ */
