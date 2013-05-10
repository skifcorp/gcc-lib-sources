/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_SOFT_DELETE_H_
#define _QX_SOFT_DELETE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSoftDelete.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Soft delete (or logical delete) behavior to update a row into database (flag it as deleted) instead of delete it from database
 */

#define QX_DAO_SOFT_DELETE_QDATETIME_FORMAT "yyyyMMddhhmmsszzz"

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSoftDelete : soft delete (or logical delete) behavior to update a row into database (flag it as deleted) instead of delete it from database
 *
 * A soft delete doesn't remove rows from database (this is not a physical delete) : a new column is added to the table definition to flag a row as deleted or not.
 * This column can contain a boolean (1 means row deleted, 0 or NULL means row not deleted), or can contain deletion date-time (if empty or NULL, row is not deleted).
 * So you can reactivate a deleted row by setting NULL or empty value into database.
 *
 * To define a soft delete behavior with QxOrm library, you have to use the class qx::QxSoftDelete in function mapping by class qx::register_class<T>.
 * Here is an example with the class <i>Bar</i> containing 2 properties <i>m_id</i> and <i>m_desc</i> :
 * \code
namespace qx {
template <> void register_class(QxClass<Bar> & t)
{
   t.setSoftDelete(qx::QxSoftDelete("deleted_at"));

   t.id(& Bar::m_id, "id");
   t.data(& Bar::m_desc, "desc");
}}
 * \endcode
 *
 * SQL queries builded by QxOrm library will take into account this soft delete parameter to add conditions (don't fetch deleted item, don't delete physically a row, etc.).
 * For example, if you execute this code with the class <i>Bar</i> :
 * \code
Bar_ptr pBar; pBar.reset(new Bar());
pBar->setId(5);
QSqlError daoError = qx::dao::delete_by_id(pBar);     qAssert(! daoError.isValid());
qx_bool bDaoExist = qx::dao::exist(pBar);             qAssert(! bDaoExist);
daoError = qx::dao::delete_all<Bar>();                qAssert(! daoError.isValid());
long lBarCount = qx::dao::count<Bar>();               qAssert(lBarCount == 0);
daoError = qx::dao::destroy_all<Bar>();               qAssert(! daoError.isValid());
 * \endcode
 *
 * You will obtain following output trace :
 * \code
[QxOrm] sql query (93 ms) : UPDATE Bar SET deleted_at = '20110617115148615' WHERE id = :id
[QxOrm] sql query (0 ms) : SELECT Bar.id AS Bar_id_0, Bar.deleted_at FROM Bar WHERE Bar.id = :id AND (Bar.deleted_at IS NULL OR Bar.deleted_at = '')
[QxOrm] sql query (78 ms) : UPDATE Bar SET deleted_at = '20110617115148724'
[QxOrm] sql query (0 ms) : SELECT COUNT(*) FROM Bar WHERE (Bar.deleted_at IS NULL OR Bar.deleted_at = '')
[QxOrm] sql query (110 ms) : DELETE FROM Bar
 * \endcode
 *
 * <i>Note :</i> To delete physically a row from database, you have to use followings functions : qx::dao::destroy_by_id() and qx::dao::destroy_all().
 *
 * <i>Other note :</i> it is recommended to define into database an index on column <i>deleted_at</i> to optimize execution of SQL queries.
 */
class QxSoftDelete
{

public:

   enum mode { mode_flag, mode_date_time };

private:

   QString m_sTable;                      //!< Table name where soft delete behavior is applied
   QString m_sColumn;                     //!< Column name to store soft delete information
   QString m_sSqlQueryToFetch;            //!< Overrided user SQL query to fetch an item, if empty QxOrm library builds a default SQL query
   QString m_sSqlQueryToUpdate;           //!< Overrided user SQL query to update an item, if empty QxOrm library builds a default SQL query
   QString m_sSqlQueryToCreateTable;      //!< Overrided user SQL query to create table, if empty QxOrm library builds a default SQL query
   mode m_eMode;                          //!< Soft delete mode : 'mode_flag' with a boolean column, 'mode_date_time' with a date-time column containing deletion date-time

public:

