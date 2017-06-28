# generateGSLfiles.py
# 
# created 22.06.17
# 
# autor: Sebastian Buerger @ surgiTAIX AG
# 
# This file is used to generate SimpleTypesMappings.h / ~.cpp, ConvertFromCDM.h / ~.cpp and ConvertToCDM.h / .cpp for the OSCLibrary
#
# to make changes in the generated files please edit the corresponding *_beginning, *_ending files


from lxml import etree
from io import StringIO, BytesIO

# typedefs
class CppTypdefStringBuilder(object):
    
    def __init__(self):
        ## init basetype_map for converting xsd-basetypes to cpp-basetypes
        # if a type is unknown the compiler throws a KeyError!
        self.__basetype_map = basetype_map
        self.__content = ''
    
    def addTypedef(self, simpleType_name, baseTypeName_xsd):
        self.__content = self.__content + 'typedef ' + self.__basetype_map[baseTypeName_xsd] + ' ' + simpleType_name + ';\n';
         
    def getCppTypedefString(self):
        return self.__content + '\n\n'
        
# enums
class CppEnumClassBuilder(object):
    
    def __init__(self, simpleType_name):
        self.__content = 'enum class ' + simpleType_name + '\n{\n'
        
    def appendEnumEntry(self, enum_name):
        self.__content = self.__content + '\t' + enum_name + ',\n'
        
    def getEnumClassAsString(self):
        return self.__content[:-2] + '\n};\n\n'
    
# EnumToStringClass declarations
class CppEnumToStringClassDeclarationBuilder(object):
    
    def __init__(self):
        self.__content = 'class EnumToString {\npublic:\n'
        
    def addConvertFunctionDeclarationForSimpleType(self, simpleType_name):
        self.__content = self.__content + '\tstatic std::string convert(' + simpleType_name + ' source);\n'
    
    def getEnumToStringClassDeclarationAsString(self):
        return self.__content + '};\n\n';
    
# EnumToStringClass definition
class CppEnumToStringClassDefinitionBuilder(object):
    
    def __init__(self,simpleType_name):
        self.__simpleType_name = simpleType_name
        self.__content = 'std::string EnumToString::convert(' + self.__simpleType_name + ' source) {\n\tswitch (source) {\n'
        
    def addConvertFunctionDefinitionForSimpleType(self,enum_name):
        self.__content = self.__content + '\t\tcase ' + self.__simpleType_name + '::' + enum_name + ': return \"' + enum_name + '\"\n';
        
    def getEnumToStringClassDefinitionsAsString(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__simpleType_name + '\");\n}\n\n'

# ConvertFromCDM header
class CppConvertFromCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.__content = ''
        
    def addType(self, type_name):
        self.__content = self.__content + '\tstatic ' + type_name +' convert(const CDM::' + type_name + ' & source);\n'
        
    def getCoverterFunctionsDeclarationsAsString(self):
        return self.__content


# Separate class for EnumConverterFunctions for ConvertFromCDM
# basetypes do not need any conversion
class CppConvertFromCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, type_name):
        self.__type_name = type_name
        self.__content = self.__type_name + ' ConvertFromCDM::convert(const CDM::' + self.__type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.__content = self.__content + '\t\tcase CDM::' + self.__type_name +  '::' + enum_name +': return ' + self.__type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__type_name + '\");\n}\n\n'
        

# ConvertFromCDM definition
class CppConvertFromCDMClassDefinitionBuilder(object):
    def __init__(self):
        self.__enums = ''
        self.__includes = ''
        self.__complex = ''
    
    def addComplexType(self, type_name):
        self.__complex = self.__complex + type_name + 'ConvertFromCDM::convert(const CDM::' + type_name +' & source) {\n\treturn ' + type_name + '(source);\n}\n\n'
        self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ type_name + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexTypeFuctionsAsString(self):
        return self.__complex
    
# ConvertToCDM header - simpleTypes only. complex types are transformed only in the definition via template method
class CppConvertToCDMClassDeclarationBuilder(object):
    def __init__(self):
        self.__content = ''
        
    def addType(self, type_name):
        self.__content = self.__content + '\tstatic CDM::' + type_name +' convert(const ' + type_name + ' & source);\n'
        
    def getCoverterFunctionsDeclarationsAsString(self):
        return self.__content

    
