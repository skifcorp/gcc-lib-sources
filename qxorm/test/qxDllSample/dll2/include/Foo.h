#ifndef _QX_FOO_H_
#define _QX_FOO_H_

#include "../include/BaseClassTrigger.h"
#include "../include/Bar.h"

class QX_DLL2_EXPORT Foo : public BaseClassTrigger, public qx::IxPersistable
{

   QX_REGISTER_FRIEND_CLASS(Foo)
   QX_PERSISTABLE_HPP(Foo)

protected:

   QString  m_sName;
   QVariant m_sDesc;
   BarX *   m_pBarX;

   qx::QxDateNeutral       m_oDateNeutral;
   qx::QxTimeNeutral       m_oTimeNeutral;
   qx::QxDateTimeNeutral   m_oDateTimeNeutral;

public:

   Foo() : BaseClassTrigger(), m_pBarX(NULL) { ; }
   virtual ~Foo()                            { reset(); }

   virtual void makeAbstractClass() { ; }

   QString getName() const          { return m_sName; }
   QVariant getDesc() const         { return m_sDesc; }
   BarX * getBarX() const           { return m_pBarX; }
   QDate getDate() const            { return m_oDateNeutral.toDate(); }
   QTime getTime() const            { return m_oTimeNeutral.toTime(); }
   QDateTime getDateTime() const    { return m_oDateTimeNeutral.toDateTime(); }

   void setName(const QString & s)           { m_sName = s; }
   void setDesc(const QVariant & s)          { m_sDesc = s; }
   void setBarX(BarX * p)                    { reset(); m_pBarX = p; }
   void setDate(const QDate & d)             { m_oDateNeutral.setDate(d); }
   void setTime(const QTime & t)             { m_oTimeNeutral.setTime(t); }
   void setDateTime(const QDateTime & dt)    { m_oDateTimeNeutral.setDateTime(dt); }

private:

   void reset() { if (m_pBarX) { delete m_pBarX; m_pBarX = NULL; } }

};

QX_REGISTER_HPP_QX_DLL2(Foo, BaseClassTrigger, 0)

typedef boost::shared_ptr<Foo> Foo_ptr;
typedef qx::QxCollection<long, Foo_ptr> FooX;
typedef boost::shared_ptr<FooX> FooX_ptr;

#endif // _QX_FOO_H_
