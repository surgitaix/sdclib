# generateGSLfiles.py
# 
# created 22.06.17
# 
# autor: Sebastian Buerger @ surgiTAIX AG
# 
# This file is used to generate SimpleTypesMappings.h / ~.cpp, ConvertFromCDM.h / ~.cpp and ConvertToCDM.h / .cpp for the OSCLibrary
#
# to make changes in the generated files please edit the corresponding *_beginning, *_ending files

# use this switch to generate a template for the Default.h/.cpp 
# the according default values have to be filled in by hand. 
# thus be careful not to overwrite an already filled out file
SWITCH_ENABLE_DEFAULT_CPP_GENERATION = 1

from lxml import etree
from io import StringIO, BytesIO
import copy

from pyclassgenerators.simpletypeshandling import CppTypdefStringBuilder, CppEnumClassBuilder, CppEnumToStringClassDeclarationBuilder, CppEnumToStringClassDefinitionBuilder
from pyclassgenerators.converterclasses import CppConvertFromCDMClassDeclarationBuilder, CppConvertFromCDMClassEnumConverterFunctionBuilder, CppConvertFromCDMClassDefinitionBuilder, CppConvertToCDMClassDeclarationBuilder, CppConvertToCDMClassEnumConverterFunctionBuilder, CppConvertToCDMClassDefinitionBuilder
from pyclassgenerators.gslmacrogenerator import GSLClassBuilder, GSLFileBuilder
from pyclassgenerators.xmlnodeparser import ComplexTypeNodeParser,  SimpleTypeNodeParser
from pyclassgenerators.defaultgenerator import DefaultDeclarationBuilder, DefaultDefinitionBuilder
##
## Setup
##
xsdFiles = {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd'), etree.parse('../datamodel/DICOMDeviceDescription.xsd') };

#xsd:duration' : 'std::string''
# mapping of basetypes:xsd -> cpp
g_basetype_map = {'xsd:unsignedLong' : 'unsigned long long', 'pm:VersionCounter' : 'unsigned long long', 'xsd:string' : 'std::string', 
                'xsd:decimal' : 'double', 'xsd:unsignedInt' : 'unsigned int', 'xsd:QName' : 'xml_schema::Qname', 'xsd:dateTime' : 'xml_schema::DateTime', 'xsd:boolean' : 'bool', 
                'xsd:duration' : 'xml_schema::Duration', 'xsd:language' : 'xml_schema::Language', 'xsd:anyURI' : 'xml_schema::Uri', 'xsd:int' : 'int' , 'xsd:long' : 'long long', 
                'pm:HandleRef' : 'std::string' , 'xsd:dateTime xsd:date xsd:gYearMonth xsd:gYear' : 'std::string', 'xsd:IDREFS' : 'xml_schema::Idrefs', 'xsd:ID' : 'xml_schema::Id', 
                'xsd:unsignedShort' : 'unsigned short'}
# apiInterfaces_global structure: 1. Classname, 2. name of typedef 3. type of typedef
# if list consists of more than three values the following entries refer to additional typdefs listed in the same 
# manner; 4. name of typedef, 5. type of typedef ...
g_apiInterfaces = [
                           ['EnsembleContextDescriptor', 'StateType', 'EnsembleContextState'],
                           ['LocationContextDescriptor', 'StateType', 'LocationContextState'],
                           ['NumericMetricDescriptor', 'StateType', 'NumericMetricState'],
                           ['OperatorContextDescriptor', 'StateType', 'OperatorContextState'],
                           ['PatientContextDescriptor', 'StateType', 'PatientContextState'],
                           ['RealTimeSampleArrayMetricDescriptor', 'StateType', 'RealTimeSampleArrayMetricState'],
                           ['StringMetricDescriptor', 'StateType', 'StringMetricState'],
                           ['WorkflowContextDescriptor', 'StateType', 'WorkflowContextState'],
                           
                           ['AlertConditionState', 'DescriptorType', 'AlertConditionDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertConditionStateHandler'],
                           ['AlertSignalState', 'DescriptorType', 'AlertSignalDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertSignalStateHandler'],
                           ['AlertSystemState', 'DescriptorType', 'AlertSystemDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertSystemStateHandler'],
                           ['ClockState', 'DescriptorType', 'ClockDescriptor'],
                           ['EnsembleContextState', 'DescriptorType', 'EnsembleContextDescriptor'],
                           ['EnumStringMetricState', 'DescriptorType', 'EnumStringMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderEnumStringMetricStateHandler'],
                           ['MdsState', 'DescriptorType', 'MdsDescriptor', 'ProviderHandlerType', 'OSCPProviderMdsStateHandler'],
                           ['LimitAlertConditionState', 'DescriptorType', 'LimitAlertConditionDescriptor', 'ProviderHandlerType', 'OSCPProviderLimitAlertConditionStateHandler'],
                           ['LocationContextState', 'DescriptorType', 'LocationContextDescriptor'],
                           ['NumericMetricState', 'DescriptorType', 'NumericMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderNumericMetricStateHandler'],
                           ['OperatorContextState', 'DescriptorType', 'OperatorContextDescriptor'],
                           ['RealTimeSampleArrayMetricState', 'DescriptorType', 'RealTimeSampleArrayMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderRealTimeSampleArrayMetricStateHandler'],
                           ['StringMetricState', 'DescriptorType', 'StringMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderStringMetricStateHandler'],
                           ['PatientContextState', 'DescriptorType', 'PatientContextDescriptor'],
                           ['WorkflowContextState', 'DescriptorType', 'WorkflowContextDescriptor']
                           ] 
# only applicable for complex types
g_customImplList = ['ChannelDescriptor', 'MdDescription', 'MdState', 'ScoDescriptor', 'AlertSystemDescriptor']

# MDIB forward declarations
class MDIBDeclacationsBuilder(object):
    def __init__(self):
        self.__content = ''
        
    def addType(self, typeName):
        self.__content = self.__content + '\tclass ' + typeName + ';\n'
        
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

class ClassBuilderForwarding(object):
    def __init__(self):
        self.__cppEnumToStringClassBuilder =  CppEnumToStringClassDeclarationBuilder()
        self.__cppConvertFromCDMClassDeclarationBuilder = CppConvertFromCDMClassDeclarationBuilder()
        self.__cppConvertFromCDMClassDefinitionBuilder = CppConvertFromCDMClassDefinitionBuilder(g_basetype_map)
        self.__cppConvertToCDMClassDeclarationBuilder = CppConvertToCDMClassDeclarationBuilder()
        self.__cppConvertToCDMClassDefinitionBuilder = CppConvertToCDMClassDefinitionBuilder()
        self.__cppTypdefStringBuilder = CppTypdefStringBuilder(g_basetype_map)
        self.__defaultDeclarationBuilder = DefaultDeclarationBuilder()
        self.__defaultDefinitionBuilder = DefaultDefinitionBuilder()
        self.__mdibDeclacationsBuilder = MDIBDeclacationsBuilder()
        self.__cppEnumClassBuilder = None
        self.__cppEnumToStringClassDefinitionBuilder = None
        self.__cppConvertFromCDMClassEnumConverterFunctionBuilder = None
        self.__cppConvertToCDMClassEnumConverterFunctionBuilder = None
        self.__enumClasses_cppCode = ''
        self.__enumToStringClassMethods_cppCode = ''
                    
    def addComplexType(self, complexTypeName, abstractBool, requiredProperties_list):
        self.__cppConvertFromCDMClassDefinitionBuilder.addComplexType(complexTypeName, abstractBool)
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(complexTypeName, abstractBool)
        self.__cppConvertToCDMClassDefinitionBuilder.addComplexType(complexTypeName, abstractBool)
        self.__mdibDeclacationsBuilder.addType(complexTypeName)
        self.__defaultDeclarationBuilder.addFunction(complexTypeName,abstractBool, requiredProperties_list)
        self.__defaultDefinitionBuilder.addFunction(complexTypeName,abstractBool,requiredProperties_list)
        
    def addItemlist(self, simpleTypeName, itemListName):
        self.__cppTypdefStringBuilder.addItemListTypedef(simpleTypeName, itemListName)
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName, False)
        self.__cppConvertFromCDMClassDefinitionBuilder.addItemList(simpleTypeName)
        self.__cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addItemList(simpleTypeName)
        
    def addBasetype(self, simpleTypeName, basetypeType):
        self.__cppTypdefStringBuilder.addTypedef(simpleTypeName, basetypeType)
    
    def initEnumClassBuilders(self, simpleTypeName):
        self.__cppEnumToStringClassBuilder.addConvertFunctionDeclarationForSimpleType(simpleTypeName)
        self.__cppEnumClassBuilder = CppEnumClassBuilder(simpleTypeName)
        self.__cppEnumToStringClassDefinitionBuilder = CppEnumToStringClassDefinitionBuilder(simpleTypeName)
        self.__cppConvertFromCDMClassEnumConverterFunctionBuilder =  CppConvertFromCDMClassEnumConverterFunctionBuilder(simpleTypeName)
        self.__cppConvertToCDMClassEnumConverterFunctionBuilder =  CppConvertToCDMClassEnumConverterFunctionBuilder(simpleTypeName)

    def addEnumEntry(self,enumEntry):
        self.__cppEnumClassBuilder.appendEnumEntry(enumEntry)
        self.__cppEnumToStringClassDefinitionBuilder.addConvertFunctionDefinitionForSimpleType(enumEntry)
        self.__cppConvertFromCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enumEntry)
        self.__cppConvertToCDMClassEnumConverterFunctionBuilder.addConvertEnumEntry(enumEntry)

    def finalizeEnumClass(self,simpleTypeName):
        self.__enumClasses_cppCode = self.__enumClasses_cppCode + self.__cppEnumClassBuilder.getEnumClassAsString()
        self.__enumToStringClassMethods_cppCode = self.__enumToStringClassMethods_cppCode + self.__cppEnumToStringClassDefinitionBuilder.getEnumToStringClassDefinitionsAsString()
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName, False)
        self.__cppConvertFromCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(self.__cppConvertFromCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
        self.__cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(self.__cppConvertToCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())

    def getSimpleTypesMappingDeclaration(self):
        return self.__cppTypdefStringBuilder.getCppTypedefString() + self.__enumClasses_cppCode  + self.__cppEnumToStringClassBuilder.getEnumToStringClassDeclarationAsString()
    
    def getSimpleTypesMappingDefintion(self):
        return self.__enumToStringClassMethods_cppCode
    
    def getConvertFromCDMDeclaration(self):
        return  self.__cppConvertFromCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + self.__cppConvertFromCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations()
    
    # get includes
    def getConvertFromCDMDefinitionIncludes(self):
        return self.__cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString();
    
    # get the rest of the class definition
    def getConvertFromCDMDefinition(self):
        return self.__cppConvertFromCDMClassDefinitionBuilder.getBaseTypesAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getComplexTypeFuctionsAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getItemListAsString()
    
    def getConvertToCDMDeclaration(self):
        return self.__cppConvertToCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + self.__cppConvertToCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations()
    
    # get includes
    def getConvertToCDMDefinitionIncludes(self):
        return self.__cppConvertToCDMClassDefinitionBuilder.getIncludesAsString()
    
    # get rest
    def getConvertToCDMDefinition(self):
        return self.__cppConvertToCDMClassDefinitionBuilder.getBasetype() + self.__cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + self.__cppConvertToCDMClassDefinitionBuilder.getComplexAsString() + self.__cppConvertToCDMClassDefinitionBuilder.getItemListAsString()
        
    def getMdibForward(self):
        return self.__mdibDeclacationsBuilder.getDeclarationsAsString()    
    
    def getBaseTypeCounter(self):
        return self.__cppTypdefStringBuilder.getBasetypeCounter()
    
    def getItemListCoutner(self):
        return self.__cppTypdefStringBuilder.getItemListCounter()
    
    def getEnumCounter(self):
        return self.__cppEnumToStringClassBuilder.getEnumCounter()
    
    def getDefaultDeclarationGenerator(self):
        return self.__defaultDeclarationBuilder.getContent()
    
    
    def getDefaultDefinitionIncludesGenerator(self):
        return self.__defaultDefinitionBuilder.getIncludes()
    
    # get rest of definition
    def getDefaultDefinitionGenerator(self):
        return self.__defaultDefinitionBuilder.getContent()
    
    
## factories
def make_FileManager():
    l_cppFileBuilder = FileManager()
    return l_cppFileBuilder

## init
simpleTypes_set = set()
g_complexTypes_set = set()
gslFileBuilder =  GSLFileBuilder()
g_embeddedAttributesNamesList = list()
classBuilderForwarder = ClassBuilderForwarding()
g_attributeGroupsNodesMap = {}
## abstract class hirachy handling, no multiple inheritance
requiredPropertiesOfClass = {} # one level of abstraction
requiredFieldsFromAllAncestors = {} # all level of abstraction
classParent_map = {}
dependencyRepresentation = list(list()) # each inner list represents one path in the inheritance tree



###
### SimpleTypes
###
print '--- simple types ---'
for tree in xsdFiles:
    for simpleTypeNode in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        simpleTypeNodeParser = SimpleTypeNodeParser(classBuilderForwarder, simpleTypes_set)
        simpleTypeNodeParser.parseSimpleTypeNode(simpleTypeNode)
###
### ComplexTypes
###
print '--- complexTypes ---'

## write all complex types to set -> later needed to add include file for entries of complexType
for tree in xsdFiles:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        if 'name' in complexType_node.attrib:
            ##> put inside gslclass!!
            g_complexTypes_set.add(complexType_node.attrib['name'])

#
## attributeGroups
#
# save attribute groups to dereference them later
# for tree in xsdFiles:
#     for attribGroup_node in tree.xpath('//xsd:attributeGroup', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
#         # node with a name define the content of an attribute group
#         if 'name' in attribGroup_node.attrib:
#             g_attributeGroupsNodesMap[attribGroup_node.attrib['name']] = attribGroup_node
#             
# # replace referenced nodes in tree
# for tree in xsdFiles:
#     for attribGroup_node in tree.xpath('//xsd:attributeGroup', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
#         # node with a name define the content of an attribute group
#         if 'ref' in attribGroup_node.attrib:
#             # get rid of the namespace prefix
#             nodeReference_xsd = attribGroup_node.attrib['ref']
#             nodeReference = nodeReference_xsd[(nodeReference_xsd.index(':')+1):]
#             copyOfNode = copy.deepcopy(g_attributeGroupsNodesMap[nodeReference])
#             
#             for element in copyOfNode.getchildren():
#                 attribGroup_node.getparent().append(element)
#             
#             attribGroup_node.getparent().remove(attribGroup_node)
#         
#         print etree.tostring(tree)

#
## inheritance
#
## save inheritance and required fields to maps
complexNodeParser = ComplexTypeNodeParser(simpleTypes_set, g_complexTypes_set, g_basetype_map, g_apiInterfaces, g_customImplList, simpleTypeNodeParser)

for tree in xsdFiles:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):                
           
        complexNodeParser.parseComplexTypeNode(complexType_node)
        
        ### build map for required fiels (= XSD constructor arguments)
        requiredPropertiesOfClass[complexNodeParser.getComplexTypeName()] = complexNodeParser.getRequiredProperties()
        classParent_map[complexNodeParser.getComplexTypeName()] = complexNodeParser.getParentTypeName()
        