# Separate class for EnumConverterFunctions for ConvertToCDM
# basetypes do not need any conversion
class CppConvertToCDMClassEnumConverterFunctionBuilder(object):    
    def __init__(self, type_name):
        self.__type_name = type_name
        self.__content = 'CDM::' + self.__type_name + ' ConvertToCDM::convert(const ' + self.__type_name + ' & source) {\n\tswitch (source) {\n'
    
    def addConvertEnumEntry(self, enum_name):
        self.__content = self.__content + '\t\tcase ' + self.__type_name +  '::' + enum_name +': return CDM::' + self.__type_name + '::' + enum_name + ';\n'
        
    def getEnumConverterFunction(self):
        return self.__content + '\t}\n\tthrow std::runtime_error(\"Illegal value for ' + self.__type_name + '\");\n}\n\n'
    

# ConvertToCDM definition
class CppConvertToCDMClassDefinitionBuilder(object):
    def __init__(self):
        self.__enums = ''
        self.__includes = ''
        self.__complex = ''
    
    def addComplexType(self, type_name):
        self.__complex = self.__complex + 'template\nstd::unique_ptr<typename ' + type_name + '::WrappedType> ConvertToCDM::convert(const '+ type_name + '&source);\n\n'
        self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ type_name + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexAsString(self):
        return self.__complex

class GSLClassBuilder(object):    
    
    def __init__(self, class_name, parent_name, abstract_string):
        self.__includes = ''
        self.__properties = ''
        self.__propertylists = ''
        self.__typedefs = ''
        self.__classdeclaration = '\t<class name = \"' + class_name + '\" parent = \"' + parent_name + '\" abstract = \"' + abstract_string + '\">\n'
        
    def addInclude(self,complexType_name):
        self.__includes = self.__includes + '\t\t<include path = \"OSCLib/Data/OSCP/MDIB/' + complexType_name + '.h\" />\n'
        
    def addProperty(self, property_name, property_type, optionality_string):
        self.__properties = self.__properties + '\t\t<property name = \"' + property_name + '\" type = \"' + property_type + '\" optional = \"' + optionality_string + '\" />\n'
    
    def addPropertyList(self, property_name, property_type):
        # automatically names nameServeral attaching a 's' to property_name
        self.__propertylists = self.__propertylists + '\t\t<propertyList nameSingle = \"' + property_name + '\" nameSeveral = \"' + property_name + 's\" type = \"' + property_type + '\" />\n'
        
    def addTypedef(self, typedef_name, typedef_type):
        self.__typedefs = self.__typedefs + '\t\t<typedef name = \"' + typedef_name + '\" type = \"' + typedef_type + '\" />\n'

    def getGSLClassAsString(self):
        return self.__classdeclaration + self.__includes + self.__typedefs + self.__properties + self.__propertylists + '\t</class>\n\n' 

# contains the gsl descriptions
class GSLFileBuilder(object):
    def __init__(self):
        self.__content = '<?xml version="1.0"?>\n<classes script = \"generate.gsl\" >\n'

    def addClassAsString(self, class_string):
        self.__content = self.__content + class_string
        
    def getContent(self):
        return self.__content + '</classes>'
    
# MDIB forward declarations
class MDIBDeclacationsBuilder(object):
    def __init__(self):
        self.__content = ''
        
    def addType(self, type_name):
        self.__content = self.__content + '\tclass ' + type_name + ';\n'
        
    def getDeclarationsAsString(self):
        return self.__content

# class: build files
class FileManager(object): 

    def writeToFile(self, filename, stringToWrite):
        with open(filename, 'w') as text_file:
            text_file.write(stringToWrite)
        
    def readFileToStr(self, filename):
        with open(filename, 'r') as myfile:
            data=myfile.read()
            return data



## factories
def make_FileManager():
    l_cppFileBuilder = FileManager()
    return l_cppFileBuilder

def make_CppEnumClassBuilder(simpleType_name):
    l_cppEnumClassBuilder = CppEnumClassBuilder(simpleType_name)
    return l_cppEnumClassBuilder

def make_CppEnumToStringClassBuilder():
    l_cppEnumToStringClassBuilder = CppEnumToStringClassDeclarationBuilder()
    return l_cppEnumToStringClassBuilder

def make_CppTypdefStringBuilder():
    l_cppTypdefStringBuilder = CppTypdefStringBuilder()
    return l_cppTypdefStringBuilder

def make_CppEnumToStringClassDefinitionBuilder(simpleType_name):
    l_cppEnumToStringClassDefinitionbuilder = CppEnumToStringClassDefinitionBuilder(simpleType_name)
    return l_cppEnumToStringClassDefinitionbuilder

