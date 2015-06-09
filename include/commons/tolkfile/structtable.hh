#ifndef STRUCTTABLE_HH
# define STRUCTTABLE_HH

# include <map>
# include <vector>
# include <iostream>

namespace tolk
{
    struct Struct
    {
        std::vector<char32_t> component;
    };

    class StructTable
    {
        private:
            std::map<char32_t, Struct> _table;

        public:
            inline void insert(char32_t key, Struct value)
            {
                _table.insert(std::pair<char32_t, Struct>(key, value));
            }

            inline Struct get(char32_t key) const
            {
                return _table.at(key);
            }

            inline const std::map<char32_t, Struct>& get_table() const
            {
                return _table;
            }

            /** serialization */
            friend std::ostream& operator<<(std::ostream& out, const StructTable& symtable);

            /** deserialization */
            friend std::istream& operator>>(std::istream& in, StructTable& symtable);
    };
}
#endif /*STRUCTTABLE_HH */
