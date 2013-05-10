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

#include <QxPrecompiled.h>

#include <QxDao/IxPersistable.h>
#include <QxDao/QxSqlError.h>

#include <QxFactory/QxFactoryX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxPersistable::IxPersistable() { ; }

IxPersistable::~IxPersistable() { ; }

qx::IxCollection_ptr IxPersistable::qxFetchAll(const QString & className, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   qx::IxPersistable_ptr ptr = qx::IxPersistable_ptr(static_cast<qx::IxPersistable *>(qx::create_void_ptr(className)));
   if (! ptr) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchAll() : 'invalid classname, unable to create a new instance'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = ptr->qxNewPersistableCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchAll() : 'unable to create a new persistable collection'", "", QSqlError::UnknownError)); }
   QSqlError daoError = ptr->qxFetchAll((* lst), columns, relation, pDatabase);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

qx::IxCollection_ptr IxPersistable::qxFetchByQuery(const QString & className, const qx::QxSqlQuery & query, const QStringList & columns /* = QStringList() */, const QStringList & relation /* = QStringList() */, QSqlDatabase * pDatabase /* = NULL */)
{
   qx::IxPersistable_ptr ptr = qx::IxPersistable_ptr(static_cast<qx::IxPersistable *>(qx::create_void_ptr(className)));
   if (! ptr) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchByQuery() : 'invalid classname, unable to create a new instance'", "", QSqlError::UnknownError)); }
   qx::IxCollection_ptr lst = ptr->qxNewPersistableCollection();
   if (! lst) { throw qx::dao::sql_error(QSqlError("[QxOrm] qx::IxPersistable::qxFetchByQuery() : 'unable to create a new persistable collection'", "", QSqlError::UnknownError)); }
   QSqlError daoError = ptr->qxFetchByQuery(query, (* lst), columns, relation, pDatabase);
   if (daoError.isValid()) { throw qx::dao::sql_error(daoError); }
   return lst;
}

} // namespace qx
