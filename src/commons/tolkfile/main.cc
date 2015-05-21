#include <iostream>
#include <iomanip>
#include "tolk-file.hh"

using namespace tolk;

int main(int argc, char** argv)
{
  std::cout << std::hex;

  for (int i = 1; i < argc; ++i)
  {
    std::shared_ptr<TolkFile> tf = TolkFile::load(argv[i]);
    std::vector<char> bytecode = tf->get_bytecode();

    std::cout << argv[i] << std::endl;

    if (bytecode.size() <= 0)
      continue;

    std::cout << "0x" << std::setfill('0') << std::setw(2) << (int) bytecode[0];
    for (size_t i = 1; i < bytecode.size(); ++i)
      std::cout << " 0x"
                << std::setfill('0')
                << std::setw(2)
                << (int) (unsigned char) bytecode[i];
    std::cout << std::endl;
  }

  return 0;
}
