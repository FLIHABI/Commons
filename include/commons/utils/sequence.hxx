#ifndef COMMONS_UTILS_SEQUENCE_HXX_
# define COMMONS_UTILS_SEQUENCE_HXX_

# include <commons/utils/traits.hxx>

namespace sequence {

    template<unsigned... Is>
    struct seq {};

    template<unsigned N, unsigned... Is>
    struct generate : generate<N - 1, N - 1, Is...> {};

    template<unsigned... Is>
    struct generate<0, Is...> : seq<Is...> {};

    template<typename R>
    struct array {

        template<unsigned size>
        struct GeneratedArray {
            R result[size];
        };

        template<typename Func, unsigned... Is>
        static constexpr GeneratedArray<sizeof...(Is)> generate(Func f, seq<Is...>) {
            return {{ f(Is)... }};
        }

        template<unsigned size, typename Func>
        static constexpr GeneratedArray<size> generate(Func f) {
            return array<R>::generate(f, sequence::generate<size>{});
        }
    };
}

#endif /* !COMMONS_UTILS_SEQUENCE_HXX_ */
