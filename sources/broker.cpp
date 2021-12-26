// Copyright 2021 Your Name <your_email>
#include "broker.hpp"

using namespace boost::filesystem;

bool check_file(const path &p) {
  if (is_regular_file(p) && p.extension().string() == ".txt") return true;
  return false;
}

void broker::read_file_info(const path &p) {
  if (!check_file(p)) throw std::exception();

  auto *accountInfo = new account::account_info();
  unsigned const arr_len = 3;
  std::string account_num;
  std::string *arr[arr_len] = {&account_num, &accountInfo->type,
                               &accountInfo->date};

  std::string file_stem = p.stem().string();

  unsigned j = 0;
  for (char i : file_stem) {
    if (i == '_') {
      if (j == arr_len - 1) break;
      j++;
    } else {
      *arr[j] += i;
    }
  }
  if (j != arr_len - 1) return;

  accountInfo->extension = p.extension().string();

  unsigned unsigned_account_num = std::stoul(account_num);
  for (auto item : accounts) {
    if (item->account_num == unsigned_account_num) {
      item->info.push_back(accountInfo);
      if (accountInfo->date > *item->last_date)
        *item->last_date = accountInfo->date;
      return;
    }
  }
  auto *new_account = new account();
  new_account->info.push_back(accountInfo);
  new_account->account_num = unsigned_account_num;
  *new_account->last_date = accountInfo->date;
}

void broker::add(const path &p) {
  if (is_directory(p)) {
    for (const directory_entry &x : directory_iterator{p}) add(x.path());
  } else if (is_symlink(p)) {
    add(read_symlink(p));
  } else {
    if (is_empty(p)) return;
    try {
      read_file_info(p);
      std::cout << "name:" << *name << " " << p.filename() << std::endl;
    } catch (std::exception &exception) {
      return;
    }
  }
}

broker::broker() {
  name = nullptr;
  read_info(boost::filesystem::current_path());
}

broker::broker(const path &p) {
  name = nullptr;
  read_info(p);
}

void broker::read_info(const path &p) {
  if (is_directory(p)) {
    if (!name) name = new std::string(p.filename().string());
  } else { return; }
  add(p);
}

void broker::set_name(std::string &str) { *name = str; }

broker::~broker() {
  delete name;
  std::destroy(accounts.begin(), accounts.end());
}

Brokers::Brokers() { read_info(boost::filesystem::current_path()); }

Brokers::Brokers(const path &p) { read_info(p); }

void Brokers::read_info(const path &p) {
  for (const directory_entry &x : directory_iterator{p}) {
    if (is_directory(x.path())) {
      bool condition_flag = true;
      for (auto item : brokers) {
        if (x.path().filename() == *item->name) {
          item->read_info(x.path());
          condition_flag = false;
          break;
        }
      }
      if (condition_flag) {
        auto *new_broker = new broker(x.path());
        if (!new_broker->accounts.empty())
          brokers.push_back(new_broker);
        else
          delete new_broker;
      }
    }
  }
}

std::ostream &Brokers::operator<<(std::ostream &os) {
  for (auto item : brokers) {
    for (auto j : item->accounts) {
      os << "broker:" << *item->name << " ";
      os << "account:" << j->account_num << " ";
      os << "files:" << j->info.size() << " ";
      os << "lastdate:" << *j->last_date;
    }
  }
  return os;
}

Brokers::~Brokers() { std::destroy(brokers.begin(), brokers.end()); }
