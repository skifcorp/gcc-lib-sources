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
struct QxSqlQueryHelper_Insert
{

   static void sql(QString & sql, qx::IxSqlQueryBuilder & builder, bool on_dublicate_key_update = false)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, (& sql), (& builder), NULL, NULL);
      QString table = builder.table();
      sql = "INSERT INTO " + table + " (";
      if (pId && ! pId->getAutoIncrement()) { sql += pId->getSqlName(", ") + ", "; }
      while ((p = builder.nextData(l1))) { sql += p->getSqlName(", ") + ", "; }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += ") VALUES (";
      l1 = 0; l2 = 0; p = NULL; pRelation = NULL;
      if (pId && ! pId->getAutoIncrement()) { sql += pId->getSqlPlaceHolder("", -1, ", ") + ", "; }
      while ((p = builder.nextData(l1))) { sql += p->getSqlPlaceHolder("", -1, ", ") + ", "; }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert_Values(params); }
      sql = sql.left(sql.count() - 2); // Remove last ", "
      sql += ")";

      if ( on_dublicate_key_update ) {

          sql += " ON DUPLICATE KEY UPDATE ";
          l1 = 0;
          qx::IxDataMember * pId = builder.getDataId();
          if (pId) {
              sql += pId->getSqlName() + " = VALUES(" + pId->getSqlName() +"), ";
          }

          while ( (p = builder.nextData(l1)) ) {
              //if ( !p->getIsPrimaryKey() ) {
                //sql += p->getSqlName() + " = " + p->getSqlPlaceHolder("", -1, "") + ", ";
                  sql += p->getSqlName() + " = VALUES(" + p->getSqlName() +"), " ;
              //}
          }

          sql = sql.left(sql.count() - 2); // Remove last ", "
          //qDebug() << "URRA! GOT DUPLICATE UPDATE! "<<sql;
      }
   }


   static void resolveInput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      long l1(0), l2(0);
      qx::IxDataMember * p = NULL;
      qx::IxDataMember * pId = builder.getDataId();
      qx::IxSqlRelation * pRelation = NULL;
      qx::QxSqlRelationParams params(0, 0, NULL, (& builder), (& query), (& t));
      if (pId && ! pId->getAutoIncrement()) { pId->setSqlPlaceHolder(query, (& t)); }
      while ((p = builder.nextData(l1))) { p->setSqlPlaceHolder(query, (& t)); }
      while ((pRelation = builder.nextRelation(l2))) { params.setIndex(l2); pRelation->lazyInsert_ResolveInput(params); }
   }

   static void resolveOutput(T & t, QSqlQuery & query, qx::IxSqlQueryBuilder & builder)
   { Q_UNUSED(t); Q_UNUSED(query); Q_UNUSED(builder); }

};

} // namespace detail
} // namespace dao
} // namespace qx
