#include <cxxtest/TestSuite.h>

#include "count_if_followed_by.h"


class MyTestSuite : public CxxTest::TestSuite {
  public:
    void test1 () {
      char const  data[6] = {'G','G','X','G','X','G'};
      int  const test_len = 4;

      int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

      // SYNOPSIS:
      //   result should be 1 since the length specified is 4,
      //   and only one pair of [X, G] is present in that range!

      TS_ASSERT_EQUALS(result, 1);
    }

    void test_that_it_does_not_look_outside_the_specified_range() {
      char const data[6] = {'G','G','X','G','X','G'};
      int  const result = count_if_followed_by (data, 4, 'G', 'X');
      TS_ASSERT_EQUALS(result, 1);
    }

    void test_that_it_does_not_crash_when_prefix_is_at_the_end() {
      char const data[6] = {'G','G','X','G','X','G'};
      int  const result = count_if_followed_by (data, 6, 'G', 'X');
      TS_ASSERT_EQUALS(result, 2);
    }

    void test_that_it_does_not_count_suffix_when_not_preceded_by_prefix() {
      char const data[6] = {'G','A','X','G','X','G'};
      int  const result = count_if_followed_by (data, 6, 'G', 'X');
      TS_ASSERT_EQUALS(result, 1);
    }
};
