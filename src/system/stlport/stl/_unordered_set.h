/*
 * Copyright (c) 2004
 * Francois Dumont
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef _STLP_INTERNAL_UNORDERED_SET_H
#define _STLP_INTERNAL_UNORDERED_SET_H

#ifndef _STLP_INTERNAL_HASHTABLE_H
#  include <stl/_hashtable.h>
#endif

namespace _STLP_STD {

//Specific iterator traits creation
_STLP_CREATE_HASH_ITERATOR_TRAITS(UnorderedSetTraitsT, Const_traits)

template <class _Value, class _HashFcn = hash<_Value>,
          class _EqualKey = equal_to<_Value>,
          class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Value) >
class unordered_set
{
  typedef unordered_set<_Value, _HashFcn, _EqualKey, _Alloc> _Self;
  //Specific iterator traits creation
  typedef _STLP_PRIV::_UnorderedSetTraitsT<_Value> _UnorderedSetTraits;
public:
  typedef hashtable<_Value, _Value, _HashFcn,
                    _UnorderedSetTraits, _STLP_PRIV::_Identity<_Value>, _EqualKey, _Alloc> _Ht;
public:
  typedef typename _Ht::key_type key_type;
  typedef typename _Ht::value_type value_type;
  typedef typename _Ht::hasher hasher;
  typedef typename _Ht::key_equal key_equal;

  typedef typename _Ht::size_type size_type;
  typedef typename _Ht::difference_type difference_type;
  typedef typename _Ht::pointer         pointer;
  typedef typename _Ht::const_pointer   const_pointer;
  typedef typename _Ht::reference       reference;
  typedef typename _Ht::const_reference const_reference;

  typedef typename _Ht::iterator iterator;
  typedef typename _Ht::const_iterator const_iterator;
  typedef typename _Ht::local_iterator local_iterator;
  typedef typename _Ht::const_local_iterator const_local_iterator;

  typedef typename _Ht::allocator_type allocator_type;

  hasher hash_function() const { return _M_ht.hash_funct(); }
  key_equal key_eq() const { return _M_ht.key_eq(); }
  allocator_type get_allocator() const { return _M_ht.get_allocator(); }

private:
  _Ht _M_ht;
  _STLP_KEY_TYPE_FOR_CONT_EXT(key_type)

public:
  explicit unordered_set(size_type __n = 100, const hasher& __hf = hasher(),
                         const key_equal& __eql = key_equal(),
                         const allocator_type& __a = allocator_type())
    : _M_ht(__n, __hf, __eql, __a) {}

  unordered_set(__move_source<_Self> src)
    : _M_ht(__move_source<_Ht>(src.get()._M_ht)) {}

  template <class _InputIterator>
  unordered_set(_InputIterator __f, _InputIterator __l,
                size_type __n = 100, const hasher& __hf = hasher(),
                const key_equal& __eql = key_equal(),
                const allocator_type& __a = allocator_type())
    : _M_ht(__n, __hf, __eql, __a)
  { _M_ht.insert_unique(__f, __l); }

  _Self& operator = (const _Self& __other)
  { _M_ht = __other._M_ht; return *this; }

  size_type size() const { return _M_ht.size(); }
  size_type max_size() const { return _M_ht.max_size(); }
  bool empty() const { return _M_ht.empty(); }
  void swap(_Self& __hs) { _M_ht.swap(__hs._M_ht); }

  iterator begin() { return _M_ht.begin(); }
  iterator end() { return _M_ht.end(); }
  const_iterator begin() const { return _M_ht.begin(); }
  const_iterator end() const { return _M_ht.end(); }

  pair<iterator, bool> insert(const value_type& __obj)
  { return _M_ht.insert_unique(__obj); }
  iterator insert(const_iterator /*__hint*/, const value_type& __obj)
  { return _M_ht.insert_unique(__obj); }
  template <class _InputIterator>
  void insert(_InputIterator __f, _InputIterator __l)
  { _M_ht.insert_unique(__f,__l); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator find(const _KT& __key) { return _M_ht.find(__key); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator find(const _KT& __key) const { return _M_ht.find(__key); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type count(const _KT& __key) const { return _M_ht.count(__key); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<iterator, iterator> equal_range(const _KT& __key)
  { return _M_ht.equal_range(__key); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<const_iterator, const_iterator> equal_range(const _KT& __key) const
  { return _M_ht.equal_range(__key); }

  size_type erase(const key_type& __key) {return _M_ht.erase(__key); }
  void erase(const_iterator __it) { _M_ht.erase(__it); }
  void erase(const_iterator __f, const_iterator __l) { _M_ht.erase(__f, __l); }
  void clear() { _M_ht.clear(); }

  size_type bucket_count() const { return _M_ht.bucket_count(); }
  size_type max_bucket_count() const { return _M_ht.max_bucket_count(); }
  size_type bucket_size(size_type __n) const { return _M_ht.elems_in_bucket(__n); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type bucket(const _KT& __k) const { return _M_ht.bucket(__k); }
  local_iterator begin(size_type __n) { return _M_ht.begin(__n); }
  local_iterator end(size_type __n) { return _M_ht.end(__n); }
  const_local_iterator begin(size_type __n) const { return _M_ht.begin(__n); }
  const_local_iterator end(size_type __n) const { return _M_ht.end(__n); }

  float load_factor() const { return _M_ht.load_factor(); }
  float max_load_factor() const { return _M_ht.max_load_factor(); }
  void max_load_factor(float __val) { _M_ht.max_load_factor(__val); }
  void rehash(size_type __hint) { _M_ht.rehash(__hint); }
};

//Specific iterator traits creation
_STLP_CREATE_HASH_ITERATOR_TRAITS(UnorderedMultisetTraitsT, Const_traits)

template <class _Value, class _HashFcn = hash<_Value>,
          class _EqualKey = equal_to<_Value>,
          class _Alloc = _STLP_DEFAULT_ALLOCATOR(_Value) >
class unordered_multiset
{
  typedef unordered_multiset<_Value, _HashFcn, _EqualKey, _Alloc> _Self;
  //Specific iterator traits creation
  typedef _STLP_PRIV::_UnorderedMultisetTraitsT<_Value> _UnorderedMultisetTraits;
public:
  typedef hashtable<_Value, _Value, _HashFcn,
                    _UnorderedMultisetTraits, _STLP_PRIV::_Identity<_Value>, _EqualKey, _Alloc> _Ht;

  typedef typename _Ht::key_type key_type;
  typedef typename _Ht::value_type value_type;
  typedef typename _Ht::hasher hasher;
  typedef typename _Ht::key_equal key_equal;

  typedef typename _Ht::size_type size_type;
  typedef typename _Ht::difference_type difference_type;
  typedef typename _Ht::pointer       pointer;
  typedef typename _Ht::const_pointer const_pointer;
  typedef typename _Ht::reference reference;
  typedef typename _Ht::const_reference const_reference;

  typedef typename _Ht::iterator iterator;
  typedef typename _Ht::const_iterator const_iterator;
  typedef typename _Ht::local_iterator local_iterator;
  typedef typename _Ht::const_local_iterator const_local_iterator;

  typedef typename _Ht::allocator_type allocator_type;

  hasher hash_function() const { return _M_ht.hash_funct(); }
  key_equal key_eq() const { return _M_ht.key_eq(); }
  allocator_type get_allocator() const { return _M_ht.get_allocator(); }

private:
  _Ht _M_ht;
  _STLP_KEY_TYPE_FOR_CONT_EXT(key_type)

public:
  explicit unordered_multiset(size_type __n = 100, const hasher& __hf = hasher(),
                              const key_equal& __eql = key_equal(),
                              const allocator_type& __a = allocator_type())
    : _M_ht(__n, __hf, __eql, __a) {}

  unordered_multiset(__move_source<_Self> src)
    : _M_ht(__move_source<_Ht>(src.get()._M_ht)) {}

  template <class _InputIterator>
  unordered_multiset(_InputIterator __f, _InputIterator __l,
                     size_type __n = 100, const hasher& __hf = hasher(),
                     const key_equal& __eql = key_equal(),
                     const allocator_type& __a = allocator_type())
    : _M_ht(__n, __hf, __eql, __a)
  { _M_ht.insert_equal(__f, __l); }

  _Self& operator = (const _Self& __other)
  { _M_ht = __other._M_ht; return *this; }

  size_type size() const { return _M_ht.size(); }
  size_type max_size() const { return _M_ht.max_size(); }
  bool empty() const { return _M_ht.empty(); }
  void swap(_Self& hs) { _M_ht.swap(hs._M_ht); }

  iterator begin() { return _M_ht.begin(); }
  iterator end() { return _M_ht.end(); }
  const_iterator begin() const { return _M_ht.begin(); }
  const_iterator end() const { return _M_ht.end(); }

  iterator insert(const value_type& __obj)
  { return _M_ht.insert_equal(__obj); }
  iterator insert(const_iterator /*__hint*/, const value_type& __obj)
  { return _M_ht.insert_equal(__obj); }
  template <class _InputIterator>
  void insert(_InputIterator __f, _InputIterator __l)
  { _M_ht.insert_equal(__f, __l); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  iterator find(const _KT& __key) { return _M_ht.find(__key); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  const_iterator find(const _KT& __key) const { return _M_ht.find(__key); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type count(const _KT& __key) const { return _M_ht.count(__key); }

  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<iterator, iterator> equal_range(const _KT& __key)
  { return _M_ht.equal_range(__key); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  pair<const_iterator, const_iterator> equal_range(const _KT& __key) const
  { return _M_ht.equal_range(__key); }

  size_type erase(const key_type& __key) {return _M_ht.erase(__key); }
  void erase(const_iterator __it) { _M_ht.erase(__it); }
  void erase(const_iterator __f, const_iterator __l) { _M_ht.erase(__f, __l); }
  void clear() { _M_ht.clear(); }

  size_type bucket_count() const { return _M_ht.bucket_count(); }
  size_type max_bucket_count() const { return _M_ht.max_bucket_count(); }
  size_type bucket_size(size_type __n) const { return _M_ht.elems_in_bucket(__n); }
  _STLP_TEMPLATE_FOR_CONT_EXT
  size_type bucket(const _KT& __k) const { return _M_ht.bucket(__k); }
  local_iterator begin(size_type __n) { return _M_ht.begin(__n); }
  local_iterator end(size_type __n) { return _M_ht.end(__n); }
  const_local_iterator begin(size_type __n) const { return _M_ht.begin(__n); }
  const_local_iterator end(size_type __n) const { return _M_ht.end(__n); }

  float load_factor() const { return _M_ht.load_factor(); }
  float max_load_factor() const { return _M_ht.max_load_factor(); }
  void max_load_factor(float __val) { _M_ht.max_load_factor(__val); }
  void rehash(size_type __hint) { _M_ht.rehash(__hint); }
};

#define _STLP_TEMPLATE_HEADER template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
#define _STLP_TEMPLATE_CONTAINER unordered_set<_Value,_HashFcn,_EqualKey,_Alloc>

#include <stl/_relops_hash_cont.h>

#undef _STLP_TEMPLATE_CONTAINER
#define _STLP_TEMPLATE_CONTAINER unordered_multiset<_Value,_HashFcn,_EqualKey,_Alloc>
#include <stl/_relops_hash_cont.h>

#undef _STLP_TEMPLATE_CONTAINER
#undef _STLP_TEMPLATE_HEADER

// Specialization of insert_iterator so that it will work for unordered_set
// and unordered_multiset.

template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
struct __move_traits<unordered_set<_Value, _HashFcn, _EqualKey, _Alloc> > :
  _STLP_PRIV::__move_traits_aux<typename unordered_set<_Value, _HashFcn, _EqualKey, _Alloc>::_Ht>
{};

template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
struct __move_traits<unordered_multiset<_Value, _HashFcn, _EqualKey, _Alloc> > :
  _STLP_PRIV::__move_traits_aux<typename unordered_multiset<_Value, _HashFcn, _EqualKey, _Alloc>::_Ht>
{};

template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
class insert_iterator<unordered_set<_Value, _HashFcn, _EqualKey, _Alloc> > {
protected:
  typedef unordered_set<_Value, _HashFcn, _EqualKey, _Alloc> _Container;
  _Container* container;
public:
  typedef _Container          container_type;
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  insert_iterator(_Container& __x) : container(&__x) {}
  insert_iterator(_Container& __x, typename _Container::iterator)
    : container(&__x) {}
  insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __val) {
    container->insert(__val);
    return *this;
  }
  insert_iterator<_Container>& operator*() { return *this; }
  insert_iterator<_Container>& operator++() { return *this; }
  insert_iterator<_Container>& operator++(int) { return *this; }
};

template <class _Value, class _HashFcn, class _EqualKey, class _Alloc>
class insert_iterator<unordered_multiset<_Value, _HashFcn, _EqualKey, _Alloc> > {
protected:
  typedef unordered_multiset<_Value, _HashFcn, _EqualKey, _Alloc> _Container;
  _Container* container;
  typename _Container::iterator iter;
public:
  typedef _Container          container_type;
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;

  insert_iterator(_Container& __x) : container(&__x) {}
  insert_iterator(_Container& __x, typename _Container::iterator)
    : container(&__x) {}
  insert_iterator<_Container>&
  operator=(const typename _Container::value_type& __val) {
    container->insert(__val);
    return *this;
  }
  insert_iterator<_Container>& operator*() { return *this; }
  insert_iterator<_Container>& operator++() { return *this; }
  insert_iterator<_Container>& operator++(int) { return *this; }
};

}

#endif /* _STLP_INTERNAL_UNORDERED_SET_H */

// Local Variables:
// mode:C++
// End:
