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

#ifndef _QX_COLLECTION_H_
#define _QX_COLLECTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxCollection.h
 * \author Lionel Marty
 * \ingroup QxCollection
 * \brief QxOrm container (keep insertion order + quick access by index + quick access by key)
 */

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4503)
#endif // _MSC_VER

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <QtCore/qpair.h>

#include <QxCollection/IxCollection.h>
#include <QxCollection/QxForeach.h>

#include <QxCommon/QxHashValue.h>

#include <QxTraits/get_class_name.h>
#include <QxTraits/is_smart_ptr.h>

namespace qx {

/*!
 * \ingroup QxCollection
 * \brief qx::QxCollection<Key, Value> : QxOrm container (keep insertion order + quick access by index + quick access by key)
 *
 * Based on boost::multi_index_container, this collection has advantages of std::vector<T> (keep insertion order + quick access by index)
 * and boost::unordered_map<Key, Value> or QHash<Key, Value> (quick access by key : hash-map).
 *
 * <i>Note :</i> qx::QxCollection<Key, Value> is compatible with the foreach macro provided by Qt library and the BOOST_FOREACH macro provided by boost library.
 * However, each element returned by these 2 macros corresponds to an object of type std::pair<Key, Value>.
 * To obtain a more natural and more readable result, it is advised to use the _foreach macro : this macro uses BOOST_FOREACH for all the containers except for qx::QxCollection<Key, Value>.
 * In this case, the returned element corresponds to the Value type (cf. following sample).
 * The macro _foreach is compatible with all containers (stl, Qt, boost...) since it uses the macro BOOST_FOREACH.
 *
 * <i>Additional note :</i> qx::QxCollection<Key, Value> is particularly suited to receive data resulting from a database.
 * Indeed, these data can be sorted (by using ORDER BY in a SQL request for example), it is thus important to preserve the insertion order of the elements in the list.
 * Furthermore, each data resulting from a database has a unique id. It is thus important to be able to access quickly to an element based on this single identifier (hash-map).
 *
 * Quick sample using qx::QxCollection<Key, Value> container :
 * \code
// definition of drug class with 3 properties : 'code', 'name' and 'description'
class drug { public: QString code; QString name; QString desc; };

// typedef a smart-pointer of drug class
typedef boost::shared_ptr<drug> drug_ptr;

// collection of drugs indexed by 'code' property (QString type)
qx::QxCollection<QString, drug_ptr> lstDrugs;

// create 3 new drugs
drug_ptr d1; d1.reset(new drug()); d1->code = "code1"; d1->name = "name1"; d1->desc = "desc1";
drug_ptr d2; d2.reset(new drug()); d2->code = "code2"; d2->name = "name2"; d2->desc = "desc2";
drug_ptr d3; d3.reset(new drug()); d3->code = "code3"; d3->name = "name3"; d3->desc = "desc3";

// insert 3 drugs into the collection
lstDrugs.insert(d1->code, d1);
lstDrugs.insert(d2->code, d2);
lstDrugs.insert(d3->code, d3);

// iterate over drugs container using QxOrm '_foreach' keyword
_foreach(drug_ptr p, lstDrugs)
{ qDebug() << qPrintable(p->name) << " " << qPrintable(p->desc); }

// iterate over drugs container using classic C++ 'for' keyword
for (long l = 0; l < lstDrugs.count(); ++l)
{
   drug_ptr p = lstDrugs.getByIndex(l);
   QString code = lstDrugs.getKeyByIndex(l);
   qDebug() << qPrintable(p->name) << " " << qPrintable(p->desc);
}

// iterate over drugs container using 'qx::QxCollectionIterator' Java-style iterator
qx::QxCollectionIterator<QString, drug_ptr> itr(lstDrugs);
while (itr.next())
{
   QString code = itr.key();
   qDebug() << qPrintable(itr.value()->name) << " " << qPrintable(itr.value()->desc);
}

// sort drugs container ascending by key and sort descending by value
lstDrugs.sortByKey(true);
lstDrugs.sortByValue(false);

// access to a drug into the collection by its 'code' property
drug_ptr p = lstDrugs.getByKey("code2");

// access to a drug into the collection by index (position in the list)
drug_ptr p = lstDrugs.getByIndex(2);

// test if a drug exists into the collection and if the collection is empty
bool bExist = lstDrugs.exist("code3");
bool bEmpty = lstDrugs.empty();

// remove the second drug from the collection
lstDrugs.removeByIndex(2);

// remove a drug from the collection using its 'code' property
lstDrugs.removeByKey("code3");

// clear the collection : remove all items from the list
lstDrugs.clear();
 * \endcode
 */
template <typename Key, typename Value>
class QxCollection : public IxCollection
{

public:

