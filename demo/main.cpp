// Copyright 2021 Your Name <your_email>
#include <broker.hpp>
using namespace boost::filesystem;

int main(int argc, char* argv[]) {
  Brokers* brs;
  if (argc < 2)
    brs = new Brokers();
  else
    brs = new Brokers(argv[1]);

  delete brs;
  return 0;
}
