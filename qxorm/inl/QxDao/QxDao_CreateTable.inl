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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_CreateTable
{

   static QSqlError createTable(QSqlDatabase * pDatabase, const QString& table_name = QString())
   {
      T t; Q_UNUSED(t);

      //qDebug () << "creating table: " << table_name;

      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "create table", table_name);
      if (! dao.isValid()) { return dao.error(); }

      QString sql = dao.builder().createTable().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().exec(sql)) { return dao.errFailed(); }

      long index = 0; qx::IxSqlRelation * pRelation = NULL;
      while ((pRelation = dao.builder().nextRelation(index)))
      {
         QString sqlExtraTable = pRelation->createExtraTable();
         if (sqlExtraTable.isEmpty()) { continue; }
         QSqlQuery queryCreateTable(dao.database());
         bool bExtraTable = queryCreateTable.exec(sqlExtraTable);
         if (! bExtraTable) { dao.updateError(queryCreateTable.lastError()); break; }
      }

      return dao.error();
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
