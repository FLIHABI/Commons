#include <utility>
#include "commons/tolkfile/structtable.hh"

namespace tolk
{
    std::ostream& operator<<(std::ostream& out, const StructTable& structable)
    {
        char32_t size = structable._table.size();
        out.write((char*) &size, sizeof (char32_t));

        for (auto i = structable._table.begin(); i != structable._table.end(); ++i)
        {
            char32_t size_ = i->second.component.size();
            out.write((char*) &i->first, sizeof(char32_t));
            out.write((char*) &size_, sizeof(char32_t));

            for (auto c : i->second.component)
            {
                out.write((char*) &c, sizeof(char32_t));
            }
        }

        return out;
    }

    std::istream& operator>>(std::istream& in, StructTable& structable)
    {
        structable._table.clear();

        char32_t size = 0;
        in.read((char*) &size, sizeof(char32_t));

        for (char32_t i = 0; i < size; ++i)
        {
            char32_t id = 0;
            char32_t size_ = 0;
            Struct struct_;

            in.read((char*) &id, sizeof(char32_t));
            in.read((char*) &size_, sizeof(char32_t));

            for (char32_t i = 0; i < size_; ++i)
            {
                char32_t component = 0;
                in.read((char*) &component, sizeof(char32_t));
                struct_.component.push_back(component);
            }

            structable._table.insert(std::pair<char32_t, Struct>(id,
                                                        std::move(struct_)));
        }
        return in;
    }

}
