#include "queue_simulator.h"
#include "heap.hpp"
#include <iostream>

void stats(const Customer& customer) {
  std::cout << "arrival time: " << customer.arrival_time();
  std::cout << " | processing time: " << customer.processing_time();
  std::cout << " | waiting time: " << customer.waiting_time();
  std::cout << " | service time: " << customer.service_time();
  std::cout << std::endl;
}

void avgWaitTime(const int numServer, const bool priorityOrder, const vector<Customer>& customer){
  int totalWeightTime = 0;
  for(int i = 0; i < customer.size(); i++){
    totalWeightTime += customer[i].waiting_time();
  }
  std::cout << "servers: " << numServer << " | priority: " << priorityOrder;
  std::cout << " | average weight time: "<< totalWeightTime / customer.size() << std::endl;
}

class Server{
private:
  bool _available;
  int _workload;

public:
  Server(): _available(true), _workload(0) {}

  bool isAvailable() const { return _available; }
  void setAvailable(const bool available) { _available = available; }
  int getWorkload() const { return _workload; }
  void increaseWorkload(const int processingTime) { _workload += processingTime; }
  void decreaseWorkload(const int processingTime) { _workload -= processingTime; }
};

class ServerPool{
private:
  vector<Server> servers;
  int _size;
public:
  ServerPool(const int numServers){
    _size = numServers;
    servers.reserve(numServers);
    for(int i = 0; i < numServers; i++){
      servers.push_back(Server());
    }
  }

  int getAvailableServerIndex(){
    for(int i = 0; i < _size; i++){
      if(servers[i].isAvailable()){
        return i;
      }
    }
    return -1; //servers buzy
  }

  bool serveCustomer(const Customer& customer){
    int serverIndex = getAvailableServerIndex();
    if(serverIndex == -1){
      return false; //servers buzy
    }
    servers[serverIndex].setAvailable(false);
    servers[serverIndex].increaseWorkload(customer.processing_time());
    return true;
  }

  void updateServers(){
    for(int i = 0; i < _size; i++){
      if(!servers[i].isAvailable()){
        servers[i].decreaseWorkload(1);
        if(servers[i].getWorkload() == 0){
          servers[i].setAvailable(true);
        }
      }
    }
  }
};

vector<Customer> fifoQueue(const vector<Customer>& customers, ServerPool& serverPool){
  vector<Customer> customer = customers;
  int time = 0;
  int queue = 0;

  while(queue < customer.size()){
    if(time >= customer[queue].arrival_time()){
      //customer in queue
      if(serverPool.serveCustomer(customer[queue])){
        //customer is served
        customer[queue].set_service_time(time);
        queue++;
      }
    }
    serverPool.updateServers();
    time++;
  }
  return customer;
}

vector<Customer> priorityQueue(const vector<Customer>& customers, ServerPool& serverPool){
  
  Customer dequeued;
  Heap<Customer> priorityQueue;
  vector<Customer> customer;

  int time = 0;
  int size = 0;
  int queue = 0;

  while(size != customers.size()){
    if(queue != customers.size() && time == customers[queue].arrival_time()){
      //customer in queue
      customers[queue].set_compare_by_processing_time(true);
      priorityQueue.insert(customers[queue]);
      queue++;
    }
    while(!priorityQueue.empty() && serverPool.getAvailableServerIndex() != -1){
      //queue not empty and server is idle
      dequeued = priorityQueue.extractMax();
      customer.push_back(dequeued);
      if(serverPool.serveCustomer(dequeued)){
        //customer is served
        customer[size].set_service_time(time);
        size++;
      }
    }
    serverPool.updateServers();
    time++;
  }

  return customer;
}

vector<Customer> QueueSimulator::simulateQueue(const vector<Customer>& customers) {

  ServerPool serverPool(_num_servers);
  vector<Customer> customer;

  if(!_priority_order){
    customer = fifoQueue(customers, serverPool);
  } else{
    customer = priorityQueue(customers, serverPool);
  }

  return customer;
}