   typedef QPair<Key, Value> type_pair_key_value;

protected:

   typedef boost::multi_index::member<type_pair_key_value, Key, & type_pair_key_value::first> type_member;
   typedef boost::multi_index::random_access<> type_first_index;
   typedef boost::multi_index::hashed_unique<type_member> type_second_index;
   typedef boost::multi_index::indexed_by<type_first_index, type_second_index> type_indexed_by;
   typedef boost::multi_index::multi_index_container<type_pair_key_value, type_indexed_by> type_container;

   typedef typename type_container::template nth_index<0>::type type_index_rand;
   typedef typename type_container::template nth_index<1>::type type_index_hash;

public:

   typedef typename type_index_rand::iterator iterator;
   typedef typename type_index_rand::const_iterator const_iterator;
   typedef typename type_index_rand::reverse_iterator reverse_iterator;
   typedef typename type_index_rand::const_reverse_iterator const_reverse_iterator;

   typedef const Key & const_reference_key;
   typedef const Value & const_reference_value;

protected:

   type_container m_qxCollection;   //!< Collection with random access (like std::vector) and fast lookup by key (like boost::unordered_map)

public:

   QxCollection();                                          //!< Construct an empty list
   QxCollection(const QxCollection<Key, Value> & other);    //!< Construct a copy of 'other'
   virtual ~QxCollection();                                 //!< Destroy the list

   QxCollection<Key, Value> & operator= (const QxCollection<Key, Value> & other);   //!< Assign 'other' to this list and return a reference to this list
   bool operator== (const QxCollection<Key, Value> & other) const;                  //!< Return 'true' if 'other' is equal to this list, otherwise return 'false' (same values in the same order)
   bool operator!= (const QxCollection<Key, Value> & other) const;                  //!< Return 'true' if 'other' is not equal to this list, otherwise return 'false'

   inline iterator begin();                  //!< Return an STL-style iterator pointing to the first item in the list
   inline iterator end();                    //!< Return an STL-style iterator pointing to the imaginary item after the last item in the list
   inline const_iterator begin() const;      //!< Return a const STL-style iterator pointing to the first item in the list
   inline const_iterator end() const;        //!< Return a const STL-style iterator pointing to the imaginary item after the last item in the list

   inline reverse_iterator rbegin();               //!< Return a reverse STL-style iterator pointing to the first item in the list
   inline reverse_iterator rend();                 //!< Return a reverse STL-style iterator pointing to the imaginary item after the last item in the list
   inline const_reverse_iterator rbegin() const;   //!< Return a const reverse STL-style iterator pointing to the first item in the list
   inline const_reverse_iterator rend() const;     //!< Return a const reverse STL-style iterator pointing to the imaginary item after the last item in the list

   inline long capacity() const;                   //!< Return size of allocated storage capacity
   inline void reserve(long size);                 //!< Request that the capacity of the allocated storage space for the items of the container be at least enough to hold 'size' elements
   inline void reverse();                          //!< Reverse all items in the list
   inline void clear();                            //!< Remove all items from the list
   inline long count() const;                      //!< Return the number of items in the list (same as 'size()')
   inline long size() const;                       //!< Return the number of items in the list (same as 'count()')
   inline bool contains(const Key & key) const;    //!< Return 'true' if the list contains an occurrence of 'key', otherwise return 'false' (same as 'exist()')
   inline bool exist(const Key & key) const;       //!< Return 'true' if the list contains an occurrence of 'key', otherwise return 'false' (same as 'contains()')
   inline bool empty() const;                      //!< Return 'true' if the list contains no items; otherwise return 'false'

