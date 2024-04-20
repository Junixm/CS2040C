#include "customer.h"

bool Customer::_compare_by_processing_time = false;

bool Customer::operator>(const Customer& c) const {
  return _compare_by_processing_time ? _processing_time < c._processing_time
                                     : _arrival_time < c._arrival_time;
};
