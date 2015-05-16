#ifndef _FUNCTABLE_HH__
# define _FUNCTABLE_HH__

# include <map>
# include <iostream>

namespace tolk
{

  /** A function pointer */
  struct Function
  {
    /** Offset of the function in the bytecode */
    char32_t offset;

    /** Registers */
    char32_t registers;

    /** Offset of the registers */
    int64_t  registers_offset;

    Function(char32_t _offset, char32_t _registers, int64_t _registers_offset)
      : offset(_offset), registers(_registers), registers_offset(_registers_offset) {}
  };

  class FuncTable
  {
  private:
    /* Association between a function ID and the function pointer structure */
    std::map<char32_t, Function> _table;

  public:

    inline void insert(char32_t key, Function value)
    {
      _table.insert(std::pair<char32_t, Function>(key, value));
    }

    inline Function get(char32_t key) const
    {
      return _table.at(key);
    }

    inline const std::map<char32_t, Function>& get_table() const
    {
      return _table;
    }

    /** serialization */
    friend std::ostream& operator<<(std::ostream& out, const FuncTable& symtable);

    /** deserialization */
    friend std::istream& operator>>(std::istream& in, FuncTable& symtable);
  };

};

#endif /* !_FUNCTABLE_HH_ */
