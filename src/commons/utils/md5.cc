#include <openssl/md5.h>

#include "commons/utils/md5.hh"

std::vector<unsigned char> utils::compute_md5(std::string datas)
{
  unsigned char md[MD5_DIGEST_LENGTH];
  MD5(reinterpret_cast<const unsigned char*>(datas.data()), datas.size(), md);

  return std::vector<unsigned char>(md, md + MD5_DIGEST_LENGTH);
}