def make_CppConvertFromCDMClassDeclarationBuilder():
    l_cppConvertFromCDMClassDeclarationBuilder = CppConvertFromCDMClassDeclarationBuilder()
    return l_cppConvertFromCDMClassDeclarationBuilder

def make_CppConvertFromCDMClassDefinitionBuilder():
    l_cppConvertFromCDMClassDefinitionBuilder = CppConvertFromCDMClassDefinitionBuilder()
    return l_cppConvertFromCDMClassDefinitionBuilder

def make_CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name):
    l_cppConvertFromCDMClassEnumConverterFunctionBuilder = CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name)
    return l_cppConvertFromCDMClassEnumConverterFunctionBuilder

def make_CppConvertToCDMClassDeclarationBuilder():
    l_cppConvertToCDMClassDeclarationBuilder = CppConvertToCDMClassDeclarationBuilder()
    return l_cppConvertToCDMClassDeclarationBuilder

def make_CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name):
    l_cppConvertToCDMClassEnumConverterFunctionBuilder = CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name)
    return l_cppConvertToCDMClassEnumConverterFunctionBuilder
    
def make_CppConvertToCDMClassDefinitionBuilder():
    l_cppConvertToCDMClassDefinitionBuilder = CppConvertToCDMClassDefinitionBuilder()
    return l_cppConvertToCDMClassDefinitionBuilder

def make_GSLFileBuilder():
    l_gslFileBuilder = GSLFileBuilder()
    return l_gslFileBuilder

def make_GSLClassBuilder(class_name, parent_name, abstract_bool):
    l_gslClassBuilder = GSLClassBuilder(class_name, parent_name, abstract_bool)
    return l_gslClassBuilder

def make_MDIBDeclacationsBuilder():
    l_mdibDeclarationsBuilder = MDIBDeclacationsBuilder()
    return l_mdibDeclarationsBuilder

## init
# orientation:https://www.ibm.com/support/knowledgecenter/en/SSGMCP_5.3.0/com.ibm.cics.ts.applicationprogramming.doc/datamapping/dfhws_wsdl2c.html
basetype_map = {'xsd:unsignedLong' : 'unsigned long', 'pm:VersionCounter' : 'unsigned long', 'xsd:string' : 'std::string', 
                'xsd:decimal' : 'double', 'xsd:unsignedInt' : 'unsigned int', 'xsd:QName' : 'std::string', 'xsd:dateTime' : 'char[40]', 'xsd:boolean' : 'bool', 
                'xsd:duration' : 'std::string', 'xsd:language' : 'std::string', 'xsd:anyURI' : 'std::string', 'xsd:int' : 'int' , 'xsd:long' : 'long long' }
simpleTypes_set = set()
complexTypes_set = set()
enumClasses_cppCode = ''
enumToStringClassMethods_cppCode = ''
cppTypdefStringBuilder = make_CppTypdefStringBuilder()
cppEnumToStringClassBuilder = make_CppEnumToStringClassBuilder()
cppConvertFromCDMClassDeclarationBuilder = make_CppConvertFromCDMClassDeclarationBuilder()
cppConvertFromCDMClassDefinitionBuilder = make_CppConvertFromCDMClassDefinitionBuilder()
cppConvertToCDMClassDeclarationBuilder = make_CppConvertToCDMClassDeclarationBuilder()
cppConvertToCDMClassDefinitionBuilder = make_CppConvertToCDMClassDefinitionBuilder()
gslFileBuilder = make_GSLFileBuilder()
mdibDeclacationsBuilder = make_MDIBDeclacationsBuilder()


