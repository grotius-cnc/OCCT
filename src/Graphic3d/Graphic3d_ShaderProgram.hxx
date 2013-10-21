// Created on: 2013-09-20
// Created by: Denis BOGOLEPOV
// Copyright (c) 2013 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

#ifndef _Graphic3d_ShaderProgram_HeaderFile
#define _Graphic3d_ShaderProgram_HeaderFile

#include <Graphic3d_ShaderObject_Handle.hxx>
#include <Graphic3d_ShaderProgram_Handle.hxx>
#include <Graphic3d_ShaderVariable.hxx>
#include <NCollection_Sequence.hxx>

//! List of shader objects.
typedef NCollection_Sequence<Handle(Graphic3d_ShaderObject)> Graphic3d_ShaderObjectList;

//! List of custom uniform shader variables.
typedef NCollection_Sequence<Handle(Graphic3d_ShaderVariable)> Graphic3d_ShaderVariableList;

//! This class is responsible for managing shader programs.
class Graphic3d_ShaderProgram : public Standard_Transient
{
public:

  //! Creates new empty program object.
  Standard_EXPORT Graphic3d_ShaderProgram();

  //! Releases resources of program object.
  Standard_EXPORT virtual ~Graphic3d_ShaderProgram();

  //! Releases resources of program object.
  Standard_EXPORT void Destroy() const;

  //! Checks if the program object is valid or not.
  Standard_EXPORT virtual Standard_Boolean IsDone() const;

  //! Returns unique ID used to manage resource in graphic driver.
  const TCollection_AsciiString& GetId() const { return myID; }

  //! Attaches shader object to the program object.
  Standard_EXPORT Standard_Boolean AttachShader (const Handle(Graphic3d_ShaderObject)& theShader);

  //! Detaches shader object from the program object.
  Standard_EXPORT Standard_Boolean DetachShader (const Handle(Graphic3d_ShaderObject)& theShader);

  //! Returns list of attached shader objects.
  const Graphic3d_ShaderObjectList& ShaderObjects() const { return myShaderObjects; }

  //! Returns list of custom uniform variables.
  const Graphic3d_ShaderVariableList& Variables() const { return myVariables; }

  //! Pushes custom uniform variable to the program.
  template<class T>
  Standard_Boolean PushVariable (const TCollection_AsciiString& theName,
                                 const T&                       theValue);

  //! Removes all custom uniform variables from the program.
  Standard_EXPORT void ClearVariables();

public:

  DEFINE_STANDARD_RTTI (Graphic3d_ShaderProgram)

private:

  TCollection_AsciiString      myID;            //!< The unique identifier of program object.
  Graphic3d_ShaderObjectList   myShaderObjects; //!< the list of attached shader objects.
  Graphic3d_ShaderVariableList myVariables;     //!< the list of custom uniform variables.

};

// =======================================================================
// function : PushVariable
// purpose  : Pushes custom uniform variable to the program
// =======================================================================
template<class T> inline
Standard_Boolean Graphic3d_ShaderProgram::PushVariable (const TCollection_AsciiString& theName,
                                                        const T& theValue)
{
  Handle(Graphic3d_ShaderVariable) aVariable = Graphic3d_ShaderVariable::Create (theName, theValue);
  if (aVariable.IsNull() || !aVariable->IsDone())
  {
    return Standard_False;
  }

  myVariables.Append (aVariable);
  return Standard_True;
}

#endif
