// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef EXTENSION_POINT_HXX
#define EXTENSION_POINT_HXX

#include "ExtensionPoint-fwd.hxx"

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include <memory>    // ::std::unique_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search
#include <utility>   // std::move

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

namespace CDM
{
  class ExtensionType: public ::xml_schema::Type
  {
    public:
    // Constructors.
    //
    ExtensionType ();

    ExtensionType (const ::xercesc::DOMElement& e,
                   ::xml_schema::Flags f = 0,
                   ::xml_schema::Container* c = 0);

    ExtensionType (const ExtensionType& x,
                   ::xml_schema::Flags f = 0,
                   ::xml_schema::Container* c = 0);

    virtual ExtensionType*
    _clone (::xml_schema::Flags f = 0,
            ::xml_schema::Container* c = 0) const;

    virtual 
    ~ExtensionType ();

    // Implementation.
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::Flags);

    protected:
  };
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace CDM
{
  // Parse a URI or a local file.
  //

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& uri,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& uri,
             ::xml_schema::ErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& uri,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  // Parse std::istream.
  //

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xml_schema::ErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& id,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& id,
             ::xml_schema::ErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& id,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  // Parse xercesc::InputSource.
  //

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& is,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& is,
             ::xml_schema::ErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& is,
             ::xercesc::DOMErrorHandler& eh,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  // Parse xercesc::DOMDocument.
  //

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::xercesc::DOMDocument& d,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
             ::xml_schema::Flags f = 0,
             const ::xml_schema::Properties& p = ::xml_schema::Properties ());
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace CDM
{
  // Serialize to std::ostream.
  //

  void
  Extension (::std::ostream& os,
             const ::CDM::ExtensionType& x, 
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  void
  Extension (::std::ostream& os,
             const ::CDM::ExtensionType& x, 
             ::xml_schema::ErrorHandler& eh,
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  void
  Extension (::std::ostream& os,
             const ::CDM::ExtensionType& x, 
             ::xercesc::DOMErrorHandler& eh,
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  // Serialize to xercesc::XMLFormatTarget.
  //

  void
  Extension (::xercesc::XMLFormatTarget& ft,
             const ::CDM::ExtensionType& x, 
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  void
  Extension (::xercesc::XMLFormatTarget& ft,
             const ::CDM::ExtensionType& x, 
             ::xml_schema::ErrorHandler& eh,
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  void
  Extension (::xercesc::XMLFormatTarget& ft,
             const ::CDM::ExtensionType& x, 
             ::xercesc::DOMErrorHandler& eh,
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             const ::std::string& e = "UTF-8",
             ::xml_schema::Flags f = 0);

  // Serialize to an existing xercesc::DOMDocument.
  //

  void
  Extension (::xercesc::DOMDocument& d,
             const ::CDM::ExtensionType& x,
             ::xml_schema::Flags f = 0);

  // Serialize to a new xercesc::DOMDocument.
  //

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
  Extension (const ::CDM::ExtensionType& x, 
             const ::xml_schema::NamespaceInfomap& m = ::xml_schema::NamespaceInfomap (),
             ::xml_schema::Flags f = 0);

  void
  operator<< (::xercesc::DOMElement&, const ExtensionType&);
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // EXTENSION_POINT_HXX
