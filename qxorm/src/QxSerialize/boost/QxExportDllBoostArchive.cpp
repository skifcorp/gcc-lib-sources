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

#if _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON

#include <QxSerialize/QxSerialize.h>

#include <QxCommon/QxStringCvt_Impl.h>

#include <QxMemLeak.h>

#define saved_exception_code exception_code
#undef exception_code


#if (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::archive_serializer_map, Archive)
#else // (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION > 103800)

#if (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_CPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::archive_serializer_map, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::archive_serializer_map, ArchiveOut)
#else // (BOOST_VERSION > 103800)
#define QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_CPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::archive_pointer_iserializer, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::archive_pointer_oserializer, ArchiveOut)
#endif // (BOOST_VERSION > 103800)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::save_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::save_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::save_non_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::save_non_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::save_enum_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::save_enum_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::save_array_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::save_array_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::load_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::load_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::load_non_pointer_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::load_non_pointer_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::load_enum_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::load_enum_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#if (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, boost::archive::detail::load_array_type, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::load_array_type, Archive)
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_CPP(Archive) /* Nothing */
#endif // (BOOST_VERSION >= 104100)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_IARCHIVE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::interface_iarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::interface_iarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_OARCHIVE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::interface_oarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::interface_oarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_IARCHIVE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::common_iarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::common_iarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_OARCHIVE_CPP(Archive) \
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(class, boost::archive::detail::common_oarchive, Archive) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_CPP(class, boost::serialization::singleton, boost::archive::detail::common_oarchive, Archive)

#define QX_BOOST_EXPORT_ARCHIVE_INTERFACE_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_IARCHIVE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_OARCHIVE_CPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_COMMON_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_IARCHIVE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_OARCHIVE_CPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_SINGLETON_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_NON_POINTER_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_POINTER_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ENUM_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_SAVE_ARRAY_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_NON_POINTER_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_POINTER_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ENUM_TYPE_CPP(ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_CPP(ArchiveIn) \
QX_BOOST_EXPORT_ARCHIVE_LOAD_ARRAY_TYPE_CPP(ArchiveOut)

#define QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_INTERFACE_CPP(ArchiveIn, ArchiveOut) \
QX_BOOST_EXPORT_ARCHIVE_COMMON_CPP(ArchiveIn, ArchiveOut)

#if _QX_SERIALIZE_POLYMORPHIC
   QX_BOOST_EXPORT_ARCHIVE_CPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_CPP(boost::archive::polymorphic_binary_iarchive, boost::archive::polymorphic_binary_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_CPP(boost::archive::polymorphic_text_iarchive, boost::archive::polymorphic_text_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_CPP(boost::archive::polymorphic_xml_iarchive, boost::archive::polymorphic_xml_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_SERIALIZER_MAP_CPP(eos::portable_iarchive, eos::portable_oarchive)
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_BOOST_EXPORT_ARCHIVE_ALL_CPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#define exception_code saved_exception_code
#undef saved_exception_code


#endif // _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON
