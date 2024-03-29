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

#include <QxSerialize/Qt/QxSerialize_QString.h>

#include <QxTraits/archive_wide_traits.h>
#include <QxTraits/archive_printable.h>

#include <QxMemLeak.h>

#define saved_exception_code exception_code
#undef exception_code




namespace boost {
namespace serialization {

template <bool isPrintable = false>
struct qx_serialize_qstring
{

   template <class Archive>
   static inline void save(Archive & ar, const QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      char cell, row;
      long lSize = t.size();
      ar << boost::serialization::make_nvp("size", lSize);
      const QChar * qcharPtr = t.constData();
      for (long l = 0; l < lSize; ++l)
      {
         cell = static_cast<char>(qcharPtr[l].cell());
         row = static_cast<char>(qcharPtr[l].row());
         ar << boost::serialization::make_nvp(NULL, cell);
         ar << boost::serialization::make_nvp(NULL, row);
      }
   }

   template <class Archive>
   static inline void load(Archive & ar, QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      char cell, row;
      long lSize = 0;
      ar >> boost::serialization::make_nvp("size", lSize);
      t.clear();
      t.reserve(lSize);
      for (long l = 0; l < lSize; ++l)
      {
         ar >> boost::serialization::make_nvp(NULL, cell);
         ar >> boost::serialization::make_nvp(NULL, row);
         t.append(QChar(cell, row));
      }
   }

};

template <>
struct qx_serialize_qstring<true>
{

   template <class Archive>
   static inline void save(Archive & ar, const QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      typedef typename qx::trait::archive_wide_traits<Archive>::type_string qx_type_string_tmp;
      qx_type_string_tmp str; qx::trait::archive_wide_traits<Archive>::fromQString(t, str);
      ar << boost::serialization::make_nvp(NULL, str);
   }

   template <class Archive>
   static inline void load(Archive & ar, QString & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      typedef typename qx::trait::archive_wide_traits<Archive>::type_string qx_type_string_tmp;
      qx_type_string_tmp str;
      ar >> boost::serialization::make_nvp(NULL, str);
      t = qx::trait::archive_wide_traits<Archive>::toQString(str);
   }

};

template <class Archive>
inline void qx_save(Archive & ar, const QString & t, const unsigned int file_version)
{
   qx_serialize_qstring<qx::trait::is_archive_printable<Archive>::value>::save(ar, t, file_version);
}

template <class Archive>
inline void qx_load(Archive & ar, QString & t, const unsigned int file_version)
{
   qx_serialize_qstring<qx::trait::is_archive_printable<Archive>::value>::load(ar, t, file_version);
}

} // namespace boost
} // namespace serialization



#define exception_code saved_exception_code
#undef saved_exception_code


QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(QString)
