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
struct QxDao_Insert_Generic
{

    static QSqlError insert(T & t, QSqlDatabase * pDatabase, const QString& table_name = QString(), bool on_dublicate_key_update=false )
    {
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "insert", table_name);
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.validateInstance(t)) { return dao.error(); }

      QString sql = dao.builder().insert(on_dublicate_key_update).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! pDatabase) { dao.transaction(); }
      dao.query().prepare(sql);

      //qDebug() << "prepared_ret: "<< ret <<" error: " << dao.query().lastError();

      IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
      if (pSqlGenerator) { pSqlGenerator->onBeforeInsert((& dao), (& t)); }
      qx::dao::on_before_insert<T>((& t), (& dao));
      qx::dao::detail::QxSqlQueryHelper_Insert<T>::resolveInput(t, dao.query(), dao.builder());
      if (! dao.query().exec()) { return dao.errFailed(); }
      dao.updateLastInsertId(t);
      qx::dao::on_after_insert<T>((& t), (& dao));
      if (pSqlGenerator) { pSqlGenerator->onAfterInsert((& dao), (& t)); }

      return dao.error();
   }

};

template <class T>
struct QxDao_Insert_Container
{

   static QSqlError insert(T & t, QSqlDatabase * pDatabase, const QString& table_name = QString(), bool on_dublicate_key_update=false)
   {
      if (qx::trait::generic_container<T>::size(t) <= 0) { return QSqlError(); }
      qx::dao::detail::QxDao_Helper_Container<T> dao(t, pDatabase, "insert", table_name);
      if (! dao.isValid()) { return dao.error(); }
      if (! dao.validateInstance(t)) { return dao.error(); }

      QString sql = dao.builder().insert(on_dublicate_key_update).getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! pDatabase) { dao.transaction(); }
      dao.query().prepare(sql);

      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { if (! insertItem((* it), dao)) { return dao.error(); } }

      return dao.error();
   }

private:

   template <typename U>
   static inline bool insertItem(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
   {
      bool bInsertOk = insertItem_Helper<U, boost::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::insert(item, dao);
      if (bInsertOk) { qx::dao::detail::QxDao_Keep_Original<U>::backup(item); }
      return bInsertOk;
   }

   template <typename U, bool bIsPointer /* = true */>
   struct insertItem_Helper
   {
      static inline bool insert(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return (item ? qx::dao::detail::QxDao_Insert_Container<T>::insertItem((* item), dao) : true); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool insert(std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool insert(const std::pair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool insert(QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool insert(const QPair<U1, U2> & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      { return qx::dao::detail::QxDao_Insert_Container<T>::insertItem(item.second, dao); }
   };

   template <typename U>
   struct insertItem_Helper<U, false>
   {
      static bool insert(U & item, qx::dao::detail::QxDao_Helper_Container<T> & dao)
      {
         IxSqlGenerator * pSqlGenerator = dao.getSqlGenerator();
         if (pSqlGenerator) { pSqlGenerator->onBeforeInsert((& dao), (& item)); }
         qx::dao::on_before_insert<U>((& item), (& dao));
         qx::dao::detail::QxSqlQueryHelper_Insert<U>::resolveInput(item, dao.query(), dao.builder());
         if (! dao.query().exec()) { dao.errFailed(); return false; }
         dao.updateLastInsertId(item);
         qx::dao::on_after_insert<U>((& item), (& dao));
         if (pSqlGenerator) { pSqlGenerator->onAfterInsert((& dao), (& item)); }

         return dao.isValid();
      }
   };

};

template <class T>
struct QxDao_Insert_Ptr
{

   static inline QSqlError insert(T & t, QSqlDatabase * pDatabase, const QString& table_name = QString(), bool on_dublicate_key_update = false)
   { return (t ? qx::dao::insert((* t), pDatabase, table_name, on_dublicate_key_update) : QSqlError()); }

};

template <class T>
struct QxDao_Insert
{

   static inline QSqlError insert(T & t, QSqlDatabase * pDatabase, const QString& table_name = QString(), bool on_dublicate_key_update=false)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_Insert_Ptr<T>, qx::dao::detail::QxDao_Insert_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_Insert_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_Insert_Container<T>, type_dao_2 >::type type_dao_3;

      QSqlError error = type_dao_3::insert(t, pDatabase, table_name, on_dublicate_key_update);
      if (! error.isValid()) { qx::dao::detail::QxDao_Keep_Original<T>::backup(t); }
      return error;
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
