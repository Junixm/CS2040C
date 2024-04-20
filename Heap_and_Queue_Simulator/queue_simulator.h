#if !defined(__QUEUE_SIMULATOR_H__)
#define __QUEUE_SIMULATOR_H__

#include <vector>

#include "customer.h"

using std::vector;

class QueueSimulator {
 private:
  bool _priority_order;
  int _num_servers;

 public:
  QueueSimulator() : _priority_order(false), _num_servers(1){};

  // If priority_order is false, then customers are served in the order they
  // arrive. If priority_order is true, then customers with the shortest
  // processing time are to be served first.
  void set_priority_order(bool priority_order) {
    _priority_order = priority_order;
  }

  // Set the number of servers available to serve customers.
  void set_num_servers(int num_servers) { _num_servers = num_servers; }

  // Simulate the queue of customers served by a single server.
  // Assume that the customer list is sorted by arrival time.
  // Individual customer service times are returned in the customers parameter.
  // If priority_order is false, then customers are served in the order they
  // arrive. If priority_order is true, then customers with the shortest
  // processing time are to be served first. The return value is the total
  // waiting time for all customers.
  vector<Customer> simulateQueue(const vector<Customer>& customers);
};

#endif  // __QUEUE_SIMULATOR_H__