## build dependency lists, representing inheritance 
for item in classParent_map.keys():
    dependencyPath = []
    child = item
    while (classParent_map[child] != 'NULL'):
        dependencyPath.append(classParent_map[child])
        child = classParent_map[child]
    #if dependencyPath:   
    dependencyPath = [item] + dependencyPath
    dependencyRepresentation.append(dependencyPath)
        
## build a new list of required fields  for the classes containing all inherited fields
for dependencyPath in dependencyRepresentation:
    requiredFieldsAlongPath_list = list()
    for item in dependencyPath:
        requiredFieldsAlongPath_list = requiredPropertiesOfClass[item] + requiredFieldsAlongPath_list 
    requiredFieldsFromAllAncestors[dependencyPath[0]] = requiredFieldsAlongPath_list


# analyse complex types
complexNodeParser.resetParser()
complexNodeParser = ComplexTypeNodeParser(simpleTypes_set, g_complexTypes_set, g_basetype_map, g_apiInterfaces, g_customImplList, simpleTypeNodeParser)

for tree in xsdFiles:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        
        complexNodeParser.parseComplexTypeNode(complexType_node)
        
        requiredFields_list = complexNodeParser.getRequiredProperties()
        if complexNodeParser.getParentTypeName() != 'NULL':
            requiredFields_list = requiredFieldsFromAllAncestors[complexNodeParser.getParentTypeName()] + requiredFields_list
        
        ### non-gsl files
        # add to ConverterClasses
        classBuilderForwarder.addComplexType(complexNodeParser.getComplexTypeName(), complexNodeParser.getAbstractBool(), requiredFields_list)         
        # GSL files
        if complexNodeParser.getGSLClassBuilder():
            gslFileBuilder.addClassAsString(complexNodeParser.getGSLClassBuilder().getGSLClassAsString())

        

