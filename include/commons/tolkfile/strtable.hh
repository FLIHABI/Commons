#ifndef _STRTABLE_HH__
# define _STRTABLE_HH__

# include <map>
# include <string>
# include <iostream>

namespace tolk
{

  class StrTable
  {
  private:
    /* Association between a string ID and the string itself */
    std::map<char32_t, std::string> _table;

  public:
    inline void insert(char32_t key, std::string value)
    {
      _table.insert(std::pair<char32_t, std::string>(key, value));
    }

    inline std::string get(char32_t key) const
    {
      return _table.at(key);
    }

    inline const std::map<char32_t, std::string>& get_table() const
    {
      return _table;
    }

    /** serialization */
    friend std::ostream& operator<<(std::ostream& out, const StrTable& symtable);

    /** deserialization */
    friend std::istream& operator>>(std::istream& in, StrTable& symtable);
  };

};

#endif /* !_STRTABLE_HH_ */
