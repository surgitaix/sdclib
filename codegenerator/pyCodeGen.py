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
        self.__cppEnumClassBuilder = None
        self.__cppEnumToStringClassDefinitionBuilder = None
        self.__cppConvertFromCDMClassEnumConverterFunctionBuilder = None
        self.__cppConvertToCDMClassEnumConverterFunctionBuilder = None
        
    def addBasetype(self):
        pass
    
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
        self.__enumClasses_cppCode = self.__enumClasses_cppCode + cppEnumClassBuilder.getEnumClassAsString()
        enumToStringClassMethods_cppCode = enumToStringClassMethods_cppCode + cppEnumToStringClassDefinitionBuilder.getEnumToStringClassDefinitionsAsString()
        cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        cppConvertFromCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertFromCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
        cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
        cppConvertToCDMClassDefinitionBuilder.addEnumConverterFunctionAsString(cppConvertToCDMClassEnumConverterFunctionBuilder.getEnumConverterFunction())
            
    def addItemlist(self):
        pass

    def addComplexType(self):
        pass

    def getConvertFromCDMClassDeclarationCppCode(self):
        pass
    

def make_CppEnumToStringClassBuilder():
    l_cppEnumToStringClassBuilder = CppEnumToStringClassDeclarationBuilder()
    return l_cppEnumToStringClassBuilder


