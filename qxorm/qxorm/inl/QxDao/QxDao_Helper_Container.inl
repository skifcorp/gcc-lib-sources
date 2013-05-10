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

#define QX_DAO_HELPER_CONTAINER(className) \
namespace qx { namespace dao { namespace detail { \
template <class T> \
class QxDao_Helper_Container< className<T> > : public IxDao_Helper \
{ \
public: \
    QxDao_Helper_Container(className<T> & t, QSqlDatabase * pDatabase, const QString & sContext, const QString& tn = QString()) : IxDao_Helper(), table_name(tn) { Q_UNUSED(t); init(pDatabase, sContext); } \
   virtual ~QxDao_Helper_Container() { BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value); } \
protected: \
    virtual void updateQueryBuilder() { m_pQueryBuilder.reset(new qx::QxSqlQueryBuilder<T>());if (!table_name.isEmpty()){m_pQueryBuilder->setTableName(table_name);} } \
private: \
    QString table_name;\
}; }}} // namespace qx::dao::detail

#define QX_DAO_HELPER_CONTAINER_KEY_VALUE(className) \
namespace qx { namespace dao { namespace detail { \
template <class Key, class Value> \
class QxDao_Helper_Container< className<Key, Value> > : public IxDao_Helper \
{ \
public: \
    QxDao_Helper_Container(className<Key, Value> & t, QSqlDatabase * pDatabase, const QString & sContext, const QString& tn=QString()) : IxDao_Helper(), table_name(tn) { Q_UNUSED(t); init(pDatabase, sContext); } \
   virtual ~QxDao_Helper_Container() { BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<Value>::type_sql>::value); } \
protected: \
   virtual void updateQueryBuilder() { m_pQueryBuilder.reset(new qx::QxSqlQueryBuilder<Value>()); if (!table_name.isEmpty()){m_pQueryBuilder->setTableName(table_name);}} \
private: \
        QString table_name;\
}; }}} // namespace qx::dao::detail

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_Helper_Container { ; };

} // namespace detail
} // namespace dao
} // namespace qx

QX_DAO_HELPER_CONTAINER(std::vector)
QX_DAO_HELPER_CONTAINER(std::list)
QX_DAO_HELPER_CONTAINER(std::set)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(std::map)

QX_DAO_HELPER_CONTAINER(boost::unordered_set)
QX_DAO_HELPER_CONTAINER(boost::unordered_multiset)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(boost::unordered_map)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(boost::unordered_multimap)

QX_DAO_HELPER_CONTAINER(QVector)
QX_DAO_HELPER_CONTAINER(QList)
QX_DAO_HELPER_CONTAINER(QLinkedList)
QX_DAO_HELPER_CONTAINER(QSet)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMap)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMultiMap)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QHash)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMultiHash)

QX_DAO_HELPER_CONTAINER_KEY_VALUE(qx::QxCollection)
