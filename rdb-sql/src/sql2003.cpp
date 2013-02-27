//  Copyright Jean-Louis Leroy 2009.
// Use, modification, and distribution are subject to the Boost Software License, Version 1.0.

#include <boost/rdb/sql.hpp>
#include <boost/rdb/sql/functions.hpp>

namespace boost { namespace rdb { namespace sql {

  void quote_text(std::ostream& os, const char* str) {
    os << "'";
    while (*str) {
      if (*str == '\'')
        os << *str;
      os << *str++;
    }
    os << "'";
  }

  select_statement_type select = ct::map0();

} } }
