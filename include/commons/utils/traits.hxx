#ifndef COMMONS_UTILS_TRAITS_HXX_
# define COMMONS_UTILS_TRAITS_HXX_

namespace traits {

    template <class F>
    struct return_type;

    template <class R, class... A>
    struct return_type<R (*)(A...)> {
        typedef R type;
    };

}

#endif /* !COMMONS_UTILS_TRAITS_HXX_ */