###
### SimpleTypes
###
print '--- simple types ---'
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    # search for simple type and go deeper
    # orientation: https://stackoverflow.com/questions/12657043/parse-xml-with-lxml-extract-element-value
    for simpleType_node in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        enum_flag = False
        # only take nodes that have an attribute
        for attribute_name in simpleType_node.attrib:
            # get the name of the simple type
            simpleType_name = simpleType_node.attrib[attribute_name] # attribute_name = 'name'
            simpleTypes_set.add(simpleType_name)
            print simpleType_name
            
            # destinguish between enums and basetypes
            # enums
            for enum_node in simpleType_node.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                
                enum_entry = enum_node.attrib['value']
                print 'enum-type>>' + enum_entry
                # enum_Flag is False at the beginning of a new enum class -> reset classes
                if not enum_flag:
                    cppEnumClassBuilder = make_CppEnumClassBuilder(simpleType_name)
                    cppEnumToStringClassBuilder.addConvertFunctionDeclarationForSimpleType(simpleType_name)
                    cppEnumToStringClassDefinitionBuilder = make_CppEnumToStringClassDefinitionBuilder(simpleType_name)
                    cppConvertFromCDMClassEnumConverterFunctionBuilder = make_CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleType_name)
                    cppConvertToCDMClassEnumConverterFunctionBuilder = make_CppConvertToCDMClassEnumConverterFunctionBuilder(simpleType_name)
                    
                # flag as enum
                enum_flag = True
                cppEnumClassBuilder.appendEnumEntry(enum_entry)
                cppEnumToStringClassDefinitionBuilder.addConvertFunctionDefinitionForSimpleType(enum_entry)
                cppConvertFromCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enum_entry)
                cppConvertToCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enum_entry)
                
                
            # basetypes
            if not enum_flag:
                for basetype_node in simpleType_node.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    basetype_name = basetype_node.attrib['base']
                    print 'base-type>>' + basetype_name
                    cppTypdefStringBuilder.addTypedef(simpleType_name, basetype_name)
                
            # append code for each enum class
            if enum_flag:
                enumClasses_cppCode = enumClasses_cppCode + cppEnumClassBuilder.getEnumClassAsString()
                enumToStringClassMethods_cppCode = enumToStringClassMethods_cppCode + cppEnumToStringClassDefinitionBuilder.getEnumToStringClassDefinitionsAsString()
                cppConvertFromCDMClassDeclarationBuilder.addType(simpleType_name)
                cppConvertFromCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertFromCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
                cppConvertToCDMClassDeclarationBuilder.addType(simpleType_name)
                cppConvertToCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertToCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
                
                
            

###
### ComplexTypes
###
print '--- complexTypes ---'

## write all complex types to set -> later needed to add include file for entries of complexType
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        for attribute_name in complexType_node.attrib:
            # get name
            complexType_name = complexType_node.attrib[attribute_name]
            complexTypes_set.add(complexType_name)
        
