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

#ifndef _QX_STRING_CVT_H_
#define _QX_STRING_CVT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxStringCvt.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief qx::cvt : namespace to provide global functions to convert any kind of objects to/from QString and QVariant format
 */

#include <QxCommon/QxBool.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename T> struct QxStringCvt_ToString;
template <typename T> struct QxStringCvt_FromString;
template <typename T> struct QxStringCvt_ToVariant;
template <typename T> struct QxStringCvt_FromVariant;
template <typename T> struct QxStringCvt_WithIndex;

} // namespace detail

template <typename T> inline QString to_string(const T & t, const QString & format)                   { return qx::cvt::detail::QxStringCvt_ToString<T>::toString(t, format, -1); }
template <typename T> inline qx_bool from_string(const QString & s, T & t, const QString & format)    { return qx::cvt::detail::QxStringCvt_FromString<T>::fromString(s, t, format, -1); }
template <typename T> inline QVariant to_variant(const T & t, const QString & format)                 { return qx::cvt::detail::QxStringCvt_ToVariant<T>::toVariant(t, format, -1); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t, const QString & format)  { return qx::cvt::detail::QxStringCvt_FromVariant<T>::fromVariant(v, t, format, -1); }

template <typename T> inline QString to_string(const T & t)                   { return qx::cvt::detail::QxStringCvt_ToString<T>::toString(t, "", -1); }
template <typename T> inline qx_bool from_string(const QString & s, T & t)    { return qx::cvt::detail::QxStringCvt_FromString<T>::fromString(s, t, "", -1); }
template <typename T> inline QVariant to_variant(const T & t)                 { return qx::cvt::detail::QxStringCvt_ToVariant<T>::toVariant(t, "", -1); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t)  { return qx::cvt::detail::QxStringCvt_FromVariant<T>::fromVariant(v, t, "", -1); }

template <typename T> inline QString to_string(const T & t, const QString & format, int index)                   { return qx::cvt::detail::QxStringCvt_WithIndex<T>::toString(t, format, index); }
template <typename T> inline qx_bool from_string(const QString & s, T & t, const QString & format, int index)    { return qx::cvt::detail::QxStringCvt_WithIndex<T>::fromString(t, s, format, index); }
template <typename T> inline QVariant to_variant(const T & t, const QString & format, int index)                 { return qx::cvt::detail::QxStringCvt_WithIndex<T>::toVariant(t, format, index); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t, const QString & format, int index)  { return qx::cvt::detail::QxStringCvt_WithIndex<T>::fromVariant(t, v, format, index); }

} // namespace cvt
} // namespace qx

#endif // _QX_STRING_CVT_H_
