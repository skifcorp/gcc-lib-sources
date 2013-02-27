#include <boost/rdb/mysql_database.hpp>


#include <boost/rdb/odbc/datetime.hpp>
#include <boost/rdb/odbc/date.hpp>
#include <boost/rdb/odbc/time.hpp>


#include <cstdio>
#include <vector>
#include <ostream>

#include <boost/format.hpp>


using namespace std;

namespace odbc = boost::rdb::odbc;


namespace boost { namespace rdb {

//const char* dynamic_value_mismatch::what() const throw() {
  //return "dynamic_value_mismatch";
//}

} }

namespace boost { namespace rdb { namespace mysql {

/*odbc_error::odbc_error(SQLSMALLINT handle_type, SQLHANDLE handle, long rc) : rc(rc) {
  sprintf(msg, "rc %ld", rc);
  SQLSMALLINT mlen;
  SQLGetDiagField(handle_type, handle, 1, SQL_DIAG_MESSAGE_TEXT, (SQLPOINTER) msg, sizeof msg, &mlen);
}*/

mysql_database::~mysql_database() {
  close();
}

void mysql_database::open(const std::string& h, const std::string& u, const std::string& p)
{
    host_     = h;
    //database_ = db;
    user_     = u;
    password_ = p;

    auto drv = ::sql::mysql::get_mysql_driver_instance();

    ::sql::ConnectOptionsMap opts {
        {"hostName", h},
        {"userName", u},
        {"password", p},
        {"CLIENT_MULTI_STATEMENTS", true},
        {"OPT_RECONNECT", true}
    } ;

    if ( !database_.empty() )
        opts["schema"] = database_;

    connection_.reset( drv->connect( opts ) );
    //also can set cjharacter sets here
}

void mysql_database::setDatabase(const string &db)
{
    database_ = db;
    if( !isClosed() )
        connection_->setSchema( db );
}

void mysql_database::open()
{
    //auto drv = ::sql::mysql::get_mysql_driver_instance();
    //connection_.reset( drv->connect( host_, user_, password_ ) );
    //connection_->setSchema(database_);

    open( host_, user_, password_ );
}

void mysql_database::close()
{
    connection_.reset(nullptr);
}

void mysql_database::exec_str(statement_typ & stmt, const string& sql) {
  if (trace_stream)
    *trace_stream << sql << "\n";

  stmt.reset( connection_->createStatement() );
  stmt->execute(sql);
}

void mysql_database::prepare_str(statement_typ&  ,const string& sql) {
  if (trace_stream)
    *trace_stream << sql << "\n";

  //stmt.reset ( connection_->prepareStatement(sql) );
  // auto prepared_statement_ = static_cast<PreparedStatement *>( statement_ );
  // need to set data here
  // prepared_statement_->execute();
}

/*const char* odbc_error::what() const throw() {
  return msg;
}*/

void results_binder::operator ()(
            const fusion::vector<const dynamic::dynamic_expressions&,
                    dynamic_values&>& zip) const {
  using fusion::at_c;

  if (at_c<0>(zip).size() != at_c<1>(zip).size())
    throw dynamic_value_mismatch();

  dynamic::dynamic_expressions::const_iterator expression_iter = at_c<0>(zip).begin(), expression_last = at_c<0>(zip).end();
  dynamic_values::iterator value_iter = at_c<1>(zip).begin();

  while (expression_iter != expression_last) {

    if (expression_iter->type() != (*value_iter)->type())
      throw dynamic_value_mismatch();

    if (expression_iter->length() != (*value_iter)->length())
      throw dynamic_value_mismatch();

    //(*value_iter)->bind_result(result_, i_);

    ++expression_iter;
    ++value_iter;
    ++i_;
  }
}

void parameter_binder::operator ()(const fusion::vector<const dynamic::dynamic_placeholders&, dynamic_values&>& zip) const {

  const dynamic::dynamic_placeholders& placeholders = fusion::at_c<0>(zip);
  const dynamic_values& values = fusion::at_c<1>(zip);

  if (placeholders.size() != values.size())
    throw dynamic_value_mismatch();

  dynamic::dynamic_placeholders::const_iterator placeholder_iter = placeholders.begin(), placeholder_last = placeholders.end();
  dynamic_values::const_iterator value_iter = values.begin();

  while (placeholder_iter != placeholder_last) {

    if (placeholder_iter->type() != (*value_iter)->type())
      throw dynamic_value_mismatch();

    if (placeholder_iter->length() != (*value_iter)->length())
      throw dynamic_value_mismatch();

    (*value_iter)->bind_parameter(stmt_, i_);

    ++placeholder_iter;
    ++value_iter;
    ++i_;
  }
}

std::ostream* trace_stream;
/*
std::ostream& operator <<(std::ostream& os, const odbc::datetime& val) {
  const SQL_TIMESTAMP_STRUCT& t = val.value();
  os << boost::str(boost::format("'%04d-%02d-%02d %02d:%02d:%02d'")
    % t.year % t.month % t.day % t.hour % t.minute % t.second);
  if (t.fraction)
    os << ' ' << t.fraction;
  return os;
}
*/
/*
std::ostream& operator <<(std::ostream& os, const date& val) {
  const SQL_DATE_STRUCT& t = val.value();
  return os << boost::str(boost::format("'%04d-%02d-%02d'") % t.year % t.month % t.day);
}
*/
/*
std::ostream& operator <<(std::ostream& os, const time& val) {
  const SQL_TIME_STRUCT& t = val.value();
  return os << boost::str(boost::format("'%02d:%02d:%02d'") % t.hour % t.minute % t.second);
}
*/
} } }

namespace boost { namespace rdb { namespace core {

/*void literal<odbc::datetime, datetime>::str(std::ostream& os) const {
  os << value_;
}

void literal<odbc::date, date>::str(std::ostream& os) const {
  os << value_;
}

void literal<odbc::time, time>::str(std::ostream& os) const {
  os << value_;
}*/

} } }