# parses one complex type node
# build the gslFile, available via getGslClassBuilder
class ComplexTypeNodeParser(object):
    #static list of embedded nodes against double treatment
    __embeddedNodesNamesList = list()
    
    def __init__(self, simpleTypes_set, complexTypes_set, basetype_map, apiInterface):
        # complexTypes_set: a set of all existing complexTypes. Complex types get own C++ Classes, thus they need to be references
        # simpleTypes_set: a set of all existing simpleTypes. simple types are all connected in simpleTypesMapping.cpp and are referenced to all complex classes by gsl script
        self.__simpleTypes_set = simpleTypes_set
        self.__complexTypes_set = complexTypes_set
        self.__basetype_map = basetype_map
        self.__apiInterface = apiInterface 
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
                    embeddedComplexTypeNode[0].set('name', nodeName + 'Type')
                    ComplexTypeNodeParser.__embeddedNodesNamesList.append(nodeName)
                    print 'embbeded node created: ' +  nodeName + 'Type'
                    
                
                embeddedSimpleUnionType = xmlNode_xpath.xpath('./xsd:simpleType/xsd:union', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'})
                if embeddedSimpleUnionType:
                    for embeddedUnion_node in embeddedSimpleUnionType:
                        # handle as basetype
                        #TODO: do element parsing
                        #>>>cppTypdefStringBuilder.addTypedef(element_name + 'Type', embeddedUnion_node.attrib['memberTypes'])
                        print '++Embedded simpleType with union: '   + ', is contained in the element named: ' + nodeName + 'Type'
                    return nodeName, nodeName + 'Type'
                
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

def make_CppTypdefStringBuilder(basetype_map):
    l_cppTypdefStringBuilder = CppTypdefStringBuilder(basetype_map)
    return l_cppTypdefStringBuilder

def make_CppConvertFromCDMClassDeclarationBuilder():
    l_cppConvertFromCDMClassDeclarationBuilder = CppConvertFromCDMClassDeclarationBuilder()
    return l_cppConvertFromCDMClassDeclarationBuilder

def make_CppConvertFromCDMClassDefinitionBuilder(basetype_map):
    l_cppConvertFromCDMClassDefinitionBuilder = CppConvertFromCDMClassDefinitionBuilder(basetype_map)
    return l_cppConvertFromCDMClassDefinitionBuilder

def make_CppConvertToCDMClassDeclarationBuilder():
    l_cppConvertToCDMClassDeclarationBuilder = CppConvertToCDMClassDeclarationBuilder()
    return l_cppConvertToCDMClassDeclarationBuilder

def make_CppConvertToCDMClassDefinitionBuilder():
    l_cppConvertToCDMClassDefinitionBuilder = CppConvertToCDMClassDefinitionBuilder()
    return l_cppConvertToCDMClassDefinitionBuilder

def make_GSLFileBuilder():
    l_gslFileBuilder = GSLFileBuilder()
    return l_gslFileBuilder

def make_MDIBDeclacationsBuilder():
    l_mdibDeclarationsBuilder = MDIBDeclacationsBuilder()
    return l_mdibDeclarationsBuilder



## init
g_simpleTypes_set = set()
g_complexTypes_set = set()
self.__enumClasses_cppCode = ''
enumToStringClassMethods_cppCode = ''
cppTypdefStringBuilder = make_CppTypdefStringBuilder(g_basetype_map)
cppConvertFromCDMClassDeclarationBuilder = make_CppConvertFromCDMClassDeclarationBuilder()
cppConvertFromCDMClassDefinitionBuilder = make_CppConvertFromCDMClassDefinitionBuilder(g_basetype_map)
cppConvertToCDMClassDeclarationBuilder = make_CppConvertToCDMClassDeclarationBuilder()
cppConvertToCDMClassDefinitionBuilder = make_CppConvertToCDMClassDefinitionBuilder()
gslFileBuilder = make_GSLFileBuilder()
mdibDeclacationsBuilder = make_MDIBDeclacationsBuilder()
g_embeddedAttributesNamesList = list()
classBuilderForwarder = ClassBuilderForwarding()


###
### SimpleTypes
###
print '--- simple types ---'
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd') }:
    # search for simple type and go deeper
    # orientation: https://stackoverflow.com/questions/12657043/parse-xml-with-lxml-extract-element-value
    for simpleType_node in tree.xpath('//xsd:simpleType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        enum_flag = False
        # only take nodes that have an attribute
        for attribute_name in simpleType_node.attrib:
            # get the name of the simple type
            simpleTypeName = simpleType_node.attrib[attribute_name] # attribute_name = 'name'
            g_simpleTypes_set.add(simpleTypeName)
            print simpleTypeName
            
            # destinguish between enums and basetypes
            # enums
            for enum_node in simpleType_node.xpath('./xsd:restriction/xsd:enumeration', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                
                enumEntry = enum_node.attrib['value']
                print 'enum-type>>' + enumEntry
                # enum_Flag is False at the beginning of a new enum class -> reset classes
                if not enum_flag:
                    classBuilderForwarder.addEnum(simpleTypeName)

                # flag as enum
                enum_flag = True
                classBuilderForwarder.addEnumEntry(enumEntry)
                
                
            # non enums
            if not enum_flag:
                # basetypes
                for basetype_node in simpleType_node.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'base' in basetype_node.attrib:
                        basetypeType = basetype_node.attrib['base']
                        print 'base-type>>' + basetypeType
                        cppTypdefStringBuilder.addTypedef(simpleTypeName, basetypeType)
                        cppConvertFromCDMClassDeclarationBuilder.addBasetype(simpleTypeName)
                        cppConvertFromCDMClassDefinitionBuilder.addBasetype(simpleTypeName)
                        cppConvertToCDMClassDeclarationBuilder.addBasetype(simpleTypeName)
                        cppConvertToCDMClassDefinitionBuilder.addBasetype(simpleTypeName)
                        
                # item lists
                for itemList_node in simpleType_node.xpath('./xsd:list', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'itemType' in itemList_node.attrib:
                        itemList_name = itemList_node.attrib['itemType']
                        print 'itemList-type>>' + itemList_name
                        cppTypdefStringBuilder.addItemListTypedef(simpleTypeName, itemList_name)
                        cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
                        cppConvertFromCDMClassDefinitionBuilder.addItemList(simpleTypeName)
                        cppConvertToCDMClassDeclarationBuilder.addNonBasetype(simpleTypeName)
                        cppConvertToCDMClassDefinitionBuilder.addItemList(simpleTypeName)
                        
            
            
            # append code for each enum class
            if enum_flag:
                classBuilderForwarder.finalizeEnumClass(simpleTypeName)
                
                

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
        
        complexNodeParser = ComplexTypeNodeParser(g_simpleTypes_set, g_complexTypes_set, g_basetype_map, g_apiInterfaces)        
        complexNodeParser.parseComplexTypeNode(complexType_node)
        
        # TODO: move maybe
        ### non-gsl files
        # add to ConverterClasses
        
        cppConvertFromCDMClassDefinitionBuilder.addComplexType(complexNodeParser.getComplexTypeName(), complexNodeParser.getAbstractBool())
        cppConvertFromCDMClassDeclarationBuilder.addNonBasetype(complexNodeParser.getComplexTypeName())
        cppConvertToCDMClassDefinitionBuilder.addComplexType(complexNodeParser.getComplexTypeName(), complexNodeParser.getAbstractBool())
        # add to mdib-fws
        mdibDeclacationsBuilder.addType(complexNodeParser.getComplexTypeName())
       
         
        # add class to fileBuilderClass
        if complexNodeParser.getGSLClassBuilder():
            gslFileBuilder.addClassAsString(complexNodeParser.getGSLClassBuilder().getGSLClassAsString())
            
            
        print complexNodeParser.getEmbeddedAttributesNamesList()
        

# build SimpleTypesMapping.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.hxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.h', contentBeginning + cppTypdefStringBuilder.getCppTypedefString() + self.__enumClasses_cppCode  + cppEnumToStringClassBuilder.getEnumToStringClassDeclarationAsString() + contentEnding)

#build SimpleTypesMapping.cpp 
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('SimpleTypesMapping_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('SimpleTypesMapping_ending.cxx')
cppFileBuilder.writeToFile('SimpleTypesMapping.cpp', contentBeginning + enumToStringClassMethods_cppCode + contentEnding)

#build ConvertFromCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertFromCDM.h', contentBeginning + cppConvertFromCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + cppConvertFromCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations() + contentEnding)

#build ConvertFromCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertFromCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertFromCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertFromCDMClassDefinitionBuilder.getBaseTypesAsString() + cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertFromCDMClassDefinitionBuilder.getComplexTypeFuctionsAsString() + cppConvertFromCDMClassDefinitionBuilder.getItemListAsString() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + cppConvertToCDMClassDeclarationBuilder.getNonBasetypeCoverterFunctionsDeclarations() + cppConvertToCDMClassDeclarationBuilder.getBasetypeCoverterFunctionsDeclarations() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', cppConvertToCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertToCDMClassDefinitionBuilder.getBasetype() + cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertToCDMClassDefinitionBuilder.getComplexAsString() + cppConvertToCDMClassDefinitionBuilder.getItemListAsString() + contentEnding)


## complex types
#build complexTypesGSLformated.xml
cppFileBuilder = make_FileManager()
cppFileBuilder.writeToFile('complexTypesGSLformated.xml', gslFileBuilder.getContent())

#build mdib-fwd.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('MDIB-fwd_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('MDIB-fwd_ending.hxx')
cppFileBuilder.writeToFile('MDIB-fwd.h', contentBeginning + mdibDeclacationsBuilder.getDeclarationsAsString() + contentEnding)


# ---- Statistics -----
print ' '
print '----- Statistics -----'
print ' '
print 'Basetypes: ' + str(cppTypdefStringBuilder.getBasetypeCounter())
print 'ItemLists: ' + str(cppTypdefStringBuilder.getItemListCounter())
print 'Enums: ' + str(cppEnumToStringClassBuilder.getEnumCounter())
print 'ComplexTypes: ' + str(gslFileBuilder.getNumOfClasses())



