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

#include <QxRegister/QxClassX.h>

#include <QxFactory/QxFactoryX.h>

#include <QxCommon/QxStringCvt.h>
#include <QxCommon/QxStringCvt_Impl.h>

#include <QxDao/QxDao.h>
#include <QxDao/QxDao_Impl.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxClassX)

namespace qx {

QxClassX::QxClassX() : QxSingleton<QxClassX>("qx::QxClassX")
{
   initSqlTypeByClassName();
   initValidatorMessage();
}

QxClassX::~QxClassX() { ; }

QxCollection<QString, IxClass *> * QxClassX::getAll()
{
   return (& m_lstClass);
}

IxClass * QxClassX::get(const QString & sKey) const
{
   IxClass * pClass = (m_lstClass.exist(sKey) ? m_lstClass.getByKey(sKey) : NULL);
   if (! pClass) { qx::create(sKey); }
   if (! pClass) { pClass = (m_lstClass.exist(sKey) ? m_lstClass.getByKey(sKey) : NULL); }

   return pClass;
}

bool QxClassX::exist(const QString & sKey) const
{
   return m_lstClass.exist(sKey);
}

bool QxClassX::insert(const QString & sKey, IxClass * pClass)
{
   return ((! pClass || sKey.isEmpty() || m_lstClass.exist(sKey)) ? false : m_lstClass.insert(sKey, pClass));
}

bool QxClassX::remove(const QString & sKey)
{
   return m_lstClass.removeByKey(sKey);
}

void QxClassX::clear()
{
   m_lstClass.clear();
}

boost::any QxClassX::create(const QString & sKey)
{
   return qx::create(sKey);
}

IxClass * QxClassX::getClass(const QString & sKey)
{
   return QxClassX::getSingleton()->get(sKey);
}

IxDataMemberX * QxClassX::getDataMemberX(const QString & sKey)
{
   IxClass * pClass = QxClassX::getClass(sKey);
   return (pClass ? pClass->getDataMemberX() : NULL);
}

IxFunctionX * QxClassX::getFctMemberX(const QString & sKey)
{
   IxClass * pClass = QxClassX::getClass(sKey);
   return (pClass ? pClass->getFctMemberX() : NULL);
}

IxDataMember * QxClassX::getDataMember(const QString & sClassKey, const QString & sDataKey, bool bRecursive /* = true */)
{
   QString sBaseClassKey = sClassKey;
   IxClass * pClass(NULL); IxDataMemberX * pDataX(NULL); IxDataMember * pData(NULL);

   do {
      pClass = QxClassX::getClass(sBaseClassKey);
      pDataX = QxClassX::getDataMemberX(sBaseClassKey);
      pData = ((pDataX && pDataX->exist(sDataKey)) ? pDataX->get(sDataKey) : NULL);
      sBaseClassKey = ((pClass && pClass->getBaseClass()) ? pClass->getBaseClass()->getKey() : QString(""));
   } while (bRecursive && ! pData && pClass && ! sBaseClassKey.isEmpty() && ! pClass->isFinalClass());

   return pData;
}

IxFunction * QxClassX::getFctMember(const QString & sClassKey, const QString & sFctKey, bool bRecursive /* = true */)
{
   QString sBaseClassKey = sClassKey;
   IxClass * pClass(NULL); IxFunctionX * pFctX(NULL); IxFunction * pFct(NULL);

   do {
      pClass = QxClassX::getClass(sBaseClassKey);
      pFctX = QxClassX::getFctMemberX(sBaseClassKey);
      pFct = ((pFctX && pFctX->exist(sFctKey)) ? pFctX->getByKey(sFctKey).get() : NULL);
      sBaseClassKey = ((pClass && pClass->getBaseClass()) ? pClass->getBaseClass()->getKey() : QString(""));
   } while (bRecursive && ! pFct && pClass && ! sBaseClassKey.isEmpty() && ! pClass->isFinalClass());

   return pFct;
}

qx_bool QxClassX::invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const QString & params /* = QString() */, boost::any * ret /* = NULL */)
{
   IxFunction * pFct = QxClassX::getFctMember(sClassKey, sFctKey, true);
   return ((pOwner && pFct) ? pFct->invoke(pOwner, params, ret) : qx_bool(false));
}

qx_bool QxClassX::invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const type_any_params & params, boost::any * ret /* = NULL */)
{
   IxFunction * pFct = QxClassX::getFctMember(sClassKey, sFctKey, true);
   return ((pOwner && pFct) ? pFct->invoke(pOwner, params, ret) : qx_bool(false));
}

const std::type_info & QxClassX::typeInfo(const QString & sKey) const
{
   IxClass * pClass = QxClassX::getClass(sKey);
   return (pClass ? pClass->typeInfo() : typeid(void));
}

QxCollection<QString, IxClass *> * QxClassX::getAllClasses()
{
   QxClassX::registerAllClasses();
   return QxClassX::getSingleton()->getAll();
}

