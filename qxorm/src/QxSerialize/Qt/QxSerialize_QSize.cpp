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

#include <QxSerialize/Qt/QxSerialize_QSize.h>

#include <QxMemLeak.h>

#define saved_exception_code exception_code
#undef exception_code




namespace boost {
namespace serialization {

template <class Archive>
inline void qx_serialize(Archive & ar, QSize & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("width", t.rwidth());
   ar & boost::serialization::make_nvp("height", t.rheight());
}

} // namespace boost
} // namespace serialization




#define exception_code saved_exception_code
#undef saved_exception_code


QX_SERIALIZE_FAST_COMPIL_SERIALIZE_CPP(QSize)