# build SimpleTypesMapping.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.hxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.h', contentBeginning + classBuilderForwarder.getSimpleTypesMappingDeclaration() + contentEnding)

#build SimpleTypesMapping.cpp 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.cxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.cpp', contentBeginning + classBuilderForwarder.getSimpleTypesMappingDefintion() + contentEnding)

#build ConvertFromCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertFromCDM.h', contentBeginning + classBuilderForwarder.getConvertFromCDMDeclaration()+ contentEnding)

#build ConvertFromCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', classBuilderForwarder.getConvertFromCDMDefinitionIncludes() + contentBeginning +  classBuilderForwarder.getConvertFromCDMDefinition() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + classBuilderForwarder.getConvertToCDMDeclaration() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', classBuilderForwarder.getConvertToCDMDefinitionIncludes() + contentBeginning + classBuilderForwarder.getConvertToCDMDefinition()+ contentEnding)


## complex types
#build complexTypesGSLformated.xml
cppFileBuilder = make_FileManager()
cppFileBuilder.writeToFile('complexTypesGSLformated.xml', gslFileBuilder.getContent())

#build mdib-fwd.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('MDIB-fwd_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('MDIB-fwd_ending.hxx')
cppFileBuilder.writeToFile('MDIB-fwd.h', contentBeginning + classBuilderForwarder.getMdibForward() + contentEnding)