void QxClassX::registerAllClasses()
{
   QHash<QString, IxFactory *> * pAllFactory = QxFactoryX::getSingleton()->getAllFactory();
   if (! pAllFactory) { qAssert(false); return; }

   QHashIterator<QString, IxFactory *> itr(* pAllFactory);
   while (itr.hasNext())
   {
      itr.next();
      IxClass * pClass = QxClassX::getClass(itr.key());
      qAssert(pClass != NULL); Q_UNUSED(pClass);
   }
}

QString QxClassX::dumpAllClasses()
{
   QxClassX::registerAllClasses();
   QxCollection<QString, IxClass *> * pAllClasses = QxClassX::getAllClasses();
   if (! pAllClasses) { qAssert(false); return ""; }

   QString sDump;
   long lCount = pAllClasses->count();
   qDebug("[QxOrm] start dump all registered classes (%ld)", lCount);
   _foreach(IxClass * pClass, (* pAllClasses))
   { if (pClass) { sDump += pClass->dumpClass(); } }
   qDebug("[QxOrm] %s", "end dump all registered classes");

   return sDump;
}

QString QxClassX::dumpSqlSchema()
{
   qDebug("[QxOrm] qx::QxClassX::dumpSqlSchema() : %s", "be careful with this function, it's just an example and tested only with SQLite database, so it's strongly recommended to write your own function to create your SQL schema");
   QxCollection<QString, IxClass *> * pAllClasses = QxClassX::getAllClasses();
   if (! pAllClasses) { qAssert(false); return ""; }
   QString sql; long lSqlCount = 0;

   for (long k = 0; k < pAllClasses->count(); k++)
   {
      IxClass * pClass = pAllClasses->getByIndex(k);
      if (! pClass) { continue; }

      // If the class is a parameter or a service from 'QxService' module, it's not a persistent class
      if (pClass->isKindOf("qx::service::IxParameter") || pClass->isKindOf("qx::service::IxService")) { continue; }

      // ----
      // Here, you can filter other classes using property bag (meta-data), for example :
      //    QString sProp = pClass->getPropertyBag("NOT_A_DATABASE_OBJECT").toString();
      //    if (sProp == "1") { continue; }
      // ----

      // Get the version of the class : if (version = 0) then 'CREATE TABLE', else if (version > 0) then 'ALTER TABLE'
      long lVersion = pClass->getVersion();
      bool bCreateTable = (lVersion <= 0);
      sql += (bCreateTable ? "CREATE TABLE " : "ALTER TABLE ");
      sql += pClass->getName() + " ";
      sql += (bCreateTable ? "(" : "ADD (");
      int iSqlCountRef = sql.count();

      // Get the primary key (id) of table, all columns into table, and other parameters associated to table
      IxDataMember * pId = pClass->getId();
      IxDataMemberX * pDataMemberX = pClass->getDataMemberX();
      QxSoftDelete oSoftDelete = pClass->getSoftDelete();

      // Insert primary key (id) to SQL schema
      if (pId && (bCreateTable || (pId->getVersion() >= lVersion)))
      { sql += pId->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! pId->getSqlType().isEmpty()); }

      // Insert all columns to SQL schema
      for (long l = 0; (pDataMemberX && (l < pDataMemberX->count_WithDaoStrategy())); l++)
      {
         IxDataMember * p = pDataMemberX->get_WithDaoStrategy(l);
         if (isValid_DataMember(p) && (p != pId) && (bCreateTable || (p->getVersion() >= lVersion)))
         { sql += p->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! p->getSqlType().isEmpty()); }

         // ----
         // Here, you can use property bag (meta-data) to add some SQL features, for example :
         //    QString sProp = p->getPropertyBag("INDEX").toString();
         //    if (sProp == "1") { sql += "CREATE INDEX" + etc...; }
         // ----
      }

      // Insert soft delete behaviour to SQL schema
      if (bCreateTable && ! oSoftDelete.isEmpty())
      { sql += oSoftDelete.buildSqlQueryToCreateTable() + ", "; }

      // Insert all relations to SQL schema
      for (long l = 0; (pDataMemberX && (l < pDataMemberX->count_WithDaoStrategy())); l++)
      {
         IxDataMember * p = pDataMemberX->get_WithDaoStrategy(l);
         QxSqlRelationParams params(0, 0, (& sql), NULL, NULL, NULL);
         if (isValid_SqlRelation(p) && (p != pId) && (bCreateTable || (p->getVersion() >= lVersion)))
         { p->getSqlRelation()->createTable(params); }
      }

      // Terminate SQL schema for current class
      bool bAddBracket = (sql.count() != iSqlCountRef);
      sql = sql.left(sql.count() - 2); // Remove last ", "
      if (bAddBracket) { sql += ")\n"; }
      else { sql += "\n"; }
      lSqlCount++;

      // Create extra-table from relations (for example, many-to-many relation needs an extra-table)
      for (long l = 0; (pDataMemberX && (l < pDataMemberX->count_WithDaoStrategy())); l++)
      {
         IxDataMember * p = pDataMemberX->get_WithDaoStrategy(l);
         if (isValid_SqlRelation(p) && (p != pId) && (bCreateTable || (p->getVersion() >= lVersion)))
         {
            QString sqlExtraTable = p->getSqlRelation()->createExtraTable();
            if (sqlExtraTable.isEmpty()) { continue; }
            sql += sqlExtraTable + "\n";
         }
      }
   }

   qDebug("[QxOrm] start dump SQL schema (%ld)", lSqlCount);
   qDebug("%s", qPrintable(sql));
   qDebug("[QxOrm] %s", "end dump SQL schema");

   return sql;
}