# analyse complex types
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        for attribute_name in complexType_node.attrib:
            # get name
            complexType_name = complexType_node.attrib[attribute_name]
            
            ### non-gsl files
            # add to ConverterClasses
            cppConvertFromCDMClassDefinitionBuilder.addComplexType(complexType_name)
            cppConvertFromCDMClassDeclarationBuilder.addType(complexType_name)
            cppConvertToCDMClassDefinitionBuilder.addComplexType(complexType_name)
            # add to mdib-fws
            mdibDeclacationsBuilder.addType(complexType_name)
            
            
            ### gsl-file
            ###
            ### structure analysis 
            # parent handling
            hasParents = False
            for complexTypeParent_node in complexType_node.xpath('./*/xsd:extension', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                hasParents = True
                for parentAttribute_name in complexTypeParent_node.attrib:
                    parentName_xsd = complexTypeParent_node.attrib[parentAttribute_name]
                    # get rid of the namespace prefix
                    parentName = parentName_xsd[(parentName_xsd.index(':')+1):]
            
            if not hasParents:
                parentName = 'NULL'
                
            # abstracts
            # consider only those types abstract that are named that way:
            abstractType_bool =  (complexType_name.find('Abstract') != -1)
            if abstractType_bool:
                abstract_string = 'true'
            else:
                abstract_string = 'false'
            
            glsClassBuilder = make_GSLClassBuilder(complexType_name, parentName, abstract_string)
            print complexType_name + ', parent= ' + parentName + ', abstract= ' + abstract_string

            ## depending on the occurence, the datatyps fields for xsd:elements are defined
            for element_node in complexType_node.xpath('.//xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                # check if element is a valid node by checking if attr. name exists
                if 'name' in element_node.attrib:
                    element_name = element_node.attrib['name']
                    if 'type' in element_node.attrib:
                        elem_type_xsd = element_node.attrib['type']
                        # get rid of the namespace prefix
                        elem_type = elem_type_xsd[(elem_type_xsd.index(':')+1):]
                        
                        # check if linked to a complexType -> include is necessary
                        if elem_type in complexTypes_set:
                            isLinkedTo = 'complexType'
                            glsClassBuilder.addInclude(elem_type)
                        elif elem_type in simpleTypes_set:
                            isLinkedTo = 'simpleType'
                        else:
                            isLinkedTo = 'baseType'                            
                            # check if datatype is a basetype -> transform in case of
                            # this is done after the checking for the complexTypes to assure that the compiler complains when a new unknown basetype occurs
                            elem_type = basetype_map[elem_type_xsd]
                        
                        # element + max occurence = unbounded -> propertyList
                        if 'maxOccurs' in element_node.attrib:
                            if element_node.attrib['maxOccurs'] == 'unbounded':
                                glsClassBuilder.addPropertyList(element_name, elem_type)
                                print '>> PropertyList: ' + element_name + ', type= ' + elem_type
                        
                        else:
                            # element + !maxoccurence + min occurence = 0 -> optional property
                            if 'minOccurs' in element_node.attrib:
                                if element_node.attrib['minOccurs'] == '0':
                                    elem_optional = 'true'

                            # element, without min/max occurence entry -> min=max=1 -> non-optional property
                            else: 
                                elem_optional = 'false'
                        
                            # add class
                            glsClassBuilder.addProperty(element_name, elem_type, elem_optional)
                            print '>> Element -> Property: ' + element_name + ', type= ' + elem_type + ', optional= ' + elem_optional + ', linkedToComplexType= ' + isLinkedTo
            
            # add attributes entries -> attributes are properties  
            for attribute_node in complexType_node.xpath('.//xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                # check if element is a valid node by checking if attr. name exists
                if 'name' in attribute_node.attrib:
                    attribute_name = attribute_node.attrib['name']
                    if 'type' in attribute_node.attrib:                    
                        attribute_type_xsd = attribute_node.attrib['type']
                        # get rid of the namespace prefix
                        attribute_type = attribute_type_xsd[(attribute_type_xsd.index(':')+1):]
                        
                        # check if linked to a complexType -> include is necessary
                        if attribute_type in complexTypes_set:
                            isLinkedTo = 'complexType'
                            glsClassBuilder.addInclude(attribute_type)
                        elif attribute_type in simpleTypes_set:
                            isLinkedTo = 'simpleType'
                        else:
                            isLinkedTo = 'baseType'                            
                            # check if datatype is a basetype -> transform in case of
                            # this is done after the checking for the complexTypes to assure that the compiler complains when a new unknown basetype occurs
                            attribute_type = basetype_map[attribute_type_xsd]
                        
                        optionality_string = 'false'
                        if 'use' in attribute_node.attrib:
                            if attribute_node.attrib['use'] == 'optional':
                                optionality_string = 'true'
                            
                        # add class
                        glsClassBuilder.addProperty(attribute_name, attribute_type, optionality_string)
                        print '>> Attribute -> Property: ' + attribute_name + ', type= ' + attribute_type + ', optional= ' + optionality_string + ', linkedToComplexType= ' + isLinkedTo
                            
                            
                                
                                
            # add class to fileBuilderClass
            gslFileBuilder.addClassAsString(glsClassBuilder.getGSLClassAsString())
            
            
                ##
                ## what to do with extensions: <xsd:element ref="ext:Extension" minOccurs="0"/> 
                ##

# build SimpleTypesMapping.h 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.hxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.h', contentBeginning + cppTypdefStringBuilder.getCppTypedefString() + enumClasses_cppCode  + cppEnumToStringClassBuilder.getEnumToStringClassDeclarationAsString() + contentEnding)

#build SimpleTypesMapping.cpp 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.cxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.cpp', contentBeginning + enumToStringClassMethods_cppCode + contentEnding)

#build ConvertFromCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertFromCDM.h', contentBeginning + cppConvertFromCDMClassDeclarationBuilder.getCoverterFunctionsDeclarationsAsString() + contentEnding)

#build ConvertFromCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertFromCDMClassDefinitionBuilder.getComplexTypeFuctionsAsString() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + cppConvertToCDMClassDeclarationBuilder.getCoverterFunctionsDeclarationsAsString() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', cppConvertToCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertToCDMClassDefinitionBuilder.getComplexAsString() + contentEnding)


## complex types
#build complexTypesGSLformated.xml
cppFileBuilder = make_FileManager()
cppFileBuilder.writeToFile('complexTypesGSLformated.xml', gslFileBuilder.getContent())

#build mdib-fwd.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('MDIB-fwd_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('MDIB-fwd_ending.hxx')
cppFileBuilder.writeToFile('MDIB-fwd.h', contentBeginning + mdibDeclacationsBuilder.getDeclarationsAsString() + contentEnding)