   inline bool push_back(const Key & key, const Value & value);               //!< Add element 'value' at the end of the list indexed by 'key'
   inline bool push_front(const Key & key, const Value & value);              //!< Insert 'value' at the beginning of the list indexed by 'key'
   inline bool insert(const Key & key, const Value & value);                  //!< Add element 'value' at the end of the list indexed by 'key'
   inline bool insert(long index, const Key & key, const Value & value);      //!< Insert element 'value' at position 'index' in the list indexed by 'key'
   inline bool insert(const QxCollection<Key, Value> & other);                //!< Add all items of 'other' at the end of the list
   inline bool insert(long index, const QxCollection<Key, Value> & other);    //!< Insert all items of 'other' at the end of the list
   inline bool replace(long index, const Key & key, const Value & value);     //!< Replace the item at index position 'index' with element 'value' indexed by 'key'
   inline bool swap(long index1, long index2);                                //!< Exchange the item at index position 'index1' with the item at index position 'index2'
   inline bool move(long indexFrom, long indexTo);                            //!< Move the item at index position 'indexFrom' to index position 'indexTo'

   inline bool removeByKey(const Key & key);             //!< Remove the item indexed by 'key' in the list
   inline bool removeByIndex(long index);                //!< Remove the item at index position 'index'
   inline bool removeByIndex(long first, long last);     //!< Remove all items from index position 'first' to index position 'last'
   inline bool removeFirst();                            //!< Remove the first item in the list
   inline bool removeLast();                             //!< Remove the last item in the list

   inline const_reference_value getByKey(const Key & key) const;     //!< Return the item associated with the 'key'
   inline const_reference_value getByIndex(long index) const;        //!< Return the item at index position 'index'
   inline const_reference_value getFirst() const;                    //!< Return the first element in the list
   inline const_reference_value getLast() const;                     //!< Return the last element in the list
   inline const_reference_key getKeyByIndex(long index) const;       //!< Return the key associated with the element at index position 'index'

   inline void sortByKey(bool bAscending = true);        //!< Sort all items in the list using associated keys to compare
   inline void sortByValue(bool bAscending = true);      //!< Sort all items in the list

   template <typename Compare>
   inline void sort(Compare comp) { m_qxCollection.template get<0>().sort(comp); }

private:

   void cloneCollection(QxCollection<Key, Value> * pClone, const QxCollection<Key, Value> & pRef);
   bool isSameCollection(const QxCollection<Key, Value> * p1, const QxCollection<Key, Value> & p2) const;

   template <bool bIsPointer /* = false */, int dummy>
   struct compareKeyValue
   {
      static inline bool compareByKeyAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)    { return (v1.first < v2.first); }
      static inline bool compareByKeyDescending(const type_pair_key_value & v1, const type_pair_key_value & v2)   { return (v1.first > v2.first); }
      static inline bool compareByValueAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)  { return (v1.second < v2.second); }
      static inline bool compareByValueDescending(const type_pair_key_value & v1, const type_pair_key_value & v2) { return (v1.second > v2.second); }
   };

   template <int dummy>
   struct compareKeyValue<true, dummy>
   {
      static inline bool compareByKeyAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)    { return ((v1.first && v2.first) ? ((* v1.first) < (* v2.first)) : false); }
      static inline bool compareByKeyDescending(const type_pair_key_value & v1, const type_pair_key_value & v2)   { return ((v1.first && v2.first) ? ((* v1.first) > (* v2.first)) : true); }
      static inline bool compareByValueAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)  { return ((v1.second && v2.second) ? ((* v1.second) < (* v2.second)) : false); }
      static inline bool compareByValueDescending(const type_pair_key_value & v1, const type_pair_key_value & v2) { return ((v1.second && v2.second) ? ((* v1.second) > (* v2.second)) : true); }
   };

public:

   virtual long _count() const               { return this->count(); }
   virtual void _clear()                     { this->clear(); }
   virtual bool _remove(long index)          { return this->removeByIndex(index); }
   virtual boost::any _at(long index) const  { Value val = this->getByIndex(index); return boost::any(val); }

};

} // namespace qx

#include "qxorm/inl/QxCollection/QxCollection.inl"

QX_REGISTER_CLASS_NAME_TEMPLATE_2(qx::QxCollection)

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // _QX_COLLECTION_H_