bool QxClassX::isValid_DataMember(IxDataMember * p)
{
   return (p && p->getDao() && ! p->hasSqlRelation());
}

bool QxClassX::isValid_SqlRelation(IxDataMember * p)
{
   bool bIsValid = (p && p->getDao() && p->hasSqlRelation());
   if (bIsValid) { p->getSqlRelation()->init(); }
   return bIsValid;
}

void QxClassX::initSqlTypeByClassName()
{
   m_lstSqlTypeByClassName.clear();

   m_lstSqlTypeByClassName.insert("bool", "SMALLINT");
   m_lstSqlTypeByClassName.insert("qx_bool", "SMALLINT");
   m_lstSqlTypeByClassName.insert("short", "SMALLINT");
   m_lstSqlTypeByClassName.insert("int", "INTEGER");
   m_lstSqlTypeByClassName.insert("long", "INTEGER");
   m_lstSqlTypeByClassName.insert("long long", "INTEGER");
   m_lstSqlTypeByClassName.insert("float", "FLOAT");
   m_lstSqlTypeByClassName.insert("double", "FLOAT");
   m_lstSqlTypeByClassName.insert("long double", "FLOAT");
   m_lstSqlTypeByClassName.insert("unsigned short", "SMALLINT");
   m_lstSqlTypeByClassName.insert("unsigned int", "INTEGER");
   m_lstSqlTypeByClassName.insert("unsigned long", "INTEGER");
   m_lstSqlTypeByClassName.insert("unsigned long long", "INTEGER");
   m_lstSqlTypeByClassName.insert("std::string", "TEXT");
   m_lstSqlTypeByClassName.insert("std::wstring", "TEXT");
   m_lstSqlTypeByClassName.insert("QString", "TEXT");
   m_lstSqlTypeByClassName.insert("QVariant", "TEXT");
   m_lstSqlTypeByClassName.insert("QUuid", "TEXT");
   m_lstSqlTypeByClassName.insert("QDate", "DATE");
   m_lstSqlTypeByClassName.insert("QTime", "TIME");
   m_lstSqlTypeByClassName.insert("QDateTime", "TIMESTAMP");
   m_lstSqlTypeByClassName.insert("QByteArray", "BLOB");
   m_lstSqlTypeByClassName.insert("qx::QxDateNeutral", "TEXT");
   m_lstSqlTypeByClassName.insert("qx::QxTimeNeutral", "TEXT");
   m_lstSqlTypeByClassName.insert("qx::QxDateTimeNeutral", "TEXT");
}

void QxClassX::initValidatorMessage()
{
   m_lstValidatorMessage.clear();

   m_lstValidatorMessage.insert("not_null", "value '%NAME%' cannot be null");
   m_lstValidatorMessage.insert("not_empty", "value '%NAME%' cannot be empty");
   m_lstValidatorMessage.insert("min_value", "value '%NAME%' must be greater than or equal to '%CONSTRAINT%'");
   m_lstValidatorMessage.insert("max_value", "value '%NAME%' must be lesser than or equal to '%CONSTRAINT%'");
   m_lstValidatorMessage.insert("min_length", "size of '%NAME%' must be greater than or equal to '%CONSTRAINT%' characters");
   m_lstValidatorMessage.insert("max_length", "size of '%NAME%' must be lesser than or equal to '%CONSTRAINT%' characters");
   m_lstValidatorMessage.insert("date_past", "date '%NAME%' must be in the past");
   m_lstValidatorMessage.insert("date_future", "date '%NAME%' must be in the future");
   m_lstValidatorMessage.insert("min_decimal", "value '%NAME%' must be greater than or equal to '%CONSTRAINT%'");
   m_lstValidatorMessage.insert("max_decimal", "value '%NAME%' must be lesser than or equal to '%CONSTRAINT%'");
   m_lstValidatorMessage.insert("regular_expression", "value '%NAME%' doesn't match the regular expression '%CONSTRAINT%'");
   m_lstValidatorMessage.insert("e_mail", "value '%NAME%' is not a valid e-mail");
}

namespace trait {
namespace detail {

/* Defined into './include/QxTraits/get_sql_type.h' file */
const char * get_sql_type_by_class_name(const char * sClassName, const char * sDefaultValue)
{
   static std::string s;
   s = qx::QxClassX::getSqlTypeByClassName(sClassName).toStdString();
   return (s.empty() ? sDefaultValue : s.c_str());
}

} // namespace detail
} // namespace trait
} // namespace qx
