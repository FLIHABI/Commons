#ifndef _SYMTABLE_HH__
# define _SYMTABLE_HH__

# include <map>
# include <iostream>

namespace tolk
{

  /** A symbol */
  struct Symbol
  {
    /** Offset of the symbol in the bytecode */
    char32_t offset;

    Symbol(char32_t _offset)
      : offset(_offset) {}
  };

  class SymTable
  {
  private:
    /* Association between a symbol ID and the symbol pointer struct */
    std::map<char32_t, Symbol> _table;

  public:
    inline void insert(char32_t key, Symbol value)
    {
      _table.insert(std::pair<char32_t, Symbol>(key, value));
    }

    inline Symbol get(char32_t key) const
    {
      return _table.at(key);
    }

    inline const std::map<char32_t, Symbol>& get_table() const
    {
      return _table;
    }

    /** serialization */
    friend std::ostream& operator<<(std::ostream& out, const SymTable& symtable);

    /** deserialization */
    friend std::istream& operator>>(std::istream& in, SymTable& symtable);
  };

};

#endif /* !_SYMTABLE_HH_ */