   QxSoftDelete() : m_eMode(mode_date_time) { ; }
   QxSoftDelete(const QString & sColumn) : m_sColumn(sColumn), m_eMode(mode_date_time) { ; }
   QxSoftDelete(const QString & sColumn, mode eMode) : m_sColumn(sColumn), m_eMode(eMode) { ; }
   ~QxSoftDelete() { ; }

   QString getTableName() const              { return m_sTable; }
   QString getColumnName() const             { return m_sColumn; }
   QString getSqlQueryToFetch() const        { return m_sSqlQueryToFetch; }
   QString getSqlQueryToUpdate() const       { return m_sSqlQueryToUpdate; }
   QString getSqlQueryToCreateTable() const  { return m_sSqlQueryToCreateTable; }
   mode getMode() const                      { return m_eMode; }

   void setTableName(const QString & sTable)          { m_sTable = sTable; }
   void setColumnName(const QString & sColumn)        { m_sColumn = sColumn; }
   void setSqlQueryToFetch(const QString & s)         { m_sSqlQueryToFetch = s; }
   void setSqlQueryToUpdate(const QString & s)        { m_sSqlQueryToUpdate = s; }
   void setSqlQueryToCreateTable(const QString & s)   { m_sSqlQueryToCreateTable = s; }
   void setMode(mode eMode)                           { m_eMode = eMode; }

   bool isEmpty() const { return (m_sTable.isEmpty() || m_sColumn.isEmpty()); }

   QString buildSqlTablePointName(const QString & sTable = QString()) const
   {
      if (this->isEmpty()) { return ""; }
      return ((sTable.isEmpty() ? m_sTable : sTable) + "." + m_sColumn);
   }

   QString buildSqlQueryToFetch(const QString & sTable = QString()) const
   {
      QString sCurrTable = (sTable.isEmpty() ? m_sTable : sTable);
      if (this->isEmpty()) { return ""; }
      else if (! m_sSqlQueryToFetch.isEmpty()) { return m_sSqlQueryToFetch; }
      else if (m_eMode == mode_flag) { return ("(" + sCurrTable + "." + m_sColumn + " IS NULL" + " OR " + sCurrTable + "." + m_sColumn + " = ''" + " OR " + sCurrTable + "." + m_sColumn + " = '0'" + ")"); }
      else if (m_eMode == mode_date_time) { return ("(" + sCurrTable + "." + m_sColumn + " IS NULL" + " OR " + sCurrTable + "." + m_sColumn + " = ''" + ")"); }
      qAssert(false); return "";
   }

   QString buildSqlQueryToUpdate() const
   {
      if (this->isEmpty()) { return ""; }
      else if (! m_sSqlQueryToUpdate.isEmpty()) { return m_sSqlQueryToUpdate; }
      else if (m_eMode == mode_flag) { return (m_sColumn + " = '1'"); }
      else if (m_eMode == mode_date_time) { return (m_sColumn + " = '" + QDateTime::currentDateTime().toString(QX_DAO_SOFT_DELETE_QDATETIME_FORMAT) + "'"); }
      qAssert(false); return "";
   }

   QString buildSqlQueryToCreateTable() const
   {
      if (this->isEmpty()) { return ""; }
      else if (! m_sSqlQueryToCreateTable.isEmpty()) { return m_sSqlQueryToCreateTable; }
      else if (m_eMode == mode_flag) { return (m_sColumn + " " + "TEXT"); }
      else if (m_eMode == mode_date_time) { return (m_sColumn + " " + "TEXT"); }
      qAssert(false); return "";
   }

};

} // namespace qx

#endif // _QX_SOFT_DELETE_H_
