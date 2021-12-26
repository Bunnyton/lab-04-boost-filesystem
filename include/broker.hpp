// Copyright 2021 Your Name <your_email>
#ifndef INCLUDE_BROKER_HPP_
#define INCLUDE_BROKER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>

#include "boost/filesystem.hpp"

struct account {
  struct account_info {
    std::string type;
    std::string date;
    std::string extension;
  };
  unsigned account_num;
  std::vector<account_info *> info;
  std::string *last_date;
};

class broker {
 public:
  std::string *name;
  std::vector<account *> accounts;

 public:
  broker();
  explicit broker(const boost::filesystem::path &p);
  void add(const boost::filesystem::path &p);
  void read_file_info(const boost::filesystem::path &p);
  void read_info(const boost::filesystem::path &p);
  void set_name(std::string &str);
  ~broker();
};

class Brokers {
 private:
  std::vector<broker *> brokers;

 public:
  Brokers();
  explicit Brokers(const boost::filesystem::path &p);
  void read_info(const boost::filesystem::path &p);
  std::ostream &operator<<(std::ostream &os);
  ~Brokers();
};
#endif  // INCLUDE_BROKER_HPP_
