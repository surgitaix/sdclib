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

from pyclassgenerators.simpletypeshandling import CppTypdefStringBuilder, CppEnumClassBuilder, CppEnumToStringClassDeclarationBuilder, CppEnumToStringClassDefinitionBuilder
from pyclassgenerators.converterclasses import CppConvertFromCDMClassDeclarationBuilder, CppConvertFromCDMClassEnumConverterFunctionBuilder, CppConvertFromCDMClassDefinitionBuilder, CppConvertToCDMClassDeclarationBuilder, CppConvertToCDMClassEnumConverterFunctionBuilder, CppConvertToCDMClassDefinitionBuilder
from pyclassgenerators.gslmacrogenerator import GSLClassBuilder, GSLFileBuilder

##
## Setup
##
# mapping of basetypes:xsd -> cpp
g_basetype_map = {'xsd:unsignedLong' : 'unsigned long', 'pm:VersionCounter' : 'unsigned long', 'xsd:string' : 'std::string', 
                'xsd:decimal' : 'double', 'xsd:unsignedInt' : 'unsigned int', 'xsd:QName' : 'xml_schema::Qname', 'xsd:dateTime' : 'xml_schema::DateTime', 'xsd:boolean' : 'bool', 
                'xsd:duration' : 'xml_schema::Duration', 'xsd:language' : 'xml_schema::Language', 'xsd:anyURI' : 'std::string', 'xsd:int' : 'int' , 'xsd:long' : 'long long', 
                'pm:HandleRef' : 'std::string' , 'xsd:dateTime xsd:date xsd:gYearMonth xsd:gYear' : 'std::string'}
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
                           
                           ['AlertConditionState', 'DescriptorType', 'AlertConditionDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertConditionStateHandler', 'ConsumerHandlerType', 'OSCPConsumerAlertConditionStateHandler'],
                           ['AlertSignalState', 'DescriptorType', 'AlertSignalDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertSignalStateHandler', 'ConsumerHandlerType', 'OSCPConsumerAlertSignalStateHandler'],
                           ['AlertSystemState', 'DescriptorType', 'AlertSystemDescriptor', 'ProviderHandlerType', 'OSCPProviderAlertSignalStateHandler', 'ConsumerHandlerType', 'OSCPConsumerAlertSignalStateHandler'],
                           ['ClockState', 'DescriptorType', 'ClockDescriptor'],
                           ['EnsembleContextState', 'DescriptorType', 'EnsembleContextDescriptor'],
                           ['EnumStringMetricState', 'DescriptorType', 'EnumStringMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderEnumStringMetricStateHandler', 'ConsumerHandlerType', 'OSCPConsumerEnumStringMetricStateHandler'],
                           ['MdsState', 'DescriptorType', 'MdsDescriptor', 'ProviderHandlerType', 'OSCPProviderHydraMDSStateHandler'],
                           ['LimitAlertConditionState', 'DescriptorType', 'EnumStringMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderEnumStringMetricStateHandler', 'ConsumerHandlerType', 'OSCPConsumerLimitAlertConditionStateHandler'],
                           ['LocationContextState', 'DescriptorType', 'LocationContextDescriptor'],
                           ['NumericMetricState', 'DescriptorType', 'NumericMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderNumericMetricStateHandler', 'ConsumerHandlerType', 'OSCPConsumerNumericMetricStateHandler'],
                           ['OperatorContextState', 'DescriptorType', 'OperatorContextDescriptor'],
                           ['RealTimeSampleArrayMetricState', 'DescriptorType', 'RealTimeSampleArrayMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderRealTimeSampleArrayMetricStateHandler', 'ConsumerHandlerType', 'OSCPConsumerRealTimeSampleArrayMetricStateHandler'],
                           ['StringMetricState', 'DescriptorType', 'StringMetricDescriptor', 'ProviderHandlerType', 'OSCPProviderStringMetricStateHandler', 'ConsumerHandlerType', 'OSCPConsumerStringMetricStateHandler'],
                           ['PatientContextState', 'DescriptorType', 'PatientContextDescriptor'],
                           ['WorkflowContextState', 'DescriptorType', 'WorkflowContextDescriptor']
                           ] 

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
        self.__mdibDeclacationsBuilder = MDIBDeclacationsBuilder()
        self.__cppEnumClassBuilder = None
        self.__cppEnumToStringClassDefinitionBuilder = None
        self.__cppConvertFromCDMClassEnumConverterFunctionBuilder = None
        self.__cppConvertToCDMClassEnumConverterFunctionBuilder = None
        self.__enumClasses_cppCode = ''
        self.__enumToStringClassMethods_cppCode = ''
                    
    def addComplexType(self, complexTypeName, abstractBool):
        self.__cppConvertFromCDMClassDefinitionBuilder.addComplexType(complexTypeName, abstractBool)
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(complexTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addComplexType(complexTypeName, abstractBool)
        self.__mdibDeclacationsBuilder.addType(complexTypeName)
        
    def addItemlist(self, simpleTypeName, itemListName):
        self.__cppTypdefStringBuilder.addItemListTypedef(simpleTypeName, itemListName)
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertFromCDMClassDefinitionBuilder.addItemList(simpleTypeName)
        self.__cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addItemList(simpleTypeName)
        
        
    def addBasetype(self, simpleTypeName, basetypeType):
        self.__cppTypdefStringBuilder.addTypedef(simpleTypeName, basetypeType)
        self.__cppConvertFromCDMClassDeclarationBuilder.addBasetype(simpleTypeName)
        self.__cppConvertFromCDMClassDefinitionBuilder.addBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDeclarationBuilder.addBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addBasetype(simpleTypeName)
    
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
        self.__cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertFromCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(self.__cppConvertFromCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
        self.__cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        self.__cppConvertToCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(self.__cppConvertToCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())

    def getSimpleTypesMappingDeclaration(self):
        return self.__cppTypdefStringBuilder.getCppTypedefString() + self.__enumClasses_cppCode  + self.__cppEnumToStringClassBuilder.getEnumToStringClassDeclarationAsString()
    
    def getSimpleTypesMappingDefintion(self):
        return self.__enumToStringClassMethods_cppCode
    
    def getConvertFromCDMDeclaration(self):
        return  self.__cppConvertFromCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + self.__cppConvertFromCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations()
    
    def getConvertFromCDMDefinition(self):
        return self.__cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getBaseTypesAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getComplexTypeFuctionsAsString() + self.__cppConvertFromCDMClassDefinitionBuilder.getItemListAsString()
    
    def getConvertToCDMDeclaration(self):
        return self.__cppConvertToCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + self.__cppConvertToCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations()
    
    def getConvertToCDMDefinition(self):
        return self.__cppConvertToCDMClassDefinitionBuilder.getIncludesAsString() + self.__cppConvertToCDMClassDefinitionBuilder.getBasetype() + self.__cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + self.__cppConvertToCDMClassDefinitionBuilder.getComplexAsString() + self.__cppConvertToCDMClassDefinitionBuilder.getItemListAsString()
        
    def getMdibForward(self):
        return self.__mdibDeclacationsBuilder.getDeclarationsAsString()    
    
    def getBaseTypeCounter(self):
        return self.__cppTypdefStringBuilder.getBasetypeCounter()
    
    def getItemListCoutner(self):
        return self.__cppTypdefStringBuilder.getItemListCounter()
    
    def getEnumCounter(self):
        return self.__cppEnumToStringClassBuilder.getEnumCounter()

class SimpleTypeNodeParser(object):
    def __init__(self, classBuilderForwarder, simpleTypes_set):
        self.__classBuilderForwarder = classBuilderForwarder
        self.__simpleTypes_set = simpleTypes_set 
        
    def parseSimpleTypeNode(self, simpleTypeNode):
        # get the name of the simple type
        enumInit_flag = False
        isEnum = False
        if 'name' in simpleTypeNode.attrib:
            simpleTypeName = simpleTypeNode.attrib['name'] # attribute_name = 'name'
            self.__simpleTypes_set.add(simpleTypeName)
            print simpleTypeName
            
            # destinguish between enums and basetypes/itemlists
            # enums
            for enumNode in simpleTypeNode.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):    
                enumEntry = enumNode.attrib['value']
                print 'enum-type>>' + enumEntry
                # enum_Flag is False at the beginning of a new enum class -> reset classes
                if not enumInit_flag:
                    enumInit_flag = True
                    isEnum = True
                    self.__classBuilderForwarder.initEnumClassBuilders(simpleTypeName)

                self.__classBuilderForwarder.addEnumEntry(enumEntry)
            
            # append code for each enum class
            if isEnum:
                self.__classBuilderForwarder.finalizeEnumClass(simpleTypeName)
            
            # non enums
            if not isEnum:
                # basetypes
                for baseTypeNode in simpleTypeNode.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'base' in baseTypeNode.attrib:
                        basetypeType = baseTypeNode.attrib['base']
                        print 'base-type>>' + basetypeType
                        self.__classBuilderForwarder.addBasetype(simpleTypeName,basetypeType)
                        
                # item lists
                for itemListNode in simpleTypeNode.xpath('./xsd:list', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'itemType' in itemListNode.attrib:
                        itemListName = itemListNode.attrib['itemType']
                        print 'itemList-type>>' + itemListName
                        self.__classBuilderForwarder.addItemlist(simpleTypeName, itemListName)
                        
                for unionTypeNode in simpleTypeNode.xpath('./xsd:union', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'memberTypes' in unionTypeNode.attrib:
                        # handle as basetype
                        basetypeType = unionTypeNode.attrib['memberTypes']
                        self.__classBuilderForwarder.addBasetype(simpleTypeName,basetypeType)
                        print 'union-type>>' + basetypeType
                    
# parses one complex type node
# build the gslFile, available via getGslClassBuilder
class ComplexTypeNodeParser(object):
    #static list of embedded nodes against double treatment
    __embeddedNodesNamesList = list()
    
    def __init__(self, simpleTypes_set, complexTypes_set, basetype_map, apiInterface, simpleTypeNodeParser):
        # complexTypes_set: a set of all existing complexTypes. Complex types get own C++ Classes, thus they need to be references
        # simpleTypes_set: a set of all existing simpleTypes. simple types are all connected in simpleTypesMapping.cpp and are referenced to all complex classes by gsl script
        self.__simpleTypes_set = simpleTypes_set
        self.__complexTypes_set = complexTypes_set
        self.__basetype_map = basetype_map
        self.__apiInterface = apiInterface 
        self.__simpleTypeNodeParser = simpleTypeNodeParser
        self.__complexTypeName = ''
        self.__abstract_bool = False
        self.__parentTypeName = 'NULL'
        # classes are None from the beginning. Check before usage
        self.__gslClassBuilder = None
           
    def parseComplexTypeNode(self, cTNode_xpath):
        # only take nodes that have a 'name' attribute
        if 'name' in cTNode_xpath.attrib:
            # get name
            self.__complexTypeName = complexType_node.attrib['name']
            ### structure analysis 
            hasParents = False
            # TODO : attribute == base check!!!
            for complexTypeParent_node in cTNode_xpath.xpath('./*/xsd:extension', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                hasParents = True
                for parentAttribute_name in complexTypeParent_node.attrib:
                    parentName_xsd = complexTypeParent_node.attrib[parentAttribute_name]
                    # get rid of the namespace prefix
                    self.__parentTypeName = parentName_xsd[(parentName_xsd.index(':')+1):]

            # consider only those types abstract that are named that way:
            self.__abstract_bool =  (self.__complexTypeName.find('Abstract') != -1)
             # gsl-file
            self.__gslClassBuilder = GSLClassBuilder(self.__complexTypeName, self.__parentTypeName, self.__abstract_bool, self.__apiInterface)      
            print 'debug: ' + self.__complexTypeName + ', parent= ' + self.__parentTypeName + ', abstract= ' + str(self.__abstract_bool)

            ## elements
            # elements have to be parsed before the attribute to provide a list of all embedded attributes
            elements_list = cTNode_xpath.xpath('./xsd:sequence/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})   + cTNode_xpath.xpath('./xsd:all/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:choice/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:complexContent/xsd:extension/xsd:sequence/xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
            for elementNode in elements_list:
                if 'name' in elementNode.attrib:
                    if not elementNode.attrib['name'] in ComplexTypeNodeParser.__embeddedNodesNamesList:
                        try:
                            element_name, element_type = self.__parseProperty(elementNode)
                            self.__parseElementsOccurenceAndOptionality(elementNode, element_name, element_type)
                        except ValueError as error:
                            print error.args[0]
                
            ## attributes
            attributeNodes = cTNode_xpath.xpath('./xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:complexContent/xsd:extension/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) + cTNode_xpath.xpath('./xsd:simpleContent/xsd:extension/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}) 
            for attribute_node in attributeNodes:
                # do not consider embedded attributes from this node
                if not attribute_node.attrib['name'] in ComplexTypeNodeParser.__embeddedNodesNamesList:
                    try:
                        attribute_name, attribute_type = self.__parseProperty(attribute_node)
                        self.__parseAttributesOptionality(attribute_node, attribute_name, attribute_type)
                    except ValueError as error:
                        print error.args[0]

                        
    
    def __parseProperty(self, xmlNode_xpath):
        # check if element is a valid node by checking if attr. name exists
        if 'name' in xmlNode_xpath.attrib:
            nodeName = xmlNode_xpath.attrib['name']
            if 'type' in xmlNode_xpath.attrib:
                nodeType_xsd = xmlNode_xpath.attrib['type']
                # get rid of the namespace prefix
                nodeType = nodeType_xsd[(nodeType_xsd.index(':')+1):]
                
                # check if linked to a complexType -> include is necessary
                if nodeType in self.__complexTypes_set:
                    self.__gslClassBuilder.addInclude(nodeType)
                elif not (nodeType in self.__simpleTypes_set):
                    # check if datatype is a basetype -> transform in case of
                    # this is done after the checking for the complexTypes to assure that the compiler complains when a new unknown basetype occurs
                    nodeType = self.__basetype_map[nodeType_xsd]
                
                return nodeName, nodeType

            # check for embedded types in elements with no 'type' attribute
            else:
                embeddedComplexTypeNode = xmlNode_xpath.xpath('./xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
                if embeddedComplexTypeNode:
                    # embedded complex classes do not have an own type name, thus named with a Type prefix
                    # add name attribute to embedded type node to convert it in the non-embedded form
                    # since the node is a mutable object this is done at the original node which is going to be parsed the next time.
                    # this approach is more efficient then working with recursion
                    embeddedComplexTypeNode[0].set('name', nodeName)
#                     embeddedComplexTypeNode[0].set('name', nodeName + 'Type')
                    ComplexTypeNodeParser.__embeddedNodesNamesList.append(nodeName)
#                     print 'embedded complex type node created: ' +  nodeName + 'Type'
                    print 'embedded complex type node created: ' +  nodeName
                    return nodeName, nodeName
#                     return nodeName, nodeName + 'Type'
                    
                embeddedSimpleTypeNode = xmlNode_xpath.xpath('./xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
                if embeddedSimpleTypeNode:
#                     embeddedSimpleTypeNode[0].set('name', nodeName + 'Type')
                    embeddedSimpleTypeNode[0].set('name', nodeName)
                    self.__simpleTypeNodeParser.parseSimpleTypeNode(embeddedSimpleTypeNode[0])
                    ComplexTypeNodeParser.__embeddedNodesNamesList.append(nodeName)
                    print 'embedded simple type node created: ' +  nodeName
#                     print 'embedded simple type node created: ' +  nodeName + 'Type'
                    return nodeName, nodeName
#                     return nodeName, nodeName + 'Type'
                
                # Errorcase if control gets here
                raise ValueError('WARNING: Property ' + nodeName + ' has no attribute type defined.') 
        else:
            raise ValueError('WARNING: Property has no attribute name defined.') 
    
    def __parseAttributesOptionality(self, attribute_node, attribute_name, attribute_type):
        optionality_string = 'false'
        if 'use' in attribute_node.attrib:
            if attribute_node.attrib['use'] == 'optional':
                optionality_string = 'true'

        # add class
        self.__gslClassBuilder.addProperty(attribute_name, attribute_type, optionality_string)
        print '>> Attribute -> Property: ' + attribute_name + ', type= ' +  attribute_type + ', optional= ' + optionality_string
                
    def __parseElementsOccurenceAndOptionality(self, element_node, element_name, element_type):
        # depending on the occurence, the datatyp's fields for xsd:elements are defined
        # element + max occurence = unbounded -> propertyList
        if 'maxOccurs' in element_node.attrib:
            if element_node.attrib['maxOccurs'] == 'unbounded':
                self.__gslClassBuilder.addPropertyList(element_name, element_type)
                print '>> PropertyList: ' + element_name + ', type= ' + element_type
        
        else:
            # element + !maxoccurence + min occurence = 0 -> optional property
            if 'minOccurs' in element_node.attrib:
                if element_node.attrib['minOccurs'] == '0':
                    elementOptional = 'true'

            # element, without min/max occurence entry -> min=max=1 -> non-optional property
            else: 
                elementOptional = 'false'       
            # add class
            self.__gslClassBuilder.addProperty(element_name, element_type, elementOptional)
            print '>> Element -> Property: ' + element_name + ', type= ' + element_type + ', optional= ' + elementOptional 

    def getGSLClassBuilder(self):
        return self.__gslClassBuilder

    def getComplexTypeName(self):
        return self.__complexTypeName
    
    def getAbstractBool(self):
        return self.__abstract_bool

    def hasEmbeddedType(self):
        return self.__hasEmbeddedComplexType

    # debug. TODO delete
    def getEmbeddedAttributesNamesList(self):
        return self.__embeddedNodesNamesList
    
    
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


###
### SimpleTypes
###
print '--- simple types ---'
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd') }:
    for simpleTypeNode in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        simpleTypeNodeParser = SimpleTypeNodeParser(classBuilderForwarder, simpleTypes_set)
        simpleTypeNodeParser.parseSimpleTypeNode(simpleTypeNode)
###
### ComplexTypes
###
print '--- complexTypes ---'

## write all complex types to set -> later needed to add include file for entries of complexType
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd')}:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        if 'name' in complexType_node.attrib:
            ##> put inside gslclass!!
            g_complexTypes_set.add(complexType_node.attrib['name'])
        
# analyse complex types
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd')}:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        
        complexNodeParser = ComplexTypeNodeParser(simpleTypes_set, g_complexTypes_set, g_basetype_map, g_apiInterfaces, simpleTypeNodeParser)   
        complexNodeParser.parseComplexTypeNode(complexType_node)
        ### non-gsl files
        # add to ConverterClasses
        classBuilderForwarder.addComplexType(complexNodeParser.getComplexTypeName(), complexNodeParser.getAbstractBool())         
        # GSL files
        if complexNodeParser.getGSLClassBuilder():
            gslFileBuilder.addClassAsString(complexNodeParser.getGSLClassBuilder().getGSLClassAsString())
        print complexNodeParser.getEmbeddedAttributesNamesList()
        

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
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', contentBeginning +  classBuilderForwarder.getConvertFromCDMDefinition() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + classBuilderForwarder.getConvertToCDMDeclaration() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', contentBeginning + classBuilderForwarder.getConvertToCDMDefinition()+ contentEnding)


## complex types
#build complexTypesGSLformated.xml
cppFileBuilder = make_FileManager()
cppFileBuilder.writeToFile('complexTypesGSLformated.xml', gslFileBuilder.getContent())

#build mdib-fwd.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('MDIB-fwd_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('MDIB-fwd_ending.hxx')
cppFileBuilder.writeToFile('MDIB-fwd.h', contentBeginning + classBuilderForwarder.getMdibForward() + contentEnding)


# ---- Statistics -----
print ' '
print '----- Statistics -----'
print ' '
print 'Basetypes: ' + str(classBuilderForwarder.getBaseTypeCounter())
print 'ItemLists: ' + str(classBuilderForwarder.getItemListCoutner())
print 'Enums: ' + str(classBuilderForwarder.getEnumCounter())
print 'ComplexTypes: ' + str(gslFileBuilder.getNumOfClasses())



