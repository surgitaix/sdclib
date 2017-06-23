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
        self.basetype_map = {'xsd:unsignedLong' : 'unsigned long', 'pm:VersionCounter' : 'unsigned long', 'xsd:string' : 'std::string', 'xsd:decimal' : 'long long', 'xsd:unsignedInt' : 'unsigned int'}
        self.content = ''
    
    def addTypedef(self, simpleType_name, baseTypeName_xsd):
        self.content = self.content + 'typedef ' + self.basetype_map[baseTypeName_xsd] + ' ' + simpleType_name + ';\n';
         
    def getCppTypedefString(self):
        return self.content + '\n\n'
        
# enums
class CppEnumClassBuilder(object):
    def __init__(self, simpleType_name):
        self.content = 'enum class' + simpleType_name + '\n{\n'
        
    def appendEnumEntry(self, enum_name):
        self.content = self.content + '\t' + enum_name + ',\n'
        
    def getEnumClassAsString(self):
        return self.content[:-2] + '\n};\n\n'
    
# declarations
class CppEnumToStringClassBuilder(object):
    def __init__(self):
        self.content = 'class EnumToString {\npublic:\n'
        
    def addConvertFunctionForSimpleType(self, simpleType_name):
        self.content = self.content + '\tstatic static std::string convert(' + simpleType_name + ' source);\n'
    
    def getEnumToStringClassAsString(self):
        return self.content + '};\n\n';
    

# class: build cpp files
class CppFileBuilder(object): 

    def writeToFile(self, filename, stringToWrite):
        with open(filename, 'w') as text_file:
            text_file.write(stringToWrite)
        
    def readFileToStr(self, filename):
        with open(filename, 'r') as myfile:
            data=myfile.read()#.replace('\n', '')
            return data

## factories
def make_CppFileBuilder():
    l_cppFileBuilder = CppFileBuilder()
    return l_cppFileBuilder

def make_CppEnumClassBuilder(simpleType_name):
    l_cppEnumClassBuilder = CppEnumClassBuilder(simpleType_name)
    return l_cppEnumClassBuilder

def make_CppEnumToStringClassBuilder():
    l_cppEnumToStringClassBuilder = CppEnumToStringClassBuilder()
    return l_cppEnumToStringClassBuilder

def make_CppTypdefStringBuilder():
    l_cppTypdefStringBuilder = CppTypdefStringBuilder()
    return l_cppTypdefStringBuilder

## init
enumClasses_cppCode = ''
cppTypdefStringBuilder = make_CppTypdefStringBuilder()
cppEnumToStringClassBuilder = make_CppEnumToStringClassBuilder()



for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/BICEPS_MessageModel.xsd'),  etree.parse('../datamodel/ExtensionPoint.xsd') }:
    # search for simple type and go deeper
    # orientation: https://stackoverflow.com/questions/12657043/parse-xml-with-lxml-extract-element-value
    for simpleType_node in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # get the name of the simple type
        enum_flag = False
        # only take nodes that have an attribute
        for attribute_name in simpleType_node.attrib:
            simpleType_name = simpleType_node.attrib[attribute_name]
            print simpleType_name # attribute_name = 'name'
            
            # destinguish between enums and basetypes
            # enums
            for enum_node in simpleType_node.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                
                enum_entry = enum_node.attrib['value']
                print 'enum-type>>' + enum_entry
                if not enum_flag:
                    cppEnumClassBuilder = make_CppEnumClassBuilder(simpleType_name)
                    cppEnumToStringClassBuilder.addConvertFunctionForSimpleType(simpleType_name)
                    
                # flag as enum
                enum_flag = True
                cppEnumClassBuilder.appendEnumEntry(enum_entry)
                
                
            # basetypes
            if not enum_flag:
                for basetype_node in simpleType_node.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    basetype_name = basetype_node.attrib['base']
                    print 'base-type>>' + basetype_name
                    cppTypdefStringBuilder.addTypedef(simpleType_name, basetype_name)
                    
            if enum_flag:
                enumClasses_cppCode = enumClasses_cppCode + cppEnumClassBuilder.getEnumClassAsString()
            
# build SimpleTypesMapping.h to file
cppFileBuilder = make_CppFileBuilder()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.hxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.h', contentBeginning + cppTypdefStringBuilder.getCppTypedefString() + enumClasses_cppCode  + cppEnumToStringClassBuilder.getEnumToStringClassAsString() + contentEnding)



    