## always build defaults.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('Defaults_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('Defaults_ending.hxx')
cppFileBuilder.writeToFile('Defaults.h', contentBeginning + classBuilderForwarder.getDefaultDeclarationGenerator() + contentEnding)


if SWITCH_ENABLE_DEFAULT_CPP_GENERATION:
    ## build defaults.cpp
    cppFileBuilder = make_FileManager()
    contentBeginning = cppFileBuilder.readFileToStr('Defaults_beginning.cxx')
    contentEnding = cppFileBuilder.readFileToStr('Defaults_ending.cxx')
    cppFileBuilder.writeToFile('Defaults.cpp', classBuilderForwarder.getDefaultDefinitionIncludesGenerator() + contentBeginning + classBuilderForwarder.getDefaultDefinitionGenerator() + contentEnding)


# ---- Statistics -----
print ' '
print '----- Inheritance representation -----'
print ' '
print dependencyRepresentation
print requiredFieldsFromAllAncestors


# ---- Statistics -----
print ' '
print '----- Statistics -----'
print ' '
print 'Basetypes: ' + str(classBuilderForwarder.getBaseTypeCounter())
print 'ItemLists: ' + str(classBuilderForwarder.getItemListCoutner())
print 'Enums: ' + str(classBuilderForwarder.getEnumCounter())
print 'ComplexTypes: ' + str(gslFileBuilder.getNumOfClasses())
