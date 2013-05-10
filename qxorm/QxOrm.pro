#############################################################################
##
## http://www.qxorm.com/
## http://sourceforge.net/projects/qxorm/
## Original file by Lionel Marty
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software.
##
## GNU Lesser General Public License Usage
## This file must be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file 'license.lgpl.txt' included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## If you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

include(./QxOrm.pri)

######################
# Globals Parameters #
######################

TEMPLATE = lib
CONFIG += dll
DEFINES += _QX_BUILDING_QX_ORM
PRECOMPILED_HEADER = ./qxorm/QxPrecompiled.h
DESTDIR                 = build

unix { VERSION = 1.2.4 }

contains(DEFINES, _QX_STATIC_BUILD) {
CONFIG -= dll
CONFIG += staticlib
}

#############################
# Compiler / Linker Options #
#############################

CONFIG(debug, debug|release) {
TARGET = QxOrmd
} else {
TARGET = QxOrm
} # CONFIG(debug, debug|release)

unix {
DESTDIR = ./lib/
target.path = /usr/local/lib/
headers.path = /usr/local/include/
headers.files = ./include/*
INSTALLS = target headers
} # unix

#################
# Headers Files #
#################

HEADERS += ./qxorm/QxPrecompiled.h

HEADERS += ./qxorm/QxMemLeak/bool_array.h
HEADERS += ./qxorm/QxMemLeak/class_level_lock.h
HEADERS += ./qxorm/QxMemLeak/cont_ptr_utils.h
HEADERS += ./qxorm/QxMemLeak/debug_new.h
HEADERS += ./qxorm/QxMemLeak/fast_mutex.h
HEADERS += ./qxorm/QxMemLeak/fixed_mem_pool.h
HEADERS += ./qxorm/QxMemLeak/mem_leak.h
HEADERS += ./qxorm/QxMemLeak/mem_pool_base.h
HEADERS += ./qxorm/QxMemLeak/object_level_lock.h
HEADERS += ./qxorm/QxMemLeak/pctimer.h
HEADERS += ./qxorm/QxMemLeak/set_assign.h
HEADERS += ./qxorm/QxMemLeak/static_assert.h
HEADERS += ./qxorm/QxMemLeak/static_mem_pool.h

HEADERS += ./qxorm/QxSingleton/IxSingleton.h
HEADERS += ./qxorm/QxSingleton/QxSingleton.h
HEADERS += ./qxorm/QxSingleton/QxSingletonX.h

HEADERS += ./qxorm/QxFactory/IxFactory.h
HEADERS += ./qxorm/QxFactory/QxFactory.h
HEADERS += ./qxorm/QxFactory/QxFactoryX.h

HEADERS += ./qxorm/QxCommon/QxConfig.h
HEADERS += ./qxorm/QxCommon/QxMacro.h
HEADERS += ./qxorm/QxCommon/QxHashValue.h
HEADERS += ./qxorm/QxCommon/QxBool.h
HEADERS += ./qxorm/QxCommon/QxCache.h
HEADERS += ./qxorm/QxCommon/QxStringCvt.h
HEADERS += ./qxorm/QxCommon/QxStringCvt_Impl.h
HEADERS += ./qxorm/QxCommon/QxStringCvt_Export.h
HEADERS += ./qxorm/QxCommon/QxPropertyBag.h
HEADERS += ./qxorm/QxCommon/QxSimpleCrypt.h
HEADERS += ./qxorm/QxCommon/QxAnyCastDynamic.h

HEADERS += ./qxorm/QxRegister/IxClass.h
HEADERS += ./qxorm/QxRegister/QxClass.h
HEADERS += ./qxorm/QxRegister/QxClassX.h
HEADERS += ./qxorm/QxRegister/QxClassName.h
HEADERS += ./qxorm/QxRegister/QxRegister.h
HEADERS += ./qxorm/QxRegister/QxRegisterInternalHelper.h
HEADERS += ./qxorm/QxRegister/IxTypeInfo.h
HEADERS += ./qxorm/QxRegister/QxRegisterQtProperty.h

HEADERS += ./qxorm/QxCollection/IxCollection.h
HEADERS += ./qxorm/QxCollection/QxCollection.h
HEADERS += ./qxorm/QxCollection/QxCollectionIterator.h
HEADERS += ./qxorm/QxCollection/QxForeach.h

HEADERS += ./qxorm/QxDataMember/IxDataMember.h
HEADERS += ./qxorm/QxDataMember/IxDataMemberX.h
HEADERS += ./qxorm/QxDataMember/QxDataMember.h
HEADERS += ./qxorm/QxDataMember/QxDataMemberX.h
HEADERS += ./qxorm/QxDataMember/QxDataMember_QObject.h

HEADERS += ./qxorm/QxDao/IxSqlQueryBuilder.h
HEADERS += ./qxorm/QxDao/QxSqlQueryBuilder.h
HEADERS += ./qxorm/QxDao/QxSqlQueryHelper.h
HEADERS += ./qxorm/QxDao/QxSqlQuery.h
HEADERS += ./qxorm/QxDao/QxSqlDatabase.h
HEADERS += ./qxorm/QxDao/IxSqlRelation.h
HEADERS += ./qxorm/QxDao/QxSqlRelation.h
HEADERS += ./qxorm/QxDao/QxSqlRelationParams.h
HEADERS += ./qxorm/QxDao/QxSqlRelation_ManyToMany.h
HEADERS += ./qxorm/QxDao/QxSqlRelation_ManyToOne.h
HEADERS += ./qxorm/QxDao/QxSqlRelation_OneToMany.h
HEADERS += ./qxorm/QxDao/QxSqlRelation_OneToOne.h
HEADERS += ./qxorm/QxDao/QxSqlRelation_RawData.h
HEADERS += ./qxorm/QxDao/QxDao.h
HEADERS += ./qxorm/QxDao/QxDao_Impl.h
HEADERS += ./qxorm/QxDao/QxDaoStrategy.h
HEADERS += ./qxorm/QxDao/QxDaoPointer.h
HEADERS += ./qxorm/QxDao/QxDao_IsDirty.h
HEADERS += ./qxorm/QxDao/QxSoftDelete.h
HEADERS += ./qxorm/QxDao/QxSqlError.h
HEADERS += ./qxorm/QxDao/QxSession.h
HEADERS += ./qxorm/QxDao/QxDateNeutral.h
HEADERS += ./qxorm/QxDao/QxTimeNeutral.h
HEADERS += ./qxorm/QxDao/QxDateTimeNeutral.h
HEADERS += ./qxorm/QxDao/IxDao_Helper.h
HEADERS += ./qxorm/QxDao/IxPersistable.h
HEADERS += ./qxorm/QxDao/QxSqlJoin.h
HEADERS += ./qxorm/QxDao/QxSqlRelationLinked.h

HEADERS += ./qxorm/QxDao/QxSqlElement/IxSqlElement.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlCompare.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlElement.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlElementTemp.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlExpression.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlFreeText.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlIn.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlIsBetween.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlIsNull.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlLimit.h
HEADERS += ./qxorm/QxDao/QxSqlElement/QxSqlSort.h

HEADERS += ./qxorm/QxDao/QxSqlGenerator/IxSqlGenerator.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.h
HEADERS += ./qxorm/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h

HEADERS += ./qxorm/QxDao/QxRepository/IxRepository.h
HEADERS += ./qxorm/QxDao/QxRepository/QxRepository.h
HEADERS += ./qxorm/QxDao/QxRepository/QxRepositoryX.h

HEADERS += ./qxorm/QxSerialize/QxArchive.h
HEADERS += ./qxorm/QxSerialize/QxClone.h
HEADERS += ./qxorm/QxSerialize/QxDump.h
HEADERS += ./qxorm/QxSerialize/QxSerializeFastCompil.h
HEADERS += ./qxorm/QxSerialize/QxSerializeInvoker.h
HEADERS += ./qxorm/QxSerialize/QxSerializeMacro.h
HEADERS += ./qxorm/QxSerialize/QxSerialize.h

HEADERS += ./qxorm/QxSerialize/boost/class_export/qx_boost_class_export.h
HEADERS += ./qxorm/QxSerialize/boost/portable_binary/portable_archive_exception.hpp
HEADERS += ./qxorm/QxSerialize/boost/portable_binary/portable_iarchive.hpp
HEADERS += ./qxorm/QxSerialize/boost/portable_binary/portable_oarchive.hpp
HEADERS += ./qxorm/QxSerialize/boost/QxSerializeInclude.h
HEADERS += ./qxorm/QxSerialize/boost/QxSerialize_shared_ptr.h
HEADERS += ./qxorm/QxSerialize/boost/QxSerialize_tuple.h
HEADERS += ./qxorm/QxSerialize/boost/QxSerialize_unordered_map.h
HEADERS += ./qxorm/QxSerialize/boost/QxSerialize_unordered_set.h
HEADERS += ./qxorm/QxSerialize/boost/QxExportDllMacroHpp.h
HEADERS += ./qxorm/QxSerialize/boost/QxExportDllMacroCpp.h
HEADERS += ./qxorm/QxSerialize/boost/QxExportDllBoostArchive.h
HEADERS += ./qxorm/QxSerialize/boost/QxImportDllBoostArchive.h

HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QBrush.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QByteArray.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QColor.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QDate.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QDateTime.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QFont.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QHash.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QImage.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QLinkedList.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QList.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QMap.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QMatrix.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QObject.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QPair.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QPicture.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QPixmap.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QPoint.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QRect.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QRegExp.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QRegion.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QScopedPointer.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QSharedPointer.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QSize.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QString.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QTime.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QUrl.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QUuid.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QVariant.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QVector.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QWeakPointer.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QMultiHash.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QMultiMap.h
HEADERS += ./qxorm/QxSerialize/Qt/QxSerialize_QStringList.h

HEADERS += ./qxorm/QxSerialize/Qx/QxSerialize_QxCollection.h
HEADERS += ./qxorm/QxSerialize/Qx/QxSerialize_QxXmlReader.h
HEADERS += ./qxorm/QxSerialize/Qx/QxSerialize_QxXmlWriter.h
HEADERS += ./qxorm/QxSerialize/Qx/QxSerialize_QxDaoPointer.h

HEADERS += ./qxorm/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h
HEADERS += ./qxorm/QxSerialize/QxBoostSerializeHelper/QxBoostInitGuid.h
HEADERS += ./qxorm/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeHelper.h
HEADERS += ./qxorm/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelper.h
HEADERS += ./qxorm/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h

HEADERS += ./qxorm/QxTraits/get_base_class.h
HEADERS += ./qxorm/QxTraits/get_primary_key.h
HEADERS += ./qxorm/QxTraits/get_class_name.h
HEADERS += ./qxorm/QxTraits/get_class_name_primitive.h
HEADERS += ./qxorm/QxTraits/is_boost_intrusive_ptr.h
HEADERS += ./qxorm/QxTraits/is_boost_scoped_ptr.h
HEADERS += ./qxorm/QxTraits/is_boost_shared_ptr.h
HEADERS += ./qxorm/QxTraits/is_boost_weak_ptr.h
HEADERS += ./qxorm/QxTraits/is_qt_shared_data_ptr.h
HEADERS += ./qxorm/QxTraits/is_qt_shared_ptr.h
HEADERS += ./qxorm/QxTraits/is_qt_scoped_ptr.h
HEADERS += ./qxorm/QxTraits/is_qt_weak_ptr.h
HEADERS += ./qxorm/QxTraits/is_smart_ptr.h
HEADERS += ./qxorm/QxTraits/is_boost_unordered_map.h
HEADERS += ./qxorm/QxTraits/is_boost_unordered_set.h
HEADERS += ./qxorm/QxTraits/is_container.h
HEADERS += ./qxorm/QxTraits/is_qt_hash.h
HEADERS += ./qxorm/QxTraits/is_qt_linked_list.h
HEADERS += ./qxorm/QxTraits/is_qt_list.h
HEADERS += ./qxorm/QxTraits/is_qt_map.h
HEADERS += ./qxorm/QxTraits/is_qt_multi_hash.h
HEADERS += ./qxorm/QxTraits/is_qt_multi_map.h
HEADERS += ./qxorm/QxTraits/is_qt_set.h
HEADERS += ./qxorm/QxTraits/is_qt_vector.h
HEADERS += ./qxorm/QxTraits/is_qt_variant_compatible.h
HEADERS += ./qxorm/QxTraits/is_qx_collection.h
HEADERS += ./qxorm/QxTraits/is_std_list.h
HEADERS += ./qxorm/QxTraits/is_std_map.h
HEADERS += ./qxorm/QxTraits/is_std_set.h
HEADERS += ./qxorm/QxTraits/is_std_vector.h
HEADERS += ./qxorm/QxTraits/is_container_base_of.h
HEADERS += ./qxorm/QxTraits/is_container_key_value.h
HEADERS += ./qxorm/QxTraits/is_container_to_pod.h
HEADERS += ./qxorm/QxTraits/is_ptr_base_of.h
HEADERS += ./qxorm/QxTraits/is_ptr_to_pod.h
HEADERS += ./qxorm/QxTraits/is_qx_pod.h
HEADERS += ./qxorm/QxTraits/is_qx_registered.h
HEADERS += ./qxorm/QxTraits/is_smart_ptr_base_of.h
HEADERS += ./qxorm/QxTraits/is_smart_ptr_to_pod.h
HEADERS += ./qxorm/QxTraits/archive_wide_traits.h
HEADERS += ./qxorm/QxTraits/archive_printable.h
HEADERS += ./qxorm/QxTraits/remove_attr.h
HEADERS += ./qxorm/QxTraits/remove_smart_ptr.h
HEADERS += ./qxorm/QxTraits/construct_ptr.h
HEADERS += ./qxorm/QxTraits/get_sql_type.h
HEADERS += ./qxorm/QxTraits/generic_container.h
HEADERS += ./qxorm/QxTraits/is_valid_primary_key.h
HEADERS += ./qxorm/QxTraits/is_qx_dao_ptr.h
HEADERS += ./qxorm/QxTraits/is_equal.h
HEADERS += ./qxorm/QxTraits/qt_meta_object.h
HEADERS += ./qxorm/QxTraits/qx_traits.h

HEADERS += ./qxorm/QxFunction/IxFunction.h
HEADERS += ./qxorm/QxFunction/QxFunction_0.h
HEADERS += ./qxorm/QxFunction/QxFunction_1.h
HEADERS += ./qxorm/QxFunction/QxFunction_2.h
HEADERS += ./qxorm/QxFunction/QxFunction_3.h
HEADERS += ./qxorm/QxFunction/QxFunction_4.h
HEADERS += ./qxorm/QxFunction/QxFunction_5.h
HEADERS += ./qxorm/QxFunction/QxFunction_6.h
HEADERS += ./qxorm/QxFunction/QxFunction_7.h
HEADERS += ./qxorm/QxFunction/QxFunction_8.h
HEADERS += ./qxorm/QxFunction/QxFunction_9.h
HEADERS += ./qxorm/QxFunction/QxFunctionError.h
HEADERS += ./qxorm/QxFunction/QxFunctionInclude.h
HEADERS += ./qxorm/QxFunction/QxFunctionMacro.h
HEADERS += ./qxorm/QxFunction/QxParameters.h

HEADERS += ./qxorm/QxService/IxParameter.h
HEADERS += ./qxorm/QxService/IxService.h
HEADERS += ./qxorm/QxService/QxClientAsync.h
HEADERS += ./qxorm/QxService/QxConnect.h
HEADERS += ./qxorm/QxService/QxServer.h
HEADERS += ./qxorm/QxService/QxService.h
HEADERS += ./qxorm/QxService/QxThread.h
HEADERS += ./qxorm/QxService/QxThreadPool.h
HEADERS += ./qxorm/QxService/QxTools.h
HEADERS += ./qxorm/QxService/QxTransaction.h

HEADERS += ./qxorm/QxXml/QxXmlReader.h
HEADERS += ./qxorm/QxXml/QxXmlWriter.h
HEADERS += ./qxorm/QxXml/QxXml.h

HEADERS += ./qxorm/QxValidator/IxValidator.h
HEADERS += ./qxorm/QxValidator/IxValidatorX.h
HEADERS += ./qxorm/QxValidator/QxInvalidValue.h
HEADERS += ./qxorm/QxValidator/QxInvalidValueX.h
HEADERS += ./qxorm/QxValidator/QxValidator.h
HEADERS += ./qxorm/QxValidator/QxValidatorError.h
HEADERS += ./qxorm/QxValidator/QxValidatorFct.h
HEADERS += ./qxorm/QxValidator/QxValidatorX.h

HEADERS += ./qxorm/QxOrm.h
HEADERS += ./qxorm/QxMemLeak.h

#################
# Sources Files #
#################

SOURCES += ./src/QxMemLeak/bool_array.cpp
SOURCES += ./src/QxMemLeak/debug_new.cpp
SOURCES += ./src/QxMemLeak/mem_pool_base.cpp
SOURCES += ./src/QxMemLeak/static_mem_pool.cpp

SOURCES += ./src/QxSingleton/IxSingleton.cpp
SOURCES += ./src/QxSingleton/QxSingletonX.cpp

SOURCES += ./src/QxFactory/IxFactory.cpp
SOURCES += ./src/QxFactory/QxFactoryX.cpp

SOURCES += ./src/QxCollection/QxCollection.cpp

SOURCES += ./src/QxCommon/QxCache.cpp
SOURCES += ./src/QxCommon/QxStringCvt_Export.cpp
SOURCES += ./src/QxCommon/QxSimpleCrypt.cpp

SOURCES += ./src/QxRegister/IxClass.cpp
SOURCES += ./src/QxRegister/QxClassX.cpp

SOURCES += ./src/QxDataMember/IxDataMember.cpp
SOURCES += ./src/QxDataMember/IxDataMemberX.cpp
SOURCES += ./src/QxDataMember/QxDataMember_QObject.cpp

SOURCES += ./src/QxTraits/unit_test_is_smart_ptr.cpp
SOURCES += ./src/QxTraits/unit_test_is_container.cpp

SOURCES += ./src/QxXml/QxXmlReader.cpp
SOURCES += ./src/QxXml/QxXmlWriter.cpp

SOURCES += ./src/QxDao/IxSqlQueryBuilder.cpp
SOURCES += ./src/QxDao/QxSqlDatabase.cpp
SOURCES += ./src/QxDao/IxSqlRelation.cpp
SOURCES += ./src/QxDao/QxSqlQuery.cpp
SOURCES += ./src/QxDao/QxSession.cpp
SOURCES += ./src/QxDao/IxDao_Helper.cpp
SOURCES += ./src/QxDao/IxPersistable.cpp
SOURCES += ./src/QxDao/QxSqlRelationLinked.cpp

SOURCES += ./src/QxDao/QxSqlElement/IxSqlElement.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlCompare.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlElementTemp.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlExpression.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlFreeText.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIn.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIsBetween.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlIsNull.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlLimit.cpp
SOURCES += ./src/QxDao/QxSqlElement/QxSqlSort.cpp

SOURCES += ./src/QxDao/QxSqlGenerator/IxSqlGenerator.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.cpp
SOURCES += ./src/QxDao/QxSqlGenerator/QxSqlGenerator_Standard.cpp

SOURCES += ./src/QxDao/QxRepository/IxRepository.cpp
SOURCES += ./src/QxDao/QxRepository/QxRepositoryX.cpp

SOURCES += ./src/QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.cpp
SOURCES += ./src/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.cpp

SOURCES += ./src/QxSerialize/boost/QxExportDllBoostArchive.cpp

SOURCES += ./src/QxSerialize/Qt/QxSerialize_QBrush.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QByteArray.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QColor.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QDate.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QDateTime.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QFont.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QImage.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QMatrix.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QObject.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPicture.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPixmap.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QPoint.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRect.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRegExp.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QRegion.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QSize.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QString.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QStringList.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QTime.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QUrl.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QUuid.cpp
SOURCES += ./src/QxSerialize/Qt/QxSerialize_QVariant.cpp

SOURCES += ./src/QxService/IxParameter.cpp
SOURCES += ./src/QxService/IxService.cpp
SOURCES += ./src/QxService/QxConnect.cpp
SOURCES += ./src/QxService/QxServer.cpp
SOURCES += ./src/QxService/QxThread.cpp
SOURCES += ./src/QxService/QxThreadPool.cpp
SOURCES += ./src/QxService/QxTools.cpp
SOURCES += ./src/QxService/QxTransaction.cpp

SOURCES += ./src/QxValidator/IxValidator.cpp
SOURCES += ./src/QxValidator/IxValidatorX.cpp
SOURCES += ./src/QxValidator/QxInvalidValue.cpp
SOURCES += ./src/QxValidator/QxInvalidValueX.cpp

SOURCES += ./src/main.cpp
