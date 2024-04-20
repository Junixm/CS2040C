#include "queue_simulator.h"
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

TEST(QueueSimulator, test_public_trivial_queue) {
  RecordProperty("expression", "Check that a single customer gets served.");
  vector<Customer> customers = {Customer(0, 1)};
  QueueSimulator sim;
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result[0].service_time(), 0);
}

TEST(QueueSimulator, test_public_simple_queue) {
  vector<Customer> customers = {Customer(0, 2), Customer(1, 5), Customer(3, 2)};
  QueueSimulator sim;
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0].service_time(), 0);
  EXPECT_EQ(result[1].service_time(), 2);
  EXPECT_EQ(result[2].service_time(), 7);

}

const vector<Customer> SAMPLE_CUSTOMERS{
    Customer(1, 5), Customer(2, 7), Customer(3, 2),
    Customer(4, 3), Customer(8, 1),
};

TEST(QueueSimulator, test_public_longer_queue) {
  vector<Customer> customers = SAMPLE_CUSTOMERS;
  QueueSimulator sim;
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0].service_time(), 1);
  EXPECT_EQ(result[1].service_time(), 6);
  EXPECT_EQ(result[2].service_time(), 13);
  EXPECT_EQ(result[3].service_time(), 15);
  EXPECT_EQ(result[4].service_time(), 18);
}

//(1/5 2/7 3/2 4/3 8/1) served: c1(t1), c3(t6), c5(t8), c4(t9), c2(t12)
TEST(QueueSimulator, test_public_priority_queue) {
  vector<Customer> customers = SAMPLE_CUSTOMERS;
  QueueSimulator sim;
  sim.set_priority_order(true);
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0].arrival_time(), 1);
  EXPECT_EQ(result[0].service_time(), 1);
  EXPECT_EQ(result[1].arrival_time(), 3);
  EXPECT_EQ(result[1].service_time(), 6);
  EXPECT_EQ(result[2].arrival_time(), 8);
  EXPECT_EQ(result[2].service_time(), 8);
  EXPECT_EQ(result[3].arrival_time(), 4);
  EXPECT_EQ(result[3].service_time(), 9);
  EXPECT_EQ(result[4].arrival_time(), 2);
  EXPECT_EQ(result[4].service_time(), 12);
}

TEST(QueueSimulator, test_public_multiple_servers) {
  vector<Customer> customers = SAMPLE_CUSTOMERS;
  QueueSimulator sim;
  sim.set_num_servers(2);
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 5);
  EXPECT_EQ(result[0].service_time(), 1);
  EXPECT_EQ(result[1].service_time(), 2);
  EXPECT_EQ(result[2].service_time(), 6);
  EXPECT_EQ(result[3].service_time(), 8);
  EXPECT_EQ(result[4].service_time(), 9);
}

TEST(QueueSimulator, test_public_multiple_servers_priority_queue) {
  vector<Customer> customers{
      Customer(1, 5), Customer(2, 7), Customer(3, 5),
      Customer(4, 2), Customer(5, 1), Customer(8, 1),
  };
  QueueSimulator sim;
  sim.set_num_servers(2);
  sim.set_priority_order(true);
  auto result = sim.simulateQueue(customers);
  ASSERT_EQ(result.size(), 6);
  EXPECT_EQ(result[0].arrival_time(), 1);
  EXPECT_EQ(result[0].service_time(), 1);
  EXPECT_EQ(result[1].arrival_time(), 2);
  EXPECT_EQ(result[1].service_time(), 2);
  EXPECT_EQ(result[2].arrival_time(), 5);
  EXPECT_EQ(result[2].service_time(), 6);
  EXPECT_EQ(result[3].arrival_time(), 4);
  EXPECT_EQ(result[3].service_time(), 7);
  EXPECT_EQ(result[4].arrival_time(), 8);
  EXPECT_EQ(result[4].service_time(), 9);
  EXPECT_EQ(result[5].arrival_time(), 3);
  EXPECT_EQ(result[5].service_time(), 9);
}

TEST(QueueSimulator, test_all) {
  vector<Customer> customers{
      Customer(1, 5), Customer(2, 7), Customer(3, 5),
      Customer(4, 2), Customer(5, 1), Customer(8, 1),
  };
  QueueSimulator sim;
  sim.set_num_servers(1);
  sim.set_priority_order(false);
  auto result = sim.simulateQueue(customers);
}

TEST(QueueSimulator, test_all1) {
  vector<Customer> customers{
      Customer(1, 5), Customer(2, 7), Customer(3, 5),
      Customer(4, 2), Customer(5, 1), Customer(8, 1),
  };
  QueueSimulator sim;
  sim.set_num_servers(2);
  sim.set_priority_order(false);
  auto result = sim.simulateQueue(customers);
}

TEST(QueueSimulator, test_all11) {
  vector<Customer> customers{
      Customer(1, 5), Customer(2, 7), Customer(3, 5),
      Customer(4, 2), Customer(5, 1), Customer(8, 1),
  };
  QueueSimulator sim;
  sim.set_num_servers(1);
  sim.set_priority_order(true);
  auto result = sim.simulateQueue(customers);
}

TEST(QueueSimulator, test_all111) {
  vector<Customer> customers{
      Customer(1, 5), Customer(2, 7), Customer(3, 5),
      Customer(4, 2), Customer(5, 1), Customer(8, 1),
  };
  QueueSimulator sim;
  sim.set_num_servers(2);
  sim.set_priority_order(true);
  auto result = sim.simulateQueue(customers);
}