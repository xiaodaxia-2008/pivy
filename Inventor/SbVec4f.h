#ifndef COIN_SBVEC4F_H
#define COIN_SBVEC4F_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for  more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <stdio.h>

#include <Inventor/SbBasic.h>

class SbVec3f;

#ifdef __PIVY__
%{
static void
convert_SbVec4f_array(PyObject *input, float temp[4])
{
  if (PySequence_Check(input)) {
	if (!PyArg_ParseTuple(input, "fff", temp+0, temp+1, temp+2, temp+3)) {
	  PyErr_SetString(PyExc_TypeError, "sequence must contain 4 float elements");
	  return;
	}
	return;
  } else {
	PyErr_SetString(PyExc_TypeError, "expected a sequence.");
    return;
  }  
}
%}

%typemap(in) float v[4] (float temp[4]) {
  convert_SbVec4f_array($input, temp);
  $1 = temp;
}

/* for some strange reason the %apply directive below doesn't work 
 * for this class on getValue(f,f,f,f)...
 * created this typemap for getValue(void) instead as a workaround.
 */
%typemap(out) float * {
  int i;
  $result = PyTuple_New(4);
  
  for (i=0; i<4; i++) {
	PyTuple_SetItem($result, i, PyFloat_FromDouble((double)(*($1+i))));
  }
}

%rename(SbVec4f_vec) SbVec4f::SbVec4f(const float v[4]);
%rename(SbVec4f_ffff) SbVec4f::SbVec4f(const float x, const float y, const float z, const float w);

%feature("shadow") SbVec4f::SbVec4f %{
def __init__(self,*args):
   if len(args) == 1:
      self.this = apply(_pivy.new_SbVec4f_vec,args)
      self.thisown = 1
      return
   elif len(args) == 4:
      self.this = apply(_pivy.new_SbVec4f_ffff,args)
      self.thisown = 1
      return
   self.this = apply(_pivy.new_SbVec3f,args)
   self.thisown = 1
%}

%rename(setValue_ffff) SbVec4f::setValue(const float x, const float y, const float z, const float w);

%feature("shadow") SbVec4f::setValue(const float vec[4]) %{
def setValue(*args):
   if len(args) == 5:
      return apply(_pivy.SbVec4f_setValue_ffff,args)
   return apply(_pivy.SbVec4f_setValue,args)
%}

%apply float *OUTPUT { float& x, float& y, float& z, float& w };
#endif

class COIN_DLL_API SbVec4f {
public:
  SbVec4f(void);
  SbVec4f(const float v[4]);
  SbVec4f(const float x, const float y, const float z, const float w);
  float dot(const SbVec4f& v) const;
  SbBool equals(const SbVec4f& v, const float tolerance) const;
  void getReal(SbVec3f& v) const;
  const float* getValue(void) const;
#ifndef __PIVY__
  void getValue(float& x, float& y, float& z, float& w) const;
#endif
  float length(void) const;
  void negate(void);
  float normalize(void);
  SbVec4f& setValue(const float v[4]);
  SbVec4f& setValue(const float x, const float y, const float z,
                    const float w);
#ifdef __PIVY__
  // swig - add a method for wrapping c++ operator[] access
  %extend {
	float __getitem__(int i) {
	  return (self->getValue())[i];
	}
  }
#else
  float& operator [](const int i);
  const float& operator [](const int i) const;
#endif
  SbVec4f& operator *=(const float d);
  SbVec4f& operator /=(const float d);
  SbVec4f& operator +=(const SbVec4f& u);
  SbVec4f& operator -=(const SbVec4f& u);
  SbVec4f operator-(void) const;
  friend COIN_DLL_API SbVec4f operator *(const SbVec4f& v, const float d);
  friend COIN_DLL_API SbVec4f operator *(const float d, const SbVec4f& v);
  friend COIN_DLL_API SbVec4f operator /(const SbVec4f& v, const float d);
  friend COIN_DLL_API SbVec4f operator +(const SbVec4f& v1, const SbVec4f& v2);
  friend COIN_DLL_API SbVec4f operator -(const SbVec4f& v1, const SbVec4f& v2);
  friend COIN_DLL_API int operator ==(const SbVec4f& v1, const SbVec4f& v2);
  friend COIN_DLL_API int operator !=(const SbVec4f& v1, const SbVec4f& v2);

  void print(FILE * fp) const;

private:
  float vec[4];
};

#ifdef __PIVY__
%clear float& x, float& y, float& z, float& w;
#endif

COIN_DLL_API SbVec4f operator *(const SbVec4f& v, const float d);
COIN_DLL_API SbVec4f operator *(const float d, const SbVec4f& v);
COIN_DLL_API SbVec4f operator /(const SbVec4f& v, const float d);
COIN_DLL_API SbVec4f operator +(const SbVec4f& v1, const SbVec4f& v2);
COIN_DLL_API SbVec4f operator -(const SbVec4f& v1, const SbVec4f& v2);
COIN_DLL_API int operator ==(const SbVec4f& v1, const SbVec4f& v2);
COIN_DLL_API int operator !=(const SbVec4f& v1, const SbVec4f& v2);

#endif // !COIN_SBVEC4F_H
