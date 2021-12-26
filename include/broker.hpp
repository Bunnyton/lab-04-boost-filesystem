#ifndef INCLUDE_BROKER_HPP_
#define INCLUDE_BROKER_HPP_

#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;

struct account{
  struct account_info{
    std::string type;
    std::string date;
    std::string extension;
  };
  unsigned account_num;
  std::vector<account_info*> info;
  std::string* last_date;
};

class broker{
 public:
  std::string* name;
  std::vector<account*> accounts;
 public:
    broker();
    broker(const path &p);
    void add(const path &p);
    void read_file_info(const path &p);
    void read_info(const path &p);
    void set_name(std::string &str);
    ~broker();
};

class Brokers{
 private:
  std::vector<broker*> brokers;
 public:
  Brokers();
  Brokers(const path &p);
  void read_info(const path &p);
  std::ostream& operator<<(std::ostream& os);
  ~Brokers();
};
#endif  // INCLUDE_BROKER_HPP_
