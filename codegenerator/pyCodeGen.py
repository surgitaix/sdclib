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


##
## Setup
##
# mapping of basetypes:xsd -> cpp
basetype_map = {'xsd:unsignedLong' : 'unsigned long', 'pm:VersionCounter' : 'unsigned long', 'xsd:string' : 'std::string', 
                'xsd:decimal' : 'double', 'xsd:unsignedInt' : 'unsigned int', 'xsd:QName' : 'xml_schema::Qname', 'xsd:dateTime' : 'xml_schema::DateTime', 'xsd:boolean' : 'bool', 
                'xsd:duration' : 'xml_schema::Duration', 'xsd:language' : 'xml_schema::Language', 'xsd:anyURI' : 'std::string', 'xsd:int' : 'int' , 'xsd:long' : 'long long', 
                'pm:HandleRef' : 'std::string' }
# apiInterfaces_global structure: 1. Classname, 2. name of typedef 3. type of typedef
# if list consists of more than three values the following entries refer to additional typdefs listed in the same 
# manner; 4. name of typedef, 5. type of typedef ...
apiInterfaces_global = [
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




# typedefs
class CppTypdefStringBuilder(object):
    
    def __init__(self):
        ## init basetype_map for converting xsd-basetypes to cpp-basetypes
        # if a type is unknown the compiler throws a KeyError!
        self.__basetype_map = basetype_map
        self.__itemListCounter = 0
        self.__basetypeCounter = 0
        self.__content = ''
    
    def addTypedef(self, simpleType_name, baseTypeName_xsd):
        self.__content = self.__content + 'typedef ' + self.__basetype_map[baseTypeName_xsd] + ' ' + simpleType_name + ';\n';
        self.__basetypeCounter = self.__basetypeCounter + 1
    
    # item list are always of basetype
    def addItemListTypedef(self, simpleType_name, baseTypeName_xsd):
        self.__content = self.__content + 'typedef std::vector<' + self.__basetype_map[baseTypeName_xsd] + '> ' + simpleType_name + ';\n';
        self.__itemListCounter = self.__itemListCounter + 1
    
    def getCppTypedefString(self):
        return self.__content + '\n\n'
    
    def getItemListCounter(self):
        return self.__itemListCounter
    
    def getBasetypeCounter(self):
        return self.__basetypeCounter
        
# enums
class CppEnumClassBuilder(object):
    
    def __init__(self, simpleType_name):
        self.__content = 'enum class ' + simpleType_name + '\n{\n'
        
    def appendEnumEntry(self, enum_name):
        self.__content = self.__content + '\t' + enum_name + ',\n'
        
    def getEnumClassAsString(self):
        return self.__content[:-2] + '\n};\n\n'
        

    
# EnumToStringClass declarations
# contains enum - counter
class CppEnumToStringClassDeclarationBuilder(object):
    
    def __init__(self):
        self.__content = 'class EnumToString {\npublic:\n'
        self.__enumCounter = 0
        
    def addConvertFunctionDeclarationForSimpleType(self, simpleType_name):
        self.__content = self.__content + '\tstatic std::string convert(' + simpleType_name + ' source);\n'
        self.__enumCounter = self.__enumCounter + 1
    
    def getEnumToStringClassDeclarationAsString(self):
        return self.__content + '};\n\n';

    def getEnumCounter(self):
        return self.__enumCounter
    
    
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
        self.__itemList = ''
        self.__basetype_map = basetype_map
    
    def addComplexType(self, type_name):
        self.__complex = self.__complex + type_name + 'ConvertFromCDM::convert(const CDM::' + type_name +' & source) {\n\treturn ' + type_name + '(source);\n}\n\n'
        self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ type_name + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;
        
    def addItemList(self,simpleType_name):
        self.__itemList = self.__itemList + simpleType_name + ' ConvertFromCDM::convert(const CDM::' + simpleType_name + ' & source) {\n\t' + simpleType_name + ' list;\n' + '\tfor (const auto & element : source) {\n\t\tlist.push_back(element);\n\t}\n\treturn list;\n}\n\n'

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexTypeFuctionsAsString(self):
        return self.__complex
    
    def getItemListAsString(self):
        return self.__itemList
    
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
        self.__itemList = ''
    
    def addComplexType(self, type_name):
        self.__complex = self.__complex + 'template\nstd::unique_ptr<typename ' + type_name + '::WrappedType> ConvertToCDM::convert(const '+ type_name + '&source);\n\n'
        self.__includes = self.__includes + '#include \"OSCLib/Data/OSCP/MDIB/'+ type_name + '.h\"\n'
        
    def addEnumConverterFunctionAsString(self,enumConverterFunction_string):
        self.__enums = self.__enums + enumConverterFunction_string;

    def addItemList(self,simpleType_name):
        self.__itemList = self.__itemList + 'CDM::' + simpleType_name + ' ConvertToCDM::convert(const ' + simpleType_name + ' & source) {\n\tCDM::' + simpleType_name + ' list;\n' + '\tfor (const auto & element : source) {\n\t\tlist.push_back(element);\n\t}\n\treturn list;\n}\n\n'

    def getEnumsAsString(self):
        return self.__enums;
    
    def getIncludesAsString(self):
        return self.__includes
    
    def getComplexAsString(self):
        return self.__complex

    def getItemListAsString(self):
        return self.__itemList

class GSLClassBuilder(object):
    
    def __init__(self, class_name, parent_name, abstract_string):
        # __apiInterfaces is a list of lists corresponding to a class. Each of these lists contains the classes' interfaces to the api. E.g. some 
        # states needs to be accessed by the provider while others do not (e.g. context states do not)
        self.__apiInterfaces = apiInterfaces_global
        self.__includes = ''
        self.__properties = ''
        self.__propertylists = ''
        self.__typedefs = ''
        self.__classdeclaration = '\t<class name = \"' + class_name + '\" parent = \"' + parent_name + '\" abstract = \"' + abstract_string + '\">\n'
        self.checkAndAddAPIInterface(class_name)
        
    def checkAndAddAPIInterface(self, class_name):
        for classInterfaceDescription in self.__apiInterfaces:
            if class_name == classInterfaceDescription[0]:
                for i in range(0,(len(classInterfaceDescription)-1)/2):
                    self.addTypedef(classInterfaceDescription[1+i], classInterfaceDescription[2+i])
        
    def addInclude(self,complexType_name):
        self.__includes = self.__includes + '\t\t<include path = \"OSCLib/Data/OSCP/MDIB/' + complexType_name + '.h\" />\n'
        
    def addProperty(self, property_name, property_type, optionality_string):
        self.__properties = self.__properties + '\t\t<property name = \"' + property_name + '\" type = \"' + property_type + '\" optional = \"' + optionality_string + '\" />\n'
    
    def addPropertyList(self, property_name, property_type):
        # automatically names nameServeral attaching a 's' to property_name
        self.__propertylists = self.__propertylists + '\t\t<propertyList nameSingle = \"' + property_name + '\" nameSeveral = \"' + property_name + 'Lists\" type = \"' + property_type + '\" />\n'
        
    def addTypedef(self, typedef_name, typedef_type):
        self.__typedefs = self.__typedefs + '\t\t<typedef name = \"' + typedef_name + '\" type = \"' + typedef_type + '\" />\n'

    def addXSDAttribute_node(self,attribute_node):
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
                    self.addInclude(attribute_type)
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
                self.addProperty(attribute_name, attribute_type, optionality_string)
                print '>> Attribute -> Property: ' + attribute_name + ', type= ' + attribute_type + ', optional= ' + optionality_string + ', linked to: ' + isLinkedTo

    def getGSLClassAsString(self):
        return self.__classdeclaration + self.__includes + self.__typedefs + self.__properties + self.__propertylists + '\t</class>\n\n' 

    
# contains the gsl descriptions
class GSLFileBuilder(object):
    def __init__(self):
        self.__numOfClasses = 0
        self.__content = '<?xml version="1.0"?>\n<classes script = \"generate.gsl\" >\n'

    def addClassAsString(self, class_string):
        self.__content = self.__content + class_string
        self.__numOfClasses = self.__numOfClasses + 1
        
    def getContent(self):
        return self.__content + '</classes>'
    
    def getNumOfClasses(self):
        return self.__numOfClasses
    
    
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

def make_GSLClassBuilder(class_name, parent_name, abstract_string):
    l_gslClassBuilder = GSLClassBuilder(class_name, parent_name, abstract_string)
    return l_gslClassBuilder

def make_MDIBDeclacationsBuilder():
    l_mdibDeclarationsBuilder = MDIBDeclacationsBuilder()
    return l_mdibDeclarationsBuilder


## init
counter = 0

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
embeddedAttributesNamesList = list()


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
                
                
            # non enums
            if not enum_flag:
                # basetypes
                for basetype_node in simpleType_node.xpath('./xsd:restriction', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'base' in basetype_node.attrib:
                        basetype_name = basetype_node.attrib['base']
                        print 'base-type>>' + basetype_name
                        cppTypdefStringBuilder.addTypedef(simpleType_name, basetype_name)
            
                # item lists
                for itemList_node in simpleType_node.xpath('./xsd:list', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                    if 'itemType' in itemList_node.attrib:
                        itemList_name = itemList_node.attrib['itemType']
                        print 'itemList-type>>' + itemList_name
                        cppTypdefStringBuilder.addItemListTypedef(simpleType_name, itemList_name)
                        cppConvertFromCDMClassDeclarationBuilder.addType(simpleType_name)
                        cppConvertFromCDMClassDefinitionBuilder.addItemList(simpleType_name)
                        cppConvertToCDMClassDeclarationBuilder.addType(simpleType_name)
                        cppConvertToCDMClassDefinitionBuilder.addItemList(simpleType_name)
                        
            
            
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
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd')}:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have an attribute
        for attribute_name in complexType_node.attrib:
            # get name
            complexType_name = complexType_node.attrib[attribute_name]
            complexTypes_set.add(complexType_name)
        
# analyse complex types
for tree in {etree.parse('../datamodel/BICEPS_ParticipantModel.xsd')}:
    for complexType_node in tree.xpath('//xsd:complexType', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
        # only take nodes that have a 'name' attribute
        if 'name' in complexType_node.attrib:
            # get name
            complexType_name = complexType_node.attrib['name']
            
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

            ## depending on the occurence, the datatyp's fields for xsd:elements are defined
            for element_node in complexType_node.xpath('.//xsd:element', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                # check if element is a valid node by checking if attr. name exists
                if 'name' in element_node.attrib:
                    element_name = element_node.attrib['name']
                    if 'type' in element_node.attrib:
                        elem_type_xsd = element_node.attrib['type']
                        # get rid of the namespace prefix
                        elem_type = elem_type_xsd[(elem_type_xsd.index(':')+1):]
                        
                        # check if linked to a complexType -> include is necessarygetEnumCounter
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
                    
                    # check for embedded types in elements with no 'type' attribute
                    else:
                        if element_node.xpath('./xsd:complexType/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                            counter = counter + 1
                            glsEmbeddedClass = make_GSLClassBuilder(element_name, "NULL", 'False')
                            # complex types have allways attributes
                            for embedded_attribute_node in element_node.xpath('./xsd:complexType/xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                                print '++Embedded complexType with attribute: ' + embedded_attribute_node.attrib['name'] + ', is contained in the element named: ' + element_name
                                glsEmbeddedClass.addXSDAttribute_node(embedded_attribute_node)
                                
                                embeddedAttributesNamesList.append(embedded_attribute_node.attrib['name'])
                                # associate element with class name
                                ''
                                #
                                #ä
                                
                            gslFileBuilder.addClassAsString(glsEmbeddedClass.getGSLClassAsString())
                            
                        for embedded_union_node in element_node.xpath('./xsd:simpleType/xsd:union', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                            print '++Embedded simpleType with union'   + ', is contained in the element named: ' + element_name
                    
                    
            # add attributes entries -> attributes are properties
            for attribute_node in complexType_node.xpath('.//xsd:attribute', namespaces={'xsd':'http://www.w3.org/2001/XMLSchema'}):
                # do not consider embedded attributes from this node
                if not attribute_node.attrib['name'] in embeddedAttributesNamesList:
                    glsClassBuilder.addXSDAttribute_node(attribute_node)

            # add class to fileBuilderClass
            gslFileBuilder.addClassAsString(glsClassBuilder.getGSLClassAsString())


print counter
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
cppFileBuilder.writeToFile('ConvertFromCDM.cpp', cppConvertFromCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertFromCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertFromCDMClassDefinitionBuilder.getComplexTypeFuctionsAsString() + cppConvertFromCDMClassDefinitionBuilder.getItemListAsString() + contentEnding)

# build ConvertToCDM.h
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.hxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.hxx')
cppFileBuilder.writeToFile('ConvertToCDM.h', contentBeginning + cppConvertToCDMClassDeclarationBuilder.getCoverterFunctionsDeclarationsAsString() + contentEnding)

#build ConvertToCDM.cpp
cppFileBuilder = make_FileManager()
contentBeginning = cppFileBuilder.readFileToStr('ConvertToCDM_beginning.cxx')
contentEnding = cppFileBuilder.readFileToStr('ConvertToCDM_ending.cxx')
cppFileBuilder.writeToFile('ConvertToCDM.cpp', cppConvertToCDMClassDefinitionBuilder.getIncludesAsString() + contentBeginning + cppConvertToCDMClassDefinitionBuilder.getEnumsAsString() + cppConvertToCDMClassDefinitionBuilder.getComplexAsString() + cppConvertToCDMClassDefinitionBuilder.getItemListAsString() + contentEnding)


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

