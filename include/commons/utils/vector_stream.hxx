#ifndef VECTOR_STREAM_HXX_
# define VECTOR_STREAM_HXX_

# include <vector>

namespace vector_stream {

    template <typename T>
    void write(std::vector<char>& vec, const T v) {
        for (int i = 0; i != sizeof (T) * 8; i += 8)
            vec.push_back((v >> i) & 0xFF);
    }
}

template <typename T>
std::vector<char>& operator<<(std::vector<char>& vec, const T v) {
    vector_stream::write(vec, v);
    return vec;
}

#endif /* !VECTOR_STREAM_HXX_ */
