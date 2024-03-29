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

#ifndef _QX_COLLECTION_ITERATOR_H_
#define _QX_COLLECTION_ITERATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxCollectionIterator.h
 * \author Lionel Marty
 * \ingroup QxCollection
 * \brief Java-style iterator to iterate over a qx::QxCollection<Key, Value> container
 */

#include <boost/noncopyable.hpp>

#include <QxCollection/QxCollection.h>

namespace qx {

/*!
 * \ingroup QxCollection
 * \brief qx::QxCollectionIterator : Java-style iterator to iterate over a qx::QxCollection<Key, Value> container
 *
 * Quick sample using qx::QxCollectionIterator Java-style iterator :
 * \code
// iterate over a drugs container using 'qx::QxCollectionIterator' Java-style iterator
qx::QxCollectionIterator<QString, drug_ptr> itr(lstDrugs);
while (itr.next())
{
   QString code = itr.key();
   qDebug() << qPrintable(itr.value()->name) << " " << qPrintable(itr.value()->desc);
}
 * \endcode
 */
template <typename Key, typename Value>
class QxCollectionIterator : private boost::noncopyable
{

private:

   const QxCollection<Key, Value> * m_pCollection;    //!< Collection to iterate over
   long m_lCurrIndex;                                 //!< Current index (position) in the collection

public:

   QxCollectionIterator(const QxCollection<Key, Value> & col);    //!< Construct an iterator for traversing the collection. The iterator is set to be at the front of the list (before the first item)
   ~QxCollectionIterator();                                       //!< Destroy the iterator

   inline const Key & key() const;        //!< Return the 'key' at current position
   inline const Value & value() const;    //!< Return the 'value' at current position

   inline void toFirst();                 //!< Move the iterator to the front of the container (before the first item)
   inline void toLast();                  //!< Move the iterator to the back of the container (after the last item)

   inline bool next();                    //!< Advance the iterator by one position. Return 'true' if there is at least one item ahead of the iterator, i.e. the iterator is not at the back of the container; otherwise return 'false'
   inline bool previous();                //!< Move the iterator back by one position. Return 'true' if there is at least one item behind the iterator, i.e. the iterator is not at the front of the container; otherwise return 'false'

};

} // namespace qx

#include "qxorm/inl/QxCollection/QxCollectionIterator.inl"

#endif // _QX_COLLECTION_ITERATOR_H_
