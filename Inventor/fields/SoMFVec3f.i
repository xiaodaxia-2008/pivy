%{
static void
convert_SoMFVec3f_array(PyObject *input, int len, float temp[][3])
{
  int i,j;

  for (i=0; i<len; i++) {
    PyObject *oi = PySequence_GetItem(input,i);

    for (j=0; j<3; j++) {
      PyObject *oj = PySequence_GetItem(oi,j);

      if (PyNumber_Check(oj)) {
        temp[i][j] = (float) PyFloat_AsDouble(oj);
      } else {
        PyErr_SetString(PyExc_ValueError,"Sequence elements must be numbers");
        free(temp);       
        return;
      }
    }
  }
  return;
}
%}

%typemap(in) const float xyz[][3] (float (*temp)[3]) {
  int len;

  if (PySequence_Check($input)) {
    len = PySequence_Length($input);

    temp = (float (*)[3]) malloc(len*3*sizeof(float));
    convert_SoMFVec3f_array($input, len, temp);
  
    $1 = temp;
  } else {
    PyErr_SetString(PyExc_TypeError, "expected a sequence.");
    $1 = NULL;
  }
}

// Free the list 
%typemap(freearg) const float xyz[][3] {
  if($1) delete[] $1;
}

%typemap(in) const float xyz[3] (float temp[3]) {
  convert_SbVec3f_array($input, temp);
  $1 = temp;
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const float xyz[3] {
  void *ptr;
  $1 = (PySequence_Check($input) && SWIG_ConvertPtr($input, &ptr, $descriptor(SoMFVec3f *), 0) == -1) ? 1 : 0;
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const float xyz[][3] {
  if(PySequence_Check($input) && PySequence_Size($input) > 0 ){
    PyObject * obj = PySequence_GetItem($input,0);
    void *ptr;
    if( SWIG_ConvertPtr(obj, &ptr, $descriptor(SbVec3f *), 0) == -1)
      $1 = 1;
    else
      $1 = 0;
  }
  else
    $1 = 0;
}

%typemap(in) const SbVec3f *newvals {
  int len;

  if (PySequence_Check($input)) {
    len = PySequence_Length($input);
    if( len > 0 ) {
      $1 = new SbVec3f[len];
      for( int i = 0; i < len; i++ ) {
          SbVec3f * VecPtr = NULL;
          PyObject * item = PyList_GetItem($input,i);
          SWIG_ConvertPtr(item, (void **) &VecPtr, $1_descriptor, 1);
          if( VecPtr != NULL )
            $1[i] = *VecPtr;
      }
    }
    else 
      $1 = NULL;
  } else {
    PyErr_SetString(PyExc_TypeError, "expected a sequence.");
  }
}

// Free the list 
%typemap(freearg) const SbVec3f *newvals {
  if($1) delete[] $1;
}

%typemap(typecheck,precedence=SWIG_TYPECHECK_POINTER) const SbVec3f *newvals {
  if(PySequence_Check($input)) {
    if(PySequence_Size($input) == 0)
      $1 = 1;
    else {
      PyObject * obj = PySequence_GetItem($input,0);
      void *ptr;
      if( SWIG_ConvertPtr(obj, &ptr, $descriptor(SbVec3f *), 0) != -1)
        $1 = 1;
      else
        $1 = 0;
    }
  }
  else
    $1 = 0;
}

%feature("shadow") SoMFVec3f::setValues %{
def setValues(*args):
   if len(args) == 2:
      return _coin.SoMFVec3f_setValues(args[0],0,len(args[1]),args[1])
   elif len(args) == 3:
      return _coin.SoMFVec3f_setValues(args[0],args[1],len(args[2]),args[2])
   return _coin.SoMFVec3f_setValues(*args)
%}

%ignore SoMFVec3f::getValues(const int start) const;

%typemap(in,numinputs=0) int & len (int temp) {
   $1 = &temp;
   *$1 = 0;
}

%typemap(argout) int & len {
  Py_XDECREF($result);   /* Blow away any previous result */
  $result = PyList_New(*$1);
  if(result) {
    for(int i = 0; i < *$1; i++){
      SbVec3f * Vec3fPtr = new SbVec3f( result[i] );
      PyObject * obj = SWIG_NewPointerObj(Vec3fPtr, $descriptor(SbVec3f *), 1);
      PyList_SetItem($result, i, obj);
    }
  }
}

%rename(getValues) SoMFVec3f::__getValuesHelper__;

%extend SoMFVec3f {
  const SbVec3f & __getitem__(int i) { return (*self)[i]; }
  void  __setitem__(int i, const SbVec3f & value) { self->set1Value(i, value); }  
  void setValue( const SoMFVec3f * other ){ *self = *other; }
  const SbVec3f * __getValuesHelper__(int & len, int i = 0) {
    if( i < 0 || i >= self->getNum())
      return NULL;
    len = self->getNum() - i;
    return self->getValues(i);
  }
}
