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

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "ExtensionPoint.hxx"

namespace CDM
{
  // ExtensionType
  // 
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

#include <xsd/cxx/tree/type-factory-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_factory_plate< 0, char >
  type_factory_plate_init;
}

namespace CDM
{
  // ExtensionType
  //

  ExtensionType::
  ExtensionType ()
  : ::xml_schema::Type ()
  {
  }

  ExtensionType::
  ExtensionType (const ExtensionType& x,
                 ::xml_schema::Flags f,
                 ::xml_schema::Container* c)
  : ::xml_schema::Type (x, f, c)
  {
  }

  ExtensionType::
  ExtensionType (const ::xercesc::DOMElement& e,
                 ::xml_schema::Flags f,
                 ::xml_schema::Container* c)
  : ::xml_schema::Type (e, f | ::xml_schema::Flags::base, c)
  {
    if ((f & ::xml_schema::Flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, false, false);
      this->parse (p, f);
    }
  }

  void ExtensionType::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::Flags)
  {
    for (; p.more_content (); p.next_content (false))
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      break;
    }
  }

  ExtensionType* ExtensionType::
  _clone (::xml_schema::Flags f,
          ::xml_schema::Container* c) const
  {
    return new class ExtensionType (*this, f, c);
  }

  ExtensionType::
  ~ExtensionType ()
  {
  }

  static
  const ::xsd::cxx::tree::type_factory_initializer< 0, char, ExtensionType >
  _xsd_ExtensionType_type_factory_init (
    "ExtensionType",
    "http://p11073-10207/draft7/ext/2017/03/17");
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace CDM
{
  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& u,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& u,
             ::xml_schema::ErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::std::string& u,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::CDM::Extension (isrc, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xml_schema::ErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::CDM::Extension (isrc, h, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::CDM::Extension (isrc, h, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& sid,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::CDM::Extension (isrc, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& sid,
             ::xml_schema::ErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0,
      (f & ::xml_schema::Flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::CDM::Extension (isrc, h, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::std::istream& is,
             const ::std::string& sid,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::CDM::Extension (isrc, h, f, p);
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& i,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& i,
             ::xml_schema::ErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xercesc::InputSource& i,
             ::xercesc::DOMErrorHandler& h,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    return ::std::unique_ptr< ::CDM::ExtensionType > (
      ::CDM::Extension (
        std::move (d), f | ::xml_schema::Flags::own_dom, p));
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (const ::xercesc::DOMDocument& doc,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties& p)
  {
    if (f & ::xml_schema::Flags::keep_dom)
    {
      ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
        static_cast< ::xercesc::DOMDocument* > (doc.cloneNode (true)));

      return ::std::unique_ptr< ::CDM::ExtensionType > (
        ::CDM::Extension (
          std::move (d), f | ::xml_schema::Flags::own_dom, p));
    }

    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
      ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
        "Extension",
        "http://p11073-10207/draft7/ext/2017/03/17",
        &::xsd::cxx::tree::factory_impl< ::CDM::ExtensionType >,
        true, true, e, n, f, 0));

    if (tmp.get () != 0)
    {
      ::std::unique_ptr< ::CDM::ExtensionType > r (
        dynamic_cast< ::CDM::ExtensionType* > (tmp.get ()));

      if (r.get ())
        tmp.release ();
      else
        throw ::xsd::cxx::tree::not_derived< char > ();

      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "Extension",
      "http://p11073-10207/draft7/ext/2017/03/17");
  }

  ::std::unique_ptr< ::CDM::ExtensionType >
  Extension (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
             ::xml_schema::Flags f,
             const ::xml_schema::Properties&)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::Flags::keep_dom) &&
       !(f & ::xml_schema::Flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (f & ::xml_schema::Flags::keep_dom)
      doc.setUserData (::xml_schema::dom::tree_node_key,
                       (c.get () ? &c : &d),
                       0);

    ::std::unique_ptr< ::xsd::cxx::tree::type > tmp (
      ::xsd::cxx::tree::type_factory_map_instance< 0, char > ().create (
        "Extension",
        "http://p11073-10207/draft7/ext/2017/03/17",
        &::xsd::cxx::tree::factory_impl< ::CDM::ExtensionType >,
        true, true, e, n, f, 0));

    if (tmp.get () != 0)
    {

      ::std::unique_ptr< ::CDM::ExtensionType > r (
        dynamic_cast< ::CDM::ExtensionType* > (tmp.get ()));

      if (r.get ())
        tmp.release ();
      else
        throw ::xsd::cxx::tree::not_derived< char > ();

      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "Extension",
      "http://p11073-10207/draft7/ext/2017/03/17");
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/type-serializer-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_serializer_plate< 0, char >
  type_serializer_plate_init;
}

namespace CDM
{
  void
  Extension (::std::ostream& o,
             const ::CDM::ExtensionType& s,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  Extension (::std::ostream& o,
             const ::CDM::ExtensionType& s,
             ::xml_schema::ErrorHandler& h,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::Flags::dont_initialize) == 0);

    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  Extension (::std::ostream& o,
             const ::CDM::ExtensionType& s,
             ::xercesc::DOMErrorHandler& h,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  Extension (::xercesc::XMLFormatTarget& t,
             const ::CDM::ExtensionType& s,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  Extension (::xercesc::XMLFormatTarget& t,
             const ::CDM::ExtensionType& s,
             ::xml_schema::ErrorHandler& h,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  Extension (::xercesc::XMLFormatTarget& t,
             const ::CDM::ExtensionType& s,
             ::xercesc::DOMErrorHandler& h,
             const ::xml_schema::NamespaceInfomap& m,
             const ::std::string& e,
             ::xml_schema::Flags f)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d (
      ::CDM::Extension (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  Extension (::xercesc::DOMDocument& d,
             const ::CDM::ExtensionType& s,
             ::xml_schema::Flags)
  {
    ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (typeid (::CDM::ExtensionType) == typeid (s))
    {
      if (n.name () == "Extension" &&
          n.namespace_ () == "http://p11073-10207/draft7/ext/2017/03/17")
      {
        e << s;
      }
      else
      {
        throw ::xsd::cxx::tree::unexpected_element < char > (
          n.name (),
          n.namespace_ (),
          "Extension",
          "http://p11073-10207/draft7/ext/2017/03/17");
      }
    }
    else
    {
      ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ().serialize (
        "Extension",
        "http://p11073-10207/draft7/ext/2017/03/17",
        e, n, s);
    }
  }

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
  Extension (const ::CDM::ExtensionType& s,
             const ::xml_schema::NamespaceInfomap& m,
             ::xml_schema::Flags f)
  {
    ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d;

    if (typeid (::CDM::ExtensionType) == typeid (s))
    {
      d = ::xsd::cxx::xml::dom::serialize< char > (
        "Extension",
        "http://p11073-10207/draft7/ext/2017/03/17",
        m, f);
    }
    else
    {
      d = ::xsd::cxx::tree::type_serializer_map_instance< 0, char > ().serialize (
        "Extension",
        "http://p11073-10207/draft7/ext/2017/03/17",
        m, s, f);
    }

    ::CDM::Extension (*d, s, f);
    return d;
  }

  void
  operator<< (::xercesc::DOMElement& e, const ExtensionType& i)
  {
    e << static_cast< const ::xml_schema::Type& > (i);
  }

  static
  const ::xsd::cxx::tree::type_serializer_initializer< 0, char, ExtensionType >
  _xsd_ExtensionType_type_serializer_init (
    "ExtensionType",
    "http://p11073-10207/draft7/ext/2017/03/17");
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

