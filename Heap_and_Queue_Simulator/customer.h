
#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

class Customer {
 private:
  // Time of arrival after the shop opened in min.
  int _arrival_time;
  // Amount of time needed to service customer in min.
  int _processing_time;
  // Time the customer is served by the shop in min after opening.
  int _service_time;

  static bool _compare_by_processing_time;

 public:
  Customer(int arrival_time = 0, int processing_time = 0)
      : _arrival_time(arrival_time),
        _processing_time(processing_time),
        _service_time(-1){};

  int arrival_time() const { return _arrival_time; };
  int processing_time() const { return _processing_time; };
  int waiting_time() const { return _service_time - _arrival_time; };
  int service_time() const { return _service_time; };
  void set_service_time(int service_time) { _service_time = service_time; };

  // When set to true, comparison is based on processing time.
  // When set to false, comparison is based on arrival time.
  static void set_compare_by_processing_time(bool v) {
    _compare_by_processing_time = v;
  }

  // Comparison depends on _compare_by_processing_time
  bool operator>(const Customer& c) const;
};

#endif /* __CUSTOMER_H__ */
