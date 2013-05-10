/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Coroutine library.
**
****************************************************************************/

// Generated code, do not edit! Use generator at tools/generatebuild/


inline static Coroutine* build(void (*functionPointer)(), const QString& n);
template <typename Param1, typename Arg1>
inline static Coroutine* build(void (*functionPointer)(Param1), const Arg1 &arg1);
template <typename Param1, typename Arg1, typename Param2, typename Arg2>
inline static Coroutine* build(void (*functionPointer)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2);
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
inline static Coroutine* build(void (*functionPointer)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
inline static Coroutine* build(void (*functionPointer)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
inline static Coroutine* build(void (*functionPointer)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename FunctionObject>
inline static Coroutine* build(FunctionObject functionObject, const QString& n);
template <typename FunctionObject, typename Arg1>
inline static Coroutine* build(FunctionObject functionObject, const Arg1 &arg1);
template <typename FunctionObject, typename Arg1, typename Arg2>
inline static Coroutine* build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3>
inline static Coroutine* build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
inline static Coroutine* build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
inline static Coroutine* build(FunctionObject functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename FunctionObject>
inline static Coroutine* build(FunctionObject *functionObject);
template <typename FunctionObject, typename Arg1>
inline static Coroutine* build(FunctionObject *functionObject, const Arg1 &arg1);
template <typename FunctionObject, typename Arg1, typename Arg2>
inline static Coroutine* build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3>
inline static Coroutine* build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
inline static Coroutine* build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename FunctionObject, typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
inline static Coroutine* build(FunctionObject *functionObject, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename Class>
inline static Coroutine* build(const Class &object, void (Class::*fn)());
template <typename Class, typename Param1, typename Arg1>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1), const Arg1 &arg1);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename Class>
inline static Coroutine* build(const Class &object, void (Class::*fn)() const);
template <typename Class, typename Param1, typename Arg1>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1) const, const Arg1 &arg1);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2) const, const Arg1 &arg1, const Arg2 &arg2);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
inline static Coroutine* build(const Class &object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename Class>
inline static Coroutine* build(Class *object, void (Class::*fn)());
template <typename Class, typename Param1, typename Arg1>
inline static Coroutine* build(Class *object, void (Class::*fn)(Param1), const Arg1 &arg1);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
inline static Coroutine* build(Class *object, void (Class::*fn)(Param1, Param2), const Arg1 &arg1, const Arg2 &arg2);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
inline static Coroutine* build(Class *object, void (Class::*fn)(Param1, Param2, Param3), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
inline static Coroutine* build(Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
inline static Coroutine* build(Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5), const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);

template <typename Class>
inline static Coroutine* build(const Class *object, void (Class::*fn)() const);
template <typename Class, typename Param1, typename Arg1>
inline static Coroutine* build(const Class *object, void (Class::*fn)(Param1) const, const Arg1 &arg1);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2>
inline static Coroutine* build(const Class *object, void (Class::*fn)(Param1, Param2) const, const Arg1 &arg1, const Arg2 &arg2);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3>
inline static Coroutine* build(const Class *object, void (Class::*fn)(Param1, Param2, Param3) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4>
inline static Coroutine* build(const Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4);
template <typename Class, typename Param1, typename Arg1, typename Param2, typename Arg2, typename Param3, typename Arg3, typename Param4, typename Arg4, typename Param5, typename Arg5>
inline static Coroutine* build(const Class *object, void (Class::*fn)(Param1, Param2, Param3, Param4, Param5) const, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4, const Arg5 &arg5);


