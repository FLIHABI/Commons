#ifndef MD5_HH
# define MD5_HH

# include <string>
# include <vector>

namespace utils
{
  std::vector<unsigned char> compute_md5(std::string datas);
}

#endif /* end of include guard: MD5_HH */